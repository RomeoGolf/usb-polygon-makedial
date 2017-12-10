
#include <iostream>
#include <fstream>
#include <windows.h>

#define PRE_SIZE 4
#define POST_SIZE 2
#define LINE_SIZE (PRE_SIZE + (19 * 2))
#define ENTRY_SIZE ((LINE_SIZE * 3) + POST_SIZE)
#define ENTRY_NUM 20
#define DATA_SIZE (ENTRY_SIZE * ENTRY_NUM)

void addCoord(uint8_t * data, int entry) {
    int index;

    index = (entry * ENTRY_SIZE);
    data[index++] = 0x01;
    data[index++] = 0x42;
    data[index++] = 0x01;
    data[index++] = 0xA6;
    data[index++] = 0x02;
    index = (entry * ENTRY_SIZE) + LINE_SIZE;
    data[index++] = 0x01;
    data[index++] = 0x43;
    data[index++] = 0x01;
    data[index++] = 0xA6;
    data[index++] = 0x02;
    index = (entry * ENTRY_SIZE) + (LINE_SIZE * 2);
    data[index++] = 0x01;
    data[index++] = 0x44;
    data[index++] = 0x01;
    data[index++] = 0xA6;
    data[index++] = 0x02;
}

int main() {
    uint8_t data[DATA_SIZE];
	memset(data, 0, DATA_SIZE);

    for(int i = 0; i < 20; i++) {
        addCoord(data, i);
    }

    std::string dfName = "DataFile.bin";
    std::ofstream dataFile {dfName, std::ios::binary | std::ios::trunc};
    if (!dataFile) {
        std::cout << "Error - stream was not opened" << std::endl;
    } else {
        std::cout << data[1];
        dataFile.write((const char *)data, DATA_SIZE);
    }



    std::cin.get();
    return 0;
}
