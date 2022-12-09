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

    std::string line;

    std::vector<std::vector<int>> rope;

    for(int i = 0; i < 10; i++) {
        std::vector<int> aaaaaaaaa;
        aaaaaaaaa.push_back(0);
        aaaaaaaaa.push_back(0);
        rope.push_back(aaaaaaaaa);
    }

    while (std::getline(file, line))
    {
        std::vector<int> base = getBaseDirection(line);

        int number = std::stoi(line.substr(2));

        for (int i = 0; i < number; i++)
        {
            head_x = rope[0][0];
            head_y = rope[0][1];

            rope[0][0] += base[0];
            rope[0][1] += base[1];

            for(int i = 1; i < rope.size(); i++) {
                std::vector<int> prev = rope[i - 1];
                std::vector<int> v = rope[i];

                int jx = v[0], jy = v[1];

                while(std::max(abs(jx - prev[0]), abs(jy - prev[1])) > 1) {
                    if(abs(jx - prev[0]) > 0) {
                        jx += (prev[0] > jx) ? 1 : -1;
                    }

                    if(abs(jy - prev[1]) > 0) {
                        jy += (prev[1] > jy) ? 1 : -1;
                    }
                }

                rope[i][0] = jx;
                rope[i][1] = jy;
            } 

            for(auto p : tail_positions) {
                if(rope[9][0] == p[0] && rope[9][1] == p[1]) goto end;
            }

            tail_positions.push_back(rope[9]);

            end:
            continue;
        }
    }

    std::cout << "answer=" << tail_positions.size() << '\n';

    return 0;
}