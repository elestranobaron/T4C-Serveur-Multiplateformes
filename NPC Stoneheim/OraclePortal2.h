#include <NPCStructure.h>

#ifndef __ORACLEPORTAL2_H
#define __ORACLEPORTAL2_H

class OraclePortal2 : public NPCstructure{
public:   
   OraclePortal2();
   ~OraclePortal2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif