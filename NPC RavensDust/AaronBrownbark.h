#include "NPCStructure.h"

#ifndef __AARONBROWNBARK_H
#define __AARONBROWNBARK_H

class AaronBrownbark : public NPCstructure{
public:   
    AaronBrownbark();
   ~AaronBrownbark();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );    
};

#endif
