#include <NPCStructure.h>

#ifndef __MAKRSHPORTAL2_H
#define __MAKRSHPORTAL2_H

class MakrshPortal2 : public NPCstructure{
public:   
	MakrshPortal2();
	~MakrshPortal2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif