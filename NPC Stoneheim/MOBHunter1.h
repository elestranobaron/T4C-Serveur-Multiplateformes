#include "SimpleMonster.h"

#ifndef __MOBHUNTER1_H
#define __MOBHUNTER1_H

class MOBHunter1 : public SimpleMonster{
public:
	MOBHunter1();
	~MOBHunter1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
//	void OnDeath( UNIT_FUNC_PROTOTYPE );   
	void OnPopup( UNIT_FUNC_PROTOTYPE );
};
 
#endif