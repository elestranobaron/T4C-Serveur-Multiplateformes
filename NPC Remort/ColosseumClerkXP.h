#include "NPCStructure.h"

#ifndef __COLOSSEUMCLERKXP_H
#define __COLOSSEUMCLERKXP_H

class ColosseumClerkXP : public NPCstructure{
public:
  ColosseumClerkXP();
  ~ColosseumClerkXP();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
