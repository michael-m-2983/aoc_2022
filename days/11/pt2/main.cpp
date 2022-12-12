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
#include <numeric>
#include <functional>

struct Monkey {
    std::deque<long> items;
    bool add = true; // true=add, false=multiply
    int wchngamt = 0;
    bool stupid = false;
    long div_test = -1;
    int true_monkey = -1;
    int false_monkey = -1;
    long items_inspected = 0;
};

std::deque<long> getStartingItems(std::string in) {

    // in is a copy
    in = in.substr(18);

    std::deque<long> r;
    std::string curr;
    
    for(int i = 0; i < in.size(); i++) {
        if(in[i] == ',') {
            r.push_back(std::stol(curr));
            curr = "";
            i++;
            continue;
        } else {
            curr += in[i];
        }
    }

    r.push_back(std::stoi(curr));

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

    std::vector<std::string> lines;

    int lsize = 0;

    std::string s;
    while(std::getline(file, s)) {
        lines.push_back(s);
        lsize++;
    }

    // think of this as an array
    std::map<int, Monkey> monkies;


    for(int i = 0; i < 8; i++) {
        int base_line = (7 * i);

        monkies[i] = Monkey();
        monkies[i].items = getStartingItems(lines[base_line + 1]);
        monkies[i].add = lines[base_line + 2][23] == '+';
        if(isdigit(lines[base_line + 2][25])) {
            monkies[i].wchngamt = std::stoi(lines[base_line + 2].substr(25));
        } else {
            monkies[i].stupid = true;
        }
        monkies[i].div_test = std::stol(lines[base_line + 3].substr(21));

        monkies[i].true_monkey = std::stoi(lines[base_line + 4].substr(29));
        monkies[i].false_monkey = std::stoi(lines[base_line + 5].substr(30));
    }

    std::vector<long> worries;

    for(auto pair : monkies) {
        worries.push_back(pair.second.div_test);
    }

    long product = std::accumulate(worries.begin(), worries.end(), 1, std::multiplies<long>{});

    for(int round = 0; round < 10000; round++) {
        for(auto & pair : monkies) {
            auto& monkey = pair.second;

            for(long item : monkey.items) {

                monkey.items_inspected++;

                if(monkey.add) {
                    item += monkey.stupid ? item : monkey.wchngamt;
                } else {
                    item *= monkey.stupid ? item : monkey.wchngamt;
                }

                // std::cout << "before: \e[35m" << item << "\e[39m\n";                
                item %= product;
                // std::cout << "after: \e[95m" << item << "\e[39m\n";    


                double d = item % monkey.div_test;

                monkey.items.pop_front();
                monkies[d == 0.00 ? monkey.true_monkey : monkey.false_monkey].items.push_back(item);
            }
        }
    }

    std::vector<long> productivity;

    for(auto m : monkies) {
        productivity.push_back(m.second.items_inspected);
    }

    std::sort(productivity.begin(), productivity.end(), std::greater<long>());

    long answer = productivity.at(0) * productivity.at(1);

    std::cout << answer << '\n';

    return 0;
}