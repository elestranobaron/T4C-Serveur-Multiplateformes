#include "NPCStructure.h"

#ifndef __CHIEFTAINTHORWAGTH_H
#define __CHIEFTAINTHORWAGTH_H

class ChieftainThorwagth : public NPCstructure{
public:   
    ChieftainThorwagth();
   ~ChieftainThorwagth();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
