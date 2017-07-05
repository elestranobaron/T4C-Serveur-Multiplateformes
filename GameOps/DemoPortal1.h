#include <NPCStructure.h>

#ifndef __DEMOPORTAL1_H
#define __DEMOPORTAL1_H

class DemoPortal1 : public NPCstructure{
public:   
	DemoPortal1();
	~DemoPortal1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
