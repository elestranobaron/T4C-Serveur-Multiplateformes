#include "SimpleMonster.h"

#ifndef __MOBOBSIDIANCONCLAVEKNIGHT_H
#define __MOBOBSIDIANCONCLAVEKNIGHT_H

class MOBObsidianConclaveKnight : public SimpleMonster{
public:   
    MOBObsidianConclaveKnight();
   ~MOBObsidianConclaveKnight();
    void Create( void );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif
