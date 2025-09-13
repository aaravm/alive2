#include "lean/pattern_match.h"
#include <sstream>
#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <regex>

namespace lean {

// Function to execute a command and capture its stdout
std::string execCommand(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;

    // Open a pipe to the process
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");

    // Read until end of process
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    // Close the pipe
    int returnCode = pclose(pipe);
    if (returnCode != 0) {
        result += "\n[Process exited with code " + std::to_string(returnCode) + "]";
    }

    return result;
}

std::string analyzeAliveFunctions(const IR::Function *fn1, const IR::Function *fn2) {
    std::stringstream ss, fn1_ss, fn2_ss;
    // return fn1_ss;
    // Get full function representation
    fn1->print(fn1_ss);
    fn2->print(fn2_ss);

    // ss << "Analysis of functions:\n";
    // ss << "Source function name: " << fn1->getName() << "\n";
    // ss << "Source function contents:\n" << fn1_ss.str() << "\n";
    // ss << "Target function name: " << fn2->getName() << "\n";
    // ss << "Target function contents:\n" << fn2_ss.str() << "\n";
    ss << "Proof Generated:\n";

    // Regex patterns
    std::regex add_zero(R"(%\w+\s*=\s*add\s+i32\s+%\w+,\s*0)");
    std::regex mul_zero(R"(%\w+\s*=\s*mul\s+i32\s+%\w+,\s*0)");
    std::regex mul_one (R"(%\w+\s*=\s*mul\s+i32\s+%\w+,\s*1)");

    // Convert stringstream to string for regex search
    std::string fn1_content = fn1_ss.str();
    if (std::regex_search(fn1_content, add_zero)) {

        try {
            // Use the CMake-provided paths
            std::string command = std::string(LEAN_EXECUTABLE) + " --run " +
                                std::string(LEAN_PROJECT_PATH) + "/type1.lean";
            std::string output = execCommand(command);

            std::cout << "Captured Output:\n" << output << std::endl;

            // Generate a timestamp for the filename
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            std::stringstream ss_time;
            ss_time << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S");
            std::string timestamp = ss_time.str();

            // Use the CMake-provided output directory
            std::string filename = std::string(PROOFS_OUTPUT_DIR) + "/proof_" + timestamp + ".txt";

            // Save the output to a file
            std::ofstream outfile(filename);
            if (outfile.is_open()) {
                outfile << output;
                outfile.close();
            } else {
                std::cerr << "Error: Unable to open file for writing: " << filename << "\n";
            }

        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }

    } else if (std::regex_search(fn1_content, mul_one)) { //type2 : x * 1 = x
        try {
            std::string command = std::string(LEAN_EXECUTABLE) + " --run " +
                                std::string(LEAN_PROJECT_PATH) + "/type2.lean";
            std::string output = execCommand(command);

            std::cout << "Captured Output:\n" << output << std::endl;

            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            std::stringstream ss_time;
            ss_time << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S");
            std::string timestamp = ss_time.str();

            std::string filename = std::string(PROOFS_OUTPUT_DIR) + "/proof_" + timestamp + ".txt";
            std::ofstream outfile(filename);
            if (outfile.is_open()) {
                outfile << output;
                outfile.close();
            } else {
                std::cerr << "Error: Unable to open file for writing: " << filename << "\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    } else if (std::regex_search(fn1_content, mul_zero)) { //type3 : x * 0 = 0
        try {
            std::string command = std::string(LEAN_EXECUTABLE) + " --run " +
                                std::string(LEAN_PROJECT_PATH) + "/type3.lean";
            std::string output = execCommand(command);

            std::cout << "Captured Output:\n" << output << std::endl;

            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            std::stringstream ss_time;
            ss_time << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S");
            std::string timestamp = ss_time.str();

            std::string filename = std::string(PROOFS_OUTPUT_DIR) + "/proof_" + timestamp + ".txt";
            std::ofstream outfile(filename);
            if (outfile.is_open()) {
                outfile << output;
                outfile.close();
            } else {
                std::cerr << "Error: Unable to open file for writing: " << filename << "\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }

    // Always return the analysis string, regardless of whether the pattern matched
    return ss.str();
}

// fn pattern_match(){
//     if(type==4){
//         my_project::exec_command1();
//     }
// }

} // namespace lean
