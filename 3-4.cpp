/*3.Clean the words by removing special characters and converting them to lowercase.
4.Normalize the words using the words_alpha.txt dictionary.*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>


std::string removeSpecialCharacters(const std::string& word) {
    std::string cleanedWord;
    for (size_t i = 0; i < word.size(); i++) {
        char c = word[i];
        if (std::isalnum(c)) {
            cleanedWord += std::tolower(c);
        }
    }
    return cleanedWord;
}

std::string normalizeWord(const std::string& word) {
    std::ifstream dictionary("words_alpha.txt");
    if (!dictionary.is_open()) {
        std::cerr << "Failed to open dictionary file." << std::endl;
        return word;
    }

    std::string normalizedWord;
    std::string dictWord;
    while (dictionary >> dictWord) {
        if (dictWord == word) {
            normalizedWord = dictWord;
            break;
        }
    }

    dictionary.close();

    return normalizedWord.empty() ? word : normalizedWord;
}


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
            char c = line[i];
            if (c == ' ' || c == '\n') {
                if (!currentWord.empty()) {
                    std::string cleanedWord = removeSpecialCharacters(currentWord);
                    std::string normalizedWord = normalizeWord(cleanedWord);
                    words.push_back(normalizedWord);
                    currentWord.clear();
                }
            }
            else {
                currentWord += c;
            }
        }
        if (!currentWord.empty()) {
            std::string cleanedWord = removeSpecialCharacters(currentWord);
            std::string normalizedWord = normalizeWord(cleanedWord);
            words.push_back(normalizedWord);
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