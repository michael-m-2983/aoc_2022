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

std::vector<int> getBaseDirection(std::string line)
{
    std::vector<int> nums;

    switch (line.at(0))
    {
    case 'U':
        nums.push_back(0);
        nums.push_back(1);
        break;
    case 'D':
        nums.push_back(0);
        nums.push_back(-1);
        break;
    case 'L':
        nums.push_back(-1);
        nums.push_back(0);
        break;
    case 'R':
        nums.push_back(1);
        nums.push_back(0);
        break;
    }

    return nums;
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

    int head_x = 0, head_y = 0;
    int tail_x = 0, tail_y = 0;

    std::vector<std::vector<int>> tail_positions;

    std::vector<int> abcdef;
    abcdef.push_back(0);
    abcdef.push_back(0);
    tail_positions.push_back(abcdef);

    std::string line;

    while (std::getline(file, line))
    {
        std::vector<int> base = getBaseDirection(line);

        int number = std::stoi(line.substr(2));

        for (int i = 0; i < number; i++)
        {
            head_x += base.at(0);
            head_y += base.at(1);

            while (std::max(abs(tail_x - head_x), abs(tail_y - head_y)) > 1)
            {
                if (abs(tail_x - head_x) > 0)
                {
                    tail_x += (head_x > tail_x) ? 1 : -1;
                }
                if (abs(tail_y - head_y) > 0)
                {
                    tail_y += (head_y > tail_y) ? 1 : -1;
                }

                std::vector<int> fsjdfkj;
                fsjdfkj.push_back(tail_x);
                fsjdfkj.push_back(tail_y);

                for (auto a : tail_positions)
                {
                    if (a.at(0) == tail_x && a.at(1) == tail_y)
                        goto end;
                }

                tail_positions.push_back(fsjdfkj);

            end:
                continue;
            }
        }
    }

    std::cout << "answer=" << tail_positions.size() << '\n';

    return 0;
}