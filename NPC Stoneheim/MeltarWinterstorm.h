#include "NPCStructure.h"

#ifndef __MELTARWINTERSTORM_H
#define __MELTARWINTERSTORM_H

class MeltarWinterstorm : public NPCstructure{
public:
	MeltarWinterstorm();
	~MeltarWinterstorm();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif