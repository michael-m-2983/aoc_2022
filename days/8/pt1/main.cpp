#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

int getInt(char c) {
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

    std::cout << "abc\n";

    while(std::getline(file, line)) {

        std::cout << line << '\n';

        for(int count2 = 0; count2 < line.size(); count2++) {
            char c = line.at(count2);

            // std::cout << "aaa->" << c << '\n';

            int integer = getInt(c);

            // std::cout << "aaa->" << integer << '\n';



            array[count][count2] = integer;

            // array[count][count2] = getInt(line.at(count2));
        }

        count++;
    }


    // actual solution

    int visible_count = 0;

    for(int i = 0; i < array.size(); i++) {
        for(int j = 0; j < array[i].size(); j++) {

            int visiblesides = 4;

            // left check
            for(int k = 0; k < j; k++) {
                if(array[i][k] >= array[i][j]) {
                    visiblesides--;
                    break;
                }
            }

            // right check
            for(int k = j + 1; k < array[i].size(); k++) {
                if(array[i][k] >= array[i][j]) {
                    visiblesides--;
                    break;
                }
            }

            // up check
            for(int k = 0; k < i; k++) {
                if(array[k][j] >= array[i][j]) {
                    visiblesides--;
                    break;
                }
            } 

            // down check
            for(int k = i + 1; k < array.size(); k++) {
                if(array[k][j] >= array[i][j]) {
                    visiblesides--;
                    break;
                }
            }

            if(visiblesides > 0) {
                visible_count++;
            }
        }
    }

    std::cout << "visible-count: " << visible_count << '\n';

    file.close();


    return 0;
}