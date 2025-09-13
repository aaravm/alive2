add_library(lean
  pattern_match.cpp
)

target_link_libraries(lean PUBLIC
  ir
)

# Create proofs output directory in the lean folder
set(PROOFS_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proofs_generated")
file(MAKE_DIRECTORY ${PROOFS_OUTPUT_DIR})

# Pass the Lean paths to the compiler
target_compile_definitions(lean PRIVATE
  LEAN_EXECUTABLE="${LEAN_EXECUTABLE}"
  LEAN_PROJECT_PATH="${LEAN_PROJECT_PATH}"
  PROOFS_OUTPUT_DIR="${PROOFS_OUTPUT_DIR}")
