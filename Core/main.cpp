#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "Headers/TText.h"


int main(){
    // system("node ../../../test.js");
    TTextLink::InitMemSystem(); // инициализация памяти!!!

    std::ifstream InFile("../file.txt");
    // system("node ../../test.js");
    
    TText R;
    R.Read("../file.txt");
    // // std::cout << R.Print().str();

    R.Reset();

    
    std::cout << R.GetLine() << std::endl;
    while(!R.GoNext()){
        std::cout << R.GetLine() << std::endl;
    }




    R.Write("../foo.txt"); 
    // std::cout << R.Print().str();
    std::cout << R.GetCopy()->Print().str() << std::endl;
    TTextLink::MemCleaner(R); std::cout << std::endl;
    std::cout << R.GetCopy()->Print().str() << std::endl;
    // std::cout << R.Print().str();
    system("node ../foo.txt");

    

    


    
    
    
    return 0;
}