#include "NPCStructure.h"

#ifndef __TERWIN_H
#define __TERWIN_H

class Terwin : public NPCstructure{
public:   
    Terwin();
   ~Terwin();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
