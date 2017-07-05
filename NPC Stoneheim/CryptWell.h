#include "NPCStructure.h"

#ifndef __CRYPTWELL_H
#define __CRYPTWELL_H

class CryptWell : public NPCstructure{
public:   
    CryptWell();
    ~CryptWell();
    void Create( void );
	void OnAttacked( UNIT_FUNC_PROTOTYPE ); 
	  void OnInitialise( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif
