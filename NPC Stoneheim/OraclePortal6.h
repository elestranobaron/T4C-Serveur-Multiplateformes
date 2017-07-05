#include <NPCStructure.h>

#ifndef __ORACLEPORTAL6_H
#define __ORACLEPORTAL6_H

class OraclePortal6 : public NPCstructure{
public:   
   OraclePortal6();
   ~OraclePortal6();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif