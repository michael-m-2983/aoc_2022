#include <string>
#include <iostream>
#include <vector>
#include <fstream>
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

    std::string rsack_1, rsack_2, rsack_3;

    std::vector<char> dupes;

    int total = 0;

    while(std::getline(file, rsack_1) && std::getline(file, rsack_2) && std::getline(file, rsack_3)) {

        for(char c : rsack_1) {
            if(rsack_2.find(c) != std::string::npos) {
                dupes.push_back(c);
            }
        }

        for(char c : dupes) {
            if(rsack_3.find(c) != std::string::npos) {
                total += getValue(c);
                goto end;
            }
        }

        end:
        dupes.clear();
    }

    std::cout << "total=" << total << '\n';
}