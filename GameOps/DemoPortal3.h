#include <NPCStructure.h>

#ifndef __DEMOPORTAL3_H
#define __DEMOPORTAL3_H

class DemoPortal3 : public NPCstructure{
public:   
	DemoPortal3();
	~DemoPortal3();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
