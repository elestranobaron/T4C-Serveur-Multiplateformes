#pragma hdrstop
#include "WitchDoctorKwarlgloth.h"

WitchDoctorKwarlgloth::WitchDoctorKwarlgloth()
{}

WitchDoctorKwarlgloth::~WitchDoctorKwarlgloth()
{}

extern NPCstructure::NPC WitchDoctorKwarlglothNPC;

void WitchDoctorKwarlgloth::Create( ){
	npc = WitchDoctorKwarlglothNPC;
   SET_NPC_NAME( "[10936]Kwarlgloth" );
	npc.InitialPos.X = 2150;
	npc.InitialPos.Y = 105;
	npc.InitialPos.world = 2;
	npc.boPrivateTalk = TRUE;
}

void WitchDoctorKwarlgloth::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT BROWSE = 1;
CONSTANT BASH = 2;
CONSTANT BLOOD = 3;

InitTalk

Begin
INTL( 8732, "Hullo dere. Wut Kwarlgloth do fur yu?")

Command2(INTL( 8733, "DEMONIC BLOOD"), INTL( 8734, "DEEMONIK BLUD"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_DEMONIC_BLOOD) >= 1)
		Conversation
		INTL( 8735, "Wut? Hummie want more deemonik blud?")
		SetYesNo(BLOOD)
	ELSE
		Conversation
		INTL( 8736, "Dat iz Kwarlgloth treasur. Hummie want blud?")
		SetYesNo(BLOOD)
	ENDIF
ELSE
	Conversation
	INTL( 8737, "Mebbe hummie wanto talk wit Kwarlgloth fist?")
	SetYesNo(BASH)
ENDIF

YES(BLOOD)
	IF(CheckFlag(__FLAG_USER_ASKED_ABOUT_DEMONIC_BLOOD) == 0)
		Conversation
		INTL( 8749, "Kwarlgloth giv hummie deemonik blud if hummie bring four \"bludstone\" \"rings\" an tree \"daggurs\" \"of\" \"bleeding\" an 20000 gold.")
		GiveFlag(__FLAG_USER_ASKED_ABOUT_DEMONIC_BLOOD, 1)
	ELSEIF(CheckItem(__OBJ_BLOODSTONE_RING) >= 4)
		IF(CheckItem(__OBJ_DAGGER_OF_BLEEDING) >= 3)
			IF(Gold >= 20000)
				Conversation
				INTL( 8738, "Guud, Kwarlgloth teik all an giv yu blud.")
				FOR(0, 4) 
					TakeItem(__OBJ_BLOODSTONE_RING)
				ENDFOR
				FOR(0, 3)
					TakeItem(__OBJ_DAGGER_OF_BLEEDING)
				ENDFOR
				TakeGold(20000)
				GiveItem(__OBJ_DEMONIC_BLOOD) 
				PRIVATE_SYSTEM_MESSAGE(INTL( 8739, "Kwarlgloth takes 4 bloodstone rings."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 8740, "Kwarlgloth takes 3 sacrificial daggers of bleeding."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 8741, "Kwarlgloth takes 20000 gold."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 10798, "Kwarlgloth gives you some demonic blood.")) 
				Conversation
				INTL( 8742, " Dere, hummie want moore blud?")
				SetYesNo(BLOOD)
			ELSE
				Conversation
				INTL( 8743, "Hummie need moore gold. Dis nut enuf.")
			ENDIF
		ELSE
			IF(Gold >= 20000)
				Conversation
				INTL( 8744, "Kwarlgloth sed tree \"daggurs\" \"of\" \"bleeding\". Nuting less.")
			ELSE
				Conversation
				INTL( 8745, "Kwarlgloth sed tree \"daggurs\" \"of\" \"bleeding\" an 20000 gold. Nuting less.")
			ENDIF
		ENDIF
	ELSE
		IF(CheckItem(__OBJ_DAGGER_OF_BLEEDING) >= 3)
			IF(Gold >= 20000)
				Conversation
				INTL( 8746, "Kwarlgloth sed four \"bludstone\" \"rings\". Nuting less.")
			ELSE
				Conversation
				INTL( 8747, "Kwarlgloth sed four \"bludstone\" \"rings\" an 20000 gold. Nuting less.")
			ENDIF
		ELSE
			IF(Gold >= 20000)
				Conversation
				INTL( 8748, "Kwarlgloth sed four \"bludstone\" \"rings\" an tree \"daggurs\" \"of\" \"bleeding\". Nuting less.")
			ELSE
				Conversation
				INTL( 10491, "Kwarlgloth giv hummie deemonik blud if hummie bring four \"bludstone\" \"rings\" an tree \"daggurs\" \"of\" \"bleeding\" an "
				"20000 gold.")
			ENDIF
		ENDIF
	ENDIF
NO(BLOOD)
	Conversation
	INTL( 8750, "Okey, wut hummie want den?")
YesNoELSE(BLOOD)
	Conversation
	INTL( 8751, "Hummie want blud or nut?")
	SetYesNo(BLOOD)

Command2(INTL( 6327, "BLOODSTONE RING"), INTL( 8752, "BLUDSTONE RING"))
""		
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8753, "If hummie wanto get bludstone ring, hummie kill \"Bludlust\".")
ELSE
	Conversation
	INTL( 8737, "Mebbe hummie wanto talk wit Kwarlgloth fist?")
	SetYesNo(BASH)
ENDIF

Command2(INTL( 8754, "BLOODLUST"), INTL( 8755, "BLUDLUST"))
""		
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8756, "Bludlust is big wurm. Kwarlgloth only see it once.")
ELSE
	Conversation
	INTL( 8737, "Mebbe hummie wanto talk wit Kwarlgloth fist?")
	SetYesNo(BASH)
ENDIF

Command4(INTL( 8757, "DAGGER OF BLEEDING"), INTL( 8758, "DAGGUR OF BLEEDING"), INTL( 8759, "DAGGERS OF BLEEDING"), INTL( 11330, "DAGGURS OF BLEEDING"))
""		
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8760, "Kwarlgloth tink Nitecreepur or Pilfurur have dem, but nut sure.")
ELSE
	Conversation
	INTL( 8737, "Mebbe hummie wanto talk wit Kwarlgloth fist?")
	SetYesNo(BASH)
ENDIF

Command(INTL( 8761, "WHERE"))
""		
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8762, "Kwarlgloth dont remembur.")
ELSE
	Conversation
	INTL( 8737, "Mebbe hummie wanto talk wit Kwarlgloth fist?")
	SetYesNo(BASH)
ENDIF

Command2(INTL( 8763, "NIGHTCREEPER"), INTL( 8764, "NITECREEPUR"))
""		
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8765, "Ya, nitecreepur.")
ELSE
	Conversation
	INTL( 8737, "Mebbe hummie wanto talk wit Kwarlgloth fist?")
	SetYesNo(BASH)
ENDIF

Command2(INTL( 8766, "PILFERER"), INTL( 8767, "PILFURUR"))
""		
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8768, "Ya, pilfurur.")
ELSE
	Conversation
	INTL( 8737, "Mebbe hummie wanto talk wit Kwarlgloth fist?")
	SetYesNo(BASH)
ENDIF
	
Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8769, "Naim? Wut yu meen?")

Command(INTL( 8770, "KWARLGLOTH"))
INTL( 8771, "Me Kwarlgloth, da witch doktor!")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8772, "Werk? Kwarlgloth werkard an becum \"hinteljent\", not like mudder an fodder.")
	   
Command2(INTL( 8773, "HINTELJENT"), INTL( 8774, "INTELLIGENT"))
INTL( 8775, "Kwarlgloth make tings an sellum too! Yu by sumting?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList
		AddBuyItem( 12,   __OBJ_TORCH )
		AddBuyItem( 50,   __OBJ_LIGHT_HEALING_POTION )
	   AddBuyItem( 125,  __OBJ_HEALING_POTION )
		AddBuyItem( 300,  __OBJ_SERIOUS_HEALING_POTION )
		AddBuyItem( 50,   __OBJ_POTION_OF_MANA )	   
		AddBuyItem( 150,  __OBJ_MANA_ELIXIR ) 	
		AddBuyItem( 1000, __OBJ_MANASTONE ) 
	SendBuyItemList

NO(BROWSE)
	Conversation
	INTL( 8776, "Kwarlgloth tinks yu bedder by sumting or yu gunna die.")
	BREAK
YesNoELSE(BROWSE)
	Conversation
	INTL( 8777, "Yu by sumting?")
	SetYesNo(BROWSE)

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8778, "Guudbye!")
BREAK

YES(BASH)
	Conversation
	INTL( 8779, "Guud! Kwarlgloth bash yu guud!")
	FIGHT
NO(BASH)
	Conversation
	INTL( 8780, "Grrr! Kwarlgloth let yu go dis time.")
YesNoELSE(BASH)
	Conversation
	INTL( 8781, "Yu want Kwarlgloth bashyurskullin?")

Default
""
IF (rnd.roll(dice(1,2)) ) 
	Conversation
	INTL( 8781, "Yu want Kwarlgloth bashyurskullin?")
	SetYesNo(BASH)
ELSE
	Conversation
	INTL( 8782, "Wut did yu juss say?")
ENDIF

EndTalk
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void WitchDoctorKwarlgloth::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )

NPC_DATA_EXCHANGE

	NPC_SHOP_DATA

      NPC_SELL( 12, __OBJ_TORCH )
		NPC_SELL( 50, __OBJ_LIGHT_HEALING_POTION )
		NPC_SELL( 50, __OBJ_POTION_OF_MANA )
		NPC_SELL( 125, __OBJ_HEALING_POTION )
		NPC_SELL( 300,  __OBJ_SERIOUS_HEALING_POTION ) 		
		NPC_SELL( 150, __OBJ_MANA_ELIXIR ) 
		NPC_SELL( 1000, __OBJ_MANASTONE ) 
      
      NPC_SOLD_ITEM(  INTL( 8783, "Dank yew!") )
      NPC_FAILED_SELL( INTL( 8784, "Hummie nutt enuff shiny peeces!"))
      NPC_BOUGHT_ITEM( INTL( 8785, "Duh... nice..") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE

