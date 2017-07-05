#include "NPCStructure.h"

#ifndef __ANNABELLE_H
#define __ANNABELLE_H

class Annabelle : public NPCstructure{
public:   
    Annabelle();
   ~Annabelle();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    //void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
