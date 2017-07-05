#include "SimpleMonster.h"

#ifndef __MOBHUNTER2_H
#define __MOBHUNTER2_H

class MOBHunter2 : public SimpleMonster{
public:
	MOBHunter2();
	~MOBHunter2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
//	void OnDeath( UNIT_FUNC_PROTOTYPE );   
	void OnPopup( UNIT_FUNC_PROTOTYPE );
};
 
#endif