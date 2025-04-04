#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>

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

// Simulated timer for timeout detection
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

// Sender in Go-Back-N protocol
class Sender {
private:
    int base;               // Base of the window
    int next_seq_num;       // Next sequence number to use
    std::vector<Frame> window;  // Buffer for frames in the window
    Timer timer;            // Timer for the oldest unacknowledged frame
    Channel* channel;       // Communication channel
    ProtocolMode mode;      // Protocol mode
    
public:
    Sender(Channel* ch, ProtocolMode m) 
        : base(0), next_seq_num(0), channel(ch), mode(m) {
        window.resize(WINDOW_SIZE);
    }
    
    // Send data using Go-Back-N protocol
    void send_data(const std::string& data) {
        // Check if window is full
        if (next_seq_num < base + WINDOW_SIZE) {
            // Create a new frame
            Frame frame(next_seq_num % MAX_SEQ_NUM, 0, false, data);
            
            // Store in window buffer
            window[next_seq_num % WINDOW_SIZE] = frame;
            
            // Start timer if this is the oldest unacknowledged frame
            if (base == next_seq_num) {
                timer.start();
            }
            
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
            // For NACK-based: resend the NACK'd frame and all subsequent frames
            std::cout << "Sender: Received NACK for frame " << ack_frame.ack_num << std::endl;
            
            // Find the position in the window
            int nack_position = ack_frame.ack_num;
            
            // Resend from NACK position
            for (int i = nack_position; i < next_seq_num; i++) {
                std::cout << "Sender: Resending frame " << (i % MAX_SEQ_NUM) << std::endl;
                channel->transmit(window[i % WINDOW_SIZE]);
            }
        } else {
            // Regular ACK processing (common to all modes)
            int ack_num = ack_frame.ack_num;
            std::cout << "Sender: Received ACK for frame " << ack_num << std::endl;
            
            // Cumulative ACK: All frames up to ack_num are acknowledged
            if (is_between(base % MAX_SEQ_NUM, ack_num, next_seq_num % MAX_SEQ_NUM)) {
                // Find the right position in the absolute sequence space
                int ack_position = base;
                while (ack_position % MAX_SEQ_NUM != ack_num) {
                    ack_position++;
                    if (ack_position >= next_seq_num) break;
                }
                
                // Only advance if we're actually moving forward
                if (ack_position >= base) {
                    // Move window base
                    base = ack_position + 1;
                    
                    // Restart timer if there are still unacknowledged frames
                    if (base < next_seq_num) {
                        timer.stop();
                        timer.start();
                    } else {
                        timer.stop();
                    }
                    
                    std::cout << "Sender: Window moved, base = " << base % MAX_SEQ_NUM 
                              << ", next_seq_num = " << next_seq_num % MAX_SEQ_NUM << std::endl;
                }
            }
        }
    }
    
    // Check for timeout and resend if necessary
    void check_timeout() {
        if (timer.is_running() && timer.has_timed_out()) {
            std::cout << "Sender: Timeout occurred, resending frames from " << base % MAX_SEQ_NUM << std::endl;
            
            // Resend all frames in window
            for (int i = 0; i < next_seq_num - base; i++) {
                std::cout << "Sender: Resending frame " << ((base + i) % MAX_SEQ_NUM) << std::endl;
                channel->transmit(window[(base + i) % WINDOW_SIZE]);
            }
            
            // Restart timer
            timer.stop();
            timer.start();
        }
    }
    
    // Helper function to check if a sequence number is in range
    bool is_between(int a, int b, int c) {
        if (((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a))) {
            return true;
        }
        return false;
    }
    
    // Check if all frames have been acknowledged
    bool is_done() {
        return (base == next_seq_num) && (next_seq_num > 0);
    }
    
    // For piggybacked mode: prepare a data frame with ACK
    Frame prepare_piggybacked_frame(const std::string& data, int ack_num) {
        Frame frame(next_seq_num % MAX_SEQ_NUM, ack_num, false, data);
        window[next_seq_num % WINDOW_SIZE] = frame;
        
        if (base == next_seq_num) {
            timer.start();
        }
        
        next_seq_num++;
        return frame;
    }
};

// Receiver in Go-Back-N protocol
class Receiver {
private:
    int expected_seq_num;   // Next expected sequence number
    Channel* channel;       // Communication channel
    ProtocolMode mode;      // Protocol mode
    std::queue<std::string> received_data;  // Buffer for received and ordered data
    
public:
    Receiver(Channel* ch, ProtocolMode m) 
        : expected_seq_num(0), channel(ch), mode(m) {}
    
    // Process received frame
    void receive_frame(const Frame& frame) {
        if (frame.seq_num == expected_seq_num % MAX_SEQ_NUM) {
            // Frame is the one we expected
            std::cout << "Receiver: Received expected frame " << frame.seq_num 
                      << " with data: " << frame.data << std::endl;
            
            // Store data
            if (frame.is_data_frame) {
                received_data.push(frame.data);
            }
            
            // Move expected sequence number
            expected_seq_num++;
            
            // Send acknowledgment based on the protocol mode
            send_acknowledgment();
        } else {
            // Frame is not what we expected
            std::cout << "Receiver: Received unexpected frame " << frame.seq_num 
                      << ", expected " << expected_seq_num % MAX_SEQ_NUM << std::endl;
            
            if (mode == NACK_BASED) {
                // Send NACK for the expected frame
                Frame nack_frame(0, expected_seq_num % MAX_SEQ_NUM, true, "", false);
                std::cout << "Receiver: Sending NACK for frame " << nack_frame.ack_num << std::endl;
                channel->transmit(nack_frame);
            } else {
                // For Non-NACK and Piggybacked modes, we just send the last ACK again
                send_acknowledgment();
            }
        }
    }
    
    // Send acknowledgment based on protocol mode
    void send_acknowledgment() {
        Frame ack_frame;
        
        if (mode == PIGGYBACKED) {
            // For piggybacked mode, we wait for data to send with the ACK
            // This is a simplified implementation - in reality, would buffer ACKs
            // until data is available to piggyback
            ack_frame = Frame(0, (expected_seq_num - 1) % MAX_SEQ_NUM, false, "ACK-Data", true);
        } else {
            // For NON_NACK and NACK_BASED modes
            ack_frame = Frame(0, (expected_seq_num - 1) % MAX_SEQ_NUM, false, "", false);
        }
        
        std::cout << "Receiver: Sending ACK for frame " << ack_frame.ack_num << std::endl;
        channel->transmit(ack_frame);
    }
    
    // Get received data
    std::string get_next_data() {
        if (received_data.empty()) {
            return "";
        }
        std::string data = received_data.front();
        received_data.pop();
        return data;
    }
    
    // For piggybacked mode: send data with acknowledgment
    void send_piggybacked_data(const std::string& data) {
        Frame frame(0, (expected_seq_num - 1) % MAX_SEQ_NUM, false, data, true);
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
        
        // Add more exchanges here...
        
        std::cout << "Bidirectional piggybacked communication simulation completed." << std::endl;
    }
};

// Main function to demonstrate the different modes
int main() {
    // Seed random number generator
    srand(time(NULL));
    
    // Test case 1: Non-NACK based
    {
        std::cout << "\n===== NON-NACK BASED PROTOCOL DEMO =====\n" << std::endl;
        
        Channel channel;
        Sender sender(&channel, NON_NACK);
        Receiver receiver(&channel, NON_NACK);
        
        // Send a few frames
        sender.send_data("Frame 0 data");
        sender.send_data("Frame 1 data");
        sender.send_data("Frame 2 data");
        
        // Simulate receipt and ACK of frame 0
        Frame received_frame0(0, 0, false, "Frame 0 data");
        receiver.receive_frame(received_frame0);
        
        // Simulate ACK received by sender
        Frame ack_frame0(0, 0, false, "", false);
        sender.receive_ack(ack_frame0);
        
        // Simulate loss of frame 1
        // (Not explicitly shown - the receiver won't get this frame)
        
        // Check for timeout
        sender.check_timeout();
        
        // Simulate receipt of retransmitted frame 1
        Frame received_frame1(1, 0, false, "Frame 1 data");
        receiver.receive_frame(received_frame1);
        
        // Simulate ACK received by sender
        Frame ack_frame1(0, 1, false, "", false);
        sender.receive_ack(ack_frame1);
        
        std::cout << "\nNon-NACK based protocol demo completed.\n" << std::endl;
    }
    
    // Test case 2: NACK based
    {
        std::cout << "\n===== NACK-BASED PROTOCOL DEMO =====\n" << std::endl;
        
        Channel channel;
        Sender sender(&channel, NACK_BASED);
        Receiver receiver(&channel, NACK_BASED);
        
        // Send a few frames
        sender.send_data("Frame 0 data");
        sender.send_data("Frame 1 data");
        sender.send_data("Frame 2 data");
        
        // Simulate receipt and ACK of frame 0
        Frame received_frame0(0, 0, false, "Frame 0 data");
        receiver.receive_frame(received_frame0);
        
        // Simulate ACK received by sender
        Frame ack_frame0(0, 0, false, "", false);
        sender.receive_ack(ack_frame0);
        
        // Simulate receipt of frame 2 (out of order, frame 1 lost)
        Frame received_frame2(2, 0, false, "Frame 2 data");
        receiver.receive_frame(received_frame2);
        
        // Simulate NACK received by sender
        Frame nack_frame1(0, 1, true, "", false);
        sender.receive_ack(nack_frame1);
        
        // Simulate receipt of retransmitted frame 1
        Frame received_frame1(1, 0, false, "Frame 1 data");
        receiver.receive_frame(received_frame1);
        
        std::cout << "\nNACK-based protocol demo completed.\n" << std::endl;
    }
    
    // Test case 3: Piggybacked
    {
        std::cout << "\n===== PIGGYBACKED PROTOCOL DEMO =====\n" << std::endl;
        
        BiDirectionalCommunication bidir;
        bidir.simulate();
    }
    
    return 0;
}
