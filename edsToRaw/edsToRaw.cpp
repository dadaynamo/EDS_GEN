#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

// Funzione per suddividere una stringa su un delimitatore, ad esempio ','
std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Genera combinazioni senza caricarle tutte in memoria, scrivendole direttamente nel file
void generateCombinationsToFile(const std::string &eds, std::ofstream &outFile) {
    std::stack<std::pair<std::string, int>> stack;  // Pila per gestire lo stato
    stack.push({"", 0});  // Inizializza con una stringa vuota e posizione iniziale

    while (!stack.empty()) {
        auto [current, pos] = stack.top();
        stack.pop();

        while (pos < eds.size()) {
            if (eds[pos] == '{') {
                // Individua il gruppo degenerato tra le graffe
                std::string options;
                pos++;
                while (pos < eds.size() && eds[pos] != '}') {
                    options += eds[pos];
                    pos++;
                }
                pos++;  // Salta la chiusura '}'

                // Processa ogni opzione separata da virgola
                std::vector<std::string> variants = split(options, ',');
                for (const auto &variant : variants) {
                    stack.push({current + variant, pos});  // Aggiungi variante alla pila
                }
                break;  // Esci dal ciclo per processare le varianti
            } else {
                // Aggiungi carattere singolo alla combinazione corrente
                current += eds[pos];
                pos++;
            }
        }

        // Se siamo alla fine, scriviamo la combinazione nel file
        if (pos >= eds.size()) {
            outFile << current << "$";  // Scrive la combinazione con delimitatore "$"
        }
    }
}

// Funzione per leggere la stringa EDS da un file .eds
std::string readEDSFromFile(const std::string &filename) {
    std::ifstream file(filename);
    std::string eds;

    if (file.is_open()) {
        std::getline(file, eds);  // Legge tutto il contenuto della prima riga
        file.close();
    } else {
        std::cerr << "Errore nell'apertura del file: " << filename << std::endl;
    }

    return eds;
}

int main(int argc, char* argv[]) {
    // Verifica parametri
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <file_input> <file_output>\n";
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    // Leggi il file .eds e preleva la stringa EDS
    std::string eds = readEDSFromFile(inputFilename);
    if (eds.empty()) {
        std::cerr << "Il file è vuoto o non è stato trovato." << std::endl;
        return 1;
    }

    // Apri il file di output
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Errore nell'apertura del file di output: " << outputFilename << std::endl;
        return 1;
    }

    // Genera combinazioni e scrivile nel file
    generateCombinationsToFile(eds, outFile);

    std::cout << "Combinazioni generate e salvate in '" << outputFilename << "'.\n";

    outFile.close();
    return 0;
}
