#include "NPCStructure.h"

#ifndef __JULIAN_H
#define __JULIAN_H

class Julian : public NPCstructure{
public:   
    Julian();
   ~Julian();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
