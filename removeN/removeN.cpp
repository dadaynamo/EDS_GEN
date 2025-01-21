#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

void removeNFromFile(const std::string& inputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "Errore: impossibile aprire il file di input " << inputFile << std::endl;
        return;
    }

    std::string tempFile = inputFile + ".tmp";
    std::ofstream outFile(tempFile);
    if (!outFile.is_open()) {
        std::cerr << "Errore: impossibile creare il file temporaneo " << tempFile << std::endl;
        inFile.close();
        return;
    }

    char c;
    while (inFile.get(c)) {
        if (c != 'N' && c != 'n') {
            outFile.put(c);
        }
    }

    inFile.close();
    outFile.close();

    if (std::remove(inputFile.c_str()) != 0) {
        std::cerr << "Errore: impossibile eliminare il file originale " << inputFile << std::endl;
        return;
    }

    if (std::rename(tempFile.c_str(), inputFile.c_str()) != 0) {
        std::cerr << "Errore: impossibile rinominare il file temporaneo " << tempFile << std::endl;
        return;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso corretto: " << argv[0] << " <file_input>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];

    removeNFromFile(inputFile);

    std::cout << "Il file " << inputFile << " è stato aggiornato senza lettere 'N' o 'n'." << std::endl;

    return 0;
}