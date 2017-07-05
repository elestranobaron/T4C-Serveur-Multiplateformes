#include <NPCStructure.h>

#ifndef __RIBCAGEENTRANCEPORTAL_H
#define __RIBCAGEENTRANCEPORTAL_H

class RibCageEntrancePortal : public NPCstructure{
public:   
  RibCageEntrancePortal();
  ~RibCageEntrancePortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
