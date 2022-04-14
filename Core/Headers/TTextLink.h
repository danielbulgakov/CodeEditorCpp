#pragma once 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "TDataValue.h"


class TText;

enum TextErrors{
    TextOk = 0,
    TextNoDown = 101,
    TextNoNext = 102,
    TextNoPrev = 103,

    TextNoMem = -101,
    TextError = -102,
};

enum StaticParameters{
    MemSize = 20,
    TextLineLength = 100
};

class TTextLink;

typedef TTextLink* PTTextLink;
typedef char TStr[TextLineLength];

class TTextMem {
    PTTextLink pFirst; // указатель на первое звено
    PTTextLink pLast; // указатель на последнее звено
    PTTextLink pFree; // указатель на первое свободное звено
    friend class TTextLink;
};
 
typedef TTextMem *PTTextMem;

class TTextLink : public TDataValue {
protected:
    TStr Str; // поле для хранения строки текста
    PTTextLink pNext, pDown; // указатели по тек. уровень и на подуровень
    inline static TTextMem MemHeader; // система управления памятью
public:
    static void InitMemSystem (int size=MemSize); // инициализация памяти
    static void PrintFreeLink (void); // печать свободных звеньев
    void * operator new (size_t size); // выделение звена
    void operator delete (void *pM); // освобождение звена
    static void MemCleaner (TText &txt); // сборка мусора
    TTextLink (TStr s = NULL, PTTextLink pn = nullptr, PTTextLink pd = nullptr){
    pNext = pn; pDown = pd;
    if (s != NULL) strcpy(Str,s); else Str[0]='\0';
    }
    ~TTextLink() {}
    int IsAtom () {return pDown == nullptr;} // проверка атомарности звена
    PTTextLink GetNext() {return pNext;}
    PTTextLink GetDown() {return pDown;}
    PTDataValue GetCopy() {return new TTextLink(Str,pNext,pDown);}

    void Print() {std::cout << Str;}
    std::string GetString(){return this->Str;}
protected:
    virtual void Print (std::ostream &os) {os << Str;}
    friend class TText;
};

