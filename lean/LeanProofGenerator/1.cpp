#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

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

int main() {
    try {
        std::string command = "lean --run MyProject.lean";
        std::string output = execCommand(command);

        std::cout << "Captured Output:\n" << output << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
