#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int getValue(char c) {
    int index = 1;

    for(char sfjasf : alphabet) {
        if(sfjasf == c) {
            return index;
        }
        index++;
    }

    std::cerr << "unknown letter '" << c << "'.";

    exit(1);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " input_file\n";
        exit(1);
    }

    std::string file_name = std::string(argv[1]);

    std::ifstream file(file_name);

    if (!file)
    {
        std::cerr << "File '" << file_name << "' does not exist or is not readable!\n";
        exit(2);
    }

    int total = 0;
    int index = 0;

    std::vector<char> potential_badges;

    std::string s;
    while (std::getline(file, s)) {
        int length = s.size();

        std::string rucksack_1 = s.substr(0, length / 2);
        std::string rucksack_2 = s.substr((length / 2), length);

        for(char c : rucksack_1) {
            for(char cj : rucksack_2) {
                if(cj == c) {
                    total += getValue(c);

                    goto endofloop;
                }
            }
            
            index += 0;
        }

        endofloop:
        total += 0; // this line is just so i can jump out of both loops. 
    }

    std::cout << "total=" << total << '\n';

    file.close();
}