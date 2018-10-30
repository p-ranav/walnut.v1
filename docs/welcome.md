# Walnut

Walnut is an interpreted high-level programming language implemented in modern C++. Walnut is simple, elegant and inspired by concepts in a number of programming languages including Python, Go, Rust and Javascript. This project is very much a work in progress and a learning experience, as I explore the world of language interpreters. Feel free to join!

## Quick Start

### Dependencies

* C++ compiler with C++11 language feature support
* CMake to generate either the Makefile or the Visual Studio solution

```bash
$ git clone https://github.com/pranav-srinivas-kumar/walnut.git
$ cd walnut
$ mkdir build
$ cd build
$ cmake ../.
$ make
$ make check
```

## Highlights

* Dynamically-typed - inferred by the interpreter
* Strongly-typed - you can't add an integer with a string
* Sets, tuples, lists, dictionaries, and functions are all first-class objects
* UTF-8 support - you can use 信息 as your variable name. Emojis are cool too!
* Function chaining with dot operator, e.g., ```[].append(2).extend([3, 4]).map(function(i) { i * 2 }).println();```
* A large pile of built-in functions implemented in C++
* Test suite checking over xyz assertions across abc test cases

A detailed wiki for this language can be found [here](https://github.com/pranav-srinivas-kumar/walnut/wiki).

## Functions

Functions are first-class objects in walnut. With UTF-8 support, you can write functions that look like this:

```javascript
/*
 * Function to calculate 🚀 thrust
 * q  - mass flow rate (kg/s)
 * Pₐ - 🌍 atmospheric pressure (N/m²)
 * Pₑ - exit pressure (N/m²)
 * Vₑ - exit velocity 🙮 (m/s)
 * Aₑ - exit area of nozzle (m²)
 */
thrust = function(q, Vₑ, Pₑ, Pₐ, Aₑ) { 
  q • Vₑ + (Pₑ - Pₐ) • Aₑ 
}
```

You can also use the arrow operator '=>' like in Javascript to define your functions. Support for unicode characters in identifier names allows for highly readable function definitions like below:

```javascript
π = 3.1415;
volume = {
    "cube" : s => { 
        s³ = s • s • s; 
        return s³; 
    },
    "cylinder" : (r, h) => {  
        r² = r • r; 
        return π • r² • h; 
    },
    "cone": (r, h) => { 
        r² = r • r; 
        return π • r² • h / 3.0; 
    },
    "sphere": r => { 
        r³ = r • r • r; 
        return 4./3 • π • r³; 
    },
};

volume["cube"](5).println();          // 125
volume["cylinder"](5, 10).println();  // 785.38
volume["cone"](5, 10).println();      // 261.79
volume["sphere"](5).println();        // 523.58
```

## Chaining Function Calls

There are two ways to call any function (both user-defined and built-in functions) in walnut:

```javascript
square = ƒ(a) { return a • a };   // ƒ is a keyword, just like 'function'

// Function Application
x = 5;
y = square(x);
println(y);                       // 25

// Dot operator
x.square().println();             // 25
(10).square().println();          // 100
(3.14 * 2).square().println();    // 39.438400
[1, 2, 3].map(square).println();  // [1, 4, 9]
```

## Closure

Decorators are a good example of closure.

```javascript
decorate = function(f) {
    wrapped_function = function() {
        println("Function is being called");
        f();
        println("Function call is finished");
    };
    return wrapped_function;
}

my_function = function() { println("Hello World"); }.decorate();
my_function();
// Function is being called
// Hello World
// Function call is finished
```

The function ```wrapped_function``` is a closure, because it retains access to the variables in its scope -- in particular, the parameter f, the original function. Closures allow you to access it. 

## Function Aliasing

Trivially create aliases to both user-defined and built-in functions

```javascript
// Alias to functions
log = println;
log("Hello");

push = append;
[].push(1).extend([2, 3]).println();

add = function(a, b) { a + b; };
sum = add;
sum(2, 3).println();
```

## Range-based Iteration

Walnut provides a range-based 'for' loop construct identical to Python:

```javascript
for i in range(99, 0, -1) {
    if i == 1 {
        println("1 bottle of beer on the wall, 1 bottle of beer!");
        println("So take it down, pass it around, no more bottles of beer on the wall!");        
    }  
    else {
        if i == 2 {
            println("2 more bottles of beer on the wall, 2 more bottles of beer!");
            println("So take one down, pass it around, 1 more bottle of beer on the wall!");            
        }
        else {
            println(i, "bottles of beer on the wall,", i, "bottles of beer!");
            println("So take it down, pass it around,", (i - 1), "more bottles of beer on the wall!");            
        }
    }
}
```

The internal iterator of range objects can be used with built-in functions like map (or fiter) to quickly build lists:

```javascript
range(9).map(i => i * i).println(); // [0, 1, 4, 9, 16, 25, 36, 49, 64]
```