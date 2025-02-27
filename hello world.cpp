#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Функция чтения из файла
vector<string> readLinesFromFile(const string& filename) {
    vector<string> lines;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cerr << "Ошибка открытия файла: " << filename << endl;
    }
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
