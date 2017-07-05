#include <NPCStructure.h>

#ifndef __ETHEREALPORTAL_H
#define __ETHEREALPORTAL_H

class EtherealPortal : public NPCstructure{
public:   
   EtherealPortal();
   ~EtherealPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
