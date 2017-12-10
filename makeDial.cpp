
#include <iostream>
#include <fstream>
#include <windows.h>

#define DATA_SIZE 16

int main() {
	char data[DATA_SIZE];
	memset(data, 0, DATA_SIZE);
	data[1] = 0xaa;

    std::string dfName = "DataFile.bin";
    std::ofstream dataFile {dfName, std::ios::binary | std::ios::trunc};
    if (!dataFile) {
        std::cout << "Error - stream was not opened" << std::endl;
    } else {
        std::cout << data[1];
        dataFile.write(data, DATA_SIZE);
    }



    std::cin.get();
    return 0;
}
