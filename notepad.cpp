#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

class Notepad {
public:
    Notepad() {
        // Initialize the notepad
    }

    void run() {
        while (true) {
            displayMenu();
            int choice;
            std::cin >> choice;
            handleUserChoice(choice);
        }
    }

private:
    void displayMenu() {
        std::cout << "--- Notepad Menu ---" << std::endl;
        std::cout << "1. Create New File" << std::endl;
        std::cout << "2. Open Existing File" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Choose an option: ";
    }

    void handleUserChoice(int choice) {
        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                openFile();
                break;
            case 3:
                exit(0);
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    }

    void createFile() {
        std::string filename;
        std::cout << "Enter the name of the file to create: ";
        std::cin >> filename;
        std::ofstream outfile(filename);
        if (!outfile) {
            std::cerr << "Error creating file: " << filename << std::endl;
            return;
        }
        std::string content;
        std::cin.ignore(); // Clear the newline
        std::cout << "Enter content (end with EOF): " << std::endl;
        while (std::getline(std::cin, content)) {
            outfile << content << std::endl;
        }
        outfile.close();
        std::cout << "File created successfully: " << filename << std::endl;
    }

    void openFile() {
        std::string filename;
        std::cout << "Enter the name of the file to open: ";
        std::cin >> filename;
        std::ifstream infile(filename);
        if (!infile) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
        std::string line;
        std::cout << "--- Content of " << filename << " ---" << std::endl;
        while (std::getline(infile, line)) {
            std::cout << line << std::endl;
        }
        infile.close();
    }
};

int main() {
    try {
        Notepad notepad;
        notepad.run();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    return 0;
}