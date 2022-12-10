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

typedef std::map<int, std::map<int, bool>> Screen;

void cycleCheck(int cycle, int x, Screen &screen)
{
    screen[cycle / 40][cycle % 40] = 
        (cycle % 40 >= x - 1)
            && (cycle % 40 <= x + 1);
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

    std::map<int, std::map<int, bool>> screen;

    while (std::getline(file, line))
    {

        if (line.at(0) == 'a')
        {

            int n = std::stoi(line.substr(5));

            cycleCheck(cycle, x, screen);
            cycle++;

            cycleCheck(cycle, x, screen);
            cycle++;

            x += n;
        }
        else
        {
            cycleCheck(cycle, x, screen);
            cycle++;
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            std::cout << ((screen[i][j]) ? '#' : '-');
        }
        std::cout << '\n';
    }

    return 0;
}