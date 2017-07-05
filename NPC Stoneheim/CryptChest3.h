#include "NPCStructure.h"

#ifndef __CRYPTCHEST3_H
#define __CRYPTCHEST3_H

class CryptChest3 : public NPCstructure{
public:
	CryptChest3();
	~CryptChest3();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnHit (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif