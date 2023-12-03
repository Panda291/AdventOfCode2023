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

struct Part {
    int part_number;
    int line;
    int offset;
    int length;
    bool valid;
};

struct Symbol {
    char symbol;
    int line;
    int offset;
    int first;
    int second;
    bool touched;
};

int main() {

    auto lines  = fileToLines("input.txt");

    std::vector<Part> parts;
    std::vector<Symbol> symbols;

    for (int i = 0; i < lines.size(); i++) {
        bool parsing_part = false;
        int part_offset;
        for (int j = 0; j < lines[i].size(); j++) {
            char current = lines[i][j];
            if (current >= '0' && current <= '9') {
                if (!parsing_part) {
                    parsing_part = true;
                    part_offset = j;
                }
            } else {
                if (current != '.') {
                    symbols.push_back({current, i, j, 0, 0, false});
                }
                if (parsing_part) {
                    parsing_part = false;
                    int part_length = j - part_offset;
                    int part_number = std::stoi(lines[i].substr(part_offset, part_length));
                    parts.push_back({part_number, i, part_offset, part_length, false});
                }
            }
        }
        if (parsing_part) {
            int part_length = lines[i].size() - part_offset;
            int part_number = std::stoi(lines[i].substr(part_offset, part_length));
            parts.push_back({part_number, i, part_offset, part_length, false});
        }
    }

    for (auto it1 = parts.begin(); it1 != parts.end(); ++it1) {
        for (auto it2 = symbols.begin(); it2 != symbols.end(); ++it2) {
            if (it1->line-1 <= it2->line && it1->line+1 >= it2->line // part is on line or adjacent line of symbol
                && it1->offset-1 <= it2->offset && (it1->offset + it1->length) >= it2->offset) { // symbol is in range of touching directly or diagonally
                it1->valid = true;
                if (!it2->touched) {
                    it2->first = it1->part_number;
                    it2->touched = true;
                } else it2->second = it1->part_number;
            }
        }
    }

    unsigned long long part1 = 0;
    unsigned long long part2 = 0;
    for (auto it1 = parts.begin(); it1 != parts.end(); ++it1) {
        if(it1->valid) part1 += it1->part_number;
    }
    for (auto it = symbols.begin(); it != symbols.end(); ++it) {
        part2 += it->first * it->second;
    }

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;

    return 0;
}
