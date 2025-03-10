class EvenOddQ2 {
    // Shared object to synchronize
    private static final Object lock = new Object();

    // Counter to track the current number to be printed
    private static int counter = 1;

    // Even thread class
    static class EvenThread extends Thread {
        public void run() {
            // Print even numbers 2, 4, 6, 8
            for (int i = 2; i <= 8; i += 2) {
                synchronized (lock) {
                    // Wait for the counter to be odd to print even number
                    while (counter % 2 != 0) {
                        try {
                            lock.wait();  // Wait if it's not the turn for even
                        } catch (InterruptedException e) {
                            Thread.currentThread().interrupt();
                        }
                    }
                    System.out.print(i + " ");
                    counter++;  // Increment counter for the next number
                    lock.notify();  // Notify the odd thread to print
                }
            }
        }
    }

    // Odd thread class
    static class OddThread extends Thread {
        public void run() {
            // Print odd numbers 1, 3, 5, 7
            for (int i = 1; i <= 7; i += 2) {
                synchronized (lock) {
                    // Wait for the counter to be even to print odd number
                    while (counter % 2 == 0) {
                        try {
                            lock.wait();  // Wait if it's not the turn for odd
                        } catch (InterruptedException e) {
                            Thread.currentThread().interrupt();
                        }
                    }
                    System.out.print(i + " ");
                    counter++;  // Increment counter for the next number
                    lock.notify();  // Notify the even thread to print
                }
            }
        }
    }

    public static void main(String[] args) {
        // Create and start the even and odd threads
        Thread evenThread = new EvenThread();
        Thread oddThread = new OddThread();
       
        evenThread.start();
        oddThread.start();
       
        try {
            // Wait for both threads to finish
            evenThread.join();
            oddThread.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

