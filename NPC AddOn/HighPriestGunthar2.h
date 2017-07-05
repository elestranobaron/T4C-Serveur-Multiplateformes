#include "NPCStructure.h"
#include "SimpleMonster.h"

#ifndef __HIGHPRIESTGUNTHAR2_H
#define __HIGHPRIESTGUNTHAR2_H

class HighPriestGunthar2 : public SimpleMonster{
public:
	HighPriestGunthar2();
	~HighPriestGunthar2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnPopup( UNIT_FUNC_PROTOTYPE );

};

#endif