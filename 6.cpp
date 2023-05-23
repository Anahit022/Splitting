/*6.Implement a small program to parse 1.txt and 2.txt files and store the parsing results into a new file,
db.txt, Each line of the db.txt is one word parsed from 1.txt or 2.txt stored in the following format “word:1,2”,
where “word” is the actual word. The numbers are the names of the files that contain the word (if any of the
files have the word, their names should be placed after the colon).*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

void parseFilesAndSaveToDatabase(const std::string& file1, const std::string& file2, const std::string& outputFilename) {
    std::vector<std::string> words;

    // Parse file 1
    std::ifstream file1Stream(file1);
    if (!file1Stream.is_open()) {
        std::cerr << "Failed to open file: " << file1 << std::endl;
        return;
    }

    std::string word;
    while (file1Stream >> word) {
        words.push_back(word);
    }
    file1Stream.close();

    // Parse file 2
    std::ifstream file2Stream(file2);
    if (!file2Stream.is_open()) {
        std::cerr << "Failed to open file: " << file2 << std::endl;
        return;
    }

    while (file2Stream >> word) {
        words.push_back(word);
    }
    file2Stream.close();

    // Normalize words
    std::transform(words.begin(), words.end(), words.begin(), [](std::string& word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            if (c >= -1 && c <= 255) {
                // Character is within the valid range
                // Perform further checks or modifications if needed
                return !std::isalnum(c);
            }
            else {
                // Character is outside the valid range
                // Handle the error or take appropriate action
                return true;
            }
        }), word.end());

    std::transform(word.begin(), word.end(), word.begin(), [](char c) {
            return std::tolower(c);
        });

        return word;
    });

    // Create database file
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFilename << std::endl;
        return;
    }

    // Write word and file numbers to the database
    for (const std::string& word : words) {
        outputFile << word << ":" << file1 << "," << file2 << std::endl;
    }

    outputFile.close();
    std::cout << "Parsing results saved to " << outputFilename << std::endl;
}

int main() {
    std::string file1 = "1.txt";
    std::string file2 = "2.txt";
    std::string outputFilename = "db.txt";

    parseFilesAndSaveToDatabase(file1, file2, outputFilename);

    return 0;
}