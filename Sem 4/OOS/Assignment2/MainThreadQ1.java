//Q1

public class MainThread {
    public static void main(String[] args) {
        ChildThread childThread = new ChildThread();
        childThread.start();
        System.out.println("In main thread");
    }
}

class ChildThread extends Thread {
    public void run() {
        System.out.println("In child thread");
    }
}
