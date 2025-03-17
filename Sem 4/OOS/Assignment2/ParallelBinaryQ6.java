public class ParallelBinaryQ6 {
    public static int result = -1;
    public static boolean found = false;

    public static void main(String[] args) {
        int[] arr = new int[100];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = i * 2;  
        }

        int target = 42;  
        int numThreads = arr.length / 10;
        Thread[] threads = new Thread[numThreads];

        for (int i = 0; i < numThreads; i++) {
            int start = i * 10;
            int end = start + 10;
            threads[i] = new Thread(new SearchTask(arr, target, start, end));
            threads[i].start();
        }

        for (Thread t : threads) {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        if (result != -1) {
            System.out.println("Element " + target + " found at index: " + result);
        } else {
            System.out.println("Element " + target + " not found.");
        }
    }

    static class SearchTask implements Runnable {
        int[] arr;
        int target;
        int start, end;

        public SearchTask(int[] arr, int target, int start, int end) {
            this.arr = arr;
            this.target = target;
            this.start = start;
            this.end = end;
        }

        public void run() {
            int low = start;
            int high = end - 1;
            while (low <= high && !found) { 
                int mid = low + (high - low) / 2;
                if (arr[mid] == target) {
                    result = mid;  
                    found = true;  
                    break;
                } else if (arr[mid] < target) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
    }
}
