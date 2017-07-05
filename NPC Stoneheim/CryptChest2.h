#include "NPCStructure.h"

#ifndef __CRYPTCHEST2_H
#define __CRYPTCHEST2_H

class CryptChest2 : public NPCstructure{
public:
	CryptChest2();
	~CryptChest2();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnHit (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif