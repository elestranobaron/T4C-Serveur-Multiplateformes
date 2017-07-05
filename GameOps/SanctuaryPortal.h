#include <NPCStructure.h>

#ifndef __SANCTUARYPORTAL_H
#define __SANCTUARYPORTAL_H

class SanctuaryPortal : public NPCstructure{
public:   
	SanctuaryPortal();
	~SanctuaryPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
