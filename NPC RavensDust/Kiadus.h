#include <NPCStructure.h>

#ifndef __KIADUS_H
#define __KIADUS_H

class Kiadus : public NPCstructure{
public:   
    Kiadus();
   ~Kiadus();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif
