#include <NPCStructure.h>

#ifndef __ISLANDPORTAL33_H
#define __ISLANDPORTAL33_H

class IslandPortal33 : public NPCstructure{
public:   
	IslandPortal33();
	~IslandPortal33();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
