#include <NPCStructure.h>

#ifndef __WOODENCHESTNOMAD1_H
#define __WOODENCHESTNOMAD1_H

class WoodenChestNomad1 : public NPCstructure{
public:   
   WoodenChestNomad1();
   ~WoodenChestNomad1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif