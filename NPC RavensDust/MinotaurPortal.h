#include "NPCStructure.h"

#ifndef __MINOTAURPORTAL_H
#define __MINOTAURPORTAL_H

class MinotaurPortal : public NPCstructure{
public:   
    MinotaurPortal();
    ~MinotaurPortal();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE);
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
};

#endif
