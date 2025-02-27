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
// Функция для чтения оглавления архива
void printRAR4Contents(const vector<uint8_t>& data) {
    // Проверка сигнатуры
    if (data.size() < sizeof(RAR4VolumeHeader)) {
        cerr << "Файл слишком мал для архива RAR4" << endl;
        return;
    }

    const RAR4VolumeHeader* volumeHeader = reinterpret_cast<const RAR4VolumeHeader*>(data.data());
    if (string(volumeHeader->signature, 7) != "Rar!\x1A\x07\x00") {
        cerr << "Неверная сигнатура архива" << endl;
        return;
    }

    // Переменная для хранения текущей позиции в данных
    size_t pos = sizeof(RAR4VolumeHeader);

    // Цикл по записям
    while (pos + sizeof(RAR4FileHeader) <= data.size()) {
        const RAR4FileHeader* fileHeader = reinterpret_cast<const RAR4FileHeader*>(data.data() + pos);

        // Проверка типа записи
        if (fileHeader->type == 0x74) { // Запись типа файла
            // Извлечение имени файла
            size_t nameSize = fileHeader->headerSize - sizeof(RAR4FileHeader);
            string fileName(reinterpret_cast<const char*>(data.data() + pos + sizeof(RAR4FileHeader)), nameSize);
			
			// Вывод информации о файле
            cout << "Имя файла: " << fileName << endl;
            cout << "Размер упакованных данных: " << fileHeader->packSize << " байт" << endl;
            cout << "----------------------------------------" << endl;
        }

        // Переход к следующей записи
        pos += fileHeader->headerSize + fileHeader->packSize;
    }
}
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
