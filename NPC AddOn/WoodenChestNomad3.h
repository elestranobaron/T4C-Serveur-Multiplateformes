#include <NPCStructure.h>

#ifndef __WOODENCHESTNOMAD3_H
#define __WOODENCHESTNOMAD3_H

class WoodenChestNomad3 : public NPCstructure{
public:   
   WoodenChestNomad3();
   ~WoodenChestNomad3();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif