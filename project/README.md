# Project Documentation

This directory contains the Mirage programming language implementation in C++.

## Building

```bash
cd project
mkdir build && cd build
cmake ..
make
```

### Requirements

- C++17 compatible compiler
- CMake 3.10+

## Structure

| Directory | Description |
|-----------|-------------|
| `include/` | Header files (AST, Lexer, Parser, etc.) |
| `src/` | Implementation files |
| `include/StdLib/` | Standard library function declarations |
| `src/StdLib/` | Standard library implementations |
| `mirage/` | Mirage standard library (.mir files) |
| `main.cpp` | Main entry point |
| `mainInterpreter.cpp` | Interpreter-only entry point |
