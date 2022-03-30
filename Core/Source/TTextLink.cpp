#include "../Headers/TTextLink.h"
#include "../Headers/TText.h"

void TTextLink::InitMemSystem(int size){
    MemHeader.pFirst = (PTTextLink) (new char[sizeof(TTextLink)*size]);
    MemHeader.pFree = MemHeader.pFirst;
    MemHeader.pLast = MemHeader.pFirst + (size - 1);
    PTTextLink pLink = MemHeader.pFirst;
    for (int i = 0; i < size - 1; i++, pLink++){
        pLink->pNext = pLink + 1;
    }
    pLink->pNext = 0;
}

void TTextLink::PrintFreeLink(){
    PTTextLink pLink = MemHeader.pFirst;
    for (; pLink != nullptr; pLink = pLink->pNext){
        std::cout << pLink->Str << std::endl;
    }
}

void * TTextLink::operator new(size_t size){
    PTTextLink pLink = MemHeader.pFree;
    if (MemHeader.pFree != nullptr)
        MemHeader.pFree = pLink->pNext;
    return pLink;
    
}

void TTextLink::operator delete(void * pM){
    PTTextLink pLink = (PTTextLink)pM;
    pLink->pNext = MemHeader.pFree;
    MemHeader.pFree = pLink;
}

/*

    --------
    --------
    -------- delete 
            --------
                    --------
                    --------
                    *
            --------
            -------- 
            * 
    *

*/


void TTextLink::MemCleaner(TText &txt){
    // Обход и маркировка всех звеньев текста
    for (txt.Reset(); !txt.IsTextEnded();  txt.GoNext()){
        if (txt.GetLine().find("&&&") != 0)
            txt.SetLine("&&&" + txt.GetLine());
    }
    PTTextLink pLink = MemHeader.pFree;
    // Обход и маркировка всех свободных звеньев
    for (;pLink != nullptr; pLink = pLink->pNext)
        strcpy(pLink->Str, "&&&");

    pLink = MemHeader.pFirst;
    // Поиск не промаркированных звеньев и их удаление
    for (;pLink <= MemHeader.pLast; pLink++){
        if (strstr(pLink->Str, "&&&") != NULL)
            strcpy(pLink->Str, pLink->Str + 3);
        else delete pLink;
    }
}
