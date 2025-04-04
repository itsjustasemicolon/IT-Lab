// COMPILE WITH: g++ -std=c++11 stop_wait.cpp -o stop_wait
#include <cstdio>   
#include <string>  
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

// Frame structure with sequence number and checksum
struct Frame {
    int seq_num;    // 0 or 1 (1-bit sequence number)
    char data[256];
    int checksum;
};

// Acknowledgement structure
struct Ack {
    int ack_num;    // 0 or 1
    int checksum;
};

// Calculate simple checksum for error detection
int calculate_checksum(const char* data) {
    int sum = 0;
    for (int i = 0; data[i] != '\0'; i++) {
        sum += static_cast<int>(data[i]);
    }
    return sum;
}

// Simulate frame transmission with loss/corruption probabilities
bool transmit_frame(Frame &frame, float loss_prob, float corrupt_prob) {
    // Check for frame loss
    if (static_cast<float>(rand()) / RAND_MAX < loss_prob) {
        return false;
    }
    
    // Simulate corruption
    if (static_cast<float>(rand()) / RAND_MAX < corrupt_prob) {
        frame.checksum += rand() % 100 + 1; // Introduce random error
    }
    
    return true;
}

// Simulate ACK transmission with loss probability
bool transmit_ack(Ack &ack, float loss_prob) {
    return (static_cast<float>(rand()) / RAND_MAX >= loss_prob);
}

// Sender function implementing Stop-and-Wait protocol
void sender(int total_frames, float frame_loss, float frame_corrupt, float ack_loss) {
    int next_seq = 0;
    int frame_count = 0;
    
    while (frame_count < total_frames) {
        Frame frame;
        frame.seq_num = next_seq;
        snprintf(frame.data, sizeof(frame.data), "Packet %d", frame_count);
        frame.checksum = calculate_checksum(frame.data);
        
        bool ack_received = false;
        int attempts = 0;
        
        while (!ack_received && attempts < 3) { // Maximum 3 attempts
            cout << "\nSender: Transmitting frame " << frame_count 
                 << " [SEQ: " << next_seq << "]" << endl;
            
            Frame frame_copy = frame;
            bool frame_delivered = transmit_frame(frame_copy, frame_loss, frame_corrupt);
            
            if (!frame_delivered) {
                cout << "Sender: Frame lost in transmission!" << endl;
                attempts++;
                continue;
            }
            
            // Simulate receiver processing
            bool frame_valid = (frame_copy.checksum == calculate_checksum(frame_copy.data));
            
            if (frame_valid) {
                cout << "Receiver: Frame " << frame_copy.seq_num 
                     << " received successfully!" << endl;
                
                // Generate ACK
                Ack ack;
                ack.ack_num = frame_copy.seq_num;
                ack.checksum = calculate_checksum(to_string(ack.ack_num).c_str());
                
                // Transmit ACK
                if (transmit_ack(ack, ack_loss)) {
                    if (ack.ack_num == next_seq) {
                        cout << "Sender: Valid ACK " << ack.ack_num << " received!" << endl;
                        ack_received = true;
                        next_seq = 1 - next_seq; // Toggle sequence number
                        frame_count++;
                    } else {
                        cout << "Sender: Received out-of-order ACK" << endl;
                    }
                } else {
                    cout << "Sender: ACK lost!" << endl;
                }
            } else {
                cout << "Receiver: Corrupted frame detected!" << endl;
            }
            
            attempts++;
            if (!ack_received) {
                cout << "Sender: Timeout, resending..." << endl;
            }
        }
        
        if (attempts >= 3) {
            cerr << "Sender: Maximum retries exceeded for frame " << frame_count << endl;
            break;
        }
    }
}

int main() {
    srand(time(NULL));
    
    cout << "Choose channel type:\n";
    cout << "1. Noiseless\n2. Noisy\n";
    int choice;
    cin >> choice;
    
    float frame_loss = 0.0;
    float frame_corrupt = 0.0;
    float ack_loss = 0.0;
    
    if (choice == 2) {
        frame_loss = 0.3;    // 30% frame loss probability
        frame_corrupt = 0.2; // 20% corruption probability
        ack_loss = 0.3;      // 30% ACK loss probability
    }
    
    cout << "\nStarting simulation...\n";
    sender(5, frame_loss, frame_corrupt, ack_loss);
    
    return 0;
}
