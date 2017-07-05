#include "NPCStructure.h"

#ifndef __JEREMIAH_H
#define __JEREMIAH_H

class Jeremiah : public NPCstructure{
public:   
    Jeremiah();
   ~Jeremiah();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
