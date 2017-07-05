#include <NPCStructure.h>

#ifndef __DEMOPORTAL5_H
#define __DEMOPORTAL5_H

class DemoPortal5 : public NPCstructure{
public:   
	DemoPortal5();
	~DemoPortal5();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
