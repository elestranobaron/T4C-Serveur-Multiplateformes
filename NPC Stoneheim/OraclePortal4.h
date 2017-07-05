#include <NPCStructure.h>

#ifndef __ORACLEPORTAL4_H
#define __ORACLEPORTAL4_H

class OraclePortal4 : public NPCstructure{
public:   
   OraclePortal4();
   ~OraclePortal4();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif