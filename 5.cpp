/*5.Design classes Word and Text, where Text is a collection of Words, supporting all the functionality to 
efficiently create and add Words by removing special characters, converting them to lowercase letters, 
and normalizing the words.*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

class Word {
private:
    std::string title;
    std::string path;

public:
    Word(const std::string& title, const std::string& path) : title(title), path(path) {}

    const std::string& getTitle() const {
        return title;
    }

    const std::string& getPath() const {
        return path;
    }
};

class Text {
private:
    std::vector<Word> words;

public:
    void addWord(const std::string& title, const std::string& path) {
        words.emplace_back(title, path);
    }

    void removeSpecialCharacters(std::string& word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return !std::isalnum(c);
            }), word.end());
    }

    void convertToLowercase(std::string& word) {
        std::transform(word.begin(), word.end(), word.begin(), [](char c) {
            return std::tolower(c);
            });
    }

    void normalizeWord(std::string& word) {
        removeSpecialCharacters(word);
        convertToLowercase(word);
    }

    void addNormalizedWord(const std::string& title, const std::string& path) {
        std::string normalizedTitle = title;
        normalizeWord(normalizedTitle);
        addWord(normalizedTitle, path);
    }

    size_t getWordCount() const {
        return words.size();
    }

    const Word& getWordAt(size_t index) const {
        return words[index];
    }
};

int main() {
    Text text;

    text.addNormalizedWord("Hello,", "file1.txt");
    text.addNormalizedWord("WORLD!", "file2.txt");
    text.addNormalizedWord("Hello,", "file3.txt");

    std::cout << "Word Count: " << text.getWordCount() << std::endl;

    for (size_t i = 0; i < text.getWordCount(); ++i) {
        const Word& word = text.getWordAt(i);
        std::cout << "Title: " << word.getTitle() << ", Path: " << word.getPath() << std::endl;
    }

    return 0;
}
