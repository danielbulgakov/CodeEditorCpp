#include "../Headers/TText.h"
#include "../Headers/TTextLink.h"

TText::TText(PTTextLink pl)
{
    if (pl == nullptr){
        pl = new TTextLink();
    }
    pFirst = pl;
}

int TText::GoFirstLink(void)
{
    while (!Path.empty())
        Path.pop();
    pCurrent = pFirst;

    if (pCurrent == nullptr) SetRetCode(TextError);
    else SetRetCode(TextOk);
    
    return RetCode;
}

int TText::GoNextLink(void)
{
    SetRetCode(TextError);

    if (pCurrent != nullptr) {
        if (pCurrent->pNext != nullptr) {
            Path.push(pCurrent);
            pCurrent = pCurrent->pNext;
            SetRetCode(TextOk);
        }
    }

    return RetCode;
}

std::string TText::GetLine(void){return std::string();};
void TText::SetLine(std::string s){return;};
bool TText::Reset (void){
    St = std::stack< PTTextLink >();
    pCurrent = pFirst;
    if (pCurrent != nullptr) {
        //St.push(pCurrent);
        if (pCurrent->pNext != nullptr) {
            St.push(pCurrent->pNext);
        }
        if (pCurrent->pDown != nullptr) {
            St.push(pCurrent->pDown);
        }
    }
    return IsTextEnded();
};

bool TText::IsTextEnded (void) const{
    return !St.size();
};

bool TText::GoNext (void){
    if (!IsTextEnded()) {
        pCurrent = St.top();
        St.pop();
        //if (pCurrent != pFirst) {
            if (pCurrent->pNext != nullptr) {
                St.push(pCurrent->pNext);
            }
            if (pCurrent->pDown != nullptr) {
                St.push(pCurrent->pDown);
            }
        //}
    }
    return IsTextEnded();
};
