#include "NPCStructure.h"

#ifndef __GOBLINASSASSINGLUBGLUB_H
#define __GOBLINASSASSINGLUBGLUB_H

class GoblinAssassinGlubGlub : public NPCstructure{
public:   
    GoblinAssassinGlubGlub();
   ~GoblinAssassinGlubGlub();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );   
};

#endif
