#include <NPCStructure.h>

#ifndef __SEBANFORGELOT_H
#define __SEBANFORGELOT_H

class SebanForgelot : public NPCstructure{
public:   
	SebanForgelot();
	~SebanForgelot();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif
