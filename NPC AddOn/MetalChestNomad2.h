#include <NPCStructure.h>

#ifndef __METALCHESTNOMAD2_H
#define __METALCHESTNOMAD2_H

class MetalChestNomad2 : public NPCstructure{
public:   
   MetalChestNomad2();
   ~MetalChestNomad2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif