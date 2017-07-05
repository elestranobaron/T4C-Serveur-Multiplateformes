#include "NPCStructure.h"

#ifndef __CRYPTCHEST4_H
#define __CRYPTCHEST4_H

class CryptChest4 : public NPCstructure{
public:
	CryptChest4();
	~CryptChest4();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnHit (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif