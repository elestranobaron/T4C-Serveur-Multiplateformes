#include <NPCStructure.h>

#ifndef __ORACLEESCAPEFLIPPEDDOOR_H
#define __ORACLEESCAPEFLIPPEDDOOR_H

class OracleEscapeFlippedDoor : public NPCstructure{
public:   
   OracleEscapeFlippedDoor();
   ~OracleEscapeFlippedDoor();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif