#include <iostream>
#include <string>
#include <cstring> // Necessario per strcmp
#include <cstdlib>  // Per rand() e srand()
#include <ctime>    // Per time()
#include <fstream> // Libreria per la gestione dei file
#include <random>

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

*/
using namespace std;

//MACROS -------------------------------------------------------------
#define SIGMA_SIZE 4  // Dimensione dell'array
//#define SIGMA {'a', 'c', 'g', 't'}  // Definizione dell'array di caratteri

//GLOBAL VARS --------------------------------------------------------

char sigma[SIGMA_SIZE] = {'a', 'c', 'g', 't'};    
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

int displayVersion(){
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
int displayHelp() {
 std::cout << "Usage: EDS-GEN [options] [arguments]" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --help                        Show this help message and exit." << std::endl;
    std::cout << std::endl;
    std::cout << "  --output <outputfile>          Specify the name of the output file." << std::endl;
    std::cout << "                                 Example: --output result.txt" << std::endl;
    std::cout << std::endl;
    std::cout << "  --size <TOTsize>               Set the maximum size of the generated output." << std::endl;
    std::cout << "                                 Example: --size 1000" << std::endl;
    std::cout << std::endl;
    std::cout << "  --repeatability <level>        Set the repeatability level for the EDS (Elastic Degenerate Sequence)." << std::endl;
    std::cout << "                                 Accepted values: 1 to 10." << std::endl;
    std::cout << "                                 Example: --repeatability 5" << std::endl;
    std::cout << std::endl;
    std::cout << "  --degenerate <percentage>      Set the percentage of degenerate symbols in the generated sequence." << std::endl;
    std::cout << "                                 Accepted values: 0 to 100." << std::endl;
    std::cout << "                                 Example: --degenerate 25" << std::endl;
    std::cout << std::endl;
    std::cout << "  --seed <seedvalue>             Specify a seed for random number generation to ensure repeatable results." << std::endl;
    std::cout << "                                 Example: --seed 12345" << std::endl;
    std::cout << std::endl;
    std::cout << "  --alphabet <alphabetType>      Specify the type of alphabet used in the generation." << std::endl;
    std::cout << "                                 Options: \"genomic\", \"amino\", \"custom\"" << std::endl;
    std::cout << "                                 Example: --alphabet genomic" << std::endl;
    std::cout << std::endl;
    std::cout << "  --custom-alphabet <string>     If --alphabet is set to \"custom\", define the custom alphabet." << std::endl;
    std::cout << "                                 Example: --custom-alphabet \"abcdxyz\"" << std::endl;
    std::cout << std::endl;
    std::cout << "  --version                      Display the version of the program and exit." << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  EDS-GEN --output sequence.txt --size 500 --repeatability 3 --degenerate 20" << std::endl;
    std::cout << "  EDS-GEN --output genome.fasta --size 1000 --alphabet genomic" << std::endl;
    std::cout << "  EDS-GEN --output proteins.txt --alphabet amino" << std::endl;
    return 0;

}
int rawGeneration(std::ofstream& file){
    //char sigma[SIGMA_SIZE] = SIGMA;
    std::cout << "Gen RAW-String" << std::endl;

    // Inizializza il generatore di numeri casuali
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "------------------------------"  << endl;
    cout << "filename output -> " << outName <<endl;
    cout << "Tot size DNA -> " << totSize <<endl;
    cout << "------------------------------"  << endl;


    //Creazione RAW-String classico
    std::string output;

    for (int i = 0; i < totSize; ++i) {
        int random_index = rand() % SIGMA_SIZE;  // Genera un numero casuale tra 0 e 3
        output += sigma[random_index];  // Concatenazione del carattere casuale
    }

    cout << "Final RAW-String " << output << endl; 
    file << output;
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
    }

    cout << "output finale: " << output << endl;
    file << output;
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











/* Cose inutili
   //char SIGMA[4] = {'a', 'c', 'g', 't'}; //alfabeto genomico

    int choice;

    std::cout << "--- Starting ---" << std::endl;

    do {
        // Stampa del menu
        
        std::cout << "\n--- Menu ---" << std::endl;
        std::cout << "1. RAW-DNA" << std::endl;
        std::cout << "2. Opzione 2" << std::endl;
        std::cout << "3. Usage help" << std::endl;
        std::cout << "0. Esci" << std::endl;
        std::cout << "------------" << std::endl;
        std::cout << "Inserisci la tua scelta: ";
        
        std::cin >> choice;  // Input dell'utente

        // Esecuzione dell'azione corrispondente all'opzione scelta
        switch (choice) {
            case 1:
                option1(outfilename, totSize, file);
                break;
            case 2:
                option2();
                break;
            case 3:
                displayHelp();
                break;
            case 0:
                std::cout << "Uscita dal programma." << std::endl;
                break;
            default:
                std::cout << "Scelta non valida. Riprova." << std::endl;
        }
    } while (choice != 0);  // Continua finché l'utente non sceglie di uscire





   for(int i = 1 ; i<argc ; i=i+2){
        if(argv[i] == "--type"){
            switch (argv[i+1]){
                case 'R':
                    type = 'R'; //RAW Generation
                    break;
                case 'E':
                    type = 'E'; //EDS Generation
                    break;
                case 'D':
                    type = 'D'; //EDS-Intensive Generation
                    break;
                default:
                    type = "R";
                    break;
            }
            
                std::string outName; //file name senza estensione
                int maxPerDeg; //numero massimo di stringhe in un insieme
                int totSize; //numero massimo di caratteri di ogni singola sequenza degenerata
                int numDegeneration; //numero di insiemi
                char type;
            
        }elseif(argv[i] == "--maxPerDeg") maxPerDeg = argv[i+1];
        elseif(argv[i] == "--numDeg") numDegeneration = argv[i+1];
        elseif(argv[i] == "--totSize") totSize = argv[i+1];
        elseif(argv[i] == "--outputName") outName = argv[i+1];
        
        
        
    }
*/