#include "NPCStructure.h"

#ifndef __AYDANGOLDSTAR_H
#define __AYDANGOLDSTAR_H

class AydanGoldstar : public NPCstructure{
public:   
    AydanGoldstar();
   ~AydanGoldstar();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
