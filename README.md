[![Build Status](http://drone.hnatekmar.xyz/api/badges/Hnatekmar/TPJ/status.svg)](http://drone.hnatekmar.xyz/Hnatekmar/TPJ)

# Mirage Programming Language

Mirage is a purely functional programming language designed for describing and creating vector images (SVG). It was created as a semester project for the TPJ course (Faculty of Economics, Mendel University).

## Language Basics

### Expressions

#### Application (calling functions/macros)

```clojure
(<function or macro> <expressions (arguments)>)
```

For example:

```clojure
(+ 1 2)
```

evaluates to 3, because the symbol `+` is bound to the addition function.

### Atoms

- **Numbers** (e.g., `100.5`)
- **Strings** (e.g., `"mirage"`)
- **Booleans** (`$p` for true or `$n` for false)
- **Symbols** (e.g., `+`)

### Expansion

Expansion is syntactic sugar for calling a function with a single argument. For example:

```clojure
(import "mirage/mirage.mir")
```

can be written using expansion as:

```clojure
#import "mirage/mirage.mir"
```

### Useful Functions / Macros / Forms

#### `definuj` (define)

Binds a value to a symbol.

```clojure
(definuj PI 3.14)
```

#### `funkce` (function)

Creates a function. Takes a list of arguments and a function body. The argument list can only contain symbols.

```clojure
; Function that returns what it receives
(definuj identity (funkce (x) x))
(identity (+ 5 6)) ; 11
```

A special symbol `...` in the argument list denotes a variadic function — all extra arguments are collected into a list.

```clojure
(definuj firstArg (funkce (...) (prvni ...)))
(firstArg 1 2 3) ; 1
```

The `...` symbol must always be at the end of the argument list.

Each function has its own scope and captures the entire enclosing scope at creation time. For example, you can implement lists using only functions:

```clojure
(definuj myList (funkce (head tail)
                       (funkce (f)
                               (f head tail))))
(definuj first (funkce (head tail) head))
(definuj rest (funkce (head tail) tail))
(definuj endOfList -1)
(definuj numbers (myList 0 (myList 2 (myList 3 endOfList))))

(first numbers)      ; 0
(first (rest numbers)) ; 2
```

#### Lists

The `list` function returns a list of items:

```clojure
(list (+ 1 3) 5 "hello") ; (4 5 "hello")
```

Basic list operations:

- Get the first element:

```clojure
(definuj numbers (list 1 2 3))
(prvni numbers) ; 1
```

- Get the rest (all but the first element):

```clojure
(definuj numbers (list 1 2 3))
(zbytek numbers) ; (2 3)
```

- Get the number of elements:

```clojure
(definuj numbers (list 1 2 3))
(velikost numbers) ; 3
```

All of these operations also work on strings (returning a string instead of a list).

#### `nevyhodnocuj` (quote) / `vyhodnot` (eval)

Since Mirage is homoiconic, any expression can be converted to its language-level representation. This is done using the `nevyhodnocuj` macro, which takes any expression and returns its Mirage representation.

```clojure
(nevyhodnocuj 5)               ; returns the number 5
(nevyhodnocuj mirage)          ; returns the symbol mirage (not its value)
(nevyhodnocuj (+ 1 2))         ; returns a list with the symbol +, 1, and 2
(nevyhodnocuj (1 2 4 (5 6)))   ; equivalent to (list 1 2 5 (list 5 6))
```

The inverse of `nevyhodnocuj` is `vyhodnot` (eval), which evaluates a representation back to a value:

```clojure
(vyhodnot 5)                           ; number 5
(definuj PI 3.14)
(vyhodnot (nevyhodnocuj PI))           ; 3.14
(vyhodnot (list + 1 2))                ; 3
```

#### Macros

Macros are functions that do not evaluate their arguments but instead evaluate their output. Macros are very powerful and form the basis of parts of the [Mirage standard library](https://github.com/Hnatekmar/TPJ/blob/master/project/mirage/makra/makra.mir).

A good example of a macro's usefulness is `defn`:

```clojure
(definuj defn (makro (name args ...)
        (list definuj name
    (spoj (list funkce args) ...))))
```

The `defn` macro replaces the verbose pattern:

```clojure
(definuj name (funkce () body))
```

with a more concise form:

```clojure
(defn name () body)
```

#### SVG Elements

The `element` function represents an SVG element:

```clojure
(element "name" (list "attribute" "value") (list (element "child" (list) (list))))
; <name attribute="value"> <child></child> </name>
```

### Rendering

Rendering is done using the `vykresli` (render) function. It requires a list of elements, followed by the width and height of the output image:

```clojure
(import "mirage/mirage.mir")
(vykresli (list (rectangle 100 100)) 100 100)
```

### Standard Library

As mentioned above, the language includes its own standard library with many useful functions and macros for manipulating images, lists, and more.

## Building & Running

### Dependencies

- A C++14-compatible compiler (tested with g++ 6.3.1, clang 3.8.1)
- [Boost](http://www.boost.org) library
- CMake 3.6 or higher

### Build Instructions

From the project root directory:

```bash
cmake -G "Unix Makefiles" CMakeLists.txt
make
```

The build produces two executables:

- **mirageI** — An interactive interpreter that reads a line from stdin, evaluates it, and prints the result to stdout.
- **mirageC** — Compiles Mirage programs to SVG. Can be called with a filename argument or without arguments (reads from stdin).

### Environment Setup

Set the `MIRAGE_PATH` environment variable to point to the directory containing the standard library. Without this, the library cannot be found and loaded.

```bash
export MIRAGE_PATH=/path/to/project/mirage
```

## Project Structure

- `project/` — Source code (C++), headers, and standard library (`.mir` files)
- `doc/` — Documentation (LaTeX source, grammar definitions, diagrams)
- `tests/` — Unit tests using the [Catch testing library](https://github.com/philsquared/Catch)
- `examples/` — Example Mirage programs

## License

This project was created as a semester project at Mendel University (PEF Mendelu).
