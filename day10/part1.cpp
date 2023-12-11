#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

struct Cell {
    int row, col;
};

bool is_in_table(const vector<string>& table, const Cell& cell) {
    return cell.row >= 0 and cell.col >= 0 and cell.row < table.size() and cell.col < table[0].size();
}

Cell other_ngbr(const vector<string>& table, Cell curr, Cell last) {
    /// define symbols
    char pipes[7] = "|-LJ7F";
    Cell delta_ngbrs[6][2] = {
        {{-1, 0}, {1, 0}},
        {{0, -1}, {0, 1}},
        {{-1, 0}, {0, 1}},
        {{-1, 0}, {0, -1}},
        {{1, 0},  {0, -1}},
        {{1, 0},  {0, 1}}
    };

    for (int i = 0; i < 6; i++) {
        if (table[curr.row][curr.col] != pipes[i]) {
            continue;
        }
        for (int j = 0; j < 2; j++) {
            const auto& d_n = delta_ngbrs[i][j];
            Cell ngbr = {curr.row + d_n.row, curr.col + d_n.col};

            /// check in table
            if (!is_in_table(table, ngbr)) {
                continue;
            }

            /// visited
            if (ngbr.row == last.row and ngbr.col == last.col) {
                continue;
            }

            return ngbr;
        }
    }

    /// ERROR
    cout << "ERROR other_ngbr\n";
    exit(-1);
}

int solve(const vector<string>& table) {
    const int ROWS = table.size();
    const int COLS = table[0].size();

    Cell last, curr;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (table[r][c] == 'S') {
                /// find ngbrs connecte to S
                Cell d[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                for (int k = 0; k < 4; k++) {
                    curr = {r+d[k].row, c+d[k].col};

                    /// check in table
                    if (!is_in_table(table, curr)) {
                        continue;
                    }

                    /// check if ngbr is not a .
                    if (table[curr.row][curr.col] == '.') {
                        continue;
                    }

                    /// check if ngbr is connected to S
                    last = {r, c};
                    Cell ngbr = other_ngbr(table, curr, last);
                    Cell start = other_ngbr(table, curr, ngbr);
                    if (table[start.row][start.col] == 'S') {
                        break;
                    }
                }
                r = ROWS;
                c = COLS;
            }
        }
    }

    /// find path
    int ans = 1;
    while (table[curr.row][curr.col] != 'S') {
        Cell ngbr = other_ngbr(table, curr, last);
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
