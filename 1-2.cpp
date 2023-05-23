/*1.Open a text file (lorem.txt) and read its contents into a string buffer.
2.Split the contents into words.*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

int main() {
    std::string inputFilename, outputFilename;
    std::cout << "Enter input filename: ";
    std::cin >> inputFilename;
    std::cout << "Enter output filename: ";
    std::cin >> outputFilename;

    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    std::vector<std::string> words;
    std::string currentWord;
    std::string line;

    while (std::getline(inputFile, line)) {
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == ' ' || line[i] == '\n') {
                if (!currentWord.empty()) {
                    words.push_back(currentWord);
                    currentWord.clear();
                }
            }
            else {
                currentWord += line[i];
            }
        }
        if (!currentWord.empty()) {
            words.push_back(currentWord);
            currentWord.clear();
        }
    }

    inputFile.close();

    std::ofstream outputFile("save.txt");

    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return 1;
    }

    for (const std::string& word : words) {
        outputFile << word << std::endl;
    }

    outputFile.close();

    std::cout << "Words extracted and saved to " << outputFilename << std::endl;
    return 0;
}
