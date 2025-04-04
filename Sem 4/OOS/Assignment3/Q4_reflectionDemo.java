import java.lang.reflect.*;

public class Q4_reflectionDemo {
    
    private int privateField;
    public String publicField;
    
    public Q4_reflectionDemo() {}
    
    public Q4_reflectionDemo(int value) {
        this.privateField = value;
    }
    
    private void privateMethod() {
        System.out.println("Private method called");
    }
    
    public void publicMethod(String message) {
        System.out.println("Public method called with: " + message);
    }
    
    public static void main(String[] args) throws Exception {
        // Create an instance for reflection
        Q4_reflectionDemo demo = new Q4_reflectionDemo(42);
        
        // 1. getClass() - Get the Class object
        Class<?> clazz = demo.getClass();
        System.out.println("Class name: " + clazz.getName());
        
        // 2. getMethods() - Get all public methods (including inherited ones)
        System.out.println("\nMethods:");
        Method[] methods = clazz.getMethods();
        for (Method method : methods) {
            System.out.println(method.getName());
        }
        
        // 3. getDeclaredMethods() - Get all methods declared in this class (public & private)
        System.out.println("\nDeclared Methods:");
        Method[] declaredMethods = clazz.getDeclaredMethods();
        for (Method method : declaredMethods) {
            System.out.println(method.getName());
        }
        
        // 4. getConstructors() - Get all public constructors
        System.out.println("\nConstructors:");
        Constructor<?>[] constructors = clazz.getConstructors();
        for (Constructor<?> constructor : constructors) {
            System.out.println(constructor);
        }
        
        // 5. getDeclaredMethod() - Get and invoke a private method
        System.out.println("\nAccessing private method:");
        Method privateMethod = clazz.getDeclaredMethod("privateMethod");
        privateMethod.setAccessible(true); // Allow access
        privateMethod.invoke(demo);
        
        // 6. getDeclaredField() - Get a private field
        System.out.println("\nAccessing private field:");
        Field privateField = clazz.getDeclaredField("privateField");
        privateField.setAccessible(true);
        System.out.println("Original value: " + privateField.getInt(demo));
        
        // Modify the private field value
        privateField.setInt(demo, 100);
        System.out.println("Modified value: " + privateField.getInt(demo));

        // 7. Accessing and modifying public field
        System.out.println("\nAccessing public field:");
        Field publicField = clazz.getField("publicField");
        publicField.set(demo, "Reflection in Java");
        System.out.println("Public field value: " + publicField.get(demo));

        // 8. Invoking a public method dynamically
        System.out.println("\nInvoking public method:");
        Method publicMethod = clazz.getMethod("publicMethod", String.class);
        publicMethod.invoke(demo, "Hello via Reflection!");
    }
}
