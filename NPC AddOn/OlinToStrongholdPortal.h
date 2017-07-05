#include <NPCStructure.h>

#ifndef __OLINTOSTRONGHOLDPORTAL_H
#define __OLINTOSTRONGHOLDPORTAL_H

class OlinToStrongholdPortal : public NPCstructure{
public:   
  OlinToStrongholdPortal();
  ~OlinToStrongholdPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
