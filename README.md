# C++ Closure

## Introduction

In C++, [lambda expression](https://leimao.github.io/blog/CPP-Lambda-Expression/)
constructs a closure, an unnamed function object 
capable of capturing variables in scope. It still 
sounds ambiguous, at least to me. Closure is a 
general concept in programming that originated from 
functional programming. When we talk about the 
closures in C++, they always come with lambda 
expressions.

In this blog post, we would take a look at an example 
for C++ lambda expression and closure, learn the 
difference between lambda expression and closure, and 
understand theconcepts.

## Lambda Expression VS Closure

The difference between the concepts of lambda 
expression and closure is sometimes confusing, since 
lambda expression and closure were talked about 
together all the time.

[Scott Meyers](http://scottmeyers.blogspot.com/2013/05/lambdas-vs-closures.html)
got a good explanation to this using analogues.
“The distinction between a lambda and the 
corresponding closure is precisely equivalent to the 
distinction between a class and an instance of the 
class. A class exists only in source code; it 
doesn’t exist at runtime. What exists at runtime are 
objects of the class type. Closures are to lambdas 
as objects are to classes. This should not be a 
surprise, because each lambda expression causes a 
unique class to be generated (during compilation) 
and also causes an object of that class type–a 
closure–to be created (at runtime).”


## Examples

See `main.cpp`.

To compile the program, please run the following 
command (e.g.) in the terminal.

    $ g++ closure.cpp -o closure -std=c++11

The outputs are as follows on my computer.

    $ ./closure 
    Value in the closure: 11
    Value in the closure: 12
    Value in the closure: 13
    -------------------------
    Value in the closure: 10
    Value in the closure: 10
    Value in the closure: 10
    -------------------------
    Value in the closure: 32765
    Value in the closure: 32766
    Value in the closure: 32767

In the above example, `func1` and `func2` are not 
closures. Instead, they are std::function wrapper 
objects that wrapped closures. `func0` is a closure, 
but it should be a copy of the closure created by the 
lambda expression `[&x](){x += 1; std::cout << "Value in the closure: " << x << std::endl;}`.

In the `func0`, it captured the reference to the 
variable `x` in the scope of `main`. Therefore, every 
time we call `func0`, the value of `x` in the scope 
of main gets increased by 1.

In the `func1`, it captured the value of the
variable `x` in the scope of `closureWrapper1` by 
making a copy of it. Therefore, every time we call 
`func1`, the value of of the closure is always 10. 
Note that after returning from the ordinary 
function, the local variables in the ordinary 
function would be out of scope.

In the `func2`, it captured the reference to the 
variable `x` in the scope of `closureWrapper2`. The 
reference “remember” the address of `x`. However, 
after returning from the function, the local 
variable `x` in the ordinary function would be out 
of scope. Then the value of reference would be 
undefined.

## Closure Analogs

### Function Object (Functor)

Function object overload the `operator()`. It could 
capture the values by making a copy of the variables 
to its member variables. The shortcoming is that for 
each different function call, regardless of how 
simple it is, we would have to implement a new 
class, whereas implementing a lambda expression is 
faster.

### Functions Using Static Variables

We don’t actually like to use static variables in 
the function, unless it is extremely necessary, 
because it would confuse the readers. In addition, 
if you have a lot of function calls, it is likely 
that we have a lot of static variables which is more 
undesired.

## FAQs

### Is Function Object Closure?

No.

According to the definition of [closure](https://en.wikipedia.org/wiki/Closure_(computer_programming)),
“In programming languages, a closure, also lexical 
closure or function closure, is a technique for 
implementing lexically scoped name binding in a 
language with first-class functions”. As C++ does 
not allow defining functions and objects inside a 
function, function object does not (always) allow [lexical scoping](https://en.wikipedia.org/wiki/Scope_(computer_science)#Lexical_scoping),
where with lexical scope, a name always refers to 
its (more or less) local lexical environment. In our 
case, `x` in the closure has always to be mapped to 
the `x` in the local scope. In a function object, 
the member variables are different from the local 
variables outside the function object, even though 
they might have the same name.

This might look like a lexical scoping exception for function objects in C++.

    #include <iostream>
    #include <functional>
    
    double pi = 3.1415926;
    
    class CircleArea
    {
    public:
        CircleArea()
        {
        }
        double operator() (double r) const
        {
            return pi * r * r;
        }
    };
    
    int main()
    {
        double r = 1.0;
        CircleArea circleArea;
        double area = circleArea(r);
        std::cout << area << std::endl;
    }

However, because we are not allowed to define a 
class in all the other scopes, class is not 
considered to support lexical scoping. For example, 
we could not compile the following program.

    #include <iostream>
    #include <functional>
    
    int main()
    {
        double pi = 3.1415926;
        
        class CircleArea
        {
        public:
            CircleArea()
            {
            }
            double operator() (double r) const
            {
                return pi * r * r;
            }
        };
    
        double r = 1.0;
        CircleArea circleArea;
        double area = circleArea(r);
        std::cout << area << std::endl;
    }

---

    $ g++ closure.cpp -o closure -std=c++17
    closure.cpp: In member function ‘double main()::CircleArea::operator()(double) const’:
    closure.cpp:16:20: error: use of local variable with automatic storage from containing function
       16 |             return pi * r * r;
          |                    ^~
    closure.cpp:6:12: note: ‘double pi’ declared here
        6 |     double pi = 3.1415926;
          |            ^~

Therefore, the only nested functions allowed in C++ are lambda expression.

### Conclusion

When we talked about the closures in C++, they are 
basically referring to the objects that lambda 
expressions constructed.

### References

- [Lambdas VS Closures](http://scottmeyers.blogspot.com/2013/05/lambdas-vs-closures.html)

---

In recent days, I've twice found myself explaining 
the difference between lambdas and closures in 
C++11, so I figured it was time to write it up.

The term "lambda" is short for lambda expression, 
and a lambda is just that: an expression. As such, 
it exists only in a program's source code. A lambda 
does not exist at runtime.

The runtime effect of a lambda expression is the 
generation of an object. Such objects are known as 
closures.

Given

    auto f = [&](int x, int y) { return fudgeFactor * (x + y); };

the blue expression to the right of the "=" is the 
lambda expression (i.e., "the lambda"), and the 
runtime object created by that expression is the 
closure.

You could be forgiven for thinking that, in this 
example, `f` was the closure, but it's not. `f` is a 
copy of the closure. The process of copying the 
closure into `f` may be optimized into a move 
(whether it is depends on the types captured by the 
lambda), but that doesn't change the fact that `f` 
itself is not the closure. The actual closure object 
is a temporary that's typically destroyed at the end 
of the statement.

The distinction between a lambda and the 
corresponding closure is precisely equivalent to the 
distinction between a class and an instance of the 
class. A class exists only in source code; it 
doesn't exist at runtime. What exists at runtime are 
objects of the class type.  Closures are to lambdas 
as objects are to classes. This should not be a 
surprise, because each lambda expression causes a 
unique class to be generated (during compilation) 
and also causes an object of that class type--a 
closure--to be created (at runtime). 

_Scott_

PS - I noted above that a closure is typically 
destroyed at the end of the statement in which it is 
created.  The exception to this rule is when you 
bind the closure to a reference. The simplest way to 
do that is to employ a universal reference,

    auto&& rrefToClosure = [&](int x, int y) { return fudgeFactor * (x + y); };

but binding it to an lvalue-reference-to-const will 
also work:

    const auto& lrefToConstToClosure = [&](int x, int y) { return fudgeFactor * (x + y); };

---

# Ask ChatGPT

<https://chat.openai.com/chat#>

## Question

In computing is there a difference between a closure and a lambda?

## Answer

Yes, there is a difference between a closure and a lambda.

A closure is a function object that remembers values in the enclosing scope even if they are not present in memory. A closure, unlike a plain function, allows the function to access those captured variables through the closure's reference to them, even when the function is invoked outside their scope.

A lambda, also known as an anonymous function, is a small, inline function without a name. In most programming languages, lambdas are used to write small, throw-away functions that are passed as arguments to other functions.

In summary, a closure is a specific type of object created when a function is defined in such a way that it remembers values in the enclosing scope, while a lambda is a shorthand for creating small, anonymous functions.
