#include <NPCStructure.h>

#ifndef __CHAOSSOUTHTOCENTERPORTAL_H
#define __CHAOSSOUTHTOCENTERPORTAL_H

class ChaosSouthToCenterPortal : public NPCstructure{
public:   
  ChaosSouthToCenterPortal();
  ~ChaosSouthToCenterPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
