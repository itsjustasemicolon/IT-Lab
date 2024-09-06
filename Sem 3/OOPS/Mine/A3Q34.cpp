    double getVolume() const override {
        return (4.0 / 3) * M_PI * pow(radius, 3);
    }
};

class Cube : public ThreeDShape {
private:
    double side;

public:
    Cube(double s) : side(s) {}

    string getName() const override {
        return "Cube";
    }

    double getArea() const override {
        return 6 * side * side;
    }

    double getVolume() const override {
        return pow(side, 3);
    }
};

int main() {

    vector<Shape*> shapes;

    shapes.push_back(new Circle(3.0));
    shapes.push_back(new Triangle(3.0, 4.0));
    shapes.push_back(new Ellipse(5.0, 2.0));
    shapes.push_back(new Sphere(4.0));
    shapes.push_back(new Cube(2.0));

    for (Shape* shape : shapes) {
        cout << "Shape: " << shape->getName() << endl;
        cout << "Area: " << shape->getArea() << endl;


        ThreeDShape* threeDShape = dynamic_cast<ThreeDShape*>(shape);
        if (threeDShape) {
            cout << "Volume: " << threeDShape->getVolume() << endl;
        }

        cout << "--------------------------" << endl;
    }

    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}
