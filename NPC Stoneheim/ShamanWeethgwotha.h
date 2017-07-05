#include "NPCStructure.h"

#ifndef __SHAMANWEETHGWOTHA_H
#define __SHAMANWEETHGWOTHA_H

class ShamanWeethgwotha : public NPCstructure{
public:
	ShamanWeethgwotha();
	~ShamanWeethgwotha();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif
