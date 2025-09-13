add_library(lean
  pattern_match.cpp
)

target_link_libraries(lean PUBLIC
  ir
)
