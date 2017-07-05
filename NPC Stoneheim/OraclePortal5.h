#include <NPCStructure.h>

#ifndef __ORACLEPORTAL5_H
#define __ORACLEPORTAL5_H

class OraclePortal5 : public NPCstructure{
public:   
   OraclePortal5();
   ~OraclePortal5();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif