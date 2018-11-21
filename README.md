# Walnut

Walnut is an interpreted high-level programming language implemented in modern C++. Walnut is simple, elegant and inspired by concepts in a number of programming languages including Python, Go, Rust and Javascript. This project is very much a work in progress and a learning experience, as I explore the world of language interpreters. 

DISCLAIMER: This is just a tree-walking interpreter. No bytecode. No VM. So, don't expect the performance to be comparable with real-world interpreted programming languages like Python. Feel free to reuse the lexer and parser for your own compiler implementation. Perhaps in the future, I'll work on a virtual machine for this language.

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
* Lists, sets, tuples, dictionaries, functions and more
* Simple, expressive syntax, e.g., ```x := 5, y := 10, z := "Success" if x.type() == "int" and y in [1, 2, 3, 4, 5].map(a => a * 2)```
* UTF-8 support - you can use 信息 as your variable name. Emojis are cool too!
* Function chaining with dot operator, e.g., ```[].append(2).extend([3, 4]).map(function(i) { i * i }).print();```
* A large pile of built-in functions implemented in C++
* Test suite - currently ~350 unit tests

<img src="https://i.imgur.com/QcTD29z.png" width="800">