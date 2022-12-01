#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " input_file\n";
        exit(1);
    }

    std::string file_name = std::string(argv[1]);

    std::ifstream file(file_name);

    if(!file) {
        std::cerr << "File '" << file_name << "' does not exist or is not readable!\n";
        exit(2);
    }

    std::vector<int> totals;
    int current = 0;

    std::string s;
    while (std::getline(file, s)) {
        if(s == "") {
            totals.push_back(current);
            current = 0;
        } else {
            current += std::stoi(s);
        }
    }

    std::sort(totals.begin(), totals.end(), std::greater<int>());

    std::cout << "Elf 1: " << totals.at(0) << " (pt 1 answer)\n";
    std::cout << "Elf 2: " << totals.at(1) << '\n';
    std::cout << "Elf 3: " << totals.at(2) << '\n';

    std::cout << "Final Answer: " 
              << (totals.at(0) + totals.at(1) + totals.at(2)) << '\n';

    file.close();
}