#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "Headers/TText.h"


int main(){
    TTextLink::InitMemSystem(); // инициализация памяти!!!

    std::ifstream InFile("../../file.txt");

    
    TText R;
    R.Read("../../file.txt");
    // // std::cout << R.Print().str();
    // R.Write("../../foo.txt");

    R.Reset();
    R.InsDownSection("adasd");
    std::cout << R.Print().str();


    

    


    
    
    
    return 0;
}