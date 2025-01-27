interface Shape
{
    void area();
    void draw();
    void rotate();
    void move();
}

class Circle implements Shape
{
    float radius;
    int n;
    Circle(float r,int n)
	{
        radius=r;
        this.n=n;
	}

	public void area()
    {
        System.out.println("Area of circle "+n+": "+ (3.14*radius*radius));
    }    

    public void draw()
    {
        System.out.println("Circle: draw");

    }

    public void rotate()
    {
        System.out.println("Circle: rotate");
    }

    public void move()
    {
        System.out.println("Circle: move");
    }

	void getDetails()
	{
		area();
		draw();
		rotate();
		move();
	}
}

class Rectangle implements Shape
{       
    float len,bre;
    int n;
	Rectangle(float l, float b,int n)
	{
		len=l;
        bre=b;
        this.n=n;
	}

    public void area()
    {
        System.out.println("Area of rectangle "+n+" : "+ (len*bre));
    }

    public void draw()
    {
        System.out.println("Rectangle: draw");
    }

    public void rotate()
    {
        System.out.println("Rectangle: rotate");
    }

    public void move()
    {
        System.out.println("Rectangle: move");
    }

	void getDetails()
	{
		area();
		draw();
		rotate();
		move();
	}
}

class Q14
{
	public static void main(String args[])
	{
		Circle c1 = new Circle(4.3f,1);
		c1.getDetails();

		Circle c2 = new Circle(6.6f,2);
		c2.getDetails();

		Rectangle r1 = new Rectangle(3.7f,4.5f,1);
		r1.getDetails();

		Rectangle r2 = new Rectangle(2.3f,3.1f,2);
		r2.getDetails();

		Rectangle r3 = new Rectangle(1.5f,2.5f,3);
		r3.getDetails();
	}
}
