#include <NPCStructure.h>

#ifndef __BLIGHTPORTAL_H
#define __BLIGHTPORTAL_H

class BlightPortal : public NPCstructure{
public:   
   BlightPortal();
   ~BlightPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
