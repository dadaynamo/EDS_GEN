#include <iostream>
#include <string.h>
using namespace std;
int main(int argc, char* argv[]){

if(argc < 3){
    std::cerr << "Errore: Questo programma richiede 2 parametri." << std::endl;
    std::cerr << "Uso: " << argv[0] << " <output> <TOTsize> [--Option1 --Option2] " << std::endl;
    return 1;
}
char sigma[4] = {'a', 'c', 'g', 't'};
cout << "--- Starting ---" << endl;
cout << argv[0]  << endl;
cout << "----------------"  << endl;
cout << "filename output -> " << argv[1];
cout << "Tot size DNA -> " << argv[2];
cout << "----------------"  << endl;

}