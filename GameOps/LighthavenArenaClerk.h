#include <NPCStructure.h>

#ifndef __LIGHTHAVENARENACLERK_H
#define __LIGHTHAVENARENACLERK_H

class LighthavenArenaClerk : public NPCstructure{
public:   
	LighthavenArenaClerk();
	~LighthavenArenaClerk();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif