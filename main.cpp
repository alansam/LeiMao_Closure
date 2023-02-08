//  This is free and unencumbered software
//  released into the public domain.
//  @see  LICENSE.md
//  @see  https://unlicense.org

//  @see:  https://leimao.github.io/blog/CPP-Closure/

#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <cmath>

int mainix(void);

std::function<void(void)> closureWrapper1() {
  int x = 10;
  return [x]() {
    std::cout << "Value in the closure: "
              << x
              << std::endl;
  };
}

std::function<void(void)> closureWrapper2() {
  int x = 10;
  return [&x]() {
    x += 1;
    std::cout << "Value in the closure: "
              << x
              << std::endl;
  };
}

static
double constexpr pi { M_PI };

class CircleArea {
public:
  CircleArea() = default;
  double operator() (double r) const {
    return pi * r * r;
  }
};

int main(int argc, char const * argv[]) {
  std::cout << std::string(40, '=') << std::endl;
  int x = 10;
  auto func0 = [&x]() {
    x += 1;
    std::cout << "Value in the closure: "
              << x
              << std::endl;
  };

  std::function<void(void)> func1 = closureWrapper1();
  std::function<void(void)> func2 = closureWrapper2();

  func0();
  func0();
  func0();

  std::cout << std::string(25, '-') << std::endl;

  func1();
  func1();
  func1();

  std::cout << std::string(25, '-') << std::endl;

  func2();
  func2();
  func2();

  std::cout.put('\n');

  std::cout << std::string(40, '=') << std::endl;
  std::cout << "FAQ 1\n";

  double r { 1.0 };
  CircleArea circleArea;
  double area = circleArea(r);
  std::cout << std::fixed << area << std::endl;

  std::cout.put('\n');

  std::cout << std::string(40, '=') << std::endl;

  mainix();

  return 0;
}

int mainix() {
#define CXPR_
#ifdef CXPR_
  constexpr
#endif
  double pix { M_PI };

  class CircleAreaX {
  public:
    CircleAreaX() = default;
    double operator() (double r) const {
      return pix * r * r;
    }
  };

  double rx = 1.0;
  CircleAreaX circleArea;
  double area = circleArea(rx);
  std::cout << area << std::endl;

  return 0;
}
