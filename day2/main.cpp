#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <algorithm>

std::vector<std::string> fileToLines(std::string filename) {
    std::ifstream file(filename);

    std::vector<std::string> res;
    std::string line;

    while(std::getline(file, line)) {
        res.push_back(line);
    }

    return res;
}

std::vector<std::string> split_string(std::string S, char D)
{
    std::vector<std::string> V;
    std::string Buf = "";
    for (int i = 0; i < S.length(); i++)
    {
        if (S.at(i) == D)
        {
            V.push_back(Buf);
            Buf = "";
        }
        else
            Buf.append(1, S.at(i));
    }
    V.push_back(Buf);
    if (V[V.size() - 1] == "")
        V.pop_back();
    return V;
}

struct Game {
    int _id = 0;
    int _red = 0;
    int _blue = 0;
    int _green = 0;

    static Game fromInputString(std::string line) {
        Game res;

        std::regex id_and_input("Game (\\d+): (.*)");
        std::smatch m;
        std::regex_search(line, m, id_and_input);

        res._id = std::stoi(m[1]);
        std::vector<std::string> cubes = split_string(m[2].str(), ' ');

        for (int i = 1; i < cubes.size() - 1; i += 2) {
            cubes[i].pop_back();
        }

        for (int i = 0; i < cubes.size() - 1; i += 2) {
            if (cubes[i+1] == "red") {
                res._red = std::max(res._red, std::stoi(cubes[i]));
            } else if (cubes[i+1] == "blue") {
                res._blue = std::max(res._blue, std::stoi(cubes[i]));
            } else if (cubes[i+1] == "green") {
                res._green = std::max(res._green, std::stoi(cubes[i]));
            }
        }

        return res;
    }

    int isLegal(int red, int blue, int green) const {
        if (_red > red) return 0;
        if (_blue > blue) return 0;
        if (_green > green) return 0;
        return _id;
    }

    int power() const {
        return _red * _blue * _green;
    }
};

int main() {
    auto lines = fileToLines("input.txt");

    int part1 = 0;
    int part2 = 0;

    std::vector<Game> games;

    for (int i = 0; i < lines.size(); i++) {
        games.push_back(Game::fromInputString(lines[i]));
    }

    for (int i = 0; i < games.size(); i++) {
        part1 += games[i].isLegal(12, 14, 13);
        part2 += games[i].power();
    }

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;

    return 0;
}
