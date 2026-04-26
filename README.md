markdown# Calc-Ult

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

The project ships as two branches:

- **Main (`1filer`)** — a single `.cpp` monolith. Download, compile, run. No headers,
  no dependencies, no build system.
- **Micro** *(in progress)* — split into proper headers per domain, functions renamed
  and grouped for use as a lightweight personal math library.

---

## Implemented Functions

All of the following are hand-coded with no standard math library:

| Function | Method used |
|---|---|
| `msqrt` | Newton-Raphson iteration |
| `nthroot` | Newton-Raphson (generalised) |
| `mpow` / `npow` / `mfpow` | Iterative, integer and real exponents |
| `mln` | Series with range reduction via repeated halving |
| `mlog` | Change of base using `mln` |
| `meexp` | Taylor series for eˣ |
| `sine` / `cosine` | Taylor series (500 terms) |
| `tangent` / `cotangent` | Derived from sine/cosine |
| `secant` / `cosecant` | Reciprocal of cosine/sine |
| `factorial` | Iterative, returns `long long` |
| `mgcd` | Euclidean algorithm |
| `abs` | Branchless bitmask (`a >> 31`) |
| `dabs` | Ternary, single instruction |
| `toFraction` | Decimal-to-fraction via GCD reduction |
| `ogl` | Digit reversal |
| `numfinder` | Digit frequency counter |
| Big number `+` / `-` | Manual carry/borrow on digit arrays (up to 1000 digits) |
| Percentage, simple & compound interest | Formula-based |
| 2D Cartesian geometry | Distance, midpoint, slope, shape areas |
| Unit conversions | Volume, mass, distance, surface, speed, density, digital storage |

---

## Modes

Run with `./calc <mode>`:

| Mode | Description |
|---|---|
| `interactive` | REPL integer calculator — type operation then operands |
| `master` | REPL real-number calculator with `double` precision |
| `mass` | Big-number arithmetic — supports integers up to 1000 digits, `+` and `-` |
| `static <a> <b> <op>` | Non-interactive single operation, result printed and exits |
| `financial` | Percentage, simple interest, compound interest with yearly breakdown |
| `geometry` | 2D Cartesian: shapes, point sets, distances, slopes, midpoints |
| `converter` | Unit conversion across common measurement systems |
| `statistics` | Descriptive statistics on integer/real datasets |
| `help` | Full usage reference |

### Static mode operations


   Addition




   Subtraction




   Multiplication


/        Division
^        Power: a^b
gcd      Greatest common divisor
sqrt     Square root of a and b
find     Count occurrences of digit b in a
ogl      Reverse digits of a and b
mul2     a × 2^b  (left bit-shift equivalent)
div2     b / 2^a  (right bit-shift equivalent)
sepmul2  2^a
sepdiv2  1 >> a

---

## How to Run

```bash
# 1. Compile
g++ calc-ult-1filer.cpp -o calc

# 2. (Linux/macOS) Make executable if needed
chmod +x calc

# 3. Run
./calc <mode>

# Examples
./calc interactive
./calc master
./calc mass
./calc static 144 12 gcd
./calc financial
./calc geometry
./calc help
```

Windows: replace `./calc` with `.\calc` in PowerShell, or just `calc` in cmd.

---

## Constants

Hardcoded to full precision, used internally by all math functions:
e   = 2.71828182845904523536
pi  = 3.14159265358979323846
ln2 = 0.6931471805599453

---

## Planned Extensions

- [ ] Geometry: 3D Cartesian, trigonometric values, stub calculus mode
- [ ] Mass mode: multiplication and division for big numbers
- [ ] Trig: range reduction for large inputs, inverse trig (arcsin, arccos, arctan)
- [ ] Complex number plane arithmetic
- [ ] Vector calculus basics
- [ ] Cartesian coordinate transformations
- [ ] Physics constants and formula evaluator (groundwork for a tiny physics engine)
- [ ] Micro branch: split into proper header files as a personal math library
- [ ] Better error handling throughout (no silent `-1` sentinel returns)
- [ ] TUI polish

---

## Known Limitations

- Trig functions accumulate floating point error for large inputs (no full range
  reduction yet beyond `mln`'s halving loop)
- Mass mode supports `+` and `-` only
- 3D geometry, trig CLI, and calculus mode are stubs
- `mfpow` returns `-1` for negative bases (complex results not supported yet)
- Big number result array is stack-allocated at fixed 1001 elements

---

## Notes

The monolith structure was a deliberate choice for the `1filer` branch —
one file, one compile command, no friction. Having now written ~1200 lines
in a single translation unit, the micro branch will exist partly as a
corrective exercise in what headers and separation of concerns actually solve.

---

The microbranch version is in the makes, there are files like header and cpp for
hexhandler, cpp for math and so on. These will be dropped on the last version V1.5,
or whenever the monolith reaches 2k lines

## Future projects worth mentioning

During the summer i promise to make the following in cpp: RSA decrypter, AES decrypter, TLS decrypter, my own pwn implementation library in cpp, and my first GUI app, GUI for calculator
