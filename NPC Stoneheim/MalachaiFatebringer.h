#include "NPCStructure.h"

#ifndef __MALACHAIFATEBRINGER_H
#define __MALACHAIFATEBRINGER_H

class  MalachaiFatebringer : public NPCstructure{
public:   
    MalachaiFatebringer();
   ~MalachaiFatebringer();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
