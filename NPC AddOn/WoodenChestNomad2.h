#include <NPCStructure.h>

#ifndef __WOODENCHESTNOMAD2_H
#define __WOODENCHESTNOMAD2_H

class WoodenChestNomad2 : public NPCstructure{
public:   
   WoodenChestNomad2();
   ~WoodenChestNomad2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif