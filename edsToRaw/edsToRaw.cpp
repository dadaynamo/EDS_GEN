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
        //cout << MaxComb << " " << degen[i] <<endl;  
    }

  

    int k = 0;
    cout << "Inserisci numero K di combinazioni da creare nel file Raw." <<endl << "Numero max creabile è " << MaxComb << endl;
    cin >> k;
    if(k > MaxComb){
        std::cerr << "Stai cercando di generare più combinazioni del previsto " << std::endl;
        return 1;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    
    //GENERAZIONE DI K COMBINAZIONI
    string Pathvect = "";
    int cinsert = 0;
    std::string path = "";
    /*
    while (cinsert < k){
        for(int i=0; i<N; i++){
            // Generatore casuale
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
    }*/
    while (cinsert < k) {
        path = ""; // Reset della variabile `path` a ogni iterazione

        for (int i = 0; i < N; i++) {
            // Generatore casuale
            std::uniform_int_distribution<> distrib(1, degen[i]);
            int n = distrib(gen);

            // Aggiungi il delimitatore solo se `path` non è vuoto
            if (!path.empty()) {
                path += "-";
            }
            path += std::to_string(n);
        }

        // Verifica se il pattern esiste già in Pathvect
        if (Pathvect.find(path) != std::string::npos) {
            std::cout << "Il pattern è stato trovato!" << std::endl;
        } else {
            // Aggiungi il nuovo path a Pathvect con il separatore corretto
            if (cinsert == 0) {
                Pathvect = path;
            } else {
                Pathvect += "-$-" + path;
            }
            cinsert++;
        }
    }

    Pathvect = Pathvect + "|";

    cout << "Il Pathvect è: " << Pathvect << endl;


    /*
        INIZIO TRASFORMAZIONE Pathvect in stringhe concatenate -------------------------------------------------------------
     */
 /*   
    // Resetta lo stato EOF e riporta il puntatore all'inizio
    file.clear();              // Cancella lo stato EOF
    file.seekg(0, std::ios::beg); // Riporta il puntatore all'inizio
    // 
    
    // Apro in modalità appen il file output
    std::ofstream fileOut(outputFilename, std::ios::app);

    if (!fileOut.is_open()) { // Controlla se il file è stato aperto correttamente
        std::cerr << "Errore: impossibile aprire il file." << std::endl;
        return 1;
    }



    string word = ""; //Word corrente rilevata
    string Output; // Output finale che scriverò su
    char c; //lettera prelevata man mano dal file eds

    int Ins = 1; //Indice dell'insieme FILE
    int wInIns = 1; //indice parola dell'insieme FILE
    int num; //val in Pathvect corrente PATHVECT
    int i=0; //indice scorrimento PATHVECT
    int i_num=1; //indice d'insieme corrispondente a num PATHVECT

    num = Pathvect[i] - '0'; // Converti il carattere in numero intero
    //cout << "Partenza: Ins: " << Ins << " wInIns: " << wInIns << " num: " << num << " i_num: " << i_num << endl;

    while (file.get(c)) { // Leggi un carattere alla volta
       // std::cout << "c prelevato:  " << c <<" Ins: " << Ins << " wInIns: " << wInIns << " num: " << num << " i_num: " << i_num  <<endl; // Stampa il carattere (puoi elaborarlo qui)
        if (c == '{'){
            //Non succede nulla
            //continue;
        }
        else if(c == ','){

            if(Ins == i_num && wInIns == num){
                //cout << "-------------------- word tecnica: " <<  word << " Insieme da cui è stata presa: " << Ins << " indice nell'insieme preso: "<< wInIns << " insieme detto da pathvect: "<< i_num << " Num:"<< num <<endl;
                Output = Output + word;    
                fileOut << word;
                //prelevo un nuovo NUMERO da pathvect
                i=i+2;
                if(Pathvect[i] == '$'){
                    //cout << "Fine parola" << endl;
                    Output = Output + "$"; 
                    fileOut << "$";            
                    cout << "FINE WORD DI PATHVECT: ho trovato un $" <<endl;
                    //ricarico il puntatore di lettura e resetto tutto
                    // Resetta lo stato EOF e riporta il puntatore all'inizio
                    file.clear();              // Cancella lo stato EOF
                    file.seekg(0, std::ios::beg); // Riporta il puntatore all'inizio
                    // 
                    Ins = 1; //Indice dell'insieme FILE
                    wInIns = 1; //indice parola dell'insieme FILE
                    i=i+2;
                    i_num=1; //indice d'insieme corrispondente a num PATHVECT
                    word="";
                    num = Pathvect[i] - '0'; // Converti il carattere in numero intero
                    continue;

                    
                }else if(Pathvect[i] == '|'){
                    cout << "FINISHED" <<endl;
                    break;
                }else{ //ho trovato un numero in pathvect... lo posso allora usare
                    num = Pathvect[i] - '0'; // Converti il carattere in numero intero
                    i_num++; //insieme di riferimento di questo nuovo numero
                }
            }
 
            word = "";
            wInIns++;
            //cout << "Ins: " << Ins << " wInIns: "<< wInIns << " i_num: "<< i_num << " num: "<< num <<endl;
            
        }
        else if(c == '}'){
            if(Ins == i_num && wInIns == num){
                //cout << "-------------------- word tecnica: " <<  word << " Insieme da cui è stata presa: " << Ins << " indice nell'insieme preso: "<< wInIns << " insieme detto da pathvect: "<< i_num << " Num:"<< num <<endl;
                Output = Output + word;    
                fileOut << word;
                //prelevo un nuovo NUMERO da pathvect
                i=i+2;
                if(Pathvect[i] == '$'){
                    //cout << "Fine parola" << endl;
                    Output = Output + "$";  
                    fileOut << "$";           
                    cout << "FINE WORD DI PATHVECT: ho trovato un $" <<endl;
                                        //ricarico il puntatore di lettura e resetto tutto
                    // Resetta lo stato EOF e riporta il puntatore all'inizio
                    file.clear();              // Cancella lo stato EOF
                    file.seekg(0, std::ios::beg); // Riporta il puntatore all'inizio
                    // 
                    Ins = 1; //Indice dell'insieme FILE
                    wInIns = 1; //indice parola dell'insieme FILE
                    i=i+2;
                    i_num=1; //indice d'insieme corrispondente a num PATHVECT
                    num = Pathvect[i] - '0'; // Converti il carattere in numero intero
                    word="";
                    continue;
   

                }else if(Pathvect[i] == '|'){
                    cout << "FINISHED" <<endl;
                    break;
                }else{ //ho trovato un numero in pathvect... lo posso allora usare
                    num = Pathvect[i] - '0'; // Converti il carattere in numero intero
                    i_num++;
                }
            }
            word = "";
            wInIns=1;
            Ins++;
            //cout << "Ins: " << Ins << " wInIns: "<< wInIns << " i_num: "<< i_num << " num: "<< num <<endl;
        }
        else{ //c è un carattere ACGT
            word = word + c;
            //cout << "word concatenata: " <<  word << endl;
        }

    }

   // cout << "Output Finale: "  << Output <<endl;

    cout << "le k combinazioni scritte correttamente in "<< outputFilename << endl; 
    file.close();
    fileOut.close(); // Chiudi il file Out
  */  return 0;
}


 






