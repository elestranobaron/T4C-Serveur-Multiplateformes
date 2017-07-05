#include <NPCStructure.h>

#ifndef __MOBMERCENARYLEADER_H
#define __MOBMERCENARYLEADER_H

class MOBMercenaryLeader : public NPCstructure{
public:   
    MOBMercenaryLeader();
   ~MOBMercenaryLeader();
    void Create( void );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
