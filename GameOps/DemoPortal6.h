#include <NPCStructure.h>

#ifndef __DEMOPORTAL6_H
#define __DEMOPORTAL6_H

class DemoPortal6 : public NPCstructure{
public:   
	DemoPortal6();
	~DemoPortal6();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
