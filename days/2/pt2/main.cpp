#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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
        char needed_result = line.at(2);

        int round_points = 0;

        // X means you need to lose, Y means you need to end the round in a draw,
        // and Z means you need to win.

        char your_move;

        switch (opponent_move)
        {
        case 'A':
            switch (needed_result)
            {
            case 'X': // lose
                your_move = 'Z';
                break;
            case 'Y': // draw
                round_points += 3;
                your_move = 'X';
                break;
            case 'Z': // win
                round_points += 6;
                your_move = 'Y';
                break;
            }
            break;
        case 'B':
            switch (needed_result)
            {
            case 'X': // lose
                your_move = 'X';
                break;
            case 'Y': // draw
                round_points += 3;
                your_move = 'Y';
                break;
            case 'Z': // win
                round_points += 6;
                your_move = 'Z';
                break;
            }
            break;
        case 'C':
            switch (needed_result)
            {
            case 'X': // lose
                your_move = 'Y';
                break;
            case 'Y': // draw
                round_points += 3;
                your_move = 'Z';
                break;
            case 'Z': // win
                round_points += 6;
                your_move = 'X';
                break;
            }
            break;
        }

        switch (your_move)
        {
        case 'X':
            round_points += 1;
            break;
        case 'Y':
            round_points += 2;
            break;
        case 'Z':
            round_points += 3;
            break;
        }

        total_points += round_points;
    }

    std::cout << "answer=" << total_points << '\n';

    file.close();
}