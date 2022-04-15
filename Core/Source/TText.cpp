#include "../Headers/TText.h"


PTTextLink TText::GetFirstAtom (PTTextLink pl) {
    
    PTTextLink pLink = pCurrent;

    while (pLink != nullptr){
        pLink = pLink->pDown;
    }

    return pLink;
    
}

void TText::WriteText (std::ofstream& Txtfile, PTTextLink ptl) {
    
    PTTextLink pptl = ptl;

    while (pptl != nullptr){

        Txtfile << pptl->GetString() << std::endl;

        if (pptl->pDown != nullptr){
            Txtfile << '{' << std::endl;

            WriteText(Txtfile, ptl->pDown);

            if (pptl->pNext == nullptr){
                Txtfile << "}" << std::endl;
            }

        }
        

        pptl = pptl->pNext;        
    }

}

void TText::PrintText (PTTextLink ptl ) {

    PTTextLink pptl = ptl;

    while (pptl != nullptr){

        std::cout << pptl->GetString() << std::endl;

        if (pptl->pDown != nullptr){
            std::cout << '{' << std::endl;

            PrintText(ptl->pDown);

            if (pptl->pNext == nullptr){
                std::cout << "}" << std::endl;
            }

        }
        

        pptl = pptl->pNext;        
    }

    

    
}

PTTextLink TText::ReadText (std::ifstream &TxtFile) {
    PTTextLink pHead, ptl;
    pHead = ptl = new TTextLink();
    char StrBuf[TextLineLength];
    int StrLen = TextLineLength;

    while(TxtFile.eof() == 0){
        TxtFile.getline(StrBuf,StrLen, '\n');
        if (StrBuf[0] == '}'){
            break;
        }
        else if (StrBuf[0] == '{'){
            ptl->pDown = ReadText(TxtFile);
        }
        else {
            ptl->pNext = new TTextLink(StrBuf, nullptr, nullptr);
            ptl = ptl->pNext;
        }
    }

    ptl = pHead;

    if (pHead->pDown == nullptr){
        pHead = pHead->pNext;
        delete ptl;
    }

    return pHead;
}

TText::TText(PTTextLink pl){
    if (pl == nullptr){
        pl = new TTextLink();
    }
    pFirst = pl;
}

int TText::GoFirstLink(void){
    while (!Path.empty())
        Path.pop();
    pCurrent = pFirst;

    if (pCurrent == nullptr) SetRetCode(TextError);
    else SetRetCode(TextOk);
    
    return RetCode;
}

int TText::GoDownLink (void) {
    SetRetCode(TextError);

    if (pCurrent != nullptr) {
        if (pCurrent->pDown != nullptr) {
            Path.push(pCurrent);
            pCurrent = pCurrent->pDown;
            SetRetCode(TextOk);
        }
    }

    return RetCode;
}

int TText::GoNextLink(void){
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

int TText::GoPrevLink (void) {
    SetRetCode(TextError);

    if (Path.size() != 0){
        PTTextLink pLink;
        pLink = Path.top();
        Path.pop();
        pCurrent = pLink;

        SetRetCode(TextOk);

    }

    return RetCode;
}

std::string TText::GetLine(void){
    return pCurrent->GetString();
}

void TText::SetLine(std::string s){    
    if (pCurrent == nullptr){
        SetRetCode(TextError);
    }
    else{

        char Buff[TextLineLength];
        s.copy(Buff, s.length());
        Buff[TextLineLength - 1] = '\0';

        PTTextLink pLink = new TTextLink(Buff, pCurrent->pNext, pCurrent->pDown);   

        SetRetCode(TextOk);
    }

    return;
}

void TText::InsDownLine(std::string s) { // переделать
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else {
        char Buff[TextLineLength];
        s.copy(Buff, s.length());
        Buff[TextLineLength - 1] = '\0';

        PTTextLink PCurDown = pCurrent->pDown;
        PTTextLink pNewDown = new TTextLink(Buff, PCurDown);
        
        pCurrent->pDown = pNewDown;

        SetRetCode(TextOk);
    }
}

void TText::InsDownSection(std::string s) { // переделать
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else {
        char Buff[TextLineLength];
        s.copy(Buff, s.length());
        Buff[TextLineLength - 1] = '\0';

        PTTextLink PCurDown = pCurrent->pDown;
        PTTextLink pNewDown = new TTextLink(Buff, nullptr, PCurDown);

        pCurrent->pDown = pNewDown;

        SetRetCode(TextOk);
    }
}

void TText::InsNextLine(std::string s){
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else {
        char Buff[TextLineLength];
        s.copy(Buff, s.length());
        Buff[TextLineLength - 1] = '\0';

        PTTextLink PCurNext = pCurrent->pNext;
        PTTextLink pNewNext = new TTextLink(Buff, PCurNext);

        pCurrent->pNext = pNewNext;

        SetRetCode(TextOk);
    }
}

void TText::InsNextSection(std::string s){
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else {
        char Buff[TextLineLength];
        s.copy(Buff, s.length());
        Buff[TextLineLength - 1] = '\0';

        PTTextLink PCurNext = pCurrent->pNext;
        PTTextLink pNewNext = new TTextLink(Buff, nullptr, PCurNext);

        pCurrent->pNext = pNewNext;

        SetRetCode(TextOk);
    }
}

void TText::DelDownLine(void){
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else if (pCurrent->pDown == nullptr) {
        SetRetCode(TextError);
    }
    else {
        PTTextLink pCurDown = pCurrent->pDown;
        PTTextLink pCurDownNext = pCurDown->pNext;
        
        if (pCurDownNext->pNext == nullptr) { // проверка на атомарность
            pCurrent->pDown = pCurDownNext;       
        }
        
        SetRetCode(TextOk);
    }
}

void TText::DelDownSection(void){
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else if (pCurrent->pDown == nullptr) {
        SetRetCode(TextError);
    }
    else {
        PTTextLink pCurDown = pCurrent->pDown;
        PTTextLink pCurDownNext = pCurDown->pNext;
        
        pCurrent->pDown = pCurDownNext;       
         
        SetRetCode(TextOk);
    }
}

void TText::DelNextLine(void){
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else if (pCurrent->pNext == nullptr) {
        SetRetCode(TextError);
    }
    else {
        PTTextLink pCurNext = pCurrent->pNext;
        PTTextLink pCurNextNext = pCurNext->pNext;
        
        if (pCurNextNext->pNext == nullptr) { // проверка на атомарность
            pCurrent->pNext = pCurNextNext;       
        }
        
        SetRetCode(TextOk);
    }
}

void TText::DelNextSection(void){
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else if (pCurrent->pNext == nullptr) {
        SetRetCode(TextError);
    }
    else {
        PTTextLink pCurNext = pCurrent->pNext;
        PTTextLink pCurNextNext = pCurNext->pNext;
        
        // if (pCurNextNext->pNext == nullptr) { // проверка на атомарность
            pCurrent->pNext = pCurNextNext;       
        // }
        
        SetRetCode(TextOk);
    }
}

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

void TText::Read (char * pFileName) {

    std::ifstream InFile(pFileName);
    this->Reset();

    pFirst = this->ReadText(InFile);
}

void TText::Write (char * pFileName) {
    
    std::ofstream InFile(pFileName);

    WriteText(InFile , pFirst);


}

void TText::Print (void) {
    this->PrintText(pFirst);
}