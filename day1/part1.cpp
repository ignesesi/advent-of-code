#include <iostream>
#include <fstream>
using namespace std;

string INPUT_NAME = "part1.in";
string OUTPUT_NAME = "part1.out";

int get_number(string line) {
    //cout << "#" << line << " ";
    int first = -1, last = -1;
    for (char& c : line) {
        if (isdigit(c)) {
            if (first == -1) {
                first = c - '0';
            }
            last = c - '0';
        }
    }
    //cout << "$" << first*10 + last << "\n";
    return first*10 + last;
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
