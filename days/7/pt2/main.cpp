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

//https://iq.opengenus.org/split-string-in-cpp/
std::vector<std::string> split(std::string str, std::string deli = " ")
{
    std::vector<std::string> r;

    int start = 0;
    int end = str.find(deli);
    int i = 0;
    while (end != -1) {
        // cout << str.substr(start, end - start) << endl;
        if(i != 0) {
            r.push_back(str.substr(0, end) + "/");
        }
        start = end + deli.size();
        end = str.find(deli, start);
        i++;
    }
    // cout << str.substr(start, end - start);

    return r;
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

    std::string line;

    std::string current_dir;

    std::map<std::string, long> sizes;

    // int tmp = 0;

    while(std::getline(file, line)) {
        if(line.at(0) == '$') {
            if(line.at(2) == 'c') {
                std::string arg = line.substr(5);

                if(arg == "/") {
                    current_dir = arg;
                } else if(arg == "..") {
                    current_dir = current_dir.substr(0, current_dir.size() - 1);

                    int lslash = current_dir.find_last_of('/');

                    current_dir = current_dir.substr(0, lslash) + "/";
                } else {
                    current_dir += arg + "/";
                }
            }
            //  else if(line.at(2) == 'l') {
            // }
        } else {
            if(line.at(0) != 'd') {
                long amount = std::stol(line.substr(0, line.find(" ")));

                auto s = split(current_dir, "/");

                // std::cout << "\t" << current_dir << '\n';

                for(std::string str : s) {
                    // std::cout << "\t\t" << str << '\n';
                    sizes[str] += amount;
                }

                sizes["/"] += amount;

            }
        }
    }


    long m = 30000000 - (70000000 - sizes["/"]);

    long answer = 80000000;

    for(auto pair : sizes) {
        if(pair.second >= m && pair.second < answer) {
            answer = pair.second;
        }
    }


    std::cout << answer << '\n';
    

    return 0;
}