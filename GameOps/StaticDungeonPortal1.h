#include "NPCStructure.h"

#ifndef __STATICDUNGEONPORTAL1_H
#define __STATICDUNGEONPORTAL1_H

class StaticDungeonPortal1 : public NPCstructure{
public:   
    StaticDungeonPortal1();
    ~StaticDungeonPortal1();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE);
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
};

#endif
