#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h> // For sleep()

using namespace std;

struct Frame {
    char data[256];
};

bool WaitForEventReceiver() {
    ifstream file("medium.dat", ios::binary);
    return file.good();
}

Frame ReceiveFrame() {
    Frame frame;
    ifstream inFile("medium.dat", ios::binary);
    if(inFile) {
        inFile.read(reinterpret_cast<char*>(&frame), sizeof(Frame));
        inFile.close();
    }
    return frame;
}

char* ExtractData(Frame frame) {
    static char data[256];
    strncpy(data, frame.data, sizeof(data));
    return data;
}

void DeliverData(char* data) {
    cout << "Received message: " << data << endl;
}

int main() {
    while(true) {
        cout << "Receiver waiting for messages... (Ctrl+C to quit)" << endl;
        if (WaitForEventReceiver()) {
            Frame received_frame = ReceiveFrame();
            char* received_data = ExtractData(received_frame);
            DeliverData(received_data);
            remove("medium.dat");
        }
        sleep(1); // Check every second
    }
    return 0;
}
