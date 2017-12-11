
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

void addStopper(uint8_t * data, int entry) {
    int index = (entry * ENTRY_SIZE) + (ENTRY_SIZE - 2);
    data[index] = 0x03;
}

void setDot(uint8_t * data, int x, int y, int entry) {
    int line = y / 8;
    int mask = 1 << (y % 8);
    int pos = (entry * ENTRY_SIZE) + (line * LINE_SIZE) + PRE_SIZE + (x * 2) + 1;
    data[pos] |= mask;
}

void setCircle(uint8_t * data, int entry){
    uint8_t dots2_16[5] =      {7, 8, 9, 10, 11};
    uint8_t dots3_15[4] =      {5, 6, 12, 13};
    uint8_t dots4_14[2] =      {4, 14};
    uint8_t dots5_6_12_13[2] = {3, 15};
    uint8_t dots7_11[2] =      {2, 16};

    for (int i = 0; i < 5; i++) {
        setDot(data, dots2_16[i], 2, entry);
        setDot(data, dots2_16[i], 16, entry);
    }

    for (int i = 0; i < 4; i++) {
        setDot(data, dots3_15[i], 3, entry);
        setDot(data, dots3_15[i], 15, entry);
    }

    for (int i = 0; i < 2; i++) {
        setDot(data, dots4_14[i], 4, entry);
        setDot(data, dots4_14[i], 14, entry);
    }

    for (int i = 0; i < 2; i++) {
        setDot(data, dots5_6_12_13[i], 5, entry);
        setDot(data, dots5_6_12_13[i], 6, entry);
        setDot(data, dots5_6_12_13[i], 12, entry);
        setDot(data, dots5_6_12_13[i], 13, entry);
    }

    for (int i = 0; i < 2; i++) {
        setDot(data, dots7_11[i], 7, entry);
        setDot(data, dots7_11[i], 8, entry);
        setDot(data, dots7_11[i], 9, entry);
        setDot(data, dots7_11[i], 10, entry);
        setDot(data, dots7_11[i], 11, entry);
    }
}

void setDigit(uint8_t * data, int pos, int digit, int entry) {
    int shiftY = 6;
    int shiftX = 10;
    if (pos != 0) {
        shiftX = 5;
    }

    switch(digit) {
        case 1:
            setDot(data, 2 + shiftX, 0 + shiftY, entry);
            setDot(data, 1 + shiftX, 1 + shiftY, entry);
            setDot(data, 1 + shiftX, 2 + shiftY, entry);
            setDot(data, 2 + shiftX, 1 + shiftY, entry);
            setDot(data, 2 + shiftX, 2 + shiftY, entry);
            setDot(data, 2 + shiftX, 3 + shiftY, entry);
            setDot(data, 2 + shiftX, 4 + shiftY, entry);
            setDot(data, 2 + shiftX, 5 + shiftY, entry);
            setDot(data, 2 + shiftX, 6 + shiftY, entry);
            setDot(data, 1 + shiftX, 6 + shiftY, entry);
            setDot(data, 3 + shiftX, 6 + shiftY, entry);
            break;
        case 2:
            setDot(data, 1 + shiftX, 0 + shiftY, entry);
            setDot(data, 5 + shiftX, 0 + shiftY, entry);
            setDot(data, 6 + shiftX, 0 + shiftY, entry);
            setDot(data, 0 + shiftX, 1 + shiftY, entry);
            setDot(data, 4 + shiftX, 1 + shiftY, entry);
            setDot(data, 6 + shiftX, 1 + shiftY, entry);
            setDot(data, 0 + shiftX, 2 + shiftY, entry);
            setDot(data, 3 + shiftX, 2 + shiftY, entry);
            setDot(data, 6 + shiftX, 2 + shiftY, entry);
            setDot(data, 1 + shiftX, 3 + shiftY, entry);
            setDot(data, 2 + shiftX, 3 + shiftY, entry);
            setDot(data, 6 + shiftX, 3 + shiftY, entry);
            break;
        case 3:
            setDot(data, 0 + shiftX, 0 + shiftY, entry);
            setDot(data, 5 + shiftX, 0 + shiftY, entry);
            setDot(data, 0 + shiftX, 1 + shiftY, entry);
            setDot(data, 3 + shiftX, 1 + shiftY, entry);
            setDot(data, 6 + shiftX, 1 + shiftY, entry);
            setDot(data, 0 + shiftX, 2 + shiftY, entry);
            setDot(data, 2 + shiftX, 2 + shiftY, entry);
            setDot(data, 3 + shiftX, 2 + shiftY, entry);
            setDot(data, 6 + shiftX, 2 + shiftY, entry);
            setDot(data, 0 + shiftX, 3 + shiftY, entry);
            setDot(data, 1 + shiftX, 3 + shiftY, entry);
            setDot(data, 4 + shiftX, 3 + shiftY, entry);
            setDot(data, 5 + shiftX, 3 + shiftY, entry);
            break;
        case 4:
            setDot(data, 0 + shiftX, 0 + shiftY, entry);
            setDot(data, 1 + shiftX, 0 + shiftY, entry);
            setDot(data, 2 + shiftX, 0 + shiftY, entry);
            setDot(data, 3 + shiftX, 0 + shiftY, entry);
            setDot(data, 3 + shiftX, 1 + shiftY, entry);
            setDot(data, 3 + shiftX, 2 + shiftY, entry);
            setDot(data, 0 + shiftX, 3 + shiftY, entry);
            setDot(data, 1 + shiftX, 3 + shiftY, entry);
            setDot(data, 2 + shiftX, 3 + shiftY, entry);
            setDot(data, 3 + shiftX, 3 + shiftY, entry);
            setDot(data, 4 + shiftX, 3 + shiftY, entry);
            setDot(data, 5 + shiftX, 3 + shiftY, entry);
            setDot(data, 6 + shiftX, 3 + shiftY, entry);
            break;
        case 5:
            setDot(data, 0 + shiftX, 0 + shiftY, entry);
            setDot(data, 1 + shiftX, 0 + shiftY, entry);
            setDot(data, 2 + shiftX, 0 + shiftY, entry);
            setDot(data, 5 + shiftX, 0 + shiftY, entry);
            setDot(data, 0 + shiftX, 1 + shiftY, entry);
            setDot(data, 2 + shiftX, 1 + shiftY, entry);
            setDot(data, 6 + shiftX, 1 + shiftY, entry);
            setDot(data, 0 + shiftX, 2 + shiftY, entry);
            setDot(data, 2 + shiftX, 2 + shiftY, entry);
            setDot(data, 6 + shiftX, 2 + shiftY, entry);
            setDot(data, 0 + shiftX, 3 + shiftY, entry);
            setDot(data, 3 + shiftX, 3 + shiftY, entry);
            setDot(data, 4 + shiftX, 3 + shiftY, entry);
            setDot(data, 5 + shiftX, 3 + shiftY, entry);
            break;
        case 6:
            setDot(data, 1 + shiftX, 0 + shiftY, entry);
            setDot(data, 2 + shiftX, 0 + shiftY, entry);
            setDot(data, 3 + shiftX, 0 + shiftY, entry);
            setDot(data, 4 + shiftX, 0 + shiftY, entry);
            setDot(data, 5 + shiftX, 0 + shiftY, entry);
            setDot(data, 0 + shiftX, 1 + shiftY, entry);
            setDot(data, 3 + shiftX, 1 + shiftY, entry);
            setDot(data, 6 + shiftX, 1 + shiftY, entry);
            setDot(data, 0 + shiftX, 2 + shiftY, entry);
            setDot(data, 3 + shiftX, 2 + shiftY, entry);
            setDot(data, 6 + shiftX, 2 + shiftY, entry);
            setDot(data, 1 + shiftX, 3 + shiftY, entry);
            setDot(data, 4 + shiftX, 3 + shiftY, entry);
            setDot(data, 5 + shiftX, 3 + shiftY, entry);
            break;
        case 7:
            setDot(data, 0 + shiftX, 0 + shiftY, entry);
            setDot(data, 0 + shiftX, 1 + shiftY, entry);
            setDot(data, 3 + shiftX, 1 + shiftY, entry);
            setDot(data, 4 + shiftX, 1 + shiftY, entry);
            setDot(data, 5 + shiftX, 1 + shiftY, entry);
            setDot(data, 6 + shiftX, 1 + shiftY, entry);
            setDot(data, 0 + shiftX, 2 + shiftY, entry);
            setDot(data, 2 + shiftX, 2 + shiftY, entry);
            setDot(data, 0 + shiftX, 3 + shiftY, entry);
            setDot(data, 1 + shiftX, 3 + shiftY, entry);
            break;
        case 8:
            setDot(data, 1 + shiftX, 0 + shiftY, entry);
            setDot(data, 2 + shiftX, 0 + shiftY, entry);
            setDot(data, 4 + shiftX, 0 + shiftY, entry);
            setDot(data, 5 + shiftX, 0 + shiftY, entry);
            setDot(data, 0 + shiftX, 1 + shiftY, entry);
            setDot(data, 3 + shiftX, 1 + shiftY, entry);
            setDot(data, 6 + shiftX, 1 + shiftY, entry);
            setDot(data, 0 + shiftX, 2 + shiftY, entry);
            setDot(data, 3 + shiftX, 2 + shiftY, entry);
            setDot(data, 6 + shiftX, 2 + shiftY, entry);
            setDot(data, 1 + shiftX, 3 + shiftY, entry);
            setDot(data, 2 + shiftX, 3 + shiftY, entry);
            setDot(data, 4 + shiftX, 3 + shiftY, entry);
            setDot(data, 5 + shiftX, 3 + shiftY, entry);
            break;
        case 9:
            setDot(data, 1 + shiftX, 0 + shiftY, entry);
            setDot(data, 2 + shiftX, 0 + shiftY, entry);
            setDot(data, 5 + shiftX, 0 + shiftY, entry);
            setDot(data, 0 + shiftX, 1 + shiftY, entry);
            setDot(data, 3 + shiftX, 1 + shiftY, entry);
            setDot(data, 6 + shiftX, 1 + shiftY, entry);
            setDot(data, 0 + shiftX, 2 + shiftY, entry);
            setDot(data, 3 + shiftX, 2 + shiftY, entry);
            setDot(data, 6 + shiftX, 2 + shiftY, entry);
            setDot(data, 1 + shiftX, 3 + shiftY, entry);
            setDot(data, 2 + shiftX, 3 + shiftY, entry);
            setDot(data, 3 + shiftX, 3 + shiftY, entry);
            setDot(data, 4 + shiftX, 3 + shiftY, entry);
            setDot(data, 5 + shiftX, 3 + shiftY, entry);
            break;
        default:
            setDot(data, 1 + shiftX, 0 + shiftY, entry);
            setDot(data, 2 + shiftX, 0 + shiftY, entry);
            setDot(data, 0 + shiftX, 1 + shiftY, entry);
            setDot(data, 3 + shiftX, 1 + shiftY, entry);
            setDot(data, 0 + shiftX, 2 + shiftY, entry);
            setDot(data, 3 + shiftX, 2 + shiftY, entry);
            setDot(data, 0 + shiftX, 3 + shiftY, entry);
            setDot(data, 3 + shiftX, 3 + shiftY, entry);
            setDot(data, 0 + shiftX, 4 + shiftY, entry);
            setDot(data, 3 + shiftX, 4 + shiftY, entry);
            setDot(data, 0 + shiftX, 5 + shiftY, entry);
            setDot(data, 3 + shiftX, 5 + shiftY, entry);
            setDot(data, 1 + shiftX, 6 + shiftY, entry);
            setDot(data, 2 + shiftX, 6 + shiftY, entry);
            setDot(data, 2 + shiftX, 2 + shiftY, entry);
            setDot(data, 1 + shiftX, 3 + shiftY, entry);
    }
}

int main() {
    uint8_t data[DATA_SIZE];
	memset(data, 0, DATA_SIZE);

    for(int i = 0; i < ENTRY_NUM; i++) {
        addCoord(data, i);
        addStopper(data, i);
    }

    setCircle(data, 0);
    setDigit(data, 0, 0, 0);
    setDigit(data, 1, 0, 0);

    std::string dfName = "DataFile.bin";
    std::ofstream dataFile {dfName, std::ios::binary | std::ios::trunc};
    if (!dataFile) {
        std::cout << "Error - stream was not opened" << std::endl;
    } else {
        std::cout << "Done.";
        dataFile.write((const char *)data, DATA_SIZE);
    }



    std::cin.get();
    return 0;
}
