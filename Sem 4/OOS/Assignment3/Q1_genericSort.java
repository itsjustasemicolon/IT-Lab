public class Q1_genericSort {

    public static <T extends Comparable<T>> T[] sortArray(T[] array) {
        int n = array.length;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (array[j].compareTo(array[j + 1]) > 0) {
                    T temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
        return array;
    }

    public static void main(String[] args) {
        // Example 1: Sorting an array of Integers
        Integer[] intArray = { 5, 3, 8, 1, 9, 2 };
        System.out.println("Original Integer array:");
        for (Integer num : intArray) {
            System.out.print(num + " ");
        }
        System.out.println();

        sortArray(intArray);

        System.out.println("Sorted Integer array:");
        for (Integer num : intArray) {
            System.out.print(num + " ");
        }
        System.out.println();

        // Example 2: Sorting an array of Strings
        String[] stringArray = { "banana", "apple", "cherry", "date" };
        System.out.println("\nOriginal String array:");
        for (String s : stringArray) {
            System.out.print(s + " ");
        }
        System.out.println();

        sortArray(stringArray);

        System.out.println("Sorted String array:");
        for (String s : stringArray) {
            System.out.print(s + " ");
        }
        System.out.println();
    }
}
