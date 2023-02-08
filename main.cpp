//  This is free and unencumbered software
//  released into the public domain.
//  @see  LICENSE.md
//  @see  https://unlicense.org

//  @see:  https://leimao.github.io/blog/CPP-Closure/
//  @see:  https://leimao.github.io/blog/CPP-Lambda-Expression/

#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <cmath>

void lambdaix(void);
void lambda2(void);

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
  lambdaix();
  std::cout.put('\n');

  std::cout << std::string(40, '=') << std::endl;
  lambda2();
  std::cout.put('\n');

  return 0;
}

void lambdaix() {
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

  return;
}

void lambda2() {
  double rate = 0.01;
  
  // Capture by reference
  auto f0 = [&rate]() {
    rate *= 2;
  };

  // Capture variables in the function body by reference by default
  auto f1 = [&]() {
    rate *= 2;
  };

  // Capture by const value
  auto f2 = [rate](double x) {
    return (1 + rate) * x;
  };

  // Specify return type
  auto f3 = [rate](double x) -> double {
    return (1 + rate) * x;
  };
  auto f4 = [rate](double x) -> int {
    return (1 + rate) * x;
  };

  // Compile time polymorphism
  // C++14 features
  auto f5 = [](auto x) {
    return 2 * x;
  };
  auto f6 = []<typename T>(T x) {
    return 2 * x;
  };
  auto f7 = []<typename T>(T x) -> T {
    return 2 * x;
  };

  // Capture by mutable value
  // This causes error because rate is immutable
  // auto f8 = [rate](double x){rate += 1.0;};
  // Rate is now mutable
  // But the mutation would not change the value outside the lambda expression scope
  auto f8 = [rate]() mutable {
    rate += 1.0; return rate;
  };

  f0();
  std::cout << rate << std::endl;
  f1();
  std::cout << rate << std::endl;
  std::cout << "f2: " << f2(10) << std::endl;
  std::cout << "f3: " << f3(10) << std::endl;
  std::cout << "f4: " << f4(10) << std::endl;
  std::cout << "f5: " << f5(15) << std::endl;
  std::cout << "f6: " << f6(16) << std::endl;
  std::cout << "f7: " << f7(17) << std::endl;
  std::cout << "f8: " << f8() << std::endl;
  std::cout << rate << std::endl;

  return;
}
