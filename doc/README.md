# Mirage Language Documentation

This directory contains the full technical documentation for the Mirage programming language.

## Overview

Mirage is a purely functional Lisp-like language for generating SVG vector graphics. The documentation covers:

- [Language Specification](#language-specification)
- [Lexical Analysis](#lexical-analysis)
- [Parsing](#parsing)
- [Semantic Analysis](#semantic-analysis)
- [Building and Running](#building-and-running)

## Language Specification

### Data Types

Mirage has the following data types:

1. **Number** — Floating-point numbers (within the SVG standard range)
2. **String** — Begins and ends with `"`, supports escape sequences with `\`
3. **Boolean** — `$p` (true) or `$n` (false)
4. **Function**
5. **Macro**
6. **List**
7. **SVG Element** — A printable representation of an SVG element

### Functions

Each function has an argument list and a body containing at least one expression. The last expression in the body is the return value. If `...` appears in the argument list, the function is variadic — extra arguments are collected into a list. The `...` must be the last argument.

```clojure
; Example function
((funkce (x) x) 5)           ; Returns 5
((funkce (...) (prvni ...)) 1 2 3) ; Returns 1
```

#### Tail Call Elimination

Mirage (like other Lisps) optimizes tail-recursive calls:

```clojure
(definuj factorial (funkce (x accumulator)
    (pokud (= x 0)
        accumulator
        (factorial (- x 1) (* x accumulator)))))
```

This only works when the recursive call is in the tail position:

```clojure
; This will use classic (non-tail) recursion
(definuj factorial (funkce (x)
    (pokud (= x 0)
        1
        (* x (factorial (- x 1))))))
```

### Macros

Macros are functions that do not evaluate their arguments; their return value is a list that is then evaluated as normal Mirage code.

**Quote (`nevyhodnocuj`):** Takes any valid value and returns its unevaluated form.

```clojure
(nevyhodnot (+ 5 6)) ; Returns (list (nevyhodnot +) 5 6)
(nevyhodnot +)       ; Returns the identifier +
```

**Eval (`vyhodnot`):** The inverse of quote.

```clojure
(vyhodnot (list + 5 6))    ; Returns 11
(vyhodnot (nevyhodnocuj +)) ; Returns the function +
```

**Example macro — `apply`:**

```clojure
(definuj apply
    (makro (fn args)
        (spoj (list fn) args)))

; Expands to (+ 5 6), which evaluates to 11
(apply + (list 5 6))
```

Macros are expanded in the caller's scope. The `if` (`pokud`) macro evaluates its first argument, then expands into either the second or third argument:

```clojure
; Expands to (+ 1 2); the error call is never evaluated
(pokud $p
    (+ 1 2)
    (chyba "Critical error!"))
```

### Expansion Syntax

Expansion is syntactic sugar for single-argument function calls using the `#` prefix:

```clojure
; Equivalent to (#quote (+ 1 2))
#quote (+ 1 2)
```

To define expansions, use `definujExpanzi` or the `funkce->expanze` macro from the standard library:

```clojure
#import "mirage/mirage.mir"
(funkce->expanze + plus)
#plus (1 2 3) ; Returns 6
```

### Standard Library

Mirage includes a standard library with useful definitions and SVG element generators. Import it with:

```clojure
(import "mirage/mirage.mir")
```

The `defn` macro simplifies function definitions:

```clojure
(import "mirage/mirage.mir")

(defn factorial (x)
    (pokud (= x 0)
        1
        (* x (factorial (- x 1)))))
```

### Drawing / SVG Generation

The `element` function represents an SVG element (name, attributes, children):

```clojure
(definuj rectangle (funkce (height width)
     (element "rect"
         (list "width" (hodnota->retezec width)
               "height" (hodnota->retezec height))
         (list))))
```

The `vykresli` (render) function outputs the SVG to stdout:

```clojure
(import "mirage/mirage.mir")
(vykresli (list (rectangle 100 100)) 100 100)
```

Output:

```xml
<svg width="100"
     height="100"
     xmlns="http://www.w3.org/2000/svg">
    <rect height="100"
          width="100"></rect>
</svg>
```

## Lexical Analysis

The lexical analyzer processes the following token grammars.

### Identifiers

An identifier starts with any character from the set `z = {a..z, A..Z, +, -, /, *, <}` and continues with any character from `m = z ∪ {0..9}`.

```
G_identifiers({S, A, B}, {z, m}, P, S)
S → zA | z
A → mA | m
```

### Numbers

```
G_numbers({S, B, C}, {d, .}, P, S)
S → dB | d
B → dB | d | .C
C → dC | d
```

### Strings

Strings start and end with `"`. Inside, any character preceded by `\` or any printable character that is not `\` or `"` is allowed.

```
G_strings({S, D, E}, {\, ", ■}, P, S)
S → "D
D → " | \E | ■E
E → "D | \D | ■D
```

### Parentheses

```
G_parens({S}, {(, )}, P, S)
S → ( | )
```

### Whitespace

```
G_whitespace({S}, {↵, ↦, ⊔}, P, S)
S → ↵S | ↦S | ⊔S
```

### Comments

Comments start with `;` or `#` and end at a newline.

```
G_comments({S, F}, {↵, ;, □}, P, S)
S → ;F
F → □F | ↵S
```

### Boolean Values

```
G_booleans({S, H}, {$, n, p})
S → $H
H → n | p
```

### Combined State Machine

The complete token language is built from separator tokens (comments, whitespace) and meaningful tokens:

```
L_separators = G_comments ∪ G_whitespace
L_tokens = L_identifiers ∪ L_numbers ∪ L_strings ∪ L_parentheses
L = (L*_separators · L_token)* · L*_separators
```

The combined grammar produces a DFA (see [automaton diagram](automat.tex) in the LaTeX source).

## Parsing

### Syntax Diagrams

The parser grammar is derived from the following syntax diagrams:

- **Program**: 0 to ∞ expressions
- **Expression**: Either an s-expression (parenthesized argument list) or an expansion
- **Atom**: A basic element (string, number, identifier, boolean, or expansion)
- **Argument**: An atom or expression
- **Expansion**: A `#` followed by a name and an argument

### Parsing Algorithm

A table-driven parsing algorithm is used. The grammar is augmented with semantic actions (evaluate current tree, build tree).

### Parser Grammar

```
G_parser({Program, Expression, Expression2, Argument, Expansion, Atom},
         {(, ), name, number, identifier, string, boolean},
         P, Program)

Program → Expression Program Eval | ε
Expression → ( Expression2 | Expansion
Expression2 → Argument Expression2 | ) BuildTree
Argument → Atom | Expression
Expansion → name Argument BuildTree
Atom → number | identifier | string | boolean
```

## Semantic Analysis

Parts of the program are translated into a semantic tree, which is then evaluated into a value internally represented as a token structure. Evaluation uses the `evaluate` method with the current context (a symbol-to-value mapping).

For example, evaluating `(+ 1 2)`:
1. The symbol `+` is resolved to its associated function
2. All arguments are applied to that function

See the [translation diagram](obrazky/preklad.png) for an illustration.

## Building and Running

See the [main README](../README.md) for build instructions.

### Dependencies

- C++14 compiler (g++ 6.3.1+, clang 3.8.1+)
- Boost library
- CMake 3.6+

### Quick Start

```bash
cmake -G "Unix Makefiles" CMakeLists.txt
make
export MIRAGE_PATH=./project/mirage
./mirageC examples/test.mir > output.svg
```

### Executables

- `mirageI` — Interactive interpreter (stdin → stdout)
- `mirageC` — Compiler (file or stdin → SVG on stdout)

## Grammar Files

The `doc/` directory also contains:

- `ebnf.txt` — EBNF grammar summary
- `grammar.py`, `automat.py` — Python scripts related to grammar/automaton generation
- `gramatiky/` — JSON grammar definition files (numbers, identifiers, lists, words)
- `obrazky/` — Syntax diagram PNG images
- `main.tex` — Full LaTeX documentation source (original Czech version)
