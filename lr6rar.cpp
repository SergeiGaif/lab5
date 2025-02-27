#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iomanip>

using namespace std;
#pragma pack(push, 1) // Выравнивание по 1 байту

// Структура для заголовка архива RAR4
struct RAR4VolumeHeader {
    char signature[7]; // Сигнатура "Rar!"
    uint16_t version;  // Версия формата
};

// Структура для общего заголовка записи
struct RAR4FileHeader {
    uint16_t crc;       // Контрольная сумма
    uint8_t type;       // Тип записи (0x74 для файла)
    uint16_t flags;     // Флаги
    uint16_t headerSize; // Размер заголовка
    uint32_t packSize;  // Размер упакованных данных
};

#pragma pack(pop) // Возвращаем выравнивание по умолчанию
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
