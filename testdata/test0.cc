struct data
{
  int x;
  double y;
};

void foo();
int foo(int);

class Base
{
 public:
  virtual ~Base()
  {
  }

  virtual void process(data* d) = 0;
};

class Derived : public Base
{
 public:
  void process(data* d) override
  {
    d->y = 19 * 82.0;
  }
};

int main()
{
  foo();
  data d;
  d.x = 1;

  Derived p;
  p.process(&d);

  Base* pb = &p;
  pb->process(&d);

  auto x = foo(123);
}
