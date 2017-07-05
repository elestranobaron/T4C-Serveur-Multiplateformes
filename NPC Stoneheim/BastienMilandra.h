#include "NPCStructure.h"

#ifndef __BASTIENMILANDRA_H
#define __BASTIENMILANDRA_H

class BastienMilandra : public NPCstructure{
public:   
    BastienMilandra();
   ~BastienMilandra();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
