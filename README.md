[![Build Status](http://drone.hnatekmar.xyz/api/badges/Hnatekmar/TPJ/status.svg)](http://drone.hnatekmar.xyz/Hnatekmar/TPJ)

# Mirage Programming Language

Mirage is a purely functional language designed for describing and creating vector graphics. It was created as a semester project for the TPJ course (PEF, Mendel University).

## Language Basics

### Expressions

#### Application (Function/Macro Calls)

```clojure
(<function or macro> <expressions (arguments)>)
```

For example:

```clojure
(+ 1 2)
```

Evaluates to `3`, because `+` is the addition function.

#### Atoms

- Numbers (e.g., `100.5`)
- Strings (e.g., `"mirage"`)
- Booleans (`$p` for true, `$n` for false)
- Symbols (e.g., `+`)

#### Expansion

Expansion is syntactic sugar for calling a function with a single argument. For example:

```clojure
(importuj "mirage/mirage.mir")
```

Can be written using expansion as:

```clojure
#importuj "mirage/mirage.mir"
```

### Useful Functions, Macros, and Special Forms

#### `definuj` (define)

Assigns a value to a symbol.

Example:

```clojure
(definuj PI 3.14)
```

#### `funkce` (function)

Creates a function. Takes a list of arguments and a function body. Arguments must be symbols only.

Example:

```clojure
; Function that returns what it received
(definuj identita (funkce (x) x))
(identita (+ 5 6)) ; 11
```

The argument list can use the special symbol `...` to indicate a variadic function. All arguments are collected into a list. Example:

```clojure
(definuj prvniArgument (funkce (...) (prvni ...)))
(prvniArgument 1 2 3) ; 1
```

The `...` symbol must always be at the end of the argument list.

Every function has its own scope and captures the entire scope at the time of its creation. You can create lists using only functions:

```clojure
(definuj mujList (funkce (hlava telo)
                         (funkce (f)
                                 (f hlava telo))))
(definuj prvni (funkce (hlava telo) hlava))
(definuj zbytek (funkce (hlava telo) telo))
(definuj konecListu -1)
(definuj cisla (mujList 0 (mujList 2 (mujList 3 konecListu))))

(prvni cisla) ; 1
(prvni (zbytek cisla)) ; 2
```

#### Lists

The `list` function returns a list of items:

```clojure
(list (+ 1 3) 5 "ahoj") ; (4 5 "ahoj")
```

Basic operations on lists:

Get the first element (throws an error if the list is empty):

```clojure
(definuj cisla (list 1 2 3))
(prvni cisla) ; 1
```

Get the rest of the list (without the first element):

```clojure
(definuj cisla (list 1 2 3))
(zbytek cisla) ; (2 3)
```

Get the number of elements in a list:

```clojure
(definuj cisla (list 1 2 3))
(velikost cisla) ; 3
```

All of these operations also work on strings (returning a string).

#### Quote/Evaluate

Since Mirage is homoiconic, any expression can be converted to its representation directly in the language. This is achieved with the `nevyhodnocuj` (quote) macro, which takes any expression and returns its Mirage representation.

Examples:

```clojure
(nevyhodnocuj 5)       ; returns the number 5
(nevyhodnocuj mirage)  ; returns the symbol mirage (not its value)
(nevyhodnocuj (+ 1 2)) ; returns a list with +, 1, and 2 — equivalent to (list (nevyhodnocuj +) 1 2)
(nevyhodnocuj (1 2 4 (5 6))) ; equivalent to (list 1 2 4 (list 5 6))
```

The opposite of `nevyhodnocuj` is the `vyhodnoť` (eval) function, which evaluates a given representation back to a value:

```clojure
(vyhodnot 5)           ; 5
(definuj PI 3.14)
(vyhodnot (nevyhodnocuj PI)) ; 3.14
(vyhodnot (list + 1 2))    ; 3
```

#### Macros

Macros are functions that do not evaluate their arguments but instead evaluate their output. Macros are very powerful and form part of the [standard library](https://github.com/Hnatekmar/TPJ/blob/master/project/mirage/makra/makra.mir) of Mirage. A good example of macro usefulness is the `defn` macro:

```clojure
(definuj defn (makro (nazev argumenty ...)
	(list definuj nazev
	  (spoj (list funkce argumenty) ...))))
```

The `defn` macro replaces the previously used combination:

```clojure
(definuj nazev (funkce () telo))
```

with the more readable:

```clojure
(defn nazev () telo)
```

#### Element (SVG)

The `element` function represents an SVG element. Examples:

```clojure
(element "name" (list "arg" "value") (list (element "child" (list) (list)))) ; <name arg="value"><child></child></name>
```

### Rendering

Rendering is done using the `vykresli` function. It requires several arguments: the first is a list of elements, and the next two represent the height and width of the image.

## Standard Library

As mentioned, the language includes its own standard library containing many useful functions and macros for manipulating images, lists, and more.