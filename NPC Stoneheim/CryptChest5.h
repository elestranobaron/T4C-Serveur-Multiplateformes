#include "NPCStructure.h"

#ifndef __CRYPTCHEST5_H
#define __CRYPTCHEST5_H

class CryptChest5 : public NPCstructure{
public:
	CryptChest5();
	~CryptChest5();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnHit (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif