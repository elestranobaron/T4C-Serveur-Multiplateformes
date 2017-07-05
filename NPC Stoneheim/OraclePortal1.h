#include <NPCStructure.h>

#ifndef __ORACLEPORTAL1_H
#define __ORACLEPORTAL1_H

class OraclePortal1 : public NPCstructure{
public:   
   OraclePortal1();
   ~OraclePortal1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif