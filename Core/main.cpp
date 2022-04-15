#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "Headers/TText.h"
#include "Headers/TTextLink.h"

int main(){
    TTextLink::InitMemSystem(); // инициализация памяти!!!

    std::ifstream InFile("../../file.txt");

    char h[10]  = "Head";
    char h1[10] = "Head1";
    char d[10]  = "Down";

    PTTextLink Down = new TTextLink(d);
    PTTextLink Next = new TTextLink(h1);
    PTTextLink Head = new TTextLink(h, Next, Down);

    // TText ptr1(nullptr);
    TText R;
    R.Read("../../file.txt");
    R.Write("../../foo.txt");
    R.Print();
    // TText Ttext(ptr1.ReadText(InFile));

    // Ttext.PrintText(Ttext.pFirst);
    
    // Ttext.Reset(); // установить pCurrent на pFirst 

    
    // Ttext.PrintCurrent();

    // Ttext.GoNext();
    // Ttext.PrintCurrent();

    // Ttext.GoNext();
    // Ttext.PrintCurrent();

    
    
    
    return 0;
}