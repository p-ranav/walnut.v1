# Walnut

Walnut is an interpreted high-level programming language implemented in C++. Walnut is simple, elegant and inspired by concepts in a number of programming languages including Python, Go, Rust and Javascript. This project is very much a work in progress and a learning experience, as I explore the world of language interpreters. 

DISCLAIMER: This is just a tree-walking interpreter. No bytecode. No VM. So, don't expect the performance to be comparable with languages like Python. Feel free to reuse the lexer and parser for your own VM implementation. Perhaps in the future, I'll work on a virtual machine for this language.

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
* Simple, expressive syntax, e.g., ```x := 5, y := 10, z := "Success" if x.type() == "int" and y in [2, 4, 6, 8, 10];```
* UTF-8 support - you can use 信息 as your variable name. Emojis are cool too!
* Function chaining with dot operator, e.g., ```[].append(2).extend([3, 4]).map(function(i) { i * i }).print();```
* A large pile of built-in functions implemented in C++
* Test suite - currently ~400 unit tests

## Code Samples

<img src="https://i.imgur.com/QcTD29z.png" alt="cone_volume" width="500"/>

<img src="https://i.imgur.com/QVNIJbC.png" alt="matrix_transpose" width="500"/>

<img src="https://i.imgur.com/mxXHJ5f.png" alt="list" width="500"/>

<img src="https://i.imgur.com/rKrBVsP.png" alt="string_format" width="500"/>

<img src="https://i.imgur.com/ondFPbP.png" alt="map_filter_reduce" width="500"/>

<img src="https://i.imgur.com/4w9ap1i.png" alt="dictionary" width="500"/>

<img src="https://i.imgur.com/IN2EHWO.png" alt="decorator" width="500"/>

<img src="https://i.imgur.com/WX96zH6.png" alt="kwargs" width="500"/>
