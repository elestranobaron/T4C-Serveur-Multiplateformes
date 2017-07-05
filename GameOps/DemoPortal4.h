#include <NPCStructure.h>

#ifndef __DEMOPORTAL4_H
#define __DEMOPORTAL4_H

class DemoPortal4 : public NPCstructure{
public:   
	DemoPortal4();
	~DemoPortal4();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
