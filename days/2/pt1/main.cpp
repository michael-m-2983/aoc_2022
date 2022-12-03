#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

/**
 * Look out, this code has a lot of round points!
 *
 * note: I took this off of repl.it after doing both parts, then removed the code that solves part 2.
 */

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

    // A & X = Rock
    // B & Y = Paper
    // C & Z = Cutting thingy

    int total_points = 0;

    std::string line;
    while (std::getline(file, line))
    {
        char opponent_move = line.at(0);
        char your_move = line.at(2);

        int round_points = 0;

        switch (your_move)
        {
        case 'X':
            round_points += 1;

            switch (opponent_move)
            {
            case 'A': // draw
                round_points += 3;
                break;
            case 'B': // loss
                break;
            case 'C': // win
                round_points += 6;
                break;
            }

            break;
        case 'Y':
            round_points += 2;

            switch (opponent_move)
            {
            case 'A': // win
                round_points += 6;
                break;
            case 'B': // draw
                round_points += 3;
                break;
            case 'C': // loss
                break;
            }

            break;
        case 'Z':
            round_points += 3;

            switch (opponent_move)
            {
            case 'A': // loss
                break;
            case 'B': // win
                round_points += 6;
                break;
            case 'C': // draw
                round_points += 3;
                break;
            }

            break;
        }

        total_points += round_points;
    }

    std::cout << "answer=" << total_points << '\n';

    file.close();
}