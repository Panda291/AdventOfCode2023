#include <iostream>
#include <vector>
#include <fstream>
#include <regex>


std::vector<std::string> fileToLines(std::string filename) {
    std::ifstream file(filename);

    std::vector<std::string> res;
    std::string line;

    while(std::getline(file, line)) {
        res.push_back(line);
    }

    return res;
}

std::string word_to_int_string(std::string word) {
    if (word == "one") {
        return "1";
    } else if (word == "two") {
        return "2";
    } else if (word == "three") {
        return "3";
    } else if (word == "four") {
        return "4";
    } else if (word == "five") {
        return "5";
    } else if (word == "six") {
        return "6";
    } else if (word == "seven") {
        return "7";
    } else if (word == "eight") {
        return "8";
    } else if (word == "nine") {
        return "9";
    } else if (word == "zero") {
        return "0";
    } else {
        return word;
    }
}

int main() {
    const auto lines = fileToLines("input.txt");

    int part1 = 0;
    int part2 = 0;

    for (int i = 0; i < lines.size(); i++) {
        std::string line = lines[i];
        std::regex first(".*?(\\d).*");
        std::regex last(".*(\\d).*");
        std::smatch f;
        std::smatch l;

        std::regex_match(line, f, first);
        std::regex_match(line, l, last);

        part1 += std::stoi(f[1].str() + l[1].str());

        std::regex first_words(".*?(one|two|three|four|five|six|seven|eight|nine|zero|\\d).*");
        std::regex last_words(".*(one|two|three|four|five|six|seven|eight|nine|zero|\\d).*");
        std::regex_match(line, f, first_words);
        std::regex_match(line, l, last_words);

        std::string fi = word_to_int_string(f[1]);
        std::string la = word_to_int_string(l[1]);

        part2 += std::stoi(fi + la);
    }

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
    return 0;
}
