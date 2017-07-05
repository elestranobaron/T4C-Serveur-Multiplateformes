#include <NPCStructure.h>

#ifndef __ISOLATEDISLANDPORTAL_H
#define __ISOLATEDISLANDPORTAL_H

class IsolatedIslandPortal : public NPCstructure{
public:   
   IsolatedIslandPortal();
   ~IsolatedIslandPortal();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
