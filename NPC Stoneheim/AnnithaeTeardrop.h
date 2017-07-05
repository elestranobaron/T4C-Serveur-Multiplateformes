#include "NPCStructure.h"

#ifndef __ANNITHAETEARDROP_H
#define __ANNITHAETEARDROP_H

class AnnithaeTeardrop : public NPCstructure{
public:   
    AnnithaeTeardrop();
   ~AnnithaeTeardrop();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
