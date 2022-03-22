#pragma once

#include "TTextLink.h"
#include "TDataCom.h"
#include "TStack.h"
#include <fstream>

typedef TText* PTText;

class TText : public TDataCom {
protected:
    PTTextLink pFirst; // указатель корня дерева
    PTTextLink pCurrent; // указатель текущей строки
    TStack< PTTextLink > Path; // стек траектории движения по тексту
    TStack< PTTextLink > St; // стек для итератора
    PTTextLink GetFirstAtom (PTTextLink pl); // поиск первого атома
    void PrintText (PTTextLink ptl); // печать текста со звена ptl
    PTTextLink ReadText (std::ifstream &TxtFile); //чтение текста из файла
public:
    TText (PTTextLink pl = NULL);
    ~TText () {pFirst =NULL;}
    PTText getCopy();
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
    int Reset (void); // установить на первую звапись
    int IsTextEnded (void) const; // текст завершен?
    int GoNext (void); // переход к следующей записи
    //работа с файлами
    void Read (char * pFileName); // ввод текста из файла
    void Write (char * pFileName); // вывод текста в файл
    //печать
    void Print (void); // печать текста
};