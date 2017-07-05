#include "NPCStructure.h"

#ifndef __HUNTERGRUTTWORGWLOTH_H
#define __HUNTERGRUTTWORGWLOTH_H

class HunterGruttWorgwloth : public NPCstructure{
public:   
    HunterGruttWorgwloth();
   ~HunterGruttWorgwloth();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif
