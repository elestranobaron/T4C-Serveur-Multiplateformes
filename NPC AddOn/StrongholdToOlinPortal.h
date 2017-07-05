#include <NPCStructure.h>

#ifndef __STRONGHOLDTOOLINPORTAL_H
#define __STRONGHOLDTOOLINPORTAL_H

class StrongholdToOlinPortal : public NPCstructure{
public:   
  StrongholdToOlinPortal();
  ~StrongholdToOlinPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
