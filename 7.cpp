/*7.Modify the program and add a simple console user interface for the user to search for a word. The user types
a word and the program searches for it in the db.txt and responds with the file names that contain the word.*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector <std::string> getFileNumbers(const std::string& line) {
    std::vector<std::string> fileNumbers;

    // Find the position of the colon (":")
    size_t colonPos = line.find(':');
    if (colonPos != std::string::npos) {
        // Extract the file numbers substring
        std::string fileNumbersStr = line.substr(colonPos + 1);

        // Split the file numbers by commas (",")
        size_t commaPos = fileNumbersStr.find(',');
        size_t startPos = 0;
        while (commaPos != std::string::npos) {
            std::string fileNumber = fileNumbersStr.substr(startPos, commaPos - startPos);
            fileNumbers.push_back(fileNumber);
            startPos = commaPos + 1;
            commaPos = fileNumbersStr.find(',', startPos);
        }

        // Add the last file number
        std::string lastFileNumber = fileNumbersStr.substr(startPos);
        fileNumbers.push_back(lastFileNumber);
    }

    return fileNumbers;
}

void searchWordInDatabase(const std::string& databaseFile) {
    std::string word;
    std::cout << "Enter a word to search: ";
    std::cin >> word;

    std::ifstream database(databaseFile);
    if (!database.is_open()) {
        std::cerr << "Failed to open database file: " << databaseFile << std::endl;
        return;
    }

    std::string line;
    bool found = false;
    while (std::getline(database, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string wordInDatabase = line.substr(0, colonPos);
            if (wordInDatabase == word) {
                std::vector<std::string> fileNumbers = getFileNumbers(line);
                if (!fileNumbers.empty()) {
                    std::cout << "Word found in the following files: ";
                    for (const std::string& fileNumber : fileNumbers) {
                        std::cout << fileNumber << " ";
                    }
                    std::cout << std::endl;
                    found = true;
                }
            }
        }
    }

    if (!found) {
        std::cout << "Word not found in the database." << std::endl;
    }

    database.close();
}

int main() {
    std::string databaseFile = "db.txt";

    // Prompt the user for word search
    searchWordInDatabase(databaseFile);

    return 0;
}