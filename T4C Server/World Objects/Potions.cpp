// Potions.cpp: implementation of the Potions class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Potions.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Potions::Potions()
{

}

Potions::~Potions()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
void Potions::OnInitialise
//////////////////////////////////////////////////////////////////////////////////////////
// Init potions
// 
(
 UNIT_FUNC_PROTOTYPE // dsfdsf
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	ObjectStructure::OnInitialise( UNIT_FUNC_PARAM );
	self->SetFlag(__FLAG_CHARGES, magic.charges);
}


//////////////////////////////////////////////////////////////////////////////////////////
void Potions::OnUse
//////////////////////////////////////////////////////////////////////////////////////////
// Uses a potion
// 
(
 UNIT_FUNC_PROTOTYPE // prototype
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	BOOL boBrakeItem = FALSE;
    LPOBJECT_SPELL lpSpell;

    int nOldCharges = self->ViewFlag( __FLAG_CHARGES );
    int nCharges = nOldCharges;    

	DWORD &itemUsed = *(DWORD *)( valueOUT );

    TRACE( "\r\nCharges %u", nCharges );

	// Search for attack spells
	tlSpells.ToHead();
	while( tlSpells.QueryNext() ){
		lpSpell = tlSpells.Object();
		
		// If there is a spell to trigger.
		if( lpSpell->wHook == MSG_OnUse ){			
			itemUsed = TRUE;
			if( nCharges != 0 ){
				WorldPos wlPos = medium->GetWL();
				SpellMessageHandler::ActivateSpell( lpSpell->wSpellID, medium, self, medium, wlPos );

                // If charges aren't unlimited.
                if( nOldCharges > 0 ){
                    nCharges--;
                    if( nCharges <= 0 ){
                        boBrakeItem = TRUE;
                    }
                }
			}else{
				OnNoMoreShots( medium, NULL, medium, NULL, NULL );
                boBrakeItem = TRUE;
			}
		}
	}

    if( nOldCharges != nCharges && nOldCharges > 0 ){
        self->SetFlag( __FLAG_CHARGES, nCharges );
    }

    if( boBrakeItem ){
        self->SetMark( MARK_DELETION );
    }

}

//////////////////////////////////////////////////////////////////////////////////////////
ObjectStructure *Potions::CreateObject( void ){
	return new Potions;
}