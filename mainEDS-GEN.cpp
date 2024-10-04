#include <iostream>
#include <string>
#include <cstdlib>  // Per rand() e srand()
#include <ctime>    // Per time()

using namespace std;

//MACROS -------------------------------------------------------------
#define SIGMA_SIZE 4  // Dimensione dell'array
#define SIGMA {'a', 'c', 'g', 't'}  // Definizione dell'array di caratteri


//FUNCTIONS ----------------------------------------------------------
void option1(std::string outfilename, int totSize){
    char sigma[SIGMA_SIZE] = SIGMA;
    std::cout << "Gen RAW-String" << std::endl;

    // Inizializza il generatore di numeri casuali
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "------------------------------"  << endl;
    cout << "filename output -> " << outfilename <<endl;
    cout << "Tot size DNA -> " << totSize <<endl;
    cout << "------------------------------"  << endl;


    //Creazione RAW-String classico
    std::string output;

    for (int i = 0; i < totSize; ++i) {
        int random_index = rand() % SIGMA_SIZE;  // Genera un numero casuale tra 0 e 3
        output += sigma[random_index];  // Concatenazione del carattere casuale
    }

    cout << "Final RAW-String " << output << endl; 

}

void option2(){
    std::cout << "Hai scelto l'opzione 1." << std::endl;
}
void option3(){
    std::cout << "Hai scelto l'opzione 1." << std::endl;
}
void option4(){
    std::cout << "Hai scelto l'opzione 1." << std::endl;
}


//MAIN ----------------------------------------------------------------
int main(int argc, char* argv[]){

    if(argc != 3){
        std::cerr << "Errore: Questo programma richiede 2 parametri." << std::endl;
        std::cerr << "Uso: " << argv[0] << " <output> <TOTsize> [--Option1 --Option2] " << std::endl;
        return 1;
    }

    std::string outfilename = argv[1]; 
    int totSize = std::stoi(argv[2]);

    //char SIGMA[4] = {'a', 'c', 'g', 't'}; //alfabeto genomico

    int choice;

    std::cout << "--- Starting ---" << std::endl;

    do {
        // Stampa del menu
        std::cout << "\n--- Menu ---" << std::endl;
        std::cout << "1. Opzione 1" << std::endl;
        std::cout << "2. Opzione 2" << std::endl;
        std::cout << "3. Opzione 3" << std::endl;
        std::cout << "0. Esci" << std::endl;
        std::cout << "Inserisci la tua scelta: ";
        
        std::cin >> choice;  // Input dell'utente

        // Esecuzione dell'azione corrispondente all'opzione scelta
        switch (choice) {
            case 1:
                option1(outfilename, totSize);
                break;
            case 2:
                option2();
                break;
            case 3:
                option3();
                break;
            case 0:
                std::cout << "Uscita dal programma." << std::endl;
                break;
            default:
                std::cout << "Scelta non valida. Riprova." << std::endl;
        }
    } while (choice != 0);  // Continua finché l'utente non sceglie di uscire

    return 0;

}