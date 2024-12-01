#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>

// Funzione per suddividere una stringa su un delimitatore, ad esempio ','
// Non cambia rispetto al tuo codice
std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Funzione ricorsiva ottimizzata per generare le combinazioni
// Senza accumulare tutte le combinazioni in memoria, ma scrivendole direttamente nel file
void generateCombinations(const std::string &eds, std::ofstream &outFile, std::string current = "", int pos = 0) {
    std::stack<std::pair<std::string, int>> stack;
    stack.push({current, pos});

    while (!stack.empty()) {
        auto [currentStr, pos] = stack.top();
        stack.pop();

        while (pos < eds.size()) {
            if (eds[pos] == '{') {
                // Individua un gruppo degenerato (tra le graffe)
                std::string options;
                pos++;
                while (pos < eds.size() && eds[pos] != '}') {
                    options += eds[pos];
                    pos++;
                }

                // Processa ogni opzione separata da virgola
                std::vector<std::string> variants = split(options, ',');

                // Aggiungi ogni variante alla combinazione corrente e metti nel stack
                for (const std::string &variant : variants) {
                    stack.push({currentStr + variant, pos});
                }
            } else {
                // Aggiungi carattere singolo alla combinazione corrente
                currentStr += eds[pos];
                pos++;
            }

            // Scrivi la combinazione corrente nel file se è una combinazione finale
            if (pos == eds.size()) {
                outFile << currentStr << "$"; // Scrive la combinazione con il delimitatore "$"
            }
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
    // Verifica 0 parametri
    if (argc == 1) {
        std::cerr << "Error: Missing required parameters.\n";
        return 1;
    }

    // > ./edsToRaw input output
    // Controlla i parametri
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <file_input> <file_output>\n";
        return 1;
    }

    // File di input e output specificati dall'utente
    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    // Leggi il file .eds e preleva la stringa EDS
    std::string eds = readEDSFromFile(inputFilename);

    // Controlla se il file è stato letto correttamente
    if (eds.empty()) {
        std::cerr << "Il file è vuoto o non è stato trovato." << std::endl;
        return 1;
    }

    // Apre il file di output per scrivere
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Errore nell'apertura del file di output: " << outputFilename << std::endl;
        return 1;
    }

    // Genera e scrive le combinazioni nel file di output
    generateCombinations(eds, outFile);

    // Messaggio di successo
    std::cout << "Combinazioni generate e salvate in '" << outputFilename << "'.\n";

    outFile.close();
    return 0;
}
