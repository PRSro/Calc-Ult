# Calc-Ult

> A from-scratch terminal calculator built without standard math libraries —
> every algorithm implemented by hand.

---

## About

Calc-Ult started as a beginner C++ project and grew into a deliberate study
of what most developers take for granted: the math underneath the functions.
No `<cmath>`. No `std::pow`. No `std::sqrt`. Everything — from Newton's method
for roots, to Taylor series for trig, to digit-by-digit big number arithmetic —
is written from the ground up.

The goal was never just a calculator. It was to understand:

- **Strings & character arrays** — parsing, digit manipulation, big number encoding
- **Bit operands** — branchless abs, shift-based multiply/divide, sign extraction
- **Manually implemented math** — Newton-Raphson, Taylor series, Euclidean GCD,
  logarithm reduction, compound interest
- **Vector/array handling** — multi-thousand-digit arithmetic without any bignum lib
- **Template design** — type-safe input handling similar to Python's `input()`

---

## Repository Structure

```
Calc-Ult/
├── README.md                    # This file
├── monolith/                    # Original single-file version (main branch)
│   ├── calc-ult-1filer.cpp      # 1970-line monolith
│   └── README.md
└── Calc-Ult-Micro/              # Modular decomposition (micro branch → now also on main)
    ├── Makefile                 # Build system
    ├── include/                 # Headers
    │   ├── bigint.h
    │   ├── cli.h
    │   ├── finance.h
    │   ├── geometry.h
    │   ├── hex.h
    │   ├── math.h
    │   ├── operations.h
    │   ├── safeinput.hpp
    │   └── statistics.h
    └── src/                     # Implementations
        ├── bigint.cpp
        ├── cli.cpp
        ├── finance.cpp
        ├── geometry.cpp
        ├── hex.cpp
        ├── main.cpp
        ├── math.cpp
        ├── operations.cpp
        └── statistics.cpp
```

---

## Build & Run

### Monolith (single file)

```bash
cd monolith
g++ calc-ult-1filer.cpp -o calc
./calc <mode>
```

### Micro (modular)

```bash
cd Calc-Ult-Micro
make
./calc <mode>
```

### Examples

```bash
./calc interactive      # REPL integer calculator
./calc master           # REPL real-number (double) calculator
./calc mass             # Big-number arithmetic (up to 1000 digits)
./calc static 144 12 gcd  # Non-interactive single operation
./calc financial        # Percentage & interest
./calc geometry         # 2D Cartesian geometry
./calc statistics       # Descriptive statistics
./calc converter        # Unit conversion
./calc hex              # Hexadecimal utilities (micro version)
./calc help             # Full usage reference
```

---

## Modes

| Mode | Description |
|---|---|
| `interactive` | REPL integer calculator — type operation then operands |
| `master` | REPL real-number calculator with `double` precision |
| `mass` | Big-number arithmetic — supports integers up to 1000 digits, `+` and `-` |
| `static <a> <b> <op>` | Non-interactive single operation, result printed and exits |
| `financial` | Percentage, simple interest, compound interest with yearly breakdown |
| `geometry` | 2D Cartesian: shapes, point sets, distances, slopes, midpoints |
| `converter` | Unit conversion across volume, mass, distance, surface, speed, density, digital storage |
| `statistics` | Descriptive statistics on integer/real datasets |
| `hex` | Hex/binary/decimal/octal conversion, bitwise ops, ASCII encoding |
| `help` | Full usage reference |

### Static Mode Operations

| Op | Description |
|---|---|
| `+` | Addition |
| `-` | Subtraction |
| `*` | Multiplication |
| `/` | Division |
| `^` | Power: a^b |
| `gcd` | Greatest common divisor |
| `sqrt` | Square root |
| `find` | Count occurrences of digit b in a |
| `ogl` | Reverse digits |
| `mul2` | a × 2^b (left bit-shift) |
| `div2` | b / 2^a (right bit-shift) |
| `sepmul2` | 2^a |
| `sepdiv2` | 1 >> a |

---

## Implemented Functions

All hand-coded with no standard math library:

### Arithmetic & Roots
| Function | Method |
|---|---|
| `msqrt` | Newton-Raphson iteration |
| `nthroot` | Newton-Raphson (generalised) |
| `mpow` / `npow` / `mfpow` | Iterative, integer and real exponents |
| `factorial` | Iterative, returns `long long` |
| `mgcd` | Euclidean algorithm |

### Logarithms & Exponentials
| Function | Method |
|---|---|
| `mln` | Series with range reduction via repeated halving |
| `mlog` | Change of base using `mln` |
| `meexp` | Taylor series for eˣ |

### Trigonometry
| Function | Method |
|---|---|
| `sine` / `cosine` | Taylor series (500 terms) |
| `tangent` / `cotangent` | Derived from sine/cosine |
| `secant` / `cosecant` | Reciprocal of cosine/sine |

### Utilities
| Function | Method |
|---|---|
| `iabs` / `dabs` | Branchless bitmask / ternary |
| `toFraction` | Decimal-to-fraction via GCD reduction |
| `ogl` | Digit reversal |
| `numfinder` | Digit frequency counter |

### Big Numbers
| Function | Method |
|---|---|
| Big `+` / `-` | Manual carry/borrow on digit arrays (up to 1000 digits) |

### Finance
| Function | Method |
|---|---|
| Percentage, simple & compound interest | Formula-based |

### Hex Mode
| Command | Description |
|---|---|
| `e` | Encode text to hex |
| `d` | Decode hex to text |
| `x` | Decimal → hex |
| `b` | Decimal → binary |
| `r` | Binary → decimal |
| `w` | Write decimal → hex |
| `p` | Write decimal → binary |
| `l` | List recent conversions |
| `f` | Fix/convert list entries |

---

## Overflow Detection

All numeric operations include overflow guards:

- **Integer power** (`npow`): checks multiplication won't exceed `INT_MAX`
- **Factorial**: checks multiplication won't exceed `LLONG_MAX`
- **Double power** (`mpow`): checks result won't exceed `DBL_MAX`
- **Basic int ops** (+, -, *, /): bounded by `INT_MAX` / `INT_MIN`
- **Bit shifts**: guarded for shift amount >= 31
- **Double ops** (+, -, *, /): detects IEEE 754 infinity

On overflow, `"Overflow"` is printed and execution continues safely.

---

## Constants

Hardcoded to full precision, used internally by all math functions:

```
e   = 2.71828182845904523536
pi  = 3.14159265358979323846
ln2 = 0.6931471805599453
```

---

## Known Limitations

- Trig functions accumulate floating point error for large inputs (no full range
  reduction yet beyond `mln`'s halving loop)
- Mass mode supports `+` and `-` only
- 3D geometry, trig CLI, and calculus mode are stubs
- `mfpow` returns `-1` for negative bases (complex results not supported yet)
- Big number result array is stack-allocated at fixed 1001 elements

---

## Planned Extensions

- [ ] Geometry: 3D Cartesian, trigonometric values, stub calculus mode
- [ ] Mass mode: multiplication and division for big numbers
- [ ] Trig: range reduction for large inputs, inverse trig (arcsin, arccos, arctan)
- [ ] Complex number plane arithmetic
- [ ] Vector calculus basics
- [ ] Cartesian coordinate transformations
- [ ] Physics constants and formula evaluator (groundwork for a tiny physics engine)
- [ ] Better error handling throughout (no silent `-1` sentinel returns)
- [ ] TUI polish

---

## File-by-File Breakdown (Micro Version)

| File | Responsibility |
|---|---|
| `src/main.cpp` | Entry point, mode dispatch |
| `src/math.cpp` / `include/math.h` | Core math: sqrt, pow, log, exp, trig, factorial, GCD, abs, fraction |
| `src/operations.cpp` / `include/operations.h` | Operation dispatchers, overflow-safe wrappers |
| `src/statistics.cpp` / `include/statistics.h` | Descriptive statistics (mean, median, mode, stddev, etc.) |
| `src/geometry.cpp` / `include/geometry.h` | 2D Cartesian: distance, midpoint, slope, shape areas |
| `src/bigint.cpp` / `include/bigint.h` | Big integer arithmetic (digit arrays, carry/borrow) |
| `src/finance.cpp` / `include/finance.h` | Percentage, simple/compound interest |
| `src/hex.cpp` / `include/hex.h` | Hex/binary/decimal conversion utilities |
| `src/cli.cpp` / `include/cli.h` | CLI interface functions per mode |
| `include/safeinput.hpp` | Header-only type-safe input template |

---

## Notes

The monolith was a deliberate choice for the original version —
one file, one compile command, no friction. The micro branch exists as a
corrective exercise in what headers and separation of concerns actually solve.

---

## Future Projects

RSA decrypter, AES decrypter, TLS decrypter, custom pwntools-like library in C++,
and a GUI calculator app.
