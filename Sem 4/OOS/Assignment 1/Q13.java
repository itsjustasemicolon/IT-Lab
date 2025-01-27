class Automobile{
  String make;
  String type;
  double maxSpeed;
  double price;
  double mileage;
  String registrationNumber;

  public Automobile(String mk, String t, double ms, double p, double m, String rn){
    make=mk;
    type=t;
    maxSpeed=ms;
    price=p;
    mileage=m;
    registrationNumber=rn;
  }

  public void displayInfo() {
        System.out.println("Make: " + make);
        System.out.println("Type: " + type);
        System.out.println("Max Speed: " + maxSpeed + " km/h");
        System.out.println("Price: Rs." + price);
        System.out.println("Mileage: " + mileage + " km/l");
        System.out.println("Registration Number: " + registrationNumber);
    }
}

class Truck extends Automobile {
    int capacity;
    String hoodType;
    int noOfWheels;

    public Truck(String make, String type, int maxSpeed, double price, double mileage, String registrationNumber, int capacity, String hoodType, int noOfWheels) {
        super(make, type, maxSpeed, price, mileage, registrationNumber);
        this.capacity = capacity;
        this.hoodType = hoodType;
        this.noOfWheels = noOfWheels;
    }

    public void displayInfo() {
        super.displayInfo();
        System.out.println("Capacity: " + capacity + " tons");
        System.out.println("Hood Type: " + hoodType);
        System.out.println("Number of Wheels: " + noOfWheels);
    }
}

class Car extends Automobile {
    int noOfDoors;
    int seatingCapacity;

    public Car(String make, String type, int maxSpeed, double price, double mileage, String registrationNumber, int noOfDoors, int seatingCapacity) {
        super(make, type, maxSpeed, price, mileage, registrationNumber);
        this.noOfDoors = noOfDoors;
        this.seatingCapacity = seatingCapacity;
    }

    public void displayInfo() {
        super.displayInfo();
        System.out.println("Number of Doors: " + noOfDoors);
        System.out.println("Seating Capacity: " + seatingCapacity);
    }
}

public class Q13 {
    static void dispInfo(Automobile a)
    {
        a.displayInfo();
    }
    public static void main(String[] args) {
        Automobile truck = new Truck("Ashok Leyland", "Cargo Truck", 80, 4999999.99, 5, "WB02G3124", 10, "Covered", 6);
        Automobile car = new Car("Mahindra", "BE6E", 180, 1999999.99, 15, "WB26AS9032", 4, 5);

        System.out.println("Truck Details:");
        dispInfo(truck);
        System.out.println();
        
        System.out.println("Car Details:");
        dispInfo(car);
    }
}
