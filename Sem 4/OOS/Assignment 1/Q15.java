import java.util.*;
class Tollbooth
{
	int totalCarsPassed;
	int carsNotPaid;
	int tollCollected;

	Tollbooth()
	{
		totalCarsPassed = 0;
	  carsNotPaid = 0;
		tollCollected = 0;
	}

	void getData()
	{
        while(true)
        {
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter the total number of cars passed : ");
            totalCarsPassed = sc.nextInt();
            System.out.println("Enter the number of cars that did not pay the toll : ");
            carsNotPaid = sc.nextInt();
            if(carsNotPaid > totalCarsPassed)
            {
                System.out.println("Cars passed without paying toll must be less than the total number of cars passed!");
            }
            else
            break;
        }
	}
 	
	void calculateToll()
	{
		tollCollected = 50*(totalCarsPassed-carsNotPaid);
	}					

	void printDetails()
	{
		
		System.out.println("Cars passed without paying : "+carsNotPaid);
   		System.out.println("Cars passed : "+totalCarsPassed);
   		System.out.println("Toll per Car : 50");
		System.out.println("Total cash collected : "+tollCollected);
		
	}
}

class Main
{
	public static void main(String args[])
	{
		Tollbooth obj = new Tollbooth();
		obj.getData();
		obj.calculateToll();
		obj.printDetails();					
	}
}
