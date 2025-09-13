# FindLean.cmake
# Finds the Lean theorem prover executable
#
# This will define:
#  LEAN_FOUND - True if Lean was found
#  LEAN_EXECUTABLE - The path to the Lean executable

find_program(LEAN_EXECUTABLE
  NAMES lean
  PATHS
  /usr/bin
  /usr/local/bin
  $ENV{HOME}/.elan/bin
  DOC "Path to Lean executable"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Lean
  REQUIRED_VARS LEAN_EXECUTABLE
)
