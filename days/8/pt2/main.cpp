#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

int getInt(char c)
{
    return c - '0';
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

    std::map<int, std::map<int, int>> array;

    int count = 0;

    // std::cout << "asdfsdfasd\n";

    while (std::getline(file, line))
    {

        // std::cout << line << '\n';

        for (int count2 = 0; count2 < line.size(); count2++)
        {
            char c = line.at(count2);

            int integer = getInt(c);

            array[count][count2] = integer;
        }

        count++;
    }

    int max_scenic_score = 0;

    for (int i = 0; i < array.size(); i++)
    {
        for (int j = 0; j < array.size(); j++)
        {

            int score = 1;

            int left = 0;

            for (int k = j - 1; k >= 0; k--)
            {
                left++;
                if (array[i][k] >= array[i][j])
                {
                    break;
                }
            }

            score *= left;

            int right = 0;

            for (int k = j + 1; k < array.size(); k++)
            {
                right++;
                if (array[i][k] >= array[i][j])
                {
                    break;
                }
            }

            score *= right;

            int up = 0;

            for (int k = i - 1; k >= 0; k--)
            {
                up++;
                if (array[k][j] >= array[i][j])
                {
                    break;
                }
            }

            score *= up;

            int down = 0;

            for (int k = i + 1; k < array.size(); k++)
            {

                down++;

                if (array[k][j] >= array[i][j])
                {
                    break;
                }
            }

            score *= down;

            if (score > max_scenic_score)
            {
                max_scenic_score = score;
            }
        }
    }

    std::cout << "max=" << max_scenic_score << '\n';

    file.close();

    return 0;
}