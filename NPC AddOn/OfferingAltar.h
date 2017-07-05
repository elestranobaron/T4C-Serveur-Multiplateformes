#include <NPCStructure.h>

#ifndef __OFFERINGALTAR_H
#define __OFFERINGALTAR_H

class OfferingAltar : public NPCstructure{
public:   
   OfferingAltar();
   ~OfferingAltar();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
