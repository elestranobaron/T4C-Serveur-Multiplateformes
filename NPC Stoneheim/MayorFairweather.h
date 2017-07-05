#include "NPCStructure.h"

#ifndef __MAYORFAIRWEATHER_H
#define __MAYORFAIRWEATHER_H

class MayorFairweather : public NPCstructure{
public:   
    MayorFairweather();
   ~MayorFairweather();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
