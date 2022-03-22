#include "../Headers/TTextLink.h"
#include "../Headers/TText.h"

void TTextLink::InitMemSystem(int size=MemSize){
    MemHeader.pFirst = (PTTextLink) (new char[sizeof(TTextLink)*size]);
    MemHeader.pFree = MemHeader.pFirst;
    MemHeader.pLast = MemHeader.pFirst + (size - 1);
    PTTextLink pLink = MemHeader.pFirst;
    for (int i = 0; i < size - 1; pLink++){
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
    PTTextLink Next = nullptr;
    PTTextLink Cur = ((PTTextLink)pM)->pNext;
    while ( Cur != nullptr){
        Next = Cur->GetNext();
        delete Cur;
        Cur = Next;
    }
}