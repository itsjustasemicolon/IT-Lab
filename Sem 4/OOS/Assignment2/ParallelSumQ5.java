public class ParallelSumQ5 {

    static class SeriesCalculator implements Runnable {
        private int start;
        private int end;
        private int sum;

        SeriesCalculator(int start, int end) {
            this.start = start;
            this.end = end;
        }
        
        public void run() {
            sum = 0;
            for (int i = start; i <= end; i += 2) {
                sum += i;
            }
        }

        public int getSum() {
            return sum;
        }
    }

    public static void main(String[] args) throws InterruptedException {
        SeriesCalculator oddSeries = new SeriesCalculator(1, 99);  // Odd numbers 1-99
        SeriesCalculator evenSeries = new SeriesCalculator(2, 100); // Even numbers 2-100

        Thread oddThread = new Thread(oddSeries);
        Thread evenThread = new Thread(evenSeries);

        oddThread.start();
        evenThread.start();

        // Wait for both threads to complete
        oddThread.join();
        evenThread.join();

        int totalSum = oddSeries.getSum() + evenSeries.getSum();
        System.out.println("Final sum: " + totalSum);
    }
}
