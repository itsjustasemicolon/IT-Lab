import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;

class SharedBuffer {
    private Queue<Integer> buffer = new LinkedList<>();
    private final int CAPACITY = 5;
    private boolean isProducerDone = false;

    synchronized void produce(int number) {
        while (buffer.size() == CAPACITY) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        buffer.offer(number);
        System.out.println("Produced: " + number);
        notify();
    }

    synchronized Integer consume() {
        while (buffer.isEmpty()) {
            if (isProducerDone) {
                return null;
            }
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return null;
            }
        }
        Integer number = buffer.poll();
        System.out.println("Consumed: " + number);
        notify();
        return number;
    }

    synchronized void setProducerDone() {
        isProducerDone = true;
        notifyAll();
    }
}

class Producer extends Thread {
    private SharedBuffer buffer;
    private String filename;

    Producer(SharedBuffer buffer, String filename) {
        this.buffer = buffer;
        this.filename = filename;
    }

    public void run() {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                int number = Integer.parseInt(line.trim());
                buffer.produce(number);
            }
            buffer.setProducerDone();
        } catch (IOException | NumberFormatException e) {
            System.out.println("Error reading file: " + e.getMessage());
            buffer.setProducerDone();
        }
    }
}

class Consumer extends Thread {
    private SharedBuffer buffer;
    private int sum = 0;

    Consumer(SharedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        while (true) {
            Integer number = buffer.consume();
            if (number == null) {
                break;
            }
            sum += number;
        }
        System.out.println("Final sum: " + sum);
    }

    public int getSum() {
        return sum;
    }
}

 class FileProcessing {
    public static void main(String[] args) {
        SharedBuffer buffer = new SharedBuffer();
        Producer producer = new Producer(buffer, "numbers.txt");
        Consumer consumer = new Consumer(buffer);

        producer.start();
        consumer.start();

        try {
            producer.join();
            consumer.join();
            System.out.println("Processing complete");
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted");
        }
    }
}
