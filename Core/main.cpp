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

    R.Reset();
    R.InsDownSection("new Section");


    R.Write("../../foo.txt"); 
    // std::cout << R.Print().str();
    std::cout << R.GetCopy()->Print().str() << std::endl;
    TTextLink::MemCleaner(R); std::cout << std::endl;
    std::cout << R.GetCopy()->Print().str() << std::endl;
    // std::cout << R.Print().str();

    

    


    
    
    
    return 0;
}