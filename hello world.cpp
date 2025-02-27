#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<string> readLinesFromFile(const string& filename) {
    vector<string> lines;
    return lines;
}

void printLines(const vector<string>& lines) {
}

void writeLinesToFile(const vector<string>& lines, const string& filename) {
}

int main() {
    string filename = "input.txt";
    vector<string> lines = readLinesFromFile(filename);
    printLines(lines);
    writeLinesToFile(lines, "output.txt");
    return 0;
}