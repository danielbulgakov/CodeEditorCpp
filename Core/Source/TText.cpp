#include "../Headers/TText.h"
#include "../Headers/TTextLink.h"

TText::TText(PTTextLink pl)
{
    if (pl == nullptr){
        pl = new TTextLink();
    }
    pFirst = pl;
}

std::string TText::GetLine(void){return std::string();};
void TText::SetLine(std::string s){return;};
int TText::Reset (void){return 0;};
int TText::IsTextEnded (void) const{return 0;};
int TText::GoNext (void){return 0;};
