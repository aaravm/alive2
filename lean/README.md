# Lean Integration for Alive2

This directory contains the integration between Alive2 and the Lean theorem prover, enabling formal verification and proof generation for LLVM IR transformations.

This is a small pipeline to turn easily-detected IR optimizations into human- or machine-checkable proof witnesses in Lean. Example: detect `%r = add i32 %x, 0` in IR → emit a Lean theorem `x + 0 = x` and print it. This repo shows a minimal, practical way to do that.

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


## How It Works

1. The system analyzes LLVM IR functions using pattern matching (`pattern_match.cpp`)
2. When a pattern is detected, it runs the corresponding Lean proof file
3. The proof output is captured and saved to a timestamped file in the `proofs_generated` directory

## Generated Proofs

Proofs are automatically generated and saved with the following naming convention:

```
proofs_generated/proof_YYYYMMDD_HHMMSS.txt
```

Each proof file contains:

- The captured output from Lean theorem prover
- Timestamp of generation
- Type of optimization proved

## Configuration

The system uses several CMake-provided variables:

- `LEAN_EXECUTABLE`: Path to the Lean executable
- `LEAN_PROJECT_PATH`: Path to the directory containing Lean proof files
- `PROOFS_OUTPUT_DIR`: Directory where generated proofs are stored


## Usage

1. **Pattern Detection**:
   ```cpp
   lean::analyzeAliveFunctions(fn1, fn2);
   ```
   This function analyzes LLVM IR functions and detects patterns requiring verification.

2. **Proof Generation**:
   - When a pattern is detected, the system automatically:
     - Calls the appropriate Lean proof generator
     - Saves the proof output with timestamp
     - Returns analysis results

3. **Testing**:
   - Use test files from `Testing_files/` directory
   - Run with alive-tv:
     ```bash
     alive-tv src_add_0.ll tgt_add_0.ll
     ```

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
   cmake -DLLVM_DIR=/path/to/llvm/cmake -DBUILD_TV=1 ..
   ninja
   ```

## Future Improvements

- [ ] Add more pattern matching rules
- [ ] Enhance proof generation capabilities
- [ ] Improve error handling and reporting
- [ ] Add more comprehensive test cases
- [ ] Extend Lean theorem proving capabilities

## Contributing

1. Follow the existing code structure
2. Add tests for new functionality
3. Update documentation accordingly
4. Ensure all tests pass before submitting changesk
