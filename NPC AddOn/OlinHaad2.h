#include "NPCStructure.h"

#ifndef __OLINHAAD2_H
#define __OLINHAAD2_H

class OlinHaad2 : public NPCstructure{
public:
	OlinHaad2();
	~OlinHaad2();
	void Create( void );
	void OnAttack( UNIT_FUNC_PROTOTYPE );
};

#endif