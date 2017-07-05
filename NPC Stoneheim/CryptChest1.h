#include "NPCStructure.h"

#ifndef __CRYPTCHEST1_H
#define __CRYPTCHEST1_H

class CryptChest1 : public NPCstructure{
public:
	CryptChest1();
	~CryptChest1();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnHit (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif