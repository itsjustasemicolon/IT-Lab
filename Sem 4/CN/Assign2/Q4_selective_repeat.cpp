#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <algorithm>

// Constants for the protocol
const int WINDOW_SIZE = 4;       // Sliding window size
const int MAX_SEQ_NUM = 8;       // Maximum sequence number (0-7)
const int TIMEOUT_MS = 500;      // Timeout in milliseconds
const float ERROR_RATE = 0.2;    // Probability of packet error/loss

// Protocol modes
enum ProtocolMode {
    NON_NACK,       // a. Non-NACK based (only ACKs)
    NACK_BASED,     // b. NACK based (both ACKs and NACKs)
    PIGGYBACKED     // c. Piggybacked (bidirectional with data+ACK)
};

// Frame structure
struct Frame {
    int seq_num;            // Sequence number
    int ack_num;            // Acknowledgment number
    bool is_nack;           // Is this a NACK? (for NACK_BASED mode)
    std::string data;       // Data payload
    bool is_data_frame;     // Is this a data frame or just ACK/NACK?
    
    Frame(int seq = 0, int ack = 0, bool nack = false, std::string d = "", bool is_data = true)
        : seq_num(seq), ack_num(ack), is_nack(nack), data(d), is_data_frame(is_data) {}
};

// Individual timer for each frame
class Timer {
private:
    bool running;
    clock_t start_time;
    int duration_ms;
    
public:
    Timer() : running(false), start_time(0), duration_ms(TIMEOUT_MS) {}
    
    void start() {
        running = true;
        start_time = clock();
    }
    
    void stop() {
        running = false;
    }
    
    bool has_timed_out() {
        if (!running) return false;
        clock_t current = clock();
        return (current - start_time) * 1000 / CLOCKS_PER_SEC > duration_ms;
    }
    
    bool is_running() {
        return running;
    }
};

// Simulated channel with error probability
class Channel {
public:
    bool transmit(Frame& frame) {
        // Simulate random packet loss/error
        if ((float)rand() / RAND_MAX < ERROR_RATE) {
            std::cout << "Channel: Frame " << frame.seq_num << " lost or corrupted" << std::endl;
            return false;
        }
        return true;
    }
};

// Sender in Selective-Repeat protocol
class Sender {
private:
    int base;                       // Base of the window
    int next_seq_num;               // Next sequence number to use
    std::vector<Frame> window;      // Buffer for frames in the window
    std::vector<Timer> timers;      // Individual timer for each frame
    std::vector<bool> acked;        // Track which frames are acknowledged
    Channel* channel;               // Communication channel
    ProtocolMode mode;              // Protocol mode
    
public:
    Sender(Channel* ch, ProtocolMode m) 
        : base(0), next_seq_num(0), channel(ch), mode(m) {
        window.resize(WINDOW_SIZE);
        timers.resize(WINDOW_SIZE);
        acked.resize(WINDOW_SIZE, false);
    }
    
    // Send data using Selective-Repeat protocol
    void send_data(const std::string& data) {
        // Check if window is full
        if (next_seq_num < base + WINDOW_SIZE) {
            // Create a new frame
            Frame frame(next_seq_num % MAX_SEQ_NUM, 0, false, data);
            
            // Store in window buffer
            int window_index = next_seq_num % WINDOW_SIZE;
            window[window_index] = frame;
            acked[window_index] = false;
            
            // Start timer for this specific frame
            timers[window_index].start();
            
            // Send the frame
            std::cout << "Sender: Sending frame " << frame.seq_num << " with data: " << frame.data << std::endl;
            channel->transmit(frame);
            
            // Increment next_seq_num
            next_seq_num++;
        } else {
            std::cout << "Sender: Window full, waiting for ACKs" << std::endl;
        }
    }
    
    // Process acknowledgment
    void receive_ack(const Frame& ack_frame) {
        if (mode == NACK_BASED && ack_frame.is_nack) {
            // For NACK-based: resend the NACK'd frame only
            std::cout << "Sender: Received NACK for frame " << ack_frame.ack_num << std::endl;
            
            // Calculate the absolute sequence number of the NACK'd frame
            int nack_seq = ack_frame.ack_num;
            int base_cycle = base / MAX_SEQ_NUM;
            int nack_abs_seq = nack_seq + base_cycle * MAX_SEQ_NUM;
            
            // Adjust if the NACK is for a frame in the next cycle
            if (nack_seq < base % MAX_SEQ_NUM && nack_abs_seq < base) {
                nack_abs_seq += MAX_SEQ_NUM;
            }
            
            // Check if the NACK'd frame is within our current window
            if (nack_abs_seq >= base && nack_abs_seq < base + WINDOW_SIZE) {
                int window_index = nack_abs_seq % WINDOW_SIZE;
                
                // Resend the NACK'd frame
                std::cout << "Sender: Resending frame " << window[window_index].seq_num << std::endl;
                channel->transmit(window[window_index]);
                
                // Restart timer for this frame
                timers[window_index].stop();
                timers[window_index].start();
            }
        } else {
            // Regular ACK processing
            int ack_num = ack_frame.ack_num;
            std::cout << "Sender: Received ACK for frame " << ack_num << std::endl;
            
            // Calculate the absolute sequence number of the ACK'd frame
            int base_cycle = base / MAX_SEQ_NUM;
            int ack_abs_seq = ack_num + base_cycle * MAX_SEQ_NUM;
            
            // Adjust if the ACK is for a frame in the next cycle
            if (ack_num < base % MAX_SEQ_NUM && ack_abs_seq < base) {
                ack_abs_seq += MAX_SEQ_NUM;
            }
            
            // Check if the ACK is within our current window
            if (ack_abs_seq >= base && ack_abs_seq < next_seq_num) {
                int window_index = ack_abs_seq % WINDOW_SIZE;
                
                // Mark this frame as acknowledged
                acked[window_index] = true;
                
                // Stop the timer for this frame
                timers[window_index].stop();
                
                // If this is the base, move the window forward
                if (ack_abs_seq == base) {
                    // Find how far we can slide the window
                    int old_base = base;
                    while (base < next_seq_num && acked[base % WINDOW_SIZE]) {
                        base++;
                    }
                    
                    std::cout << "Sender: Window moved, base = " << base % MAX_SEQ_NUM << std::endl;
                }
            }
        }
    }
    
    // Check for timeouts and resend if necessary
    void check_timeouts() {
        for (int i = 0; i < WINDOW_SIZE; i++) {
            int seq_num = base + i;
            if (seq_num < next_seq_num) {  // Only check frames that have been sent
                int window_index = seq_num % WINDOW_SIZE;
                
                if (!acked[window_index] && timers[window_index].has_timed_out()) {
                    std::cout << "Sender: Timeout for frame " << window[window_index].seq_num 
                              << ", resending" << std::endl;
                    
                    // Resend just this frame
                    channel->transmit(window[window_index]);
                    
                    // Restart timer
                    timers[window_index].stop();
                    timers[window_index].start();
                }
            }
        }
    }
    
    // Check if all frames have been acknowledged
    bool is_done() {
        return (base == next_seq_num) && (next_seq_num > 0);
    }
    
    // For piggybacked mode: prepare a data frame with ACK
    Frame prepare_piggybacked_frame(const std::string& data, int ack_num) {
        if (next_seq_num < base + WINDOW_SIZE) {
            Frame frame(next_seq_num % MAX_SEQ_NUM, ack_num, false, data);
            
            int window_index = next_seq_num % WINDOW_SIZE;
            window[window_index] = frame;
            acked[window_index] = false;
            timers[window_index].start();
            
            next_seq_num++;
            return frame;
        } else {
            // Window is full, return an ACK-only frame
            return Frame(0, ack_num, false, "", false);
        }
    }
};

// Receiver in Selective-Repeat protocol
class Receiver {
private:
    int rcv_base;                   // Base of receiver window
    std::vector<bool> received;     // Track which frames are received
    std::vector<Frame> buffer;      // Buffer for out-of-order frames
    Channel* channel;               // Communication channel
    ProtocolMode mode;              // Protocol mode
    std::queue<std::string> received_data;  // Buffer for received and ordered data
    
public:
    Receiver(Channel* ch, ProtocolMode m) 
        : rcv_base(0), channel(ch), mode(m) {
        received.resize(WINDOW_SIZE, false);
        buffer.resize(WINDOW_SIZE);
    }
    
    // Process received frame
    void receive_frame(const Frame& frame) {
        int seq_num = frame.seq_num;
        
        // Calculate position in the window
        int base_cycle = rcv_base / MAX_SEQ_NUM;
        int seq_abs = seq_num + base_cycle * MAX_SEQ_NUM;
        
        // Adjust if the frame is from the next cycle
        if (seq_num < rcv_base % MAX_SEQ_NUM && seq_abs < rcv_base) {
            seq_abs += MAX_SEQ_NUM;
        }
        
        // Check if the frame is within the receiver window
        if (seq_abs >= rcv_base && seq_abs < rcv_base + WINDOW_SIZE) {
            std::cout << "Receiver: Received frame " << seq_num 
                      << " with data: " << frame.data << std::endl;
            
            // Buffer the frame and mark as received
            int buffer_index = seq_abs % WINDOW_SIZE;
            buffer[buffer_index] = frame;
            received[buffer_index] = true;
            
            // Send ACK or NACK based on protocol mode
            if (mode == NACK_BASED) {
                // For NACK based, send ACK for the received frame
                Frame ack_frame(0, seq_num, false, "", false);
                std::cout << "Receiver: Sending ACK for frame " << ack_frame.ack_num << std::endl;
                channel->transmit(ack_frame);
                
                // If this is not the expected frame, send NACK for the expected one
                if (seq_abs != rcv_base) {
                    Frame nack_frame(0, rcv_base % MAX_SEQ_NUM, true, "", false);
                    std::cout << "Receiver: Sending NACK for expected frame " << nack_frame.ack_num << std::endl;
                    channel->transmit(nack_frame);
                }
            } else {
                // For NON_NACK and PIGGYBACKED modes, send ACK
                send_acknowledgment(seq_num);
            }
            
            // Deliver frames in order
            deliver_frames();
        } else if (seq_abs < rcv_base) {
            // This is a duplicate frame that we've already processed
            std::cout << "Receiver: Received duplicate frame " << seq_num << std::endl;
            
            // Send ACK for this frame (even though we already delivered it)
            send_acknowledgment(seq_num);
        } else {
            // Frame is outside the window
            std::cout << "Receiver: Received frame " << seq_num 
                      << " outside window, ignoring" << std::endl;
        }
    }
    
    // Deliver frames in order to the upper layer
    void deliver_frames() {
        while (received[rcv_base % WINDOW_SIZE]) {
            int index = rcv_base % WINDOW_SIZE;
            
            // Deliver the data
            std::cout << "Receiver: Delivering frame " << buffer[index].seq_num 
                      << " with data: " << buffer[index].data << std::endl;
            received_data.push(buffer[index].data);
            
            // Mark as no longer received and advance window
            received[index] = false;
            rcv_base++;
        }
    }
    
    // Send acknowledgment based on protocol mode
    void send_acknowledgment(int seq_num) {
        Frame ack_frame;
        
        if (mode == PIGGYBACKED) {
            // For piggybacked mode, we might want to include data
            // This is a simplified implementation
            ack_frame = Frame(0, seq_num, false, "ACK-Data", true);
        } else {
            // For NON_NACK and NACK_BASED modes
            ack_frame = Frame(0, seq_num, false, "", false);
        }
        
        std::cout << "Receiver: Sending ACK for frame " << ack_frame.ack_num << std::endl;
        channel->transmit(ack_frame);
    }
    
    // Get next available data
    std::string get_next_data() {
        if (received_data.empty()) {
            return "";
        }
        std::string data = received_data.front();
        received_data.pop();
        return data;
    }
    
    // For piggybacked mode: send data with acknowledgment
    void send_piggybacked_data(const std::string& data, int ack_num) {
        Frame frame(0, ack_num, false, data, true);
        std::cout << "Receiver: Sending piggybacked data with ACK " << frame.ack_num << std::endl;
        channel->transmit(frame);
    }
};

// Bidirectional communication for piggybacked mode
class BiDirectionalCommunication {
private:
    Sender* sender1;
    Receiver* receiver1;
    Sender* sender2;
    Receiver* receiver2;
    Channel* channel;
    
public:
    BiDirectionalCommunication() {
        channel = new Channel();
        sender1 = new Sender(channel, PIGGYBACKED);
        receiver1 = new Receiver(channel, PIGGYBACKED);
        sender2 = new Sender(channel, PIGGYBACKED);
        receiver2 = new Receiver(channel, PIGGYBACKED);
    }
    
    ~BiDirectionalCommunication() {
        delete sender1;
        delete receiver1;
        delete sender2;
        delete receiver2;
        delete channel;
    }
    
    void simulate() {
        std::cout << "Starting bidirectional piggybacked communication simulation..." << std::endl;
        
        // Simulate a few exchanges
        // Node 1 sends data
        Frame frame1 = sender1->prepare_piggybacked_frame("Data from node 1", 0);
        if (channel->transmit(frame1)) {
            receiver2->receive_frame(frame1);
        }
        
        // Node 2 sends data + ACK
        Frame frame2 = sender2->prepare_piggybacked_frame("Data from node 2", frame1.seq_num);
        if (channel->transmit(frame2)) {
            receiver1->receive_frame(frame2);
            sender1->receive_ack(frame2);
        }
        
        // Send more data from Node 1
        Frame frame3 = sender1->prepare_piggybacked_frame("More data from node 1", frame2.seq_num);
        if (channel->transmit(frame3)) {
            receiver2->receive_frame(frame3);
        }
        
        // Simulate frame loss
        Frame frame4 = sender2->prepare_piggybacked_frame("This will be lost", frame3.seq_num);
        // Intentionally not transmitting this frame
        
        // Send another frame after the lost one
        Frame frame5 = sender2->prepare_piggybacked_frame("Data after lost frame", 0);
        if (channel->transmit(frame5)) {
            receiver1->receive_frame(frame5);
        }
        
        // Check for timeouts
        sender2->check_timeouts();
        
        std::cout << "Bidirectional piggybacked communication simulation completed." << std::endl;
    }
};

// Main function to demonstrate the different modes
int main() {
    // Seed random number generator
    srand(time(NULL));
    
    // Test case 1: Non-NACK based Selective-Repeat
    {
        std::cout << "\n===== NON-NACK BASED SELECTIVE-REPEAT PROTOCOL DEMO =====\n" << std::endl;
        
        Channel channel;
        Sender sender(&channel, NON_NACK);
        Receiver receiver(&channel, NON_NACK);
        
        // Send a few frames
        sender.send_data("Frame 0 data");
        sender.send_data("Frame 1 data");
        sender.send_data("Frame 2 data");
        sender.send_data("Frame 3 data");
        
        // Simulate receipt and ACK of frames 0, 2, 3 (frame 1 lost)
        Frame received_frame0(0, 0, false, "Frame 0 data");
        receiver.receive_frame(received_frame0);
        
        // Frame 1 is "lost"
        
        Frame received_frame2(2, 0, false, "Frame 2 data");
        receiver.receive_frame(received_frame2);
        
        Frame received_frame3(3, 0, false, "Frame 3 data");
        receiver.receive_frame(received_frame3);
        
        // Simulate ACKs received by sender
        Frame ack_frame0(0, 0, false, "", false);
        sender.receive_ack(ack_frame0);
        
        Frame ack_frame2(0, 2, false, "", false);
        sender.receive_ack(ack_frame2);
        
        Frame ack_frame3(0, 3, false, "", false);
        sender.receive_ack(ack_frame3);
        
        // Check for timeout on frame 1
        sender.check_timeouts();
        
        // Simulate receipt of retransmitted frame 1
        Frame received_frame1(1, 0, false, "Frame 1 data");
        receiver.receive_frame(received_frame1);
        
        // Simulate ACK received by sender
        Frame ack_frame1(0, 1, false, "", false);
        sender.receive_ack(ack_frame1);
        
        std::cout << "\nNon-NACK based Selective-Repeat protocol demo completed.\n" << std::endl;
    }
    
    // Test case 2: NACK based Selective-Repeat
    {
        std::cout << "\n===== NACK-BASED SELECTIVE-REPEAT PROTOCOL DEMO =====\n" << std::endl;
        
        Channel channel;
        Sender sender(&channel, NACK_BASED);
        Receiver receiver(&channel, NACK_BASED);
        
        // Send a few frames
        sender.send_data("Frame 0 data");
        sender.send_data("Frame 1 data");
        sender.send_data("Frame 2 data");
        sender.send_data("Frame 3 data");
        
        // Simulate receipt and ACK of frame 0
        Frame received_frame0(0, 0, false, "Frame 0 data");
        receiver.receive_frame(received_frame0);
        
        // Frame 1 is "lost"
        
        // Simulate receipt of frame 2 (out of order)
        Frame received_frame2(2, 0, false, "Frame 2 data");
        receiver.receive_frame(received_frame2);
        
        // Simulate ACK for frame 0 and NACK for frame 1 received by sender
        Frame ack_frame0(0, 0, false, "", false);
        sender.receive_ack(ack_frame0);
        
        Frame nack_frame1(0, 1, true, "", false);
        sender.receive_ack(nack_frame1);
        
        // Simulate receipt of retransmitted frame 1
        Frame received_frame1(1, 0, false, "Frame 1 data");
        receiver.receive_frame(received_frame1);
        
        // Now receive frame 3
        Frame received_frame3(3, 0, false, "Frame 3 data");
        receiver.receive_frame(received_frame3);
        
        std::cout << "\nNACK-based Selective-Repeat protocol demo completed.\n" << std::endl;
    }
    
    // Test case 3: Piggybacked Selective-Repeat
    {
        std::cout << "\n===== PIGGYBACKED SELECTIVE-REPEAT PROTOCOL DEMO =====\n" << std::endl;
        
        BiDirectionalCommunication bidir;
        bidir.simulate();
    }
    
    return 0;
}
