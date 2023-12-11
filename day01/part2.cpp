#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

string INPUT_NAME = "part2.in";
string OUTPUT_NAME = "part2.out";

int get_number(string line) {
    // cout << "#" << line << " ";
    int first_digit = -1, last_digit = -1;
    size_t first_index = string::npos, last_index = string::npos;

    /// find first digit
    string string_digits[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    int digits[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // string string_digits[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    // int digits[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 18; i++) {
        const auto& d = string_digits[i];
        size_t index = line.find(d);
        // cout << d << " " << index << "\n";
        if (first_index == string::npos or (index != string::npos and index < first_index)) {
            first_index = index;
            first_digit = digits[i];
        }
    }

    /// find last digit
    reverse(line.begin(), line.end());
    for (int i = 0; i < 9; i++) {
        reverse(string_digits[i].begin(), string_digits[i].end());
    }

    for (int i = 0; i < 18; i++) {
        const auto& d = string_digits[i];
        size_t index = line.find(d);
        // cout << d << " " << index << "\n";
        if (last_index == string::npos or (index != string::npos and index < last_index)) {
            last_index = index;
            last_digit = digits[i];
        }
    }

    // cout << "#" << first_digit << last_digit << "\n\n\n";
    return first_digit*10 + last_digit;
}

// try again with windows endings

int main(int argc, char *argv[]) {
    if (argc == 2) {
        string name = argv[1];
        INPUT_NAME = name + ".in";
        OUTPUT_NAME = name + ".out";
    }

    /// INPUT
    ifstream input_file(INPUT_NAME);
    if (!input_file.is_open()) {
        cout << "Unable to open input file.\n";
        return -1;
    }

    /// OUTPUT
    ofstream output_file(OUTPUT_NAME);
    if (!output_file.is_open()) {
        cout << "Unable to open output file.\n";
        return -1;
    }

    /// SOLUTION
    string line;
    long long ans = 0;
    while (getline(input_file, line)) {
        //cout << "ESI" << endl;
        // cout << "papa" << flush;
        //cout << "(" << line << ")" << endl << endl;
        ans += get_number(line);
    }
    input_file.close();

    output_file << ans << "\n";
    output_file.close();
    return 0;
}
