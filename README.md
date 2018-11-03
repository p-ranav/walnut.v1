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
* Function chaining with dot operator, e.g., ```[].append(2).extend([3, 4]).map(function(i) { i * 2 }).print();```
* A large pile of built-in functions implemented in C++
* Test suite checking over xyz assertions across abc test cases

A detailed wiki for this language can be found [here](https://github.com/pranav-srinivas-kumar/walnut/wiki). Everything described below, although not exhaustive, is a working, completed language feature:

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

volume["cube"](5).print();          // 125
volume["cylinder"](5, 10).print();  // 785.38
volume["cone"](5, 10).print();      // 261.79
volume["sphere"](5).print();        // 523.58
```

## Chaining Function Calls

There are two ways to call any function (both user-defined and built-in functions) in walnut:

```javascript
square = ƒ(a) { return a • a };   // ƒ is a keyword, just like 'function'

// Function Application
x = 5;
y = square(x);
print(y);                       // 25

// Dot operator
x.square().print();             // 25
(10).square().print();          // 100
(3.14 * 2).square().print();    // 39.438400
[1, 2, 3].map(square).print();  // [1, 4, 9]
```

## Decorators

Decorators are a good example of closure.

```javascript
decorate = function(f) {
    wrapped_function = function() {
        print("Function is being called");
        f();
        print("Function call is finished");
    };
    return wrapped_function;
}

my_function = function() { print("Hello World"); }.decorate();
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
log = print;
log("Hello");

push = append;
[].push(1).extend([2, 3]).print();

add = function(a, b) { a + b; };
sum = add;
sum(2, 3).print();
```

## Lists

A list is an ordered, changeable collection. In Walnut, lists are written with square brackets.

```javascript
list = [
    1,                             // integer
    3.14,                          // double
    false,                         // boolean
    'λ',                           // character
    "Hello, 世界",                 // string
    function(i, j) { i * j },      // function
    [2, 3, [4, 5, [6]]],           // nested lists
    {"a": 7, "b": 8.0},            // dictionary
    {9, 10, 10},                   // set {9, 10}
    (x, true)                      // tuple
];
```

The above list is pretty heterogeneous. It contains integers, doubles, booleans, characters, strings, functions, lists, dictionaries, sets and tuples! You can index into this list and modify anything.

```javascript
list[5](2, 3).print();   // access function and call with arguments (2, 3) - result = 6
list[0] = 3;             // modify element at index 0
list[7]["a"] = 0.88;     // change value at dictionary key "a"
```

## Range-based Iteration

Walnut provides a range-based 'for' loop construct identical to Python:

```javascript
for i in range(99, 0, -1) {
    if i == 1 {
        print("1 bottle of beer on the wall, 1 bottle of beer!");
        print("So take it down, pass it around, no more bottles of beer on the wall!");        
    }  
    else if i == 2 {
        print("2 more bottles of beer on the wall, 2 more bottles of beer!");
        print("So take one down, pass it around, 1 more bottle of beer on the wall!");            
    }
    else {
        print(i, "bottles of beer on the wall,", i, "bottles of beer!");
        print("So take it down, pass it around,", (i - 1), "more bottles of beer on the wall!");            
    }
}
```

The iterator for range objects can be used with built-in functions like map (or fiter) to quickly build lists:

```javascript
range(9).map(i => i * i).print(); // [0, 1, 4, 9, 16, 25, 36, 49, 64]
```

## Dictionaries

Walnut dictionaries are most like Javascript objects. You can use range-based iteration on dictionaries too!

```javascript
dict = {
    "value" : 
    { 
        "pi": 3.14, 
        "greet": "Hello, 世界", 
        "func": function(a, b) { a * b }
    },
};

for key, value in dict["value"] {
    print(key, ":", value)
}

// func : function(a, b) { a * b; }
// greet : Hello, 世界
// pi : 3.14

for pair in dict["value"] {
    print(pair)
}

// [func, function(a, b) { a * b; }]
// [greet, Hello, 世界]
// [pi, 3.14]
```

## Sets

Sets are unordered collections of unique elements. Common uses include membership testing, removing duplicates from sequences, and computing standard math operations on sets such as intersection, union, difference, and symmetric difference.

```cpp
x = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 3, 4, 5, 6};
print(x);
// {1, 2, 3, 4, 5, 6, 7, 8, 9}

for i in x { i.print(end = " ") }
print()
// 1 2 3 4 5 6 7 8 9

x = {1, 3.14, 3.14, 5, 3.1415, 6, "H", 'c', function(a) { a }};
x.print()
// {1, 3.14, 5, 6, "H", 'c', function(a) { a; }}
```

## Rust-style Error Reporting

The Walnut parser and interpreter use a Rust-style error reporting system. Here's an example parser error message:

```cpp
error: cannot use 5 as left-hand side of => operator
  --> tests/tuple.txt:31:5
   |
30 |  print("Process started");
   |
31 |  x = 5 => print(5);
   |      ^^^^ LHS of arrow operator needs to be an identifier or an identifier-tuple
32 |
   |
```

