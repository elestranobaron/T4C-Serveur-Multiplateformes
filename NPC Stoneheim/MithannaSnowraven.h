#include "NPCStructure.h"

#ifndef __MITHANNASNOWRAVEN_H
#define __MITHANNASNOWRAVEN_H

class  MithannaSnowraven : public NPCstructure{
public:
	MithannaSnowraven();
	~MithannaSnowraven();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE ); 

};

#endif