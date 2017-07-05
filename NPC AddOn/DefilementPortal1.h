#include <NPCStructure.h>

#ifndef __DEFILEMENTPORTAL1_H
#define __DEFILEMENTPORTAL1_H

class DefilementPortal1 : public NPCstructure{
public:   
  DefilementPortal1();
  ~DefilementPortal1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
