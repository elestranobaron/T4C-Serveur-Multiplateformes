#include <NPCStructure.h>

#ifndef __GMassistant_H
#define __GMassistant_H

class GMassistant : public NPCstructure{
public:   
	GMassistant();
	~GMassistant();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
