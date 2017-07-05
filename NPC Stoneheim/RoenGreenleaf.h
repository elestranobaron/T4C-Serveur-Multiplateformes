#include "NPCStructure.h"

#ifndef __ROENGREENLEAF_H
#define __ROENGREENLEAF_H

class RoenGreenleaf : public NPCstructure{
public:   
    RoenGreenleaf();
   ~RoenGreenleaf();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
 	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

    
};

#endif
