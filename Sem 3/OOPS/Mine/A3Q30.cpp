class A{
public:
  A(){cout<<"A constructor";}
};

class B{
public:
  B(){cout<<"B constructor";}
};

class C{
public:
  C(){cout<<"C constructor";}
};

class D:public A, public B {
public:
  D(){cout<<"D constructor";}
};

class E:public B, public C {
public:
  E(){cout<<"E constructor";}
};

class F:public D, public E {
public:
  F(){cout<<"F constructor";}
};

int main()
{ return 0;}
