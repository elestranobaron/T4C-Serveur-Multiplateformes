#include <NPCStructure.h>

#ifndef __WHIRLPOOLMAZEEXITPORTAL_H
#define __WHIRLPOOLMAZEEXITPORTAL_H

class WhirlpoolMazeExitPortal : public NPCstructure{
public:   
  WhirlpoolMazeExitPortal();
  ~WhirlpoolMazeExitPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
