#include <NPCStructure.h>

#ifndef __MAZEEXITPORTAL_H
#define __MAZEEXITPORTAL_H

class MazeExitPortal : public NPCstructure{
public:   
  MazeExitPortal();
  ~MazeExitPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
