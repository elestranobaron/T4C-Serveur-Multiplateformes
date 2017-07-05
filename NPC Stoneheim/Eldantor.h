#include "NPCStructure.h"

#ifndef __ELDANTOR_H
#define __ELDANTOR_H

class Eldantor : public NPCstructure{
public:   
    Eldantor();
   ~Eldantor();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	   void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

    
};

#endif
