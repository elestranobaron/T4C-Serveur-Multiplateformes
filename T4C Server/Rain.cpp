// Rain.cpp: implementation of the Rain class.
// By:       Scotch for Dialsoft
// Date:     02/20/2005
// Purpose:  Raining system & client / server communication
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Rain.h"
#include "Broadcast.h"
#include "WeatherEffect.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Rain::Rain()
{
	bRain = false;
}

Rain::~Rain()
{

}

//**********************************************************
// Function : GetInstance
// Args : /
// Function : Returns the only instance of Rain
// returns : The instance.
//**********************************************************
Rain *Rain::GetInstance(void)
{
    static Rain m_pInstance;
    return &m_pInstance;
}

//**********************************************************
// Function : SetState
// Args : bool NewState
// Function : Set current raining state
// returns : void.
//**********************************************************
void Rain::SetState(short bNewState)
{
   bRain = false;
   if(bNewState)
	   bRain = true;

	WorldPos wlPos = { 0, 0, 0 };
	Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_RAIN , bNewState );
}

//**********************************************************
// Function : SwitchState
// Args : /
// Function : Switch the rain (on/off)
// returns : void.
//**********************************************************
void Rain::SwitchState(void)
{
	bRain = !bRain;
}

//**********************************************************
// Function : GetState
// Args : /
// Function : Get the current raining state
// returns : bool
//**********************************************************
bool Rain::GetState(void)
{
	return bRain;
}

//////////////////////////////////////////////////////////////////////
// Send the rain state to the player
void Rain::SendRainState( Unit* self )
{
	TFCPacket sending;

	sending << (long) WEATHER_RAIN;
	sending << (RQ_SIZE) RQ_WeatherMsg;
	sending << (short) bRain;

	self->SendPlayerMessage( sending );
}