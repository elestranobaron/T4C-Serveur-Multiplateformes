#include <NPCStructure.h>

#ifndef __MORDREDCHEST_H
#define __MORDREDCHEST_H

class MordredChest : public NPCstructure{
public:   
	MordredChest();
	~MordredChest();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
