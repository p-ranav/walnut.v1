# Walnut

Walnut is an interpreted high-level programming language implemented in modern C++. Walnut is simple, elegant and inspired by concepts in a number of programming languages including Python, Go, Rust and Javascript. This project is very much a work in progress and a learning experience, as I explore the world of language interpreters. Feel free to join!

## Quick Start

This code base has been tested with both Visual Studio 2017 and gcc 7.3.0. 

```bash
$ mkdir build
$ cd build
$ cmake ../.
$ make && make check
```

## Highlights

* Dynamically-typed and Strongly-typed
* Lists, ranges, sets, tuples, dictionaries, and functions are all first-class objects
* Simple, expressive syntax, e.g., ```x := 5, y := 10, z := "Success" if x.type() == "int" and y in [1, 2, 3, 4, 5].map(a => a * 2)```
* UTF-8 support - you can use 信息 as your variable name. Emojis are cool too!
* Function chaining with dot operator, e.g., ```[].append(2).extend([3, 4]).map(function(i) { i * i }).print();```
* A large pile of built-in functions implemented in C++
* Test suite - currently ~350 unit tests