#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int solve(const vector<string>& table) {
    const int ROWS = table.size();
    const int COLS = table[0].size();
    bool is_gal_row[ROWS] = {};
    bool is_gal_col[COLS] = {};

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (table[r][c] == '#') {
                is_gal_row[r] = true;
                is_gal_col[c] = true;
            }
        }
    }

    vector<pair<int, int> > galaxies;

    int dr = 0, dc = 0;
    for (int r = 0; r < ROWS; r++) {
        if (!is_gal_row[r]) {
            dr++;
            continue;
        }
        dc = 0;
        for (int c = 0; c < COLS; c++) {
            if (!is_gal_col[c]) {
                dc++;
                continue;
            }
            if (table[r][c] == '#') {
                galaxies.push_back({r+dr, c+dc});
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            ans = ans + abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second);
        }
    }

    return ans;
}

int main(int argc, char *argv[]) {
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
        cout << "Unable to open input file " << INPUT_NAME << ".\n";
        return -1;
    }

    /// OPEN OUTPUT
    ofstream output_file(OUTPUT_NAME);
    if (!output_file.is_open()) {
        cout << "Unable to open output file " << OUTPUT_NAME << ".\n";
        return -1;
    }

    /// SOLUTION
    vector<string> input;
    string line;
    long long ans = 0;
    while (getline(input_file, line)) {
        input.push_back(line);
    }
    input_file.close();

    output_file << solve(input) << "\n";
    output_file.close();
    return 0;
}
