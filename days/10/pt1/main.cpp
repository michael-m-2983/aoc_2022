#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <assert.h>
#include <chrono>
#include <random>
#include <regex>

int cycleCheck(int cycle, int x)
{
    int cyclea = cycle;
    if (cyclea == 20 || cyclea == 60 || cyclea == 100 || cyclea == 140 || cyclea == 180 || cyclea == 220)
    {
        return (x * cycle);
    }
    return 0;
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

    int cycle = 0;
    int x = 1;

    std::string line;

    int sum = 0;

    while (std::getline(file, line))
    {

        if (line.at(0) == 'a')
        {

            int n = std::stoi(line.substr(5));


            cycle++;

            sum += cycleCheck(cycle, x);

            cycle++;

            sum += cycleCheck(cycle, x);

            x += n;
        }
        else
        {
            cycle++;
            sum += cycleCheck(cycle, x);
        }
    }

    std::cout << sum << '\n';

    return 0;
}