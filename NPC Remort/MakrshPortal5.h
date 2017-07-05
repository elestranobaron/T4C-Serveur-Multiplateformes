#include <NPCStructure.h>

#ifndef __MAKRSHPORTAL5_H
#define __MAKRSHPORTAL5_H

class MakrshPortal5 : public NPCstructure{
public:   
	MakrshPortal5();
	~MakrshPortal5();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif