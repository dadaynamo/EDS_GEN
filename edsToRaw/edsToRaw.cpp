/*
ATTENZIONE 
TEST NON OTTIMIZZATO
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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

// Funzione ricorsiva per generare tutte le combinazioni da un Elastic Degenerate String (EDS)
void generateCombinations(const std::string &eds, std::vector<std::string> &results, std::string current = "", int pos = 0) {
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
            std::vector<std::string> newResults;

            // Combina ogni variante con le combinazioni esistenti
            for (const std::string &variant : variants) {
                for (const std::string &res : results) {
                    newResults.push_back(res + variant);
                }
            }
            results = newResults;
        } else {
            // Aggiungi carattere singolo alla combinazione corrente
            for (std::string &res : results) {
                res += eds[pos];
            }
        }
        pos++;
    }
}

// Funzione helper per iniziare le combinazioni
std::vector<std::string> expandEDS(const std::string &eds) {
    std::vector<std::string> results(1, "");
    generateCombinations(eds, results);
    return results;
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

// Funzione per scrivere tutte le combinazioni in un file
void writeCombinationsToFile(const std::vector<std::string> &combinations, const std::string &filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const std::string &combo : combinations) {
            file << combo << "$";
        }
        file.close();
    } else {
        std::cerr << "Errore nell'apertura del file per scrittura: " << filename << std::endl;
    }
}

int main(int argc, char* argv[]) {
        //Verifica 0 parametri 
    if (argc == 1){
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
    //std::string filename = argv[1];
    std::string eds = readEDSFromFile(inputFilename);

    // Controlla se il file è stato letto correttamente
    if (eds.empty()) {
        std::cerr << "Il file è vuoto o non è stato trovato." << std::endl;
        return 1;
    }

    // Ottieni tutte le combinazioni possibili espandendo l'EDS
    std::vector<std::string> allCombinations = expandEDS(eds);

      // Scrivi le combinazioni nel file di output
    writeCombinationsToFile(allCombinations, outputFilename);

    // Messaggio di successo
    std::cout << "Combinazioni generate e salvate in '" << outputFilename << "'.\n";

    return 0;
}
