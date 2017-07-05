#include <NPCStructure.h>

#ifndef __ORACLEPORTAL3_H
#define __ORACLEPORTAL3_H

class OraclePortal3 : public NPCstructure{
public:   
   OraclePortal3();
   ~OraclePortal3();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif