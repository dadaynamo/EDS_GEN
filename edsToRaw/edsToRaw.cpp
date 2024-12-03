#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
/*
    {AC,G}{GC,TT}{A}
*/
using namespace std;

/* GLOBAL*/
    std::vector<int> degen; // Vettore di interi
    int N = 0; // Numero di simboli degeneri nel file EDS
    int MaxComb = 1; //Numero massimo di combinazioni creabili con il file EDS

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


void numDegenCalc(std::ifstream& file){
    char c; // Variabile per memorizzare il carattere corrente
    int count = 0;
    while (file.get(c)) { // Leggi un carattere alla volta
       // std::cout << c << endl; // Stampa il carattere
        if (c == '{'){
           // cout << "PER FORZA" << endl;
            count = 0;
        }
        if(c == ','){
            count ++; //passaggio parola nuova
        }
        if(c == '}'){
            degen.push_back(count+1);
        }
    }

}


int main(int argc, char* argv[]) {
    // Verifica parametri
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <file_input> <file_output>\n";
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];
    std::ifstream file(inputFilename);

    //Controllo file esiste
    if (!file) { // Controlla se il file è stato aperto correttamente
        std::cerr << "Errore nell'apertura del file " << inputFilename <<  " !" << std::endl;
        return 1;
    }
    numDegenCalc(file); //GENERAZIONE Degen array

    cout << "****************************************************************************" << endl;
    cout << "Struttura dati degen creata con successo !! " << endl;
    N = degen.size();
    for (size_t i = 0; i < degen.size(); ++i) {
        std::cout << degen[i] << " ";
    }
    cout << endl << "Numero di simboli degeneri (insiemi) è " << N << endl;
    cout << "****************************************************************************" << endl;
    
    
   
    for(int i=0; i<N; i++){
        MaxComb = MaxComb * degen[i];
        cout << MaxComb << " " << degen[i] <<endl;  
    }

    int k = 0;
    cout << "Inserisci numero K di combinazioni da creare nel file Raw." <<endl << "Numero max creabile è " << MaxComb << endl;
    cin >> k;
    if(k > MaxComb){
        std::cerr << "Stai cercando di generare più combinazioni del previsto " << std::endl;
        return 1;
    }

    //GENERAZIONE DI K COMBINAZIONI


    
    std::cout << "Combinazioni generate e salvate in '" << outputFilename << "'.\n";
    file.close();
    return 0;
}

/*
    {AC,G}{GC,TT}{A}
*/
