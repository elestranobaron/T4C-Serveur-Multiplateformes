#include "NPCStructure.h"

#ifndef __BELTIGANWHITESWORD_H
#define __BELTIGANWHITESWORD_H

class BeltiganWhitesword : public NPCstructure{
public:   
    BeltiganWhitesword();
    ~BeltiganWhitesword();
    void Create( void );   
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
  
};

#endif
