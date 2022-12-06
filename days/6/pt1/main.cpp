#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <deque>

template <typename T>
bool is_unique(std::deque<T> vec)
{
    std::sort(vec.begin(), vec.end());
    return std::unique(vec.begin(), vec.end()) == vec.end();
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

    std::deque<char> values;

    std::string content;

    std::getline(file, content);

    for(int i = 0; i < content.size(); i++) {
        char c = content.at(i);

        if(values.size() >= 4) {
            values.pop_front();
        }

        values.push_back(c);

        if(values.size() < 4) continue;

        if(is_unique(values)) {
            std::cout << "answer=" << (i + 1) << '\n';
            return 0;
        }
    }


    return 0;
}