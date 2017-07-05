#include "NPCStructure.h"

#ifndef __KHERALSILVERHAWK_H
#define __KHERALSILVERHAWK_H

class KheralSilverhawk : public NPCstructure{
public:   
   KheralSilverhawk();
   ~KheralSilverhawk();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );    
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnAttack( UNIT_FUNC_PROTOTYPE );
   void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif
