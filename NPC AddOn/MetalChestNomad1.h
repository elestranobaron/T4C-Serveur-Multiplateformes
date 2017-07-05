#include <NPCStructure.h>

#ifndef __METALCHESTNOMAD1_H
#define __METALCHESTNOMAD1_H

class MetalChestNomad1 : public NPCstructure{
public:   
   MetalChestNomad1();
   ~MetalChestNomad1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif