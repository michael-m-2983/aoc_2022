#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stack>
#include <sstream>

std::vector<int> getNumbers(std::string str)
{
    std::stringstream ss;

    ss << str;

    std::string temp;
    int found;

    std::vector<int> ints;

    while (!ss.eof())
    {

        ss >> temp;

        if (std::stringstream(temp) >> found)
            ints.push_back(found);

        temp = "";
    }
    return ints;
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

    std::vector<std::stack<char>> stacks;

    std::vector<std::vector<char>> stack_orig;

    std::string line;

    for (int i = 0; i < 9; i++)
    {
        stacks.push_back(std::stack<char>());
        stack_orig.push_back(std::vector<char>());
    }

    while (std::getline(file, line) && line.at(1) != '1')
    {

        int index = 0;

        for (int i = 0; i < 9; i++)
        {
            if (line.at(index) != '[')
            {
                index += 4;
                continue;
            }

            index++; // skip [

            stack_orig.at(i).push_back(line.at(index++));

            index += 2; // skip ] and the space
        }
    }

    std::getline(file, line); // skip the blank line

    for (int i = 0; i < 9; i++)
    {
        std::vector<char> vec = stack_orig.at(i);
        std::reverse(vec.begin(), vec.end());

        for (char c : vec)
        {
            stacks.at(i).push(c);
        }
    }

    // finally, its setup

    while (std::getline(file, line))
    {
        // move 7 from 6 to 8

        auto nums = getNumbers(line);

        int times = nums[0];
        int from = nums[1] - 1;
        int to = nums[2] - 1;

        for (int i = 0; i < times; i++)
        {
            char value = ' ';

            value = stacks.at(from).top();

            stacks.at(from).pop();
            stacks.at(to).push(value);
        }
    }

    // Print out the result!

    std::cout << "answer: ";

    for (auto stack : stacks)
    {
        std::cout << stack.top();
    }

    std::cout << '\n';

    file.close();

    return 0;
}