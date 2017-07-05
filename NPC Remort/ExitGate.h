#include <NPCStructure.h>

#ifndef __EXITGATE_H
#define __EXITGATE_H

class ExitGate : public NPCstructure{
public:   
  ExitGate();
  ~ExitGate();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
  void OnAttacked( UNIT_FUNC_PROTOTYPE );
  void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
