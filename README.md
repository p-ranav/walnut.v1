<p align="center">
  <img src ="https://i.imgur.com/1sGgx4z.png" width="400" />
</p>

Walnut is an interpreted high-level programming language implemented in C++. Walnut is simple, elegant and inspired by concepts in a number of programming languages including Python, Go, Rust and Javascript. This project is very much a work in progress and a learning experience, as I explore the world of language interpreters. 

* Lexer with UTF-8 support
* Recursive-descent Parser
* Tree-walking Interpreter

## Highlights

* Dynamically-typed and Strongly-typed
* Lists, sets, tuples, dictionaries, functions and more
* Simple, expressive syntax, e.g., ```x := 5, y := 10, z := "Success" if x.type() == "int" and y in [2, 4, 6, 8, 10];```
* UTF-8 support - you can use 信息 as your variable name. Emojis are cool too!
* Function chaining with dot operator, e.g., ```[].append(2).extend([3, 4]).map(function(i) { i * i }).print();```
* A large pile of built-in functions implemented in C++
* Test suite - currently ~400 unit tests

## Quick Start

This code base has been tested with both Visual Studio 2017 and gcc 7.3.0. 

```console
$ mkdir build
$ cd build
$ cmake ../.
$ make && make check
```

<img src="https://i.imgur.com/ugf7Qee.png" alt="Functions Defined"/>

<img src="https://i.imgur.com/qkRegHZ.png" alt="Functions Defined"/>

<img src="https://i.imgur.com/158nYK7.png" alt="Functions Defined"/>

<img src="https://i.imgur.com/Vz9gcaS.png" alt="Functions Defined"/>

<img src="https://i.imgur.com/3boEIEb.png" alt="Functions Defined"/>