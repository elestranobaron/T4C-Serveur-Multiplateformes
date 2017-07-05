#include <NPCStructure.h>

#ifndef __SCATTEREDBONESPORTAL_H
#define __SCATTEREDBONESPORTAL_H

class ScatteredBonesPortal : public NPCstructure{
public:   
   ScatteredBonesPortal();
   ~ScatteredBonesPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
