#include <iostream>
#include <random>
#include <string>

using namespace std;
int main(int argc, char* argv[]){

if(argc != 3){
    std::cerr << "Errore: Questo programma richiede 2 parametri." << std::endl;
    std::cerr << "Uso: " << argv[0] << " <output> <TOTsize> [--Option1 --Option2] " << std::endl;
    return 1;
}

std::string outfilename = argv[1]; 
int totSize = std::stoi(argv[2]); ;
char sigma[4] = {'a', 'c', 'g', 't'}; //alfabeto genomico

// 1. Generare un numero casuale tra 0 e 3
std::random_device rd;  // Generatore di numeri casuali
std::mt19937 gen(rd());  // Inizializzazione del generatore
std::uniform_int_distribution<> dis(0, 3);  // Distribuzione uniforme



cout << "--- Starting ---" << endl;
cout << argv[0]  << endl;
cout << "------------------------------"  << endl;
cout << "filename output -> " << argv[1] <<endl;
cout << "Tot size DNA -> " << argv[2] <<endl;
cout << "------------------------------"  << endl;


//Creazione RAW-String classico
 std::string output;

for(int i=0 ; i<totSize ; i++){
    int random_number = dis(gen);  // Estrazione del numero casuale
    output = output + sigma[random_number];
}

cout << "Final RAW-String " << output << endl; 
}