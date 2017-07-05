#include <NPCStructure.h>

#ifndef __INVISIBLEMAZEEXITPORTAL_H
#define __INVISIBLEMAZEEXITPORTAL_H

class InvisibleMazeExitPortal : public NPCstructure{
public:   
  InvisibleMazeExitPortal();
  ~InvisibleMazeExitPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
