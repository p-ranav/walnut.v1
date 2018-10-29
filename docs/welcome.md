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