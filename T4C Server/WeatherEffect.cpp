// WeatherEffect.cpp: implementation of the WeatherEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WeatherEffect.h"
#include "Random.h"
#include "T4CLog.h"
#include "Random.h"
#include <process.h>

static HANDLE hWeatherHandle = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WeatherEffect::WeatherEffect()
{
	StartWeatherRandom();	
}

WeatherEffect::~WeatherEffect()
{

}

//////////////////////////////////////////////////////////////////////
// Return the only instance of the class
WeatherEffect* WeatherEffect::GetInstance( void )
{
    static WeatherEffect m_pInstance;
    return &m_pInstance;
}

//////////////////////////////////////////////////////////////////////
// The thread that randomly changes meteo //BLBLBL 08/12/2010
void __cdecl WeatherMaintenance(void*)
{
    DWORD meteoRound = 0;
	DWORD meteoNextRound=0;
	Random rnd;

	while( 1 ){
        
        Sleep( 1000 );//chaque boucle dure 1 seconde

            //DWORD 
			//currentTime = timeGetTime();
			
			//toutes les +/-30 min - 4 heures il y a une averse
			if (meteoNextRound==0){
				meteoNextRound=rnd(2000,14000);
				meteoRound=0;
			}
			
			meteoRound++;
	            
			if (meteoRound==meteoNextRound){
				//la pluie arrive :
			    if( WeatherEffect::GetInstance()->GetEffectState( WEATHER_RAIN ) == false){
					WeatherEffect::GetInstance()->SetEffectState( 1, WEATHER_RAIN );
				}
			}
			else if (meteoRound==meteoNextRound+10){
				//le brouillard arrive :
				if( WeatherEffect::GetInstance()->GetEffectState( WEATHER_FOG ) == false){
					WeatherEffect::GetInstance()->SetEffectState( 0, WEATHER_FOG ); // steph 0 au lieu de 1								
				}
			}
			else if (meteoRound ==meteoNextRound+300){
				//la pluie s'en va 
				if( WeatherEffect::GetInstance()->GetEffectState( WEATHER_RAIN ) == true){
					WeatherEffect::GetInstance()->SetEffectState( 0, WEATHER_RAIN );									
				}
			}
			else if (meteoRound == meteoNextRound+310){
				//le brouillard s'en va
				if( WeatherEffect::GetInstance()->GetEffectState( WEATHER_FOG ) == true){
					WeatherEffect::GetInstance()->SetEffectState( 0, WEATHER_FOG );									
				}
				meteoRound=0;
				meteoNextRound=0;
			}

					
	}
	_endthread();
}

//////////////////////////////////////////////////////////////////////
// Starts meteo thread
void WeatherEffect::StartWeatherRandom(void)
{
    if( hWeatherHandle == NULL ){
        hWeatherHandle = (HANDLE)_beginthread( WeatherMaintenance,0, NULL);
    }
}


//////////////////////////////////////////////////////////////////////
// Set a weather effect to on/off
void WeatherEffect::SetEffectState( short bNewState, DWORD weatherEffect )
{
	switch( weatherEffect )
	{
		// Rain
		case WEATHER_RAIN:
		{
			// Check if it's snowing
			if( bSnow == true )
			{
				// if it's the case, switch the Snow off
				SwitchEffectState( WEATHER_SNOW );
			}

			bRain = false;
			if( bNewState )
			{
				// Switch the rain on
				bRain = true;
			}

			WorldPos wlPos = { 0, 0, 0 };
			Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_RAIN, bNewState );
			
			break;
		}
		case WEATHER_SNOW:
		{
			// Check if it's rainning
			if( bRain == true )
			{
				// if it's the case, switch the Rain off
				SwitchEffectState( WEATHER_RAIN );
			}

			bSnow = false;
			if( bNewState )
			{
				// Switch the rain on
				bSnow = true;
			}

			WorldPos wlPos = { 0, 0, 0 };
			Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_SNOW, bNewState );
			
			break;
		}
		case WEATHER_FOG:
		{
			bFog = false;
			if( bNewState )
			{
				// Switch the fog on
				bFog = true;
			}

			// Broadcast the new state
			// Since fog in cavern/dungeon is allowed
			WorldPos wlPos = { 0, 0, 0 };
			Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_FOG, bNewState );

			break;
		}
		default:
			return;
	}	
}

//////////////////////////////////////////////////////////////////////
// Switch an effect (on->off or off->on)
void WeatherEffect::SwitchEffectState( DWORD weatherEffect )
{
	switch( weatherEffect )
	{
		case WEATHER_RAIN:
		{
			bRain = !bRain;
			break;
		}
		case WEATHER_SNOW:
		{
			bSnow = !bSnow;
			break;
		}
		case WEATHER_FOG:
		{
			bFog = !bFog;
			break;
		}
		default:
			return;
	}
}

//////////////////////////////////////////////////////////////////////
// Return true if effect is activated, else otherwise
bool WeatherEffect::GetEffectState( DWORD weatherEffect )
{
	switch( weatherEffect )
	{
		case WEATHER_RAIN:
		{
			return bRain;
		}
		case WEATHER_SNOW:
		{
			return bSnow;
		}
		case WEATHER_FOG:
		{
			return bFog;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
// Disable all the effects
void WeatherEffect::DisableAllEffects()
{
	WorldPos wlPos = { 0, 0, 0 };

	bRain = false;	
	Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_RAIN, (short) bRain );

	bSnow = false;
	Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_SNOW, (short) bSnow );

	bFog  = false;
	Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_FOG, (short) bFog );
}

//////////////////////////////////////////////////////////////////////
// Return true if all the effects are switched off
bool WeatherEffect::AreEffectsOff()
{
	return !( bRain || bSnow || bFog );
}

//////////////////////////////////////////////////////////////////////
// Check the new pos of the player and determines if effects must continue or not
void WeatherEffect::CheckWeatherState( Unit* self, WorldPos newPos )
{
	// If there are no effects ON, stop here
	if( AreEffectsOff() == true )
	{
		return;
	}

	// Fetch the right effect(s) on the area
	/*COLORREF effect = vWeatherMaps[newPos.world].Effects[newPos.X][newPos.Y];

	// If the pixel contains the color red, then it's raining here
	if( GetRValue( effect ) > 0 && (bRain == true) )
	{
		// Check if it is necessary to sent a packet
		if( self->bRainState == false )
		{
			SetEffectState( WEATHER_RAIN, true );
			self->bRainState = true;

			self->SendSystemMessage( "Rain ON" );
		}
	}
	else
	{
		// else disable
		if( self->bRainState == true )
		{
			SetEffectState( WEATHER_RAIN, false );
			self->bRainState = false;

			self->SendSystemMessage( "Rain FALSE" );
		}
	}

	// If the pixel contains the color green, then it's snowing here
	if( GetGValue( effect ) > 0 && (bSnow == true) )
	{
		// Check if it is necessary to sent a packet
		if( self->bRainState == false )
		{
			SetEffectState( WEATHER_SNOW, true );
			self->bSnowState = true;

			self->SendSystemMessage( "Snow ON" );
		}
	}
	else
	{
		// else disable
		if( self->bSnowState == true )
		{
			SetEffectState( WEATHER_SNOW, false );
			self->bSnowState = false;

			self->SendSystemMessage( "SNOW FALSE" );
		}
	}

	// If the pixel contains the color blue, then it's foggy here
	if( GetBValue( effect ) > 0 && (bFog == true) )
	{
		// Check if it is necessary to sent a packet
		if( self->bFogState == false )
		{
			SetEffectState( WEATHER_FOG, true );
			self->bFogState = true;

			self->SendSystemMessage( "Fog ON" );
		}
	}
	else
	{
		// else disable
		if( self->bFogState == true )
		{
			SetEffectState( WEATHER_FOG, false );
			self->bFogState = false;

			self->SendSystemMessage( "Fog FALSE" );
		}
	}*/

		// Now check the pos
	if( newPos.world == 1 || newPos.world == 2 )
	{
		// Do not show RAIN or SNOW effect in the caverns/dungeons (fog is allowed)
		if( bRain )
		{
			SendWeatherState( self, WEATHER_RAIN, false );			
		}

		if( bSnow )
		{
			SendWeatherState( self, WEATHER_SNOW, false );
		}

		return;
	}

	if( bRain )
		SendWeatherState( self, WEATHER_RAIN, bRain );

	if( bSnow )
		SendWeatherState( self, WEATHER_SNOW, bSnow );

	if( bFog )	
		SendWeatherState( self, WEATHER_FOG, bFog );	

	return;
}

//////////////////////////////////////////////////////////////////////
// Send to the player the state of an effect
void WeatherEffect::SendWeatherState( Unit* self, DWORD weatherEffect, short bValue )
{	
	TFCPacket sending;

	// Prepare then send the packet	
	sending << (RQ_SIZE) RQ_WeatherMsg;
	sending << (short) bValue;
	sending << (long) weatherEffect;
	self->SendPlayerMessage( sending );

	// Free
	sending.Destroy();
}

//////////////////////////////////////////////////////////////////////
// Load a map that contains the weather effects
bool WeatherEffect::LoadWeatherMaps( void )
{
	/****************************************************
	* Note:                                             *
	* Weather maps are bitmap files, each color defines *
	* effect(s) applying on an area                     *
	*                                          Destiny  *
	****************************************************/

	if( LoadBmpMap( "WeatherMap0.bmp", 0 ) == false )
	{
		_LOG_DEBUG 
			LOG_CRIT_ERRORS, "Cannot load weather map WeatherMap0.bmp." LOG_		
		END_LOG;
	}
	

	return true;
}

//////////////////////////////////////////////////////////////////////
// Free the memory
void WeatherEffect::FreeWeatherMaps( void )
{

}

//////////////////////////////////////////////////////////////////////
// Load a map in memory
bool WeatherEffect::LoadBmpMap( char* szFile, int world )
{
	HANDLE hFile;
	DWORD  dwRead;

	BITMAPFILEHEADER biFileHeader;
	/*  WORD    bfType;//for reference
        DWORD   bfSize;
        WORD    bfReserved1;
        WORD    bfReserved2;
        DWORD   bfOffBits;*/

	BITMAPINFOHEADER biImageHeader;
	/*  DWORD      biSize;//for reference 
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;*/

	// Open the file
	hFile = CreateFile( szFile, GENERIC_READ, FILE_SHARE_READ, NULL,
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	if( hFile == INVALID_HANDLE_VALUE )
	{
		return false;
	}

	// Read the FILE header to get the total file size, and the total DATA size.
	if( !ReadFile( hFile, &biFileHeader, sizeof(BITMAPFILEHEADER), &dwRead, 0 ) )
	{		
		CloseHandle( hFile );
		return false;
	}
	
	//Continuing file reading, with Image header :
	if( !ReadFile( hFile, &biImageHeader, sizeof(BITMAPINFOHEADER), &dwRead, 0 ) )	
	{
		/*if( MapData.bData )
		{
			delete MapData.bData;
			MapData.bData = NULL;
		}*/

		CloseHandle(hFile);
		return false;
	}

    //Creating the DATA storage :
	WeatherMapData MapData;
	//MapData.bData = new BYTE[biFileHeader.bfSize - biFileHeader.bfOffBits];
	MapData.bData = new BYTE[biImageHeader.biSizeImage];

	if (MapData.bData == NULL) {
		//memory manager is not yet up or no memory was allowed
		CloseHandle(hFile);
		return false;
	}

	// Read the bitmap
	if( !ReadFile( hFile, MapData.bData, 100/*biImageHeader.biSizeImage*/, &dwRead,0 ) )
	{
		if( MapData.bData )
		{
			delete MapData.bData;
			MapData.bData = NULL;
		}

		CloseHandle(hFile);
		return false;
	}

	CloseHandle( hFile );

	// Set the size of the map
	MapData.wMapX	  = biImageHeader.biWidth;
	MapData.wMapY	  = biImageHeader.biHeight;
	MapData.wWorldID  = world;

	// Put the colors in memory (this isn't the best way :D)
	int i;

	// Memory
	MapData.Effects = new COLORREF*[biImageHeader.biWidth];
	for( i = 0; i < biImageHeader.biWidth; i++ )
	{
		MapData.Effects[i] = new COLORREF[biImageHeader.biHeight];
	}
		
	int x = biImageHeader.biWidth - 1;
	int y = 0;

	i = biFileHeader.bfSize - biFileHeader.bfOffBits - 1;

	while( i >= 0 )
	{
		MapData.Effects[x][y] = RGB( MapData.bData[i], MapData.bData[i-1], MapData.bData[i-2] );
		x--;

		if( x == -1 )
		{
			x = biImageHeader.biWidth - 1;
			y++;
		}

		i -= 3;
	}


	MapData.bLoaded = true;

	vWeatherMaps.push_back( MapData );

	// free the buffer
	if( MapData.bData )
	{
		delete MapData.bData;
		MapData.bData = NULL;
	}

	return true;
}