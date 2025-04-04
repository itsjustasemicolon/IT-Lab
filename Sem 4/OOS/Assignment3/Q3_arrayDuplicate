import java.util.ArrayList;
import java.util.List;

public class Q3_arrayDuplicate<T> {
    public <E> void printDuplicates(E[] array) {
        List<E> seenElements = new ArrayList<>();
        List<E> duplicates = new ArrayList<>();

        for (E element : array) {
            if (seenElements.contains(element)) {
                continue;
            }

            int count = 0;
            for (E e : array) {
                if (element == null ? e == null : element.equals(e)) {
                    count++;
                }
            }

            if (count > 1) {
                duplicates.add(element);
            }
            seenElements.add(element);
        }

        System.out.println("Duplicate elements:");
        for (E dup : duplicates) {
            System.out.println(dup);
        }
    }

    public static void main(String[] args) {
        q3_arrayDuplicate<Object> dup = new q3_arrayDuplicate<>();

        // Example with String array
        String[] stringArray = { "apple", "banana", "apple", "orange", "banana", "kiwi" };
        System.out.println("Checking duplicates in stringArray:");
        dup.printDuplicates(stringArray);

        // Example with Integer array
        Integer[] intArray = { 1, 2, 3, 2, 4, 3, 5, 6, 7, 8, 7 };
        System.out.println("\nChecking duplicates in intArray:");
        dup.printDuplicates(intArray);
    }
}
