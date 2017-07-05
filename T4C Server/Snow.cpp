// Snow.cpp: implementation of the Snow class.
// By:       Destiny for Dialsoft
// Date:     01/04/2007
// Purpose:  Snow system & client / server communication
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Snow.h"
#include "Broadcast.h"
#include "WeatherEffect.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Snow::Snow()
{
	bSnow = false;
}

Snow::~Snow()
{

}

//**********************************************************
// Function : GetInstance
// Args : /
// Function : Returns the only instance of Snow
// returns : The instance.
//**********************************************************
Snow *Snow::GetInstance( void )
{
    static Snow m_pInstance;
    return &m_pInstance;
}

//**********************************************************
// Function : SetState
// Args : bool NewState
// Function : Set current snowing state
// returns : void.
//**********************************************************
void Snow::SetState( short bNewState )
{
   bSnow = false;
   if( bNewState )
   {
	   bSnow = true;
   }

	WorldPos wlPos = { 0, 0, 0 };
	Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_SNOW, bNewState );
}

//**********************************************************
// Function : SwitchState
// Args : /
// Function : Switch the Snow (on/off)
// returns : void.
//**********************************************************
void Snow::SwitchState(void)
{
	bSnow = !bSnow;
}

//**********************************************************
// Function : GetState
// Args : /
// Function : Get the current snowing state
// returns : bool
//**********************************************************
bool Snow::GetState(void)
{
	return bSnow;
}