#include "NPCStructure.h"

#ifndef __CRYPTCOFFIN1_H
#define __CRYPTCOFFIN1_H

class CryptCoffin1 : public NPCstructure{
public:
	CryptCoffin1();
	~CryptCoffin1();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif