#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<string> readLinesFromFile(const string& filename) {
    vector<string> lines;
    return lines;
}

void printLines(const vector<string>& lines) {
	for (const auto& line : lines) {
        cout << line << endl;
    }
}

void writeLinesToFile(const vector<string>& lines, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& line : lines) {
            file << line << endl;
        }
        file.close();
    } else {
        cerr << "Ошибка открытия файла: " << filename << endl;
    }
}

int main() {
    string filename = "input.txt";
    vector<string> lines = readLinesFromFile(filename);
    printLines(lines);
    writeLinesToFile(lines, "output.txt");
    return 0;
}