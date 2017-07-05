#include <NPCStructure.h>

#ifndef __ORACLEPORTAL7_H
#define __ORACLEPORTAL7_H

class OraclePortal7 : public NPCstructure{
public:   
	OraclePortal7();
	~OraclePortal7();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif