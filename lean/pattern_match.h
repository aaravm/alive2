#pragma once

#include "ir/function.h"
#include <string>

namespace lean {
  std::string analyzeAliveFunctions(const IR::Function *fn1, const IR::Function *fn2);
}