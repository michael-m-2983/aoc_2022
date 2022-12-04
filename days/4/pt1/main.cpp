#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

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

    std::string s;
    int count = 0;

    while (std::getline(file, s))
    {
        int sepIndex = s.find(',');

        std::string elf1 = s.substr(0, sepIndex);
        std::string elf2 = s.substr(sepIndex + 1, s.size());

        int elf1_spos = elf1.find('-');
        int elf1_min = std::stoi(elf1.substr(0, elf1_spos));
        int elf1_max = std::stoi(elf1.substr(elf1_spos + 1, elf1.size()));

        int elf2_spos = elf2.find('-');
        int elf2_min = std::stoi(elf2.substr(0, elf2_spos));
        int elf2_max = std::stoi(elf2.substr(elf2_spos + 1, elf2.size()));

        if((elf1_min <= elf2_min && elf1_max >= elf2_max) || (elf1_min >= elf2_min && elf1_max <= elf2_max)) {
            count++;
        }
    }

    std::cout << "count=" << count << '\n';

    return 0;
}