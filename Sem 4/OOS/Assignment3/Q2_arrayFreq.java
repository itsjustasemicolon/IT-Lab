import java.util.HashMap;
import java.util.Map;

public class Q2_arrayFreq {
    public static <T> Map<T, Integer> findFrequency(T[] array) {
        Map<T, Integer> freqMap = new HashMap<>();
        for (T item : array) {
            if (freqMap.containsKey(item)) {
                freqMap.put(item, freqMap.get(item) + 1);
            } else {
                freqMap.put(item, 1);
            }
        }
        return freqMap;
    }
    
    public static void main(String[] args) {
        // Example with Integer array
        Integer[] intArray = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
        Map<Integer, Integer> intFrequency = findFrequency(intArray);
        System.out.println("Frequency of integers:");
        for (Map.Entry<Integer, Integer> entry : intFrequency.entrySet()) {
            System.out.println(entry.getKey() + ": " + entry.getValue());
        }
        
        // Example with String array
        String[] stringArray = {"apple", "banana", "apple", "orange", "banana", "apple"};
        Map<String, Integer> stringFrequency = findFrequency(stringArray);
        System.out.println("\nFrequency of strings:");
        for (Map.Entry<String, Integer> entry : stringFrequency.entrySet()) {
            System.out.println(entry.getKey() + ": " + entry.getValue());
        }
    }
}
