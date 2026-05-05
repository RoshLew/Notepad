#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// Function to clear input stream
void clearInputStream() {
    std::cin.clear(); // Clear the fail state
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
}

// Class to manage file operations with RAII
class FileManager {
public:
    explicit FileManager(const std::string& filename) : fileStream(filename) {
        if (!fileStream.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }
    ~FileManager() {}
    std::ifstream& getStream() { return fileStream; }
private:
    std::ifstream fileStream;
};

void readFile(const std::string& filename) {
    FileManager fileManager(filename);
    std::string line;
    while (std::getline(fileManager.getStream(), line)) {
        std::cout << line << '\n';
    }
}

int main() {
    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;

    // Input validation
    if (filename.empty()) {
        std::cerr << "Filename cannot be empty." << std::endl;
        clearInputStream();
        return 1;
    }

    try {
        readFile(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}