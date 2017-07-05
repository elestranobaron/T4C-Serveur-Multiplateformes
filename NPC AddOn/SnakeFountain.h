#include <NPCStructure.h>

#ifndef __SNAKEFOUNTAIN_H
#define __SNAKEFOUNTAIN_H

class SnakeFountain : public NPCstructure{
public:   
   SnakeFountain();
   ~SnakeFountain();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
