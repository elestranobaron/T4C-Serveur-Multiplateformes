#include "NPCStructure.h"

#ifndef __HEREWALDIRONBENDER_H
#define __HEREWALDIRONBENDER_H

class HerewaldIronbender: public NPCstructure{
public:   
    HerewaldIronbender();
   ~HerewaldIronbender();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );   
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif
