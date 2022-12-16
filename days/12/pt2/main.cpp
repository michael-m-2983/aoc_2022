#include <iostream>
#include <string>
#include <deque>
#include <fstream>
#include <map>
#include <queue>
#include <assert.h>

typedef std::array<int, 2> coords;

typedef std::map<coords, int> grid_t;
typedef std::map<coords, bool> gridb_t;

int width, height;

bool valid(coords from, coords to, grid_t & grid) {
    // Bounds check
    if(to[0] < 0 || to[0] > width || to[1] < 0 || to[1] > height) {
        return false;
    }

    // Height check
    int from_value = grid.at(from), to_value = grid.at(to);

    if(to_value - 1 > from_value) {
        return false;
    }

    return true;
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

    grid_t grid;
    gridb_t bgrid;

    coords front, end;

    std::string line;
    int y = 0;

    while (std::getline(file, line))
    {
        width = line.size() - 1;
        int x = 0;
        for (char c : line)
        {

            bgrid[{x, y}] = false;

            switch(c) {
                case 'S':
                    front = {x, y};
                    grid[{x, y}] = 0;
                    break;
                case 'E':
                    end = {x, y};
                    grid[{x, y}] = 25;
                    break;
                default:
                    grid[{x, y}] = c - 'a';
                    break;
            }

            x++;
        }
        y++;
    }

    height = y - 1;

    std::queue<coords> coords_queue;


    for(auto pair : grid) {
        if(pair.second == 0) {
            coords_queue.push(pair.first);
        }
    }

    for(int round = 0 ;; round++) {
        std::cout << "round #" << round << " qsize=" << coords_queue.size() << '\n';
        std::queue<coords> tmp;

        if(coords_queue.empty()) {
            std::cerr << "something bad happened!\n";
            return 0;
        }

        while(!coords_queue.empty()) {
            coords current = coords_queue.front();
            coords_queue.pop();

            bgrid[current] = true;

            if(current[0] == end[0] && current[1] == end[1]) {
                file.close();
                std::cout << "answer=" << round << '\n';
                return 0;
            }

            coords left = {current[0] - 1, current[1]};
            coords right = {current[0] + 1, current[1]};
            coords up = {current[0], current[1] + 1};
            coords down = {current[0], current[1] - 1};

            std::array<coords, 4> adjacent = {left, right, up, down};

            for(coords c : adjacent) {
                if(valid(current, c, grid) && !bgrid.at(c)) {
                    tmp.push(c);
                    bgrid[c] = true;
                }
            }
        }


        while(!tmp.empty()) {
            coords_queue.push(tmp.front());
            tmp.pop();
        }
    }

    file.close();
    return 0;
}
