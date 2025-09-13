# Lean Proof Generator

This component generates and stores formal proofs for LLVM optimizations using the Lean theorem prover.

## Overview

The Lean Proof Generator analyzes LLVM IR functions and generates formal proofs for various optimization patterns. Each proof is stored in a timestamped file within the `proofs_generated` directory.

## Supported Optimization Patterns

Currently, the system supports proof generation for three types of optimizations:

1. **Type 1: Addition with Zero** (`x + 0 = x`)

   - Pattern: `%result = add i32 %x, 0`
   - Proof file: `type1.lean`

2. **Type 2: Multiplication by One** (`x * 1 = x`)

   - Pattern: `%result = mul i32 %x, 1`
   - Proof file: `type2.lean`

3. **Type 3: Multiplication by Zero** (`x * 0 = 0`)
   - Pattern: `%result = mul i32 %x, 0`
   - Proof file: `type3.lean`

## Proof Generation Process

1. The system analyzes the input LLVM IR function using regex patterns to identify the optimization type.
2. Once identified, it runs the corresponding Lean proof file (type1.lean, type2.lean, or type3.lean).
3. The proof output is captured and stored in a uniquely named file:
   ```
   proofs_generated/proof_YYYYMMDD_HHMMSS.txt
   ```
   where YYYYMMDD_HHMMSS is the timestamp when the proof was generated.

## File Structure

- `/proofs_generated/` - Directory containing all generated proof files
- `type1.lean` - Proof template for x + 0 = x
- `type2.lean` - Proof template for x \* 1 = x
- `type3.lean` - Proof template for x \* 0 = 0

## Output Format

Each proof file contains:

- The captured output from the Lean theorem prover
- Timestamp of generation
- Type of optimization proved
- Any error messages if the proof generation failed

## Example

For an optimization that simplifies `%1 = add i32 %x, 0` to `%x`, the system will:

1. Identify it as a Type 1 pattern
2. Execute type1.lean
3. Generate a file like `proof_20250913_143022.txt` containing the formal proof

## Configuration

The proof generator uses several CMake-provided paths:

- `LEAN_EXECUTABLE` - Path to the Lean executable
- `LEAN_PROJECT_PATH` - Path to the Lean project files
- `PROOFS_OUTPUT_DIR` - Directory where proof files are stored
