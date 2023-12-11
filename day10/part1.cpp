#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

bool is_in_table(int num, int lim) {
    return num >= 0 and num < lim;
}

pair<int, int> other_ngbr(const vector<string>& table, pair<int, int> curr, pair<int, int> last) {
    const int ROWS = table.size();
    const int COLS = table[0].size();

    char pipes[7] = "|-LJ7F";
    pair<int, int> delta_ngbrs[6][2] = {
        {{-1, 0}, {1, 0}},
        {{0, -1}, {0, 1}},
        {{-1, 0}, {0, 1}},
        {{-1, 0}, {0, -1}},
        {{1, 0},  {0, -1}},
        {{1, 0},  {0, 1}}
    };

    int row = curr.first;
    int col = curr.second;
    int last_row = last.first;
    int last_col = last.second;

    for (int i = 0; i < 6; i++) {
        if (table[row][col] != pipes[i]) {
            continue;
        }
        for (int j = 0; j < 2; j++) {
            const auto& ngbr = delta_ngbrs[i][j];
            int n_r = row + ngbr.first;
            int n_c = col + ngbr.second;

            /// check in table
            if (!is_in_table(n_r, ROWS) or !is_in_table(n_c, COLS)) {
                continue;
            }

            /// visited
            if (n_r == last_row and n_c == last_col) {
                continue;
            }

            return {n_r, n_c};
        }
    }
    cout << "ERROR other_ngbr\n";
    exit(-1);
}

int solve(const vector<string>& table) {
    const int ROWS = table.size();
    const int COLS = table[0].size();

    pair<int, int> last, curr;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (table[r][c] == 'S') {
                pair<int, int> d[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                for (int k = 0; k < 4; k++) {
                    curr = {r+d[k].first, c+d[k].second};
                    if (!is_in_table(curr.first, ROWS) or !is_in_table(curr.second, COLS)) {
                        continue;
                    }
                    if (table[curr.first][curr.second] == '.') {
                        continue;
                    }
                    last = {r, c};
                    pair<int, int> ngbr = other_ngbr(table, curr, last);
                    pair<int, int> start = other_ngbr(table, curr, ngbr);
                    if (table[start.first][start.second] == 'S') {
                        break;
                    }
                }
                r = ROWS;
                c = COLS;
            }
        }
    }

    int ans = 1;
    while (table[curr.first][curr.second] != 'S') {
        pair<int, int> ngbr = other_ngbr(table, curr, last);
        last = curr;
        curr = ngbr;
        ans++;
    }
    return ans/2;
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
