#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <array>
#include <cctype>
#include <vector>
#include <stdexcept>

constexpr int NUM_OF_LETTERS = 26;
constexpr int NUM_OF_WORKERS = 10;
constexpr char NULL_TERMINATOR = '\0';
constexpr const char *FILE_PATH = "/usr/share/dict/words";

/**
 * Count the number of occurrences of each letter in a text
 * @param text
 * @param histogram contains the number of occurrences of each letter
 */
void countLetters(const std::string &text, std::array<int, NUM_OF_LETTERS> &histogram) {
    for (char letter : text) {
        if (std::isalpha(letter)) {
            char lowercaseLetter = static_cast<char> (std::tolower(letter));
            histogram[lowercaseLetter - 'a']++;
        }
    }
}

/**
 * given a file, calculates the size of a segment that divides the file evenly
 * @param filePath
 * @param numParts the number of parts to divide the file to
 * @return size of each segment
 */
int getSegmentSize(std::ifstream &file, int numSegments) {
    file.seekg(0, std::ios::end);
    const int fileSize = static_cast<int>(file.tellg());
    file.seekg(0, std::ios::beg);
    int segmentSize = fileSize / numSegments;
    return segmentSize;
}

/**
 * given a file, divides the content of the file to equal segments
 * @param file_path
 * @param numSegments
 * @return
 */
std::vector<std::string> divideFileContentToEqualSegments(const std::string &filePath, const int numSegments) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file in the location: " + filePath);
    }

    int segmentSize = getSegmentSize(file, numSegments);
    std::vector<std::string> content(numSegments);

    // create the segments for each worker
    for (int segment = 0; segment < numSegments; ++segment) {

        std::string segmentContent(segmentSize, NULL_TERMINATOR);

        // the last worker handles remaining words
        if (segment == numSegments - 1) {
            std::getline(file, segmentContent, NULL_TERMINATOR);
        } else {
            file.read(&segmentContent[0], segmentSize);
        }
        content[segment] = segmentContent;
    }
    return content;
}

namespace parallelHistogram {
    /**
     * given a file containing words one per line, produces a histogram of the letters
     * @param file_path
     * @return histogram of the letters
     */
    std::array<int, NUM_OF_LETTERS> histogram(const std::string &file_path) {
        std::vector<std::thread> workers;
        std::vector<std::array<int, NUM_OF_LETTERS>> histograms(NUM_OF_WORKERS);
        std::vector<std::string> content = divideFileContentToEqualSegments(file_path, NUM_OF_WORKERS);

        // initiate workers
        for (int worker = 0; worker < NUM_OF_WORKERS; ++worker) {
            workers.emplace_back([&content, &histograms, worker]() {
                countLetters(content[worker], histograms[worker]);
            });
        }

        for (auto &worker : workers) {
            worker.join();
        }

        // merge local histograms
        std::array<int, NUM_OF_LETTERS> mergedHistogram{};
        for (auto &histogram : histograms) {
            for (int letter = 0; letter < NUM_OF_LETTERS; ++letter) {
                mergedHistogram[letter] += histogram[letter];
            }
        }
        return mergedHistogram;
    }
}

/**
 * prints the histogram
 */
void printParallelHistogram() {
    std::array<int, NUM_OF_LETTERS> histogramResult = parallelHistogram::histogram(FILE_PATH);
    for (int i = 0; i < NUM_OF_LETTERS; ++i) {
        char letter = static_cast<char>('a' + i);
        std::cout << letter << ": " << histogramResult[i] << std::endl;
    }
}


// int main() {
//     printParallelHistogram();
// }