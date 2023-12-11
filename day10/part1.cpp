#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

bool is_in_table(int num, int lim) {
    return num >= 0 and num < lim;
}

pair<int, int> find_start(const vector<string>& table, int r, int c){
    //cout << r << " " << c << endl;

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
    pair<int, int> delta[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int k = 0; k < 4; k++) {
        int curr_r = r + delta[k].first;
        int curr_c = c + delta[k].second;
        if (!is_in_table(curr_r, ROWS) or !is_in_table(curr_c, COLS)) {
            continue;
        }

        for (int i = 0; i < 6; i++) {
            if (table[curr_c][curr_r] != pipes[i]) {
                continue;
            }
            for (int j = 0; j < 2; j++) {
                const auto& ngbr = delta_ngbrs[i][j];
                int n_r = curr_r + ngbr.first;
                int n_c = curr_c + ngbr.second;
                //cout << n_r << " " << n_c << endl;
                if (!is_in_table(n_r, ROWS) or !is_in_table(n_c, COLS)) {
                    //cout << "wtf\n";
                    continue;
                }

                if (table[n_r][n_c] == 'S') {
                    return {curr_r, curr_c};
                }
            }
            break;
        }
    }
    cout << "ERROR\n";
    exit(-1);
}

int solve(const vector<string>& table) {
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
    pair<int, int> delta[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    pair<int, int> start;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (table[r][c] == 'S') {
                start = find_start(table, r, c);
                r = ROWS;
                c = COLS;
            }
        }
    }

    int ans = 2;
    int last_row = -1, last_col = -1;
    int row = start.first, col = start.second;
    while (true) {
        for (int i = 0; i < 6; i++) {
            if (table[row][col] != pipes[i]) {
                continue;
            }
            for (int j = 0; j < 2; j++) {
                const auto& ngbr = delta_ngbrs[i][j];
                int n_r = row + ngbr.first;
                int n_c = col + ngbr.second;

                /// first step
                if (table[n_r][n_c] == 'S') {
                    if (ans == 2) {
                        continue;
                    }
                    return ans/2;
                }

                /// visited
                if (n_r == last_row and n_c == last_col) {
                    continue;
                }

                last_row = row;
                last_col = col;
                row = n_r;
                col = n_c;
                ans++;
                break;
            }
            break;
        }
    }

    return -1;
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
