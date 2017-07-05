#include <NPCStructure.h>

#ifndef __MAKRSHPORTAL3_H
#define __MAKRSHPORTAL3_H

class MakrshPortal3 : public NPCstructure{
public:   
	MakrshPortal3();
	~MakrshPortal3();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif