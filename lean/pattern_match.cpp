#include "lean/pattern_match.h"
#include <sstream>
#include <string>

namespace lean {

std::string analyzeAliveFunctions(const IR::Function *fn1, const IR::Function *fn2) {
  std::stringstream ss, fn1_ss, fn2_ss;
  // return fn1_ss;
  // Get full function representation
  fn1->print(fn1_ss);
  fn2->print(fn2_ss);
 
  ss << "Analysis of functions:\n";
  ss << "Source function name: " << fn1->getName() << "\n";
  ss << "Source function contents:\n" << fn1_ss.str() << "\n";
  ss << "Target function name: " << fn2->getName() << "\n";
  ss << "Target function contents:\n" << fn2_ss.str() << "\n";
  
  return ss.str();
}

// fn pattern_match(){
//     if(type==4){
//         my_project::exec_command1();
//     }
// }

} // namespace lean
