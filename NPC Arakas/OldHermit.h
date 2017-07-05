#include "NPCStructure.h"

#ifndef __OLDHERMIT_H
#define __OLDHERMIT_H

class OldHermit : public NPCstructure{
public:   
    OldHermit();
   ~OldHermit();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
   // void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
