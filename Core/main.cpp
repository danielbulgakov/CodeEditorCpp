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
<<<<<<< HEAD
    
    std::cout << R.GetLine() << std::endl;
    while(!R.GoNext()){
        std::cout << R.GetLine() << std::endl;
    }
=======
    R.InsDownSection("new Section");


    R.Write("../../foo.txt"); 
    // std::cout << R.Print().str();
    std::cout << R.GetCopy()->Print().str() << std::endl;
    TTextLink::MemCleaner(R); std::cout << std::endl;
    std::cout << R.GetCopy()->Print().str() << std::endl;
    // std::cout << R.Print().str();
>>>>>>> 520c041702fab6eef735f4d413b0c2a1ad247086

    

    


    
    
    
    return 0;
}