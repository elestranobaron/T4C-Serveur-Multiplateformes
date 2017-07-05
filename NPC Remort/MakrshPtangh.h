#include "NPCStructure.h"

#ifndef __MAKRSHPTANGH_H
#define __MAKRSHPTANGH_H

class MakrshPtangh : public NPCstructure{
public:
	MakrshPtangh();
	~MakrshPtangh();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif