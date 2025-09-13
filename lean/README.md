# Lean Integration in Alive2

This directory contains the Lean theorem prover integration for Alive2, which is used to formally verify compiler optimizations.

## Overview

The Lean integration provides formal mathematical proofs for various compiler optimization patterns. Currently, it handles three main types of optimizations:

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

## Dependencies

- Lean Theorem Prover
- CMake for build configuration
- C++ compiler with C++11 support

## Usage

The Lean integration is automatically invoked when analyzing LLVM IR optimizations. The pattern matcher will:

1. Identify the optimization pattern
2. Run the corresponding Lean proof
3. Generate and save the proof file
4. Return analysis results

The proof files can be found in the configured output directory with timestamps indicating when they were generated.
