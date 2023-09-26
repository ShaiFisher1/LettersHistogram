#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cctype>
#include <chrono>

constexpr int NUM_LETTERS = 26;
constexpr const char *PATH = "/usr/share/dict/words";


/**
 * Count the number of occurrences of each letter in the file
 * @param file
 * @param histogram will contains the number of occurrences of each letter
 */
std::array<int, NUM_LETTERS> countLetters(std::ifstream &file) {
    std::array<int, NUM_LETTERS> histogramResult{};
    std::string line;
    while (std::getline(file, line)) {
        for (char letter : line) {
            if (std::isalpha(letter)) {
                char lowercaseLetter = static_cast<char> (std::tolower(letter));
                histogramResult[lowercaseLetter - 'a']++;

            }
        }
    }
    return histogramResult;
}


namespace simpleHistogram {
    /**
     * given a file containing words one per line, produces a histogram of the letters
     * @param file_path
     * @return histogram of the letters
     */
    std::array<int, NUM_LETTERS> histogram(const std::string &file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file in the location: " + file_path);
        }
        return countLetters(file);
    }
}


/**
 * prints the histogram
 */
void printSimpleHistogram() {
    std::array<int, NUM_LETTERS> histogramResult = simpleHistogram::histogram(PATH);
    for (int i = 0; i < NUM_LETTERS; ++i) {
        char letter = static_cast<char>('a' + i);
        std::cout << letter << ": " << histogramResult[i] << std::endl;
    }

}


// int main() {
//     printSimpleHistogram();
// }