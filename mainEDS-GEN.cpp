#include <iostream>
#include <string>
#include <cstring> // Necessario per strcmp
#include <cstdlib>  // Per rand() e srand()
#include <ctime>    // Per time()
#include <fstream> // Libreria per la gestione dei file
#include <random>
#include <cstdlib>
#include <fstream>
#include <iostream>
/*
Pensare all'intensive EDS, con qualche pattern molto ripetitivo.
Aggiungere gli spazi vuoti nelle EDS come degenerazioni
Prendere spunto da https://github.com/webmasterar/EDSRand/blob/master/EDSRand.py per generazioni particolari
Fare un getEDSsize.cpp

Provare a implementare questi nuovi parametri
PARAMETERS ---> EXAMPLES
- n : number of positions in text T ---> 1000000
- d% : percentage of positions in text T which are degenerate i.e. represent indels ---> 3
- S_max : maximum size of set at any position T[i] i.e. maximum number of S_j ---> 3
- L_max : upper bound on length of any string S_j in T[i] ---> 6


IMPLEMENTAZIONE EDS TO RAW !!IMPORTANTE
*/
using namespace std;

//MACROS -------------------------------------------------------------
#define SIGMA_SIZE 4  // Dimensione dell'array
//#define SIGMA {'a', 'c', 'g', 't'}  // Definizione dell'array di caratteri

//GLOBAL VARS --------------------------------------------------------

char sigma[SIGMA_SIZE] = {'A', 'C', 'G', 'T'};    
std::string outName; //file name senza estensione
int totSize; //numero massimo di caratteri di ogni singola sequenza degenerata
int maxPerDeg; //numero massimo di stringhe in un insieme
int numDegeneration; //numero di insiemi
char type;

//FUNCTIONS ----------------------------------------------------------
int generateRandomNumber(int min, int max) { //gen num tra min e max compresi
    // Inizializza il generatore di numeri casuali con un seme basato sul tempo attuale
    std::random_device rd;  // Generatore casuale basato su hardware
    std::mt19937 gen(rd());  // Mersenne Twister, un buon generatore di numeri pseudo-casuali

    // Definisce una distribuzione uniforme tra min e max inclusivi
    std::uniform_int_distribution<> distrib(min, max);

    // Genera il numero casuale
    return distrib(gen);
}

int displayVersion(){ //mostra la versione del progetto
       std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "                EDS-GEN Program                    " << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Versione: 1.0.0" << std::endl;
    std::cout << "Autore: Mattia Laszlo Daday" << std::endl;
    std::cout << "Anno: 2024/2025" << std::endl;
    std::cout << "Descrizione: Questo programma genera sequenze degenerate " << std::endl;
    std::cout << "basate su input specificati dall'utente. È possibile " << std::endl;
    std::cout << "personalizzare la generazione di sequenze con vari parametri " << std::endl;
    std::cout << "come dimensione, tipo di sequenza e percentuale di simboli degenerati." << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    return 0;
}
int displayHelp() { //descrizione generale
   std::cout << "Usage:\n";
    std::cout << "./EDS-GEN [option] [argument] | ...\n\n";
    
    std::cout << "Options:\n";
    std::cout << "  --help                        Show this help message and exit.\n\n";
    std::cout << "  --type <type>                 Specify the type of sequences (Raw, Eds, Eds-intensive, Test)\n";
    std::cout << "                                Example: --type [R, E, I, T]\n\n";
    std::cout << "  --output <outputfile>          Specify the name of the output file without the extension.\n";
    std::cout << "                                Example: --output result\n\n";
    std::cout << "  --totSize <TOTsize>           Set the maximum size of the generated output.\n";
    std::cout << "                                Example: --totSize 1000\n\n";
    std::cout << "  --maxPerDeg <maxPerDeg>       Set the max number of degenerate symbols in the generated sequence.\n";
    std::cout << "                                Example: --maxPerDeg 25\n\n";
    std::cout << "  --numDeg <numDeg>             Set the max number of degenerate symbols in the generated sequence.\n";
    std::cout << "                                Example: --numDeg 5\n\n";
    std::cout << "  --repeatability <level>       Set the repeatability level for the EDS (Elastic Degenerate Sequence). (NOT IN USE)\n";
    std::cout << "                                Accepted values: 1 to 10.\n";
    std::cout << "                                Example: --repeatability 5\n\n";
    std::cout << "  --degenerate <percentage>     Set the percentage of degenerate symbols in the generated sequence. (NOT IN USE)\n";
    std::cout << "                                Accepted values: 0 to 100.\n";
    std::cout << "                                Example: --degenerate 25\n\n";
    std::cout << "  --seed <seedvalue>            Specify a seed for random number generation to ensure repeatable results. (NOT IN USE)\n";
    std::cout << "                                Example: --seed 12345\n\n";
    std::cout << "  --custom-alphabet <string>    If --alphabet is set to 'custom', define the custom alphabet. (NOT IN USE)\n";
    std::cout << "                                Example: --custom-alphabet \"abcdxyz\"\n\n";
    std::cout << "  --version                     Display the version of the program and exit.\n\n";

    std::cout << "Examples:\n";
    std::cout << "  ./mainEDS-GEN --type E --outputName intensive --totSize 1000 --maxPerDeg 2 --numDeg 100\n";
    std::cout << "  ./mainEDS-GEN --type R --outputName intensive --totSize 1000\n";
    return 0;

}

int rawGeneration(std::ofstream& file){ //generazione DNA RAW
    //char sigma[SIGMA_SIZE] = SIGMA;
    std::cout << "Gen RAW-String" << std::endl;

    // Inizializza il generatore di numeri casuali
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "------------------------------"  << endl;
    cout << "filename output -> " << outName <<endl;
    cout << "Tot size DNA -> " << totSize <<endl;
    cout << "------------------------------"  << endl;

    // Definisci una dimensione di blocco per la scrittura incrementale
    const long chunkSize = 1024 * 1024 * 1024;  // 1 GB di blocco chunk
    char* buffer = new char[chunkSize + 1];  // Buffer temporaneo per ogni blocco


    //Creazione RAW-String classico
    std::string output;

    for (int i = 0; i < totSize; i += 1) {
        // unsigned long currentChunkSize = std::min(chunkSize, totSize - i);  // Gestisce l'ultimo blocco
        
        for (unsigned long j = 0; j < chunkSize; ++j) {
            int random_index = rand() % SIGMA_SIZE;  // Genera un indice casuale tra 0 e 3
            buffer[j] = sigma[random_index];  // Inserisce il carattere nel buffer
        }

        // Scrivi il blocco nel file
        file.write(buffer, chunkSize); 
        cout << i << " Scrittura buffer" << endl;
        
    }

    //cout << "Final RAW-String " << output << endl; 
    //file << output;
    delete[] buffer;  // Rilascia la memoria del buffer
    cout << "Scrittura su " << outName << " completata." << std::endl;
    file.close();
    return 0;
}

std::string generateString (){

    std::string s;
    int random = generateRandomNumber(1,totSize); //per fare le singole parole di dimensione randomica
      for (int i = 0; i < random; ++i) {
        int random_index = generateRandomNumber(0,3);  // Genera un numero casuale tra 0 e 3
        s += sigma[random_index];  // Concatenazione del carattere casuale
    }
    return s;
}
/*int edsGeneration(std::ofstream& file){
 
    std::string output;

    for(int i = 0; i<numDegeneration; i++){ //Insiemi
        std::string degeneration = "{";

        int random = generateRandomNumber(1,maxPerDeg); //numero parole in un insieme
        for(int j=0; j<random ; j++){ //Crea una parola
            std::string s = generateString();
            degeneration += s;
            if(j != random-1) degeneration += ',';
        }

        degeneration += "}";
        output += degeneration; //inserisco un insieme nell'output
    }

    //cout << "output finale: " << output << endl;
    file << output;
    cout << "Scrittura su " << outName << " completata." << std::endl;
    file.close();
    return 0;
}*/

int edsGeneration(std::ofstream& file){
 
    std::string output;

    for(int i = 0; i<numDegeneration; i++){ //Insiemi
        std::string degeneration = "{";

        int random = generateRandomNumber(1,maxPerDeg); //numero parole in un insieme
        for(int j=0; j<random ; j++){ //Crea una parola
            std::string s = generateString();
            degeneration += s;
            if(j != random-1) degeneration += ',';
        }

        degeneration += "}";
        output += degeneration; //inserisco un insieme nell'output
        file << degeneration; //Scrittura bufferizzata
        cout << "Scrittura numero " << i+1 << " completata!!" << endl;
    }


    cout << "Scrittura su " << outName << " completata." << std::endl;
    file.close();
    return 0;
}

void printGlobal (){
    cout << "outName " << outName << endl;
    cout << "maxPerDeg " << maxPerDeg << endl;
    cout << "totSize " << totSize << endl;
    cout << "numDegeneration " << numDegeneration << endl;
    cout << "Type " << type << endl;
}
unsigned long long gb_to_bytes(unsigned int gb) {
    // 1 GB = 1024^3 Byte
    unsigned long long bytes_in_gb = 1024ULL * 1024ULL * 1024ULL;
    return gb * bytes_in_gb;
}


//MAIN ----------------------------------------------------------------
int main(int argc, char* argv[]){

    //Verifica 0 parametri 
    if (argc == 1){
        std::cerr << "Error: Missing required parameters.\n";
        return 1;
    }

    // Verifica gli argomenti passati
    if (argc > 1 && std::string(argv[1]) == "--help"){
        displayHelp();
        return 0;
    }


    // Verifica gli argomenti passati
    if (argc > 1 && std::string(argv[1]) == "--version"){
        displayVersion();
        return 0;
    }

 

    // Analizza gli argomenti della riga di comando
    for(int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--type") == 0) {
            if (i + 1 < argc) { // Controlla se c'è un argomento successivo
                if (strcmp(argv[i + 1], "R") == 0) {
                    type = 'R'; // RAW Generation
                } else if (strcmp(argv[i + 1], "E") == 0) {
                    type = 'E'; // EDS Generation
                } else if (strcmp(argv[i + 1], "I") == 0) {
                    type = 'I'; // EDS-Intensive Generation
                }else if (strcmp(argv[i + 1], "T") == 0) {
                    type = 'T'; // Test
                }else {
                    type = 'R'; // Valore predefinito
                }
            }
        } else if (strcmp(argv[i], "--maxPerDeg") == 0) {
            if (i + 1 < argc) {
                maxPerDeg = std::stoi(argv[i + 1]); // Converte in intero
            }
        } else if (strcmp(argv[i], "--numDeg") == 0) {
            if (i + 1 < argc) {
                numDegeneration = std::stoi(argv[i + 1]); // Converte in intero
            }
        } else if (strcmp(argv[i], "--totSize") == 0) {
            if (i + 1 < argc) {

                totSize = std::stoi(argv[i + 1]); // Converte in intero
            }
        } else if (strcmp(argv[i], "--outputName") == 0) {
            if (i + 1 < argc) {
                outName = argv[i + 1]; // Assegna il nome del file
            }
        }
    }

       
    // Crea un oggetto di tipo ofstream per aprire il file in modalità di scrittura
    
    // Crea un oggetto di tipo ofstream
    std::ofstream file;

  
    // Seleziona il tipo di file in base a 'type'
    if (type == 'R') {
        file.open(outName + ".txt");
    } 
    else if (type == 'E' || type == 'I') {
        file.open(outName + ".eds");
    } 
    else if (type == 'T') {
        file.open(outName + ".txt");
    } 
    else {
        std::cout << "Errore Assegnazione TYPE" << std::endl;
        return 1;
    }
    
    // Controlla se il file è stato aperto correttamente
    if (!file) {
        std::cerr << "Errore nell'apertura del file!" << std::endl;
        return 1;
    }


    //eseguo la funzione di generazione
    switch (type)
    {
    case 'R':
        rawGeneration(file);
        break;
    case 'E':
        edsGeneration(file);
        break;
    case 'I':
        break;
    case 'T':
        printGlobal();
        break;
    
    default:
        break;
    }
    return 0;

}