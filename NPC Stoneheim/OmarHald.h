#include "NPCStructure.h"

#ifndef __OMARHALD_H
#define __OMARHALD_H

class OmarHald : public NPCstructure{
public:   
    OmarHald();
   ~OmarHald();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
   
};

#endif
