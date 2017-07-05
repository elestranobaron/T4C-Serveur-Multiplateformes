#include <NPCStructure.h>

#ifndef __HARVESTERPORTAL_H
#define __HARVESTERPORTAL_H

class HarvesterPortal : public NPCstructure{
public:   
  HarvesterPortal();
  ~HarvesterPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
