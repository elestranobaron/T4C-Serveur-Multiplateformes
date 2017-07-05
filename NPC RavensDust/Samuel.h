#include "NPCStructure.h"

#ifndef __SAMUEL_H
#define __SAMUEL_H

class Samuel : public NPCstructure{
public:   
    Samuel();
   ~Samuel();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
