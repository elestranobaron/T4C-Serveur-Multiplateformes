// AreaSensitiveEffect.cpp: implementation of the AreaSensitiveEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AreaSensitiveEffect.h"
#include "TFCTimers.h"
#include "tfc_main.h"
#include "SpellListing.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define TRACE printf//#define TRACE 1 ? (void) 0 : printf
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AreaSensitiveEffect::AreaSensitiveEffect()
{
	minx = maxx = 0;
	params = NULL;
}

AreaSensitiveEffect::~AreaSensitiveEffect()
{	
	if(params) delete params;
}

void AreaSensitiveEffect::Create(unsigned int hminx, unsigned int hmaxx, unsigned short heffect, LPVOID hparams, int hparamsize)
{
	if(params) delete params;
	minx = hminx;
	maxx = hmaxx;	
	effect = heffect;
	if(hparams){
		params = (LPVOID)(new BYTE [hparamsize]);
		memcpy(params, hparams, hparamsize);
	}
}
/********************************************************************************************/
BOOL AreaSensitiveEffect::QueryEffect(WorldPos where, Unit *who_stepped_in)
{
	// Check if we are in the sensitive area
	if(where.X >= static_cast< int >( minx ) && where.X < static_cast< int >( maxx ) )
	{
		Execute(who_stepped_in);
		return TRUE;
	}

return FALSE;
}


void AreaSensitiveEffect::Execute(Unit *target)
{
switch(effect)
{
case __AREA_TELEPORT: {
	TRACE( "\r\nTeleporting unit!!" );
		WorldPos *wl = (WorldPos *)params;
        if( target->GetType() == U_PC )
        {
		    target->Teleport(*wl, 0);
        }
	}break;
		


}
}
