#include <iostream>
#include <fstream>
using namespace std;

int char_to_color(char c) {
    if (c == 'r') {
        return 0;
    }
    if (c == 'g') {
        return 1;
    }
    if (c == 'b') {
        return 2;
    }
    return -1;
}

long long solve(const string& line) {
    int number = 0;
    int color = -1;
    /**    color  limit
    red      0      12
    green    1      13
    blue     2      14
    */
    int limit[] = {12, 13, 14};
    bool check = false;
    bool is_last_space = false;
    bool game = true;
    long long min_col[] = {-1, -1, -1};

    int i=0;
    for (const char& c: line) {
        //const char* add = c;
        //cout << (void *)(c) << "\n";
        // asci
        if (c == ' ' or i+1 == line.size()) {
            i++;
            /// Skip multiple spaces.
            if (is_last_space) {
                continue;
            }
            is_last_space = true;

            if (check) {
                /// Skip game number.
                if (game) {
                    game = false;
                    check = false;
                    number = 0;
                    continue;
                }
                /// COLOR ERROR
                if (color < 0) {
                    cout << "ERROR\n";
                    exit(-1);
                }
                /// Check if it is possible.
                if (min_col[color] < number) {
                    min_col[color] = number;
                }
                check = false;
                number = 0;
            } else {
                check = true;
            }
        } else {
            i++;
            /// Read input.
            if (check) {
                if (is_last_space) {
                    color = char_to_color(c);
                }
            } else {
                number = number*10 + c - '0';
            }
            is_last_space = false;
        }
    }
    return min_col[0]*min_col[1]*min_col[2];
}

int main(int argc, char *argv[]) {

    //char* ptr = reinterpret_cast<char*>(0x47);
    //(&ptr) = 14;
    //cout<<(*ptr);

    /// DEFAULT FILE NAMES
    string INPUT_NAME = "part1.in";
    string OUTPUT_NAME = "part1.out";

    /// GET FILE NAMES FROM COMMAND LINE
    if (argc == 2) {
        string name = argv[1];
        INPUT_NAME = name + ".in";
        OUTPUT_NAME = name + ".out";
    }

    if (argc == 3) {
        INPUT_NAME = argv[1];
        OUTPUT_NAME = argv[2];
    }

    /// OPEN INPUT
    ifstream input_file(INPUT_NAME);
    if (!input_file.is_open()) {
        cout << "Unable to open input file.\n";
        return -1;
    }

    /// OPEN OUTPUT
    ofstream output_file(OUTPUT_NAME);
    if (!output_file.is_open()) {
        cout << "Unable to open output file.\n";
        return -1;
    }

    /// SOLUTION
    string line;
    long long ans = 0;
    for (int i = 1; getline(input_file, line); i++) {
        ans+=solve(line);
    }
    input_file.close();

    output_file << ans << "\n";
    output_file.close();
    return 0;
}
