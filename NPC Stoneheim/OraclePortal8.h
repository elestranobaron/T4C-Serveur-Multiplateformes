#include <NPCStructure.h>

#ifndef __ORACLEPORTAL8_H
#define __ORACLEPORTAL8_H

class OraclePortal8 : public NPCstructure{
public:   
	OraclePortal8();
	~OraclePortal8();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif