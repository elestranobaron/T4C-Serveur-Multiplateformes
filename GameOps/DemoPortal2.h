#include <NPCStructure.h>

#ifndef __DEMOPORTAL2_H
#define __DEMOPORTAL2_H

class DemoPortal2 : public NPCstructure{
public:   
	DemoPortal2();
	~DemoPortal2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
