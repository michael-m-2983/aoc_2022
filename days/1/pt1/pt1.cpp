#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
/**
 * made this on a chromebook using repl.it
 * 
 * not very proud of it, but it worked
 */
#include <string>

int main()
{
    std::ifstream file("day1_input.txt");

    std::deque<int> numbers;

    int curNum = 0;

    std::string line;
    while (std::getline(file, line))
    {
        if (line == "")
        {
            numbers.push_back(curNum);
            curNum = 0;
        }
        else
        {
            int number = std::stoi(line);

            curNum += number;
        }
    }

    int max = 0;

    for (int n : numbers)
    {
        if (n > max)
        {
            max = n;
        }
    }

    std::cout << max << '\n';

    file.close();
}