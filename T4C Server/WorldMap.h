// WorldMap.h: interface for the WorldMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORLDMAP_H__8F5DDC53_D5B8_11D0_B55C_00E029058623__INCLUDED_)
#define AFX_WORLDMAP_H__8F5DDC53_D5B8_11D0_B55C_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SharedStructures.h"
#include "Unit.h"
#include "TFCPacket.h"
#include "Directions.h"
#include "AreaSensitiveEffect.h"
#include "Capuchon.h"
#include "Lock.h"
#include "vdlist.h"

class EXPORT WorldMap : public CLock
{
public:
	WorldMap();
	virtual ~WorldMap();

	void Create(unsigned short x, unsigned short y, unsigned short world, unsigned char *buffy/*, TemplateList <MonsterEncounter> *werw*/
		);
	
	// Grabs (removes and returns) a unit from the world
	//Unit *grab_unit(unsigned short xo, unsigned short yo);	
	// Adds an object to the world
	void deposit_unit(WorldPos where, Unit *obj);
	
	// uses an item on the ground
	void UseItem(WorldPos where, DWORD dwID, Unit *self, Unit *target = NULL); // default for "self" use
	
	// For "world" effects (such as poison clouds, traps etc
	void add_effect(unsigned int minx, unsigned int miny, unsigned int maxx, unsigned int maxy, unsigned short effect, LPVOID params, int paramsize);
	void QueryEffects(WorldPos where, Unit *who_stepped);
		
	// Returns TRUE of 'where' is blocking
	BOOL IsBlocking(WorldPos where, Unit *obj = NULL, signed short xo = 0, signed short yo = 0);

	// Creates a world unit
	Unit *create_world_unit(char UnitType, UINT which, WorldPos where, Unit *Provided = NULL, BOOL ForceCreation = FALSE);
	// external implementation of remove_world_unit	
	void remove_world_unit( WorldPos where, DWORD ID );	
	// moves a world object
	BOOL move_world_unit(WorldPos from, WorldPos to, DWORD ID, char direction, BOOL god, bool boBroadcastMove = true );
	
	// returns the top unit on the ground.
	Unit *ViewTopUnit( WorldPos wlPos );		
	
	// returns a packet with the surrounding units
	int  packet_inview_units(WorldPos where, TFCPacket &sending, unsigned char range, Unit *self );
	BOOL packet_peripheral_units(WorldPos where, unsigned char range, DIR::MOVE dir, TFCPacket &sending, Unit *self );
	
	// returns TRUE of where is a possible place in World
    bool IsValidPosition(WorldPos where){
        return ( where.X < MAXX && where.Y < MAXY && where.X >= 0 && where.Y >= 0 );
    }






	// Makes a monster 'scan for hostiles'
	Unit *ScanHostiles(WorldPos where, char range, Unit *ThisCreature);
	
	// returns max X and Y coordinates of the world
	int GetMAXX();
	int GetMAXY();

	// Searches the nearby areas for a particular unit using it's ID
	Unit *FindNearUnit(WorldPos where, DWORD ID);
	
	BOOL SetBlockingUnit(WorldPos where, Unit *unit);
	void RemoveBlockingUnit(WorldPos where, Unit *obj);
	void RemoveAllBlockingUnits( WorldPos where, Unit *obj );

	TemplateList <Unit> *GetLocalUnits(WorldPos wlWhere, BYTE bRange, BOOL boLiving);	


	WorldPos GetLocalRandomPos( WorldPos offset, BYTE range = 0 );
	bool SummonMonster( Unit *mob, BOOL boCreateAbsolute );

	// Returns the area type, __BLOCK... of a given pos.
	BYTE QueryAreaType( WorldPos wlPos );

	// Returns TRUE if a player is near that position.
	BOOL IsNearPlayer( WorldPos wlPos );

	// Finds a valid non-blocking area around the given point within the given range.
	WorldPos FindValidSpot( WorldPos wlCenter, WORD wRange, BOOL bAllowPiles=false );//BLBLBL added BOOL bAllowPiles

	inline void VerifyPeripheralHives( WorldPos wlPos, DIR::MOVE dirPOV );
	inline void VerifyInviewHives( WorldPos wlPos );

    // Returns the position where it would collide betwen Pos1 and Pos2,
    BOOL GetCollisionPos( WorldPos Pos1, WorldPos Pos2, WorldPos *lpReturnPos, Unit **lpCollideUnit, bool boTargetPC = true, bool boTargetNPC = true );
	bool AttackBlockTest( WorldPos Pos1, WorldPos Pos2, WorldPos *lpReturnPos);
	void SetBlocking(WorldPos where, unsigned char which);//BLBLBL passage de privé en public

private:	
	inline Unit *GetHiveAt( int nX, int nY );
    inline BOOL IsCollideArea( BYTE bAreaType );

    inline BOOL QueryPositionCollision( WorldPos wlPos, Unit **lpCollisionUnit, bool boTargetPC );

	//Unit *search_unit(unsigned short X, unsigned short Y, DWORD ID);

	// Blocking functions
	inline BOOL internalIsBlocking(WorldPos where, Unit *lpuCheck = NULL,signed short xo = 0, signed short yo = 0);		
	//void SetBlocking(WorldPos where, unsigned char which);	//BLBLBL passage en public

	//TemplateList <MonsterEncounter>    *WorldMonsters;
	TemplateList <AreaSensitiveEffect> *EffectList;
	Capuchon ***WorldUnits;
	//MonsterGroup *MonsterGroups;

	unsigned int world;
	unsigned short MAXX, MAXY;
	unsigned char *map_buffy; // Holds the map for blocking structures (1 blocks, 0 passes)



    inline void VerifyStackPacketting( WorldPos wlPos, Capuchon *lpStack, TemplateList< Unit > &tlItemsFound, Unit *target );
    inline bool VerifyUnitPacketting ( Unit *lpUnit, Unit *target, WorldPos wlPos );
};

#endif // !defined(AFX_WORLDMAP_H__8F5DDC53_D5B8_11D0_B55C_00E029058623__INCLUDED_)
