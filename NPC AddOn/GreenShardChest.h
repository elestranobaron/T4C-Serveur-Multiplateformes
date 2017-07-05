#include <NPCStructure.h>

#ifndef __GREENSHARDCHEST_H
#define __GREENSHARDCHEST_H

class GreenShardChest : public NPCstructure{
public:   
   GreenShardChest();
   ~GreenShardChest();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
