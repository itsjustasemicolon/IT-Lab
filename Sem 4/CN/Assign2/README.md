### **Q1. Implement the Simplest Protocol in C/C++ for sender-site DLL and receiver-site DLL with the following the following elementary functionalities: WaitForEvent(), GetData(), MakeFrame(), SendFrame(), ReceiveFrame(), ExtractData(), DeliverData()**

**The Big Picture**
Imagine you have two computers: **Sender Sam** and **Receiver Rita**. They want to chat, but they can't talk directly. Instead, they pass notes (messages) through a shared desk drawer (**medium.dat** file). Here's how it works:

---

### **1. Sender Sam (sender.cpp)**
**Sam's Job:** *Write notes and put them in the drawer.*

1. **"What's your message?"**  
   - Sam asks you to type a message (using `GetData()`).  
   - You type anything: "Hey Rita! Pizza tonight?" 🍕

2. **Putting it in an envelope**  
   - Sam stuffs your message into a digital envelope called a **Frame** (`MakeFrame()`).  
   - This envelope has a max size (255 characters) so you can't write a novel.

3. **Dropping it in the drawer**  
   - Sam saves this envelope to a file named **medium.dat** (`SendFrame()`).  
   - Think of this like putting the note in a shared drawer between their desks.

---

### **2. Receiver Rita (receiver.cpp)**
**Rita's Job:** *Check the drawer for notes and read them.*

1. **"Is there a note?"**  
   - Rita checks the drawer (**medium.dat**) every second (`WaitForEventReceiver()`).  
   - She’s very patient and keeps checking forever (the `while(true)` loop).

2. **"Got one!"**  
   - When she finds a note, she opens the envelope (`ReceiveFrame()`).  
   - She carefully copies the message out of the frame (`ExtractData()`).

3. **"Look what Sam sent!"**  
   - Rita shows you the message on her screen (`DeliverData()`).  
   - Then she throws away the envelope (`remove("medium.dat")`) so it doesn’t pile up.

---

### **Key Details (For Nerdy Stuff Lovers)**
- **The Drawer (medium.dat):**  
  This file acts like a shared space. Sam writes to it, Rita reads from it. It’s temporary storage.

- **Timing:**  
  Rita checks the drawer every second. If Sam sends 5 notes in a row *too fast*, Rita might only see the last one because each new note overwrites the file.

- **Safety First:**  
  The code limits messages to 255 characters to prevent overflow (like using a ruler to keep notes from being too long).

- **Binary Mode:**  
  The envelope (Frame) is saved as raw data (0s and 1s) so it doesn’t get messed up during storage.

---

### **How to Use It (IRL)**
1. **Run Rita first** (she’s the listener):  
   ```bash
   ./receiver
   ```

2. **Then run Sam whenever you want to send a message:**  
   ```bash
   ./sender
   ```

3. **Type your message** when Sam asks, and watch Rita display it!

---

### **Why This Matters**
This is a simplified version of how *real* networking works! When you send a text message or email, devices use similar principles (just with way more security and error-checking). You’re basically building a tiny internet! 🌐

Let me know if you want to dive deeper into any part! 😊


### **Q2. Implement Stop-n-wait protocol in C/C++ by considering: a. Channel is noiseless b. Channel is noisy (hint: introduce probability of damaging/losing the frame in transit)**

Absolutely! Let's break down this code like we're explaining how two friends send text messages with read receipts, but with some "tech magic" to make it reliable. 📱✨

---

### **The Big Picture**
Imagine **Sam** (Sender) and **Riley** (Receiver) texting each other:
- Sam sends a message
- Waits for Riley's "👍" (ACK)
- Only sends the next message after getting the 👍
- If no 👍 comes, Sam resends the message

---

### **Key Components**
1. **The Text Message (Frame)** 📨
   - `seq_num`: A label (0 or 1) to track messages
   - `data`: The actual message ("Packet 0", "Packet 1", etc.)
   - `checksum`: A secret code to verify if the message was messed up

2. **The Read Receipt (Ack)** ✅
   - `ack_num`: Matches the message label (0/1)
   - `checksum`: Verification code for the receipt itself

---

### **How It Works**
**1. Sending a Message (Sam's Side)**  
```cpp
snprintf(frame.data, sizeof(frame.data), "Packet %d", frame_count);
```
- Sam writes a message like "Packet 0"
- Adds a label (0) and calculates a secret code (checksum)
- Sends it through "cell service" (simulated with random chances)

**2. Cell Service Simulator** 📶  
- **Good service (Noiseless):** Perfect delivery
- **Bad service (Noisy):**  
  - 30% chance message gets lost  
  - 20% chance message gets garbled (like "Pakcet 0")  
  - 30% chance read receipt gets lost

**3. Receiving (Riley's Side)**  
- Checks secret code (checksum) to see if message is intact  
- If good: Sends back matching 👍 (ACK 0/1)  
- If bad/corrupted: Ignores it  

**4. Retry System** 🔄  
- Sam waits 3 seconds for 👍  
- If no 👍: Resends (max 3 tries)  
- After 3 fails: Gives up (error message)  

---

### **Real-Life Example**
1. Sam sends: "Packet 0 [checksum: 1234]" (Label 0)  
2. Bad service corrupts it to "Pakcet 0 [checksum: 1234]"  
3. Riley detects mismatch (real checksum ≠ 1234) → Ignores  
4. Sam resends → This time it arrives clean  
5. Riley sends back "👍 0"  
6. Sam now sends "Packet 1" (Label 1)  

---

### **Why This Matters**
1. **No Duplicates:** Labels (0/1) prevent Riley from accepting the same message twice  
   - If Sam resends "Packet 0" but Riley already processed it, Riley knows to ignore it  
2. **Error Detection:** Checksums catch corrupted messages  
3. **Reliability:** Even with bad service (30% loss!), messages eventually get through  

---

### **How to Run It**
1. **Choose Channel Type**  
   - **1 (Noiseless):** Perfect texting  
   - **2 (Noisy):** Like texting with spotty service  

2. **Watch the Conversation**  
   - See messages get lost/corrupted  
   - Watch Sam retry until success  

---

### **Life Comparison**
Think of it like:
- Sam: "Did you get my last text?"  
- Riley: *Only replies if message was clear*  
- If Riley doesn't reply, Sam texts again after a while  
- Labels (0/1) prevent confusion like:  
  "Wait, is this about the pizza or the movie?"  

---

This code is a simplified version of how *real* networks (like WiFi/cellular) ensure your messages/photos arrive intact, even when the connection isn't perfect! 🌐🔒




### Q3 Implement Go-back-n based sliding window protocol in C/C++ by considering the followings: a. DLL communications are Non-NACK based b. DLL communications are NACK based c. DLL communications are Piggybacked based (i.e.. bi-directional communication)
### Go-Back-N Protocol Explained

Imagine you're sending a bunch of text messages to your friend, but sometimes the messages get lost. How would you make sure all your messages arrive? That's what this code solves!

## The Basic Idea

The Go-Back-N protocol is like having numbered messages with receipts:

1. You send multiple messages at once (let's say messages 0, 1, 2, 3)
2. Your friend confirms when they get each message ("Got message 0!")
3. If a message gets lost, you resend that message and all the ones after it

## Three Ways It Works in This Code

### 1. Non-NACK Based (Just Confirmations)
- You send messages 0, 1, 2, 3
- Your friend confirms each message they receive
- If you don't get confirmation after waiting a while, you assume something got lost and resend everything

### 2. NACK-Based (With Rejection Notices)
- Same as above, but if your friend gets message 2 before message 1, they can immediately tell you "Hey, I'm missing message 1!"
- Then you can quickly resend message 1 without waiting

### 3. Piggybacked (Two-Way Conversation)
- Both you and your friend are sending messages to each other
- Instead of sending separate confirmation messages, you just attach confirmations to your regular messages
- Like saying "Got your message 3! By the way, here's my message 5..."

## Main Parts of the Code

- `Frame`: This is just a message with a number and some data
- `Sender`: This sends messages and keeps track of which ones got confirmed
- `Receiver`: This receives messages and sends confirmations
- `Channel`: This simulates the connection between sender and receiver, including random message loss
- `Timer`: This helps the sender know when to resend messages if confirmations don't come back

## How It Works Step by Step

1. The sender maintains a "window" of messages (let's say 4 messages) it can send without waiting for confirmations
2. As confirmations come in, the window slides forward allowing new messages to be sent
3. If confirmations don't come back in time (timeout) or the receiver reports a missing message (NACK), the sender resends messages
4. The receiver only accepts messages in the correct order and sends confirmations

The `main()` function shows examples of how each method works, including what happens when messages get lost.

This is basically how reliable communication works on the internet - making sure all your data gets where it's going, even when parts of it get lost along the way!


### Q4. Write a program in C/C++ with suitable functions to implement Selective-repeat based sliding window protocol by considering the followings: a. DLL communications are Non-NACK based b. DLL communications are NACK based c. DLL communications are Piggybacked based

### Selective-Repeat Protocol Explained Simply

I've created a program that shows how the Selective-Repeat sliding window protocol works. Unlike Go-Back-N (which resends all unacknowledged frames when there's an error), Selective-Repeat only resends the specific frames that were lost or corrupted. This makes it more efficient.

## The Key Differences from Go-Back-N

1. **Individual Timers**: Each frame has its own timer instead of one timer for the oldest unacknowledged frame
2. **Buffering**: The receiver can accept frames out of order and buffer them
3. **Selective Resending**: Only lost frames are resent, not the entire window

## The Three Communication Types

### 1. Non-NACK Based
- Receiver sends positive acknowledgments (ACKs) for frames it receives correctly
- Sender relies on timeouts to detect lost frames
- When a timeout occurs, only the specific lost frame is resent

### 2. NACK Based
- Receiver sends both ACKs and NACKs (Negative ACKs)
- When it receives a frame out of order, it immediately sends a NACK for the missing frame
- This allows faster recovery than waiting for a timeout

### 3. Piggybacked
- Both sides are sending data to each other
- Acknowledgments are attached to data frames going in the opposite direction
- Saves bandwidth by combining data and control information

## How the Program Works

The code includes these key components:

- `Frame` struct: Represents a message with sequence numbers and data
- `Sender` class: Manages sending frames and tracking which ones are acknowledged
- `Receiver` class: Receives frames, buffers out-of-order ones, and delivers in-order data
- `Channel` class: Simulates a connection with random errors
- `Timer` class: Individual timers for each frame

The `main()` function demonstrates all three communication types with examples of frame loss and recovery.

## How It Differs from Go-Back-N

In the Go-Back-N implementation, when a frame is lost, the sender resends all frames from the lost one to the end of the window. In Selective-Repeat, only the specific lost frame is resent, making it more efficient when multiple frames might be lost.

Additionally, the receiver in Selective-Repeat can accept and buffer out-of-order frames, while Go-Back-N simply discards them.

### Q5. Suppose there is a provision to let the sender know about the condition of the receiver’s buffer (i.e., buffer size is 1 or 2m-1) by using a framing bit along with ACK. Write an optimized sliding window protocol in C/C++ to improve performance of the DLL communication systems

Here's a detailed explanation of how the optimized sliding window protocol works in this code:

### **Key Components**
1. **Packet Structure**:
   ```cpp
   struct Packet {
       int seq_num;    // Sequence number for ordering
       string data;    // Payload data
   };
   ```
2. **ACK Structure**:
   ```cpp
   struct Ack {
       int ack_num;      // Cumulative ACK number
       bool framing_bit; // Buffer status (0=spacious, 1=congested)
   };
   ```

---

### **Core Mechanism**
The protocol implements a **dynamic sliding window** that adapts based on receiver's buffer status:

1. **Sender Workflow**:
   - Maintains a send window (cwnd) that can switch between:
     - **Conservative mode (cwnd=1)** when receiver buffer is nearly full
     - **Aggressive mode (cwnd=2m-1)** when receiver has space
   - Uses three key sequence numbers:
     - `send_base`: First unacknowledged packet
     - `next_seq_num`: Next packet to send
     - `max_seq`: Maximum sequence number (2^m - 1)

2. **Receiver Workflow**:
   - Buffer size = 2m-1 packets
   - Uses framing bit to indicate buffer status:
     - **0**: Buffer has >1 free space (can handle window size 2m-1)
     - **1**: Buffer has ≤1 free space (needs window size 1)

---

### **Key Operations**

**1. Packet Transmission**:
```cpp
void Sender::send_packets() {
    while (next_seq_num < (send_base + cwnd) % (max_seq + 1) && 
          !send_queue.empty()) {
        // Create and send packet
        Packet pkt = send_queue.front();
        pkt.seq_num = next_seq_num;
        in_flight.push_back(pkt);
        // Update sequence numbers with modulo wrap
        next_seq_num = (next_seq_num + 1) % (max_seq + 1);
    }
}
```
- Operates within current window size (cwnd)
- Uses modulo arithmetic for sequence number wrapping

**2. ACK Processing**:
```cpp
void Sender::receive_ack(Ack ack) {
    // Update window size based on framing bit
    cwnd = ack.framing_bit ? 1 : (2*m - 1);
    
    // Remove acknowledged packets
    list<Packet>::iterator it = in_flight.begin();
    while (it != in_flight.end() && it->seq_num < ack.ack_num) {
        it = in_flight.erase(it);
    }
}
```
- Uses cumulative ACKs (ack_num indicates next expected packet)
- Dynamically adjusts window size using framing bit

**3. Buffer Management (Receiver)**:
```cpp
Ack Receiver::process_packet(Packet pkt) {
    // Only accept in-order packets with buffer space
    if (pkt.seq_num == expected_seq_num && buffer.size() < buffer_size) {
        buffer.push(pkt);
        expected_seq_num = (expected_seq_num + 1) % (max_seq + 1);
    }
    
    // Set framing bit based on buffer status
    ack.framing_bit = (buffer_size - buffer.size()) <= 1;
}
```
- Maintains packet ordering
- Calculates available buffer space for framing bit

---

### **Sequence Diagram**
```
Sender                            Receiver
  |------- Packet (seq=0) --------->| 
  |                                 | Processes packet
  |<------- ACK(1, framing=0) ------|
  | (Window expands to 2m-1)        |
  |--- Packets (seq=1,2,3,4,5,6) -->|
  |                                 | Buffer fills up
  |<------- ACK(7, framing=1) ------|
  | (Window shrinks to 1)           |
  |------- Packet (seq=7) --------->|
```

---

### **Key Features**
1. **Adaptive Congestion Control**:
   - Automatically reduces transmission rate when receiver buffer fills
   - Quickly maximizes throughput when buffer space is available

2. **Efficient Buffer Utilization**:
   - Receiver buffer size = maximum window size (2m-1)
   - Maintains 1 packet buffer margin for flow control

3. **Cumulative Acknowledgments**:
   - ACK numbers indicate next expected sequence
   - Automatically acknowledges all previous packets

4. **Sequence Number Management**:
   - Uses modulo arithmetic (2^m) for sequence numbers
   - Handles wrap-around correctly

---

### **Simulation Flow (main())**
1. Initialize sender/receiver with m=3 (8 sequence numbers)
2. Load sample data into sender
3. Simulation loop:
   - Receiver processes its buffer (emulates application consumption)
   - Sender transmits packets within current window
   - Receiver generates ACKs with framing bit
   - Sender adjusts window size based on ACKs

---

### **Performance Optimization**
- **Rapid Adaptation**: Immediate window size changes based on receiver feedback
- **Prevent Overflow**: Framing bit triggers window reduction before buffer overflows
- **Full Bandwidth Utilization**: Maximizes window size (2m-1) when possible

This implementation provides a foundation that can be extended with:
- Retransmission mechanisms for lost packets
- Error detection using checksums
- Actual network communication layers
- Threading for concurrent processing
- More sophisticated congestion control algorithms
