#include <NPCStructure.h>

#ifndef __CRYSTALPORTAL_H
#define __CRYSTALPORTAL_H

class CrystalPortal : public NPCstructure{
public:   
  CrystalPortal();
  ~CrystalPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
