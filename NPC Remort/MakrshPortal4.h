#include <NPCStructure.h>

#ifndef __MAKRSHPORTAL4_H
#define __MAKRSHPORTAL4_H

class MakrshPortal4 : public NPCstructure{
public:   
	MakrshPortal4();
	~MakrshPortal4();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif