#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int in_table(int num, int lim) {
    if (num < 0) {
        return 0;
    }
    if (num > lim) {
        return lim;
    }
    return num;
}

bool check_ngbrs(const vector<string>& table, int row, int col) {
    int drow[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dcol[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        //int new_row = min(table.size() - 1, max(0, row+drow[i]));
        //int new_col = min(table[0].size() - 1, max(0, col+dcol[i]));
        int new_row = in_table(row+drow[i], table.size() - 1);
        int new_col = in_table(col+dcol[i], table[0].size() - 1);

        const char& c = table[new_row][new_col];
        if (!(isdigit(c) or c == '.')) {
            return true;
        }
    }
    return false;
}

int solve(const vector<string>& table) {
    long long ans = 0;
    size_t num_rows = table.size();
    size_t num_cols = table[0].size();

    long long number = 0;
    bool is_last_number = false, is_sch = false;

    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            if (isdigit(table[row][col])) {
                number = number*10 + table[row][col] - '0';
                if (check_ngbrs(table, row, col)) {
                    is_sch = true;
                }
            } else {
                if (is_sch) {
                    ans += number;
                }
                is_sch = false;
                number = 0;
            }
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
    vector<string> table;
    string line;
    long long ans = 0;
    while (getline(input_file, line)) {
        table.push_back(line);
    }
    input_file.close();

    output_file << solve(table) << "\n";
    output_file.close();
    return 0;
}
