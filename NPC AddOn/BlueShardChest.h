#include <NPCStructure.h>

#ifndef __BLUESHARDCHEST_H
#define __BLUESHARDCHEST_H

class BlueShardChest : public NPCstructure{
public:   
   BlueShardChest();
   ~BlueShardChest();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
