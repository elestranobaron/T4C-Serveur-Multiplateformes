#include <NPCStructure.h>

#ifndef __METALCHESTNOMAD3_H
#define __METALCHESTNOMAD3_H

class MetalChestNomad3 : public NPCstructure{
public:   
   MetalChestNomad3();
   ~MetalChestNomad3();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif