add_library(lean
  pattern_match.cpp
)

target_link_libraries(lean PUBLIC
  ir
)

# Pass the Lean paths to the compiler
target_compile_definitions(lean PRIVATE
  LEAN_EXECUTABLE="${LEAN_EXECUTABLE}"
  LEAN_PROJECT_PATH="${LEAN_PROJECT_PATH}")
