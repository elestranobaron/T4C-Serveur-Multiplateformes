#include <NPCStructure.h>

#ifndef __ORACLEESCAPEDOOR_H
#define __ORACLEESCAPEDOOR_H

class OracleEscapeDoor : public NPCstructure{
public:   
   OracleEscapeDoor();
   ~OracleEscapeDoor();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif