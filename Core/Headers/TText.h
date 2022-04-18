#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "TDataCom.h"
#include "TStack.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include "TTextLink.h"

class TText;
typedef TText* PTText;

class TText : public TDataCom {
protected:
    PTTextLink pCurrent; // указатель текущей строки
    PTTextLink pFirst; // указатель корня дерева
    std::stack< PTTextLink > Path; // стек траектории движения по тексту
    std::stack< PTTextLink > St; // стек для итератора
    PTTextLink GetFirstAtom (PTTextLink pl); // поиск первого атома
    std::stringstream PrintText (PTTextLink ptl); // печать текста со звена ptl
    PTTextLink ReadText (std::ifstream &TxtFile); //чтение текста из файла

    // методы форматирования кода
    int CheckForBraces(char* buff);
    char* DeleteSpace(char* buff);

public:
    TText (PTTextLink pl = nullptr);
    ~TText () {pFirst =nullptr;};
    PTText GetCopy();
    // навигация
    int GoFirstLink (void); // переход к первой строке
    int GoDownLink (void); // переход к следующей строке по Down
    int GoNextLink (void); // переход к следующей строке по Next
    int GoPrevLink (void); // переход к предыдущей позиции в тексте
    // доступ
    std::string GetLine(void); // чтение текущей строки
    void SetLine ( std::string s); // замена текущей строки
    // модификация
    void InsDownLine (std::string s); // вставка строки в подуровень
    void InsDownSection (std::string s); // вставка раздела в подуровень
    void InsNextLine (std::string s); // вставка строки в том же уровне
    void InsNextSection (std::string s); // вставка раздела в том же уровне
    void DelDownLine (void); // удаление строки в подуровне
    void DelDownSection (void); // удаление раздела в подуровне
    void DelNextLine (void); // удаление строки в том же уровне
    void DelNextSection (void); // удаление раздела в том же уровне
    // итератор
    bool Reset (void); // установить на первую звапись
    bool IsTextEnded (void) const; // текст завершен?
    bool GoNext (void); // переход к следующей записи
    //работа с файлами
    void Read (char * pFileName); // ввод текста из файла
    void Write (char * pFileName); // вывод текста в файл
    //печать
    std::stringstream Print (void); // печать текста

};


