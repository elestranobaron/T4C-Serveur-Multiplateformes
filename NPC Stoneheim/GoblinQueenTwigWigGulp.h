#include "NPCStructure.h"

#ifndef __GOBLINQUEENTWIGWIGGULP_H
#define __GOBLINQUEENTWIGWIGGULP_H

class GoblinQueenTwigWigGulp : public NPCstructure{
public:   
    GoblinQueenTwigWigGulp();
   ~GoblinQueenTwigWigGulp();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
