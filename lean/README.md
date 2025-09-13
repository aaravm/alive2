# Lean Integration for Alive2

This project aims to bridge compiler optimization validation with interactive theorem proving.
Alive2 already checks LLVM optimizations for correctness using SMT solvers. Our goal is to automatically generate machine-checked Lean proofs for compiler optimizations, scaling from toy peepholes to optimization pipelines like -O2.

Instead of "just checking" that an optimization is correct, we want to produce a formal proof artifact in Lean that certifies the equivalence of source and target programs under all environments.

Ultimately, this project envisions a world where:

Every LLVM optimization ships with a Lean proof certificate.

Compiler trust is shifted from heuristic validation to mathematical certainty.

Proof artifacts can be composed, audited, and extended to future verification frameworks.

<b> PPT LINK: </b> [canva presentation](https://www.canva.com/design/DAGRcBeQffY/tw_6S0cgtlL65YDS26bPdA/edit?utm_content=DAGRcBeQffY&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)

## Big picture

This project is a stepping stone toward a formally verified LLVM, where correctness is not only checked by an SMT solver but proven in an interactive theorem prover.

Alive2’s SMT engine tells us "this optimization looks safe."
Our extended toolchain will tell us:
"Here’s a Lean proof. Trust mathematics, not heuristics."


## Directory Structure

```
lean/
├── CMakeLists.txt              # Build configuration for Lean integration
├── pattern_match.cpp           # C++ implementation of pattern matching and Lean interaction
├── pattern_match.h            # Header file for pattern matching interface
├── LeanProofGenerator/         # Lean theorem prover code
│   ├── Main.lean              # Main entry point for Lean proofs
│   ├── type1.lean             # Type-specific proof strategies
│   ├── type2.lean             # Additional proof strategies
│   ├── type3.lean             # More proof strategies
│   └── ...
├── proofs_generated/          # Directory containing generated proof files
└── Testing_files/            # Test cases for verification
    ├── src_add_0.ll          # Source LLVM IR for addition
    ├── tgt_add_0.ll          # Target LLVM IR for addition
    ├── src_mul_0.ll          # Source LLVM IR for multiplication
    └── tgt_mul_0.ll          # Target LLVM IR for multiplication

```

## Components

### Pattern Matching (C++)
- `pattern_match.h/cpp`: Implements the interface between Alive2 and Lean
- Detects specific LLVM IR patterns that require formal verification
- Manages the execution of Lean proofs and captures their output

### Lean Proof Generator
- Located in `LeanProofGenerator/`
- Contains Lean theorem prover code for verifying LLVM IR transformations
- Organized by transformation types (type1.lean, type2.lean, etc.)
- Uses mathlib and other Lean packages for formal proofs

### Generated Proofs
- Stored in `proofs_generated/`
- Each proof file is timestamped (format: proof_YYYYMMDD_HHMMSS.txt)
- Contains formal verification results and proof details

### Test Files
- Located in `Testing_files/`
- Contains pairs of source and target LLVM IR files
- Used for testing the verification process
- Naming convention: src_<operation>_<number>.ll and tgt_<operation>_<number>.ll

### Types of Proofs
1. **Type 1: Addition with Zero** (x + 0 = x)

   - File: `type1.lean`
   - Pattern: Matches instructions like `%result = add i32 %x, 0`
   - Proves that adding zero to a number results in the same number

2. **Type 2: Multiplication by One** (x \* 1 = x)

   - File: `type2.lean`
   - Pattern: Matches instructions like `%result = mul i32 %x, 1`
   - Proves that multiplying a number by one results in the same number

3. **Type 3: Multiplication by Zero** (x \* 0 = 0)
   - File: `type3.lean`
   - Pattern: Matches instructions like `%result = mul i32 %x, 0`
   - Proves that multiplying any number by zero results in zero

## Sample Output

```
Source function in Alive IR:
define i32 @f(i32 %x) {
#0:
  %r = add i32 %x, 0
  ret i32 %r
}

Target function in Alive IR:
define i32 @f(i32 %x) {
#0:
  ret i32 %x
}
Captured Output:
theorem zero_add : ∀ (x : Nat), 0 +ₘ x = x :=
fun x =>
  Nat.recAux (of_eq_true (eq_self 0))
    (fun x ih =>
      of_eq_true
        (Eq.trans (Eq.trans (congrArg (fun x_1 => x_1.succ = x + 1) ih) Nat.add_left_cancel_iff._simp_1) (eq_self 1)))
    x
ends[]


Analysis Result:
Proof Generated:


----------------------------------------
define i32 @f(i32 %x) {
#0:
  %r = add i32 %x, 0
  ret i32 %r
}
=>
define i32 @f(i32 %x) {
#0:
  ret i32 %x
}
Transformation seems to be correct!

Summary:
  1 correct transformations
  0 incorrect transformations
  0 failed-to-prove transformations
  0 Alive2 errors
```

## Architecture

<img width="1280" height="472" alt="image" src="https://github.com/user-attachments/assets/5491eb76-6aea-4777-b428-e5538bbd660b" />

   
## Dependencies

- Lean 4 (must be installed and available in PATH)
- Required Lean packages (managed through Lake):
  - mathlib
  - aesop
  - batteries
  - Other supporting packages

## Build Instructions

1. Ensure Lean is installed:
   ```bash
   which lean
   ```

2. Build the project:
   ```bash
   cd build
   cmake -G Ninja       -DLLVM_DIR=path-to-latest-llvm-build -DBUILD_TV=1 -DCMAKE_BUILD_TYPE=Release       ..
   ninja
   ```
3. Run with alive-tv:
     ```bash
     alive-tv src_add_0.ll tgt_add_0.ll
     ```



## Generated Proofs

Proofs are automatically generated and saved with the following naming convention:

```
proofs_generated/proof_YYYYMMDD_HHMMSS.txt
```

Each proof file contains:

- The captured output from Lean theorem prover
- Timestamp of generation
- Type of optimization proved


## Future Improvements

- [ ] Add more pattern matching rules
- [ ] Optimize the process of finding which standard optimzation to use. (Currently, we are bruteforcing)
- [ ] Extend Lean theorem proving capabilities
- [ ] Extend the proving capabilitis to other OS
