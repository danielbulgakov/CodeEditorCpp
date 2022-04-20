#include "../Headers/TText.h"



PTTextLink TText::GetFirstAtom (PTTextLink pl) {
    
    PTTextLink tmp = pl;

    while(!tmp->IsAtom()){
        St.push(tmp);
        tmp = tmp->GetDown();
    }
    return tmp;
    
}

std::stringstream TText::PrintText (PTTextLink ptl) {

    static int level = 0;
    const int space_size = 4;
    
    PTTextLink pLink  = ptl;
    std::stringstream ss;
    while (pLink != nullptr){
        
        ss << std::string (space_size * level, ' ');
        pLink->Print(ss);
        ss << std::endl;
        
        if (pLink->pDown != nullptr){
            ss << std::string (space_size * level, ' ')<< '{' << std::endl;
            level++;
            ss << PrintText(pLink->pDown).rdbuf();
            level--;
            ss << std::string (space_size * level, ' ')<< '}' << std::endl;
        }

        pLink = pLink->pNext;
    }
    
  
    return ss;
    
}

int TText::CheckForBraces(char* buff) {
    std::string check (buff);
    check.erase(std::remove_if(check.begin(), check.end(), ::isspace), check.end());
    if (check.length() != 1) return 0;
    if (check[0] == '}') return 1;
    if (check[0] == '{') return 2;
    return 0;
}

char* TText::DeleteSpace(char* buff) {
    std::string check (buff);
    size_t start = check.find_first_not_of(' ');
    check = check.substr(start);
    strncpy(buff, check.c_str(), TextLineLength);
    return buff;
}

PTText TText::GetCopy() {
    PTTextLink pl1, pl2, pl = pFirst, cpl = nullptr;
    if (pFirst != nullptr){
        while(!St.empty())
            St.pop();
        while(true){
            if (pl != nullptr){
                pl = GetFirstAtom(pl);
                St.push(pl);
                pl = pl->GetDown();
            }
            else if (St.empty())
                break;
            else{
                pl1 = St.top();
                St.pop();
                if (strstr(pl1->Str, "Copy") == NULL){
                    pl2 = new TTextLink("Copy", pl1, cpl);
                    St.push(pl2);
                    pl = pl1->GetNext();
                    cpl = nullptr;
                }
                else {
                    pl2 = pl1->GetNext();
                    strcpy(pl1->Str, pl2->Str);
                    pl1->pNext = cpl;
                    cpl = pl1;
                }
            }
            
        }
    }
    return new TText(cpl);
}

PTTextLink TText::ReadText (std::ifstream &TxtFile) {
    PTTextLink pHead, ptl;
    pHead = ptl = new TTextLink();
    char StrBuf[TextLineLength];
    int StrLen = TextLineLength;

    while(TxtFile.eof() == 0){
        TxtFile.getline(StrBuf,StrLen, '\n');
        if (CheckForBraces(StrBuf) == 1){
            break;
        }
        else if (CheckForBraces(StrBuf) == 2){
            ptl->pDown = ReadText(TxtFile);
        }
        else {
            ptl->pNext = new TTextLink(DeleteSpace(StrBuf), nullptr, nullptr);
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
    SetRetCode(TextNoPrev);

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

    std::ostringstream stream; 
    pCurrent->Print(stream);

    return stream.str();
}

void TText::SetLine(std::string s){    
    if (pCurrent == nullptr){
        SetRetCode(TextError);
    }
    else{
        
        strncpy(pCurrent->Str, s.c_str(), TextLineLength);
        pCurrent->Str[TextLineLength - 1] = '\0';

        
        SetRetCode(TextOk);
    }

    return;
}

void TText::InsDownLine(std::string s) { // переделать
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink("", pd, nullptr);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pDown = pl;
    

        SetRetCode(TextOk);
    }
}

void TText::InsDownSection(std::string s) { // переделать
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink("", nullptr, pd);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pDown = pl;
    

        SetRetCode(TextOk);
    }
}

void TText::InsNextLine(std::string s){
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else {
        PTTextLink pd = pCurrent->pNext;
        PTTextLink pl = new TTextLink("", pd, nullptr);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pNext = pl;
    

        SetRetCode(TextOk);
    }
}

void TText::InsNextSection(std::string s){
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else {
        PTTextLink pd = pCurrent->pNext;
        PTTextLink pl = new TTextLink("", nullptr, pd);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pNext = pl;
    

        SetRetCode(TextOk);
    }
}

void TText::DelDownLine(void){
    SetRetCode(TextOk);
    if (pCurrent == nullptr) {
        SetRetCode(TextError);
    }
    else if (pCurrent->pDown == nullptr) {
        SetRetCode(TextError);
    }
    else {
        PTTextLink pCurDown = pCurrent->pDown;
        PTTextLink pCurDownNext = pCurDown->pNext;
        
        if (pCurDown->IsAtom()) { // проверка на атомарность
            pCurrent->pDown = pCurDownNext;       
        }
        
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
        
        if (pCurNext->IsAtom()) { // проверка на атомарность
            pCurrent->pNext = pCurNextNext;       
            SetRetCode(TextOk);
        }
        
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
        St.push(pCurrent);
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
        if (pCurrent != pFirst) {
            if (pCurrent->pNext != nullptr) {
                
                St.push(pCurrent->pNext);
            }
            if (pCurrent->pDown != nullptr) {
                
                St.push(pCurrent->pDown);
            }
        }
    }
    return IsTextEnded();
};

void TText::Read (char * pFileName) {

    std::ifstream InFile(pFileName);
    pFirst = this->ReadText(InFile);
    this->Reset();

}

void TText::Write (char * pFileName) {
    
    std::ofstream InFile(pFileName);
    InFile << this->Print().rdbuf();

}

std::stringstream TText::Print (void) {

    return this->PrintText(pFirst);

}