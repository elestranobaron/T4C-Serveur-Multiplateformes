#include "NPCStructure.h"

#ifndef __TRISTAN_H
#define __TRISTAN_H

class Tristan : public NPCstructure{
public:
  Tristan();
  ~Tristan();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif
