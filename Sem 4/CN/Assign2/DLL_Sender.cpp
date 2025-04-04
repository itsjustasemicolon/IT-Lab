#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Frame {
    char data[256];
};

bool WaitForEventSender() {
    return true; // Always ready to send
}

char* GetData() {
    static char data[256];
    cout << "Enter message to send (max 255 chars): ";
    cin.getline(data, sizeof(data));
    return data;
}

Frame MakeFrame(char* data) {
    Frame frame;
    strncpy(frame.data, data, sizeof(frame.data) - 1);
    frame.data[sizeof(frame.data) - 1] = '\0'; // Ensure null-termination
    return frame;
}

void SendFrame(Frame frame) {
    ofstream outFile("medium.dat", ios::binary);
    outFile.write(reinterpret_cast<char*>(&frame), sizeof(Frame));
    outFile.close();
}

int main() {
    if (WaitForEventSender()) {
        char* data = GetData();
        Frame frame = MakeFrame(data);
        SendFrame(frame);
        cout << "Sender transmitted: " << data << endl;
    }
    return 0;
}
