# Mirage Programming Language

[![Build Status](http://drone.hnatekmar.xyz/api/badges/Hnatekmar/TPJ/status.svg)](http://drone.hnatekmar.xyz/Hnatekmar/TPJ)

**Mirage** is a purely functional language for describing and generating vector images. It was created as a semester project for the course TPJ (Programming Languages) at MENDELU.

## Language Basics

### Expressions

#### Application (function/macro calls)

```clojure
(<function-or-macro> <expressions (arguments)>)
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

Expansion is syntactic sugar for calling a function with one argument. For example:

```clojure
(import "mirage/mirage.mir")
```

can be written using expansion as:

```clojure
#import "mirage/mirage.mir"
```

### Useful Functions, Macros, and Forms

#### `definuj` (Define)

Binds a value to a symbol.

```clojure
(definuj PI 3.14)   ; Define PI as 3.14
```

#### `funkce` (Function)

Creates a function. Takes a list of arguments and a function body. The argument list can only contain symbols.

```clojure
; Function that returns its argument
(definuj identity (funkce (x) x))
(identity (+ 5 6))  ; → 11
```

The special symbol `...` denotes a variadic function — all remaining arguments are collected into a list.

```clojure
(definuj firstArg (funkce (...) (first ...)))
(firstArg 1 2 3)  ; → 1
```

`...` must always appear at the end of the argument list.

Each function has its own scope and captures the enclosing scope at creation time (closures). This allows implementing data structures like lists using only functions:

```clojure
(definuj myList (funkce (head tail)
                       (funkce (f)
                               (f head tail))))
(definuj first (funkce (head tail) head))
(definuj rest (funkce (head tail) tail))
(definuj endOfList -1)
(definuj numbers (myList 0 (myList 2 (myList 3 endOfList))))

(first numbers)        ; → 0
(first (rest numbers)) ; → 2
```

#### Lists

The `list` function returns a list of items:

```clojure
(list (+ 1 3) 5 "hello")  ; → (4 5 "hello")
```

Basic list operations:

```clojure
(definuj numbers (list 1 2 3))
(first numbers)   ; → 1
(rest numbers)    ; → (2 3)
(size numbers)    ; → 3
```

These operations also work on strings (returning string results).

#### `nevyhodnocuj` / `vyhodnot` (Quote / Eval)

Since Mirage is homoiconic, any expression can be converted to its language-internal representation. The macro `nevyhodnocuj` (quote) takes any expression and returns its Mirage representation.

```clojure
(nevyhodnocuj 5)              ; returns number 5
(nevyhodnocuj mirage)         ; returns the symbol `mirage` (not its value)
(nevyhodnocuj (+ 1 2))        ; returns a list with symbol +, 1, and 2
(nevyhodnocuj (1 2 4 (5 6)))  ; equivalent to (list 1 2 5 (list 5 6))
```

The opposite is `vyhodnot` (eval), which evaluates a representation back to a value:

```clojure
(vyhodnot 5)                        ; → 5
(definuj PI 3.14)
(vyhodnot (nevyhodnocuj PI))        ; → 3.14
(vyhodnot (list + 1 2))             ; → 3
```

#### Macros

Macros are functions that do not evaluate their arguments but evaluate their output. Macros are very powerful and form the basis of parts of the [standard library](https://github.com/Hnatekmar/TPJ/blob/master/project/mirage/makra/makra.mir).

A good example of macro usefulness is `defn`:

```clojure
(definuj defn (makro (name args ...)
    (list definuj name
  (concat (list funkce args) ...))))
```

The `defn` macro replaces the verbose pattern:

```clojure
(definuj name (funkce () body))
```

with the cleaner:

```clojure
(defn name () body)
```

#### Element (SVG)

The `element` function represents an SVG element:

```clojure
(element "name" (list "attr" "value") (list (element "child" (list) (list))))
; → <name attr="value"> <child></child> </name>
```

### Rendering

Rendering is handled by the `vykresli` (render) function, which takes a list of elements, width, and height.

## Standard Library

Mirage includes its own standard library with many useful functions and macros for image manipulation, list processing, and more.

> This is an English translation of the original Czech documentation. For the full language specification, please refer to the `doc/` directory.
