#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iomanip>

using namespace std;
int main() {
    // Чтение файла архива
    ifstream file("Example.rar", ios::binary | ios::ate);
    if (!file) {
        cerr << "Не удалось открыть файл архива" << endl;
        return 1;
    }

    // Получение размера файла
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    // Чтение данных в вектор
    vector<uint8_t> data(size);
    if (!file.read(reinterpret_cast<char*>(data.data()), size) {
        cerr << "Не удалось прочитать файл архива" << endl;
        return 1;
    }

    // Вывод оглавления архива
    printRAR4Contents(data);

    return 0;
}
