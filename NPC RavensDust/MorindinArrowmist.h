#include "NPCStructure.h"

#ifndef __MORINDINARROWMIST_H
#define __MORINDINARROWMIST_H

class MorindinArrowmist : public NPCstructure{
public:   
    MorindinArrowmist();
   ~MorindinArrowmist();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif
