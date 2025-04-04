Q1. Implement the Simplest Protocol in C/C++ for sender-site DLL and receiver-site DLL
with the following the following elementary functionalities:
WaitForEvent(), GetData(), MakeFrame(), SendFrame(), ReceiveFrame(),
ExtractData(), DeliverData(

### **The Big Picture**
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
