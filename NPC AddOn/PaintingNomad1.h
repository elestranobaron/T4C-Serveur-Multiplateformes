#include <NPCStructure.h>

#ifndef __PAINTINGNOMAD1_H
#define __PAINTINGNOMAD1_H

class PaintingNomad1 : public NPCstructure{
public:   
   PaintingNomad1();
   ~PaintingNomad1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif