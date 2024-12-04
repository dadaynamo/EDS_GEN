#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <random>
/*
    {AC,G}{GC,TT}{A}
*/
using namespace std;

/* GLOBAL*/
    std::vector<int> degen; // Vettore di interi
    int N = 0; // Numero di simboli degeneri nel file EDS
    int MaxComb = 1; //Numero massimo di combinazioni creabili con il file EDS
    int MAX_NUM = INT32_MAX; 

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
        if(MaxComb < 0){
            //sforato
            MaxComb = MAX_NUM;
            break;
        }
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
    string Pathvect = "";
    int cinsert = 0;
    std::string path = "";
    while (cinsert < k){
        for(int i=0; i<N; i++){
            // Generatore casuale
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(1, degen[i]);

            int n = distrib(gen);
            //cout << n <<endl; 
            if(i != 0)
            path = path + "-" + std::to_string(n);
            else
            path = path  + std::to_string(n);
        }

        // Cerca il pattern nella stringa
        if (Pathvect.find(path) != std::string::npos) {
            std::cout << "Il pattern è stato trovato!" << std::endl;
        } else {
            //std::cout << "Il pattern non è stato trovato." << std::endl;
            if(cinsert == 0)
            Pathvect = Pathvect + path;
            if(cinsert != 0)
            Pathvect = Pathvect + "-$-" + path;
            path = "";
            cinsert ++;
        }
    }
    Pathvect = Pathvect + "|";

    cout << "Il Pathvect è: " << Pathvect << endl;


    /*
        INIZIO TRASFORMAZIONE Pathvect in stringhe concatenate
     */
    
    // Resetta lo stato EOF e riporta il puntatore all'inizio
    file.clear();              // Cancella lo stato EOF
    file.seekg(0, std::ios::beg); // Riporta il puntatore all'inizio


    // 
    int ins = 1; //Indice dell'insieme
    int wInIns = 1; //indice parola dell'insieme
    char c;
    for(int i=0; i<Pathvect.size(); i++){ //per ogni carattere di Pathvect trasformo il numero in
    if(Pathvect[i] == '-'){
        continue;
    }
    if(Pathvect[i] == '$'){
        cout << "Fine parola" << endl;
        continue;
    }

    try {
        int num = Pathvect[i] - '0'; // Converti il carattere in numero intero
        //Dentro num ho il numero della corrispondente stringa da prendere dal file eds
            
        while (file.get(c)) { // Leggi un carattere alla volta
        // std::cout << c << endl; // Stampa il carattere
            if (c == '{'){
            // cout << "PER FORZA" << endl;
                ins ++;
            }
            if(c == ','){
                wInIns ++;
            }
            if(c == '}'){
            }
        }
            

        std::cout << "Valore convertito: " << num+1 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Errore: stringa non valida! Contenuto: " << Pathvect[i] << std::endl;
    }

    }



    char c;
    while (file.get(c)) { // Leggi un carattere alla volta
        std::cout << c; // Stampa il carattere (puoi elaborarlo qui)
    }

    


    std::cout << "Combinazioni generate e salvate in '" << outputFilename << "'.\n";
    file.close();
    return 0;
}

/*
    {AC,G}{GC,TT}{A}
*/
