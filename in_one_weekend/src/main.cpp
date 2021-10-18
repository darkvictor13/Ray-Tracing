#include <iostream>
#include <cctype>
#include <fstream>

#define IMG_PATH          "../images/"
#define DEFAULT_FILE_NAME "first.ppm"

#define IMG_WIDTH  256
#define IMG_HEIGHT 256

#include "color.hpp"

int main (int argc, char *argv[]) {
    std::string file_name;
    if (argc == 2) {
        file_name = argv[1];
    } else {
        char input;
        std::cout << "Deseja inserir o nome do arquivo? [s/N] ";
        std::cin.get(input);
        if (std::tolower(input) == 's') {
            std::cout << "Entre com o nome do arquivo: ";
            std::cin >> file_name;
        }else{
            file_name = DEFAULT_FILE_NAME;
        }
    }

    std::ofstream file;
    file.open(IMG_PATH + file_name);
    file << "P3\n" << IMG_WIDTH << ' ' << IMG_HEIGHT << "\n255\n";

    int i, j;
    for (j = IMG_HEIGHT - 1; j >= 0; j--) {
        std::cout << "Faltam " << j << " linhas para gerar\n";
        for (i = 0; i < IMG_WIDTH; i++) {
            Color pixel(double(i)/(IMG_WIDTH-1), double(j)/(IMG_HEIGHT-1), 0.25);
            writeColor(file, pixel);
        }
    }

    file.close();
    return 0;
}
