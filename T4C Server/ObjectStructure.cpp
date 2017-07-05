///////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ObjectStructure.h"

ObjectStructure::ObjectStructure(){
	//InitializeCriticalSection(&csMyObject);
	
	blocking = __BLOCK_NONE;
	appearance = 0;
	cRadiance = 0;
	bResistance = 0;
	equip_position = 0xFFFF;
	lock.key = 0;
	text.csText.Empty();
    size = 0;
    weapon.Agi = 0;
    weapon.Att = 0;
    weapon.Str = 0;
    
    uniqueItem = false;
    magic.charges = 0;
    magic.wStr = 0;
    
	ZeroMemory( &armor, sizeof( _armor ) );
	ZeroMemory( &trap, sizeof( _trap ) );
    
	name = NULL;
	cost = CANNOT_SELL;

//	name = new char[ strlen( "[undefined]" ) + 1 ];
//	strcpy( name, "[undefined]" );
	int i = 0;
	for(i = 0; i < NB_CLASS; i++)
		MinLevel[i] = 0;
}


ObjectStructure::~ObjectStructure(){
//	DeleteCriticalSection(&csMyObject);

	tlSpells.AnnihilateList();
	tlBoosts.AnnihilateList();

/*	LPOBJECT_GROUPITEMS lpGroup;

	container.tlItemGroups.ToHead();

	while( container.tlItemGroups.QueryNext() ){	
		lpGroup = container.tlItemGroups.Object();
		
		// Destroy the item references in the group
		lpGroup->tlItemBaseReferenceID.AnnihilateList();
		
		// Destroy this group
		container.tlItemGroups.DeleteAbsolute();
	}
  */

	if( name ) delete name;
}


//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnInitialise
//////////////////////////////////////////////////////////////////////////////////////////
// Init an object structure
// 
(
 UNIT_FUNC_PROTOTYPE // 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	TRACE( "\r\nCharges in item %u", magic.charges );
    self->SetFlag( __FLAG_CHARGES, magic.charges );
//    self->SetStaticFlagsReference(this);
	self->SetAppearance(appearance);
	self->SetRadiance( cRadiance );

	//NOTE: The flag below relates to how many 'tiles' will receive this object's blocking status
	// when it get dropped on the ground.
	// The name is misleading! Remember it dont refer to the kind of blocking this object has!
	// It is now set to 1 couse regular objects should affect AT LEAST 1 tile (the one its placed on)
	//	self->SetFlag(__FLAG_BLOCKING, blocking );
	self->SetFlag(__FLAG_BLOCKING, 1 ); 

    if( uniqueItem || magic.charges > 1 ){
        static_cast< Objects * >( self )->SetUnique();
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnGetUnitStructure
//////////////////////////////////////////////////////////////////////////////////////////
// Used to query the unit's structure
// 
(
 UNIT_FUNC_PROTOTYPE // Standard unit message protoype
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	// DataOUT contains the pointer to the object
	(*(_item **)valueOUT) = this;
}

// Default spell hooks

//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnAttack
//////////////////////////////////////////////////////////////////////////////////////////
// When attacking, spill spell.
// 
(
 UNIT_FUNC_PROTOTYPE
 // medium	attacker.
 // target	attacked.
 // self	this item.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPOBJECT_SPELL lpSpell;

    // If the attacker is the same as the target.
    if( medium == target ){
        // Do not query any effects.
        return;
    }

    int nOldCharges = self->ViewFlag( __FLAG_CHARGES );
    int nCharges = nOldCharges;

    // Search for attack spells
	tlSpells.Lock();
    tlSpells.ToHead();
	while( tlSpells.QueryNext() ){
		lpSpell = tlSpells.Object();
		
		// If there is a spell to trigger.
		if( lpSpell->wHook == MSG_OnAttack ){		            
			if( nCharges != 0 ){
				WorldPos wlPos = target == NULL ? self->GetWL() : target->GetWL();			
				SpellMessageHandler::ActivateSpell( lpSpell->wSpellID, medium, self, target, wlPos );
                nCharges--;
			}else{
				OnNoMoreShots( self, NULL, target, NULL, NULL );
			}
		}
	}
    tlSpells.Unlock();

    if( nOldCharges != nCharges && nOldCharges > 0 ){
        self->SetFlag( __FLAG_CHARGES, nCharges );
    }

    // First trigger all timer effects.
    self->VerifyTimers();
    self->QueryEffects( MSG_OnAttack, NULL, self, target );

}
//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnAttacked
//////////////////////////////////////////////////////////////////////////////////////////
// When attecked.
// 
(
 UNIT_FUNC_PROTOTYPE 
 // medium	victim.
 // target	attacker.
 // self	this item.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPOBJECT_SPELL lpSpell;

    // If the victim of the attack is the attacker.
    if( medium == target ){
        // Do not process item effects.
        return;
    }

    int nOldCharges = self->ViewFlag( __FLAG_CHARGES );
    int nCharges = nOldCharges;
    
	// Search for attack spells
	tlSpells.Lock();
    tlSpells.ToHead();
	while( tlSpells.QueryNext() ){
		lpSpell = tlSpells.Object();
		
		// If there is a spell to trigger.
		if( lpSpell->wHook == MSG_OnAttacked ){			
			if( nCharges != 0 ){
                WorldPos wlPos = target == NULL ? self->GetWL() : target->GetWL();			
				SpellMessageHandler::ActivateSpell( lpSpell->wSpellID, medium, self, target, wlPos );
				nCharges--;
			}else{
				OnNoMoreShots( self, NULL, target, NULL, NULL );
			}
		}
	}
    tlSpells.Unlock();

    if( nOldCharges != nCharges && nOldCharges > 0 ){
        self->SetFlag( __FLAG_CHARGES, nCharges );
    }

    // First trigger all timer effects.
    self->VerifyTimers();
    self->QueryEffects( MSG_OnAttacked, NULL, self, target );

}
//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnHit
//////////////////////////////////////////////////////////////////////////////////////////
// When an opponent makes a successful hit against the wielder of this item.
// 
(
 UNIT_FUNC_PROTOTYPE 
 // medium	victim.
 // target	attacker.
 // self	this item.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPOBJECT_SPELL lpSpell;

    // If the victim is the attacker.
    if( medium == target ){
        // Do not process any triggers.
        return;
    }

    int nOldCharges = self->ViewFlag( __FLAG_CHARGES );
    int nCharges = nOldCharges;
    
	// Search for attack spells
	tlSpells.Lock();
    tlSpells.ToHead();
	while( tlSpells.QueryNext() ){
		lpSpell = tlSpells.Object();
		
		// If there is a spell to trigger.
		if( lpSpell->wHook == MSG_OnHit ){			
			if( nCharges != 0 ){
                WorldPos wlPos = target == NULL ? self->GetWL() : target->GetWL();			
				SpellMessageHandler::ActivateSpell( lpSpell->wSpellID, medium, self, target, wlPos );
				nCharges--;
			}else{
				OnNoMoreShots( self, NULL, target, NULL, NULL );
			}
		}
	}
    tlSpells.Unlock();

    if( nOldCharges != nCharges && nOldCharges > 0 ){
        self->SetFlag( __FLAG_CHARGES, nCharges );
    }

    // First trigger all timer effects.
    self->VerifyTimers();
    self->QueryEffects( MSG_OnHit, NULL, self, target );

}
//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnAttackHit
//////////////////////////////////////////////////////////////////////////////////////////
// When the wielder of this item makes a successful hit against an enemy.
// 
(
 UNIT_FUNC_PROTOTYPE
 // medium	attacker.
 // target	attacked.
 // self	this item.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPOBJECT_SPELL lpSpell;

    // If the victim is the attacker.
    if( medium == target ){
        // Do not process any spell effects.
        return;
    }

    int nOldCharges = self->ViewFlag( __FLAG_CHARGES );
    int nCharges = nOldCharges;

    // Search for attack spells
	tlSpells.Lock();
    tlSpells.ToHead();
	while( tlSpells.QueryNext() ){
		lpSpell = tlSpells.Object();
		
		// If there is a spell to trigger.
		if( lpSpell->wHook == MSG_OnAttackHit ){		            
			if( nCharges != 0 ){
				WorldPos wlPos = target == NULL ? self->GetWL() : target->GetWL();			
				SpellMessageHandler::ActivateSpell( lpSpell->wSpellID, medium, self, target, wlPos );
                nCharges--;
			}else{
				OnNoMoreShots( self, NULL, target, NULL, NULL );
			}
		}
	}
    tlSpells.Unlock();

    if( nOldCharges != nCharges && nOldCharges > 0 ){
        self->SetFlag( __FLAG_CHARGES, nCharges );
    }

    // First trigger all timer effects.
    self->VerifyTimers();
    self->QueryEffects( MSG_OnAttackHit, NULL, self, target );
}

//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnDisturbed
//////////////////////////////////////////////////////////////////////////////////////////
// When object is disturbed
// 
(
 UNIT_FUNC_PROTOTYPE
 // self		this item.
 // target		unit which disturbed this item.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPOBJECT_SPELL lpSpell;
	
    int nOldCharges = self->ViewFlag( __FLAG_CHARGES );
    int nCharges = nOldCharges;

    // Search for attack spells
	tlSpells.Lock();
    tlSpells.ToHead();
	while( tlSpells.QueryNext() ){
		lpSpell = tlSpells.Object();
		
		// If there is a spell to trigger.
		if( lpSpell->wHook == MSG_OnDisturbed ){
			
			if( nCharges != 0 ){
				WorldPos wlPos = target == NULL ? self->GetWL() : target->GetWL();			
				// The bearer is the target ;-)
				SpellMessageHandler::ActivateSpell( lpSpell->wSpellID, target, self, target, wlPos );
				nCharges--;
			}else{
				OnNoMoreShots( target, NULL, target, NULL, NULL );
			}
		}
	}
    tlSpells.Unlock();

    // First trigger all timer effects.
    self->VerifyTimers();
    TRACE( "\r\nself=0x%x, target=0x%x.", self, target );
    self->QueryEffects( MSG_OnDisturbed, NULL, self, target );

    if( nOldCharges != nCharges && nOldCharges > 0 ){
        self->SetFlag( __FLAG_CHARGES, nCharges );
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnNoMoreShots
//////////////////////////////////////////////////////////////////////////////////////////
// When object is out of charges
// 
(
 UNIT_FUNC_PROTOTYPE
 // self	Unit holding this item.
 // target	Last target when item went out of shots. Otherwise = self.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPOBJECT_SPELL lpSpell;
	
	// Search for attack spells
    tlSpells.Lock();
	tlSpells.ToHead();
	while( tlSpells.QueryNext() ){
		lpSpell = tlSpells.Object();
		
		// If there is a spell to trigger.
		if( lpSpell->wHook == MSG_OnNoMoreShots ){			
			WorldPos wlPos = target == NULL ? self->GetWL() : target->GetWL();			
			SpellMessageHandler::ActivateSpell( lpSpell->wSpellID, self, NULL, target, wlPos );
		}
	}
    tlSpells.Unlock();
}
//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnUse
//////////////////////////////////////////////////////////////////////////////////////////
// When used.
// 
(
 UNIT_FUNC_PROTOTYPE
 // self	Unit being used.
 // medium	Unit using item.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPOBJECT_SPELL lpSpell;

    int nOldCharges = self->ViewFlag( __FLAG_CHARGES );
    int nCharges = nOldCharges;

	DWORD &itemUsed = *(DWORD *)( valueOUT );

	// Search for attack spells
	tlSpells.Lock();
    tlSpells.ToHead();
	while( tlSpells.QueryNext() ){
		lpSpell = tlSpells.Object();
		
		// If there is a spell to trigger.
		if( lpSpell->wHook == MSG_OnUse ){
			itemUsed = 1;
            if( nCharges != 0 ){            
				WorldPos wlPos = medium->GetWL();
				SpellMessageHandler::ActivateSpell( lpSpell->wSpellID, medium, self, medium, wlPos );
				nCharges--;
			}else{
				OnNoMoreShots( medium, NULL, medium, NULL, NULL );
			}
		}
	}
    tlSpells.Unlock();
    
    if( nOldCharges != nCharges && nOldCharges > 0 ){
        self->SetFlag( __FLAG_CHARGES, nCharges );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnEquip
//////////////////////////////////////////////////////////////////////////////////////////
// When the object is being equipped.
// 
(
 UNIT_FUNC_PROTOTYPE
 // self		This object being equipped.
 // target		The unit equipping it.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPOBJECT_BOOST lpBoost;

	tlBoosts.Lock();
    tlBoosts.ToHead();
	while( tlBoosts.QueryNext() ){
		lpBoost = tlBoosts.Object();
		// If target has enough int and wis
		if( target->GetTrueINT() >= lpBoost->nMinINT && target->GetTrueWIS() >= lpBoost->nMinWIS ){
			// Add the item's boost.
            TRACE( "\r\nAdding boost ID=%u for stat=%u.", lpBoost->dwBoostID, lpBoost->wStat );
            target->SetBoost( lpBoost->dwBoostID, lpBoost->wStat, static_cast< int >( lpBoost->bfBoost.GetBoost( target ) ) );
		}

	}
    tlBoosts.Unlock();

}
//////////////////////////////////////////////////////////////////////////////////////////
void ObjectStructure::OnUnequip
//////////////////////////////////////////////////////////////////////////////////////////
// When the object is being unequipped.
// 
(
 UNIT_FUNC_PROTOTYPE
 // self		This object being unequipped.
 // target		The unit unequipping it.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPOBJECT_BOOST lpBoost;

	tlBoosts.Lock();
    tlBoosts.ToHead();
	while( tlBoosts.QueryNext() ){
		lpBoost = tlBoosts.Object();
	
        TRACE( "\r\nRemoving boost ID=%u.", lpBoost->dwBoostID );
		// Remove the item's boost.
		target->RemoveBoost( lpBoost->dwBoostID );
	}
    tlBoosts.Unlock();
}