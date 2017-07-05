#include "NPCStructure.h"

#ifndef __TWINNEVANIS_H
#define __TWINNEVANIS_H

class TwinNevanis : public NPCstructure{
public:   
        TwinNevanis();
       ~TwinNevanis();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif
