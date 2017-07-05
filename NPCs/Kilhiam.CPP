//////////////////////////////////////////////////////////////////////
// Kilhiam.CPP: implementation of the Khiliam class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Kilhiam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Kilhiam::Kilhiam()
{}

Kilhiam::~Kilhiam()
{}

extern NPCstructure::NPC KilhiamNPC;

void Kilhiam::Create(){
        npc = KilhiamNPC;
        SET_NPC_NAME( "[3045]Kilhiam" );
        npc.InitialPos.X = 2961;
        npc.InitialPos.Y = 1058;
        npc.InitialPos.world = 0;
}

void Kilhiam::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1))
    {
         case 0: SHOUT(INTL( 1587, "AAHHHHHHH!")); break;
         case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}
	self->Do(flee);
	self->SetTarget(target);
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Kilhiam::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT QUEST = 1;
CONSTANT LIGHT = 2;
CONSTANT SANCTUARY = 3;
CONSTANT DONATION = 4;

InitTalk

Begin
"" 
IF (CheckFlag(__FLAG_ADDON_CRIMSONSCALE_LETTER)==0) 
	Conversation
	FORMAT(INTL( 11758, "Hello %s, a messenger brought this parchment yesterday for you. It seemed very important... "
	"I think you should read it at once."), USER_NAME) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 11759, "Kilhiam gives you a sealed scroll.")) 
	GiveItem(__OBJ_LETTER_FROM_CRIMSONSCALE) 
	GiveFlag(__FLAG_ADDON_CRIMSONSCALE_LETTER, 1) 
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 19)
	Conversation
	INTL( 11760, "The High Priest? He had to leave to take care of some important matters. You should talk "
	"to Brother Kiran if you need more details.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 20)
	Conversation
	INTL( 11761, "You should talk to Brother Kiran again if you need more details.")
ELSEIF(CheckFlag(__BALORK_BRAND) == 1)
    Conversation
    INTL( 1588, "Oh!! You too bear the dreadful mark of Balork upon your brow! What a disaster! He "
    "brands so many adventurers, these days. What? A cure? I apologize, I "
    "am but a lowly head priestess here, I cannot remove it. You must seek "
    "help elsewhere.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 11762, "Welcome to the temple. If the guards are bothering you, you can always take refuge here.")
ELSE
	Conversation
	FORMAT(INTL( 11763, "Always a pleasure to see you, %s! Please come visit us as often as you like."), USER_NAME)
ENDIF

Command2(INTL( 1006, "HIGH PRIEST"),INTL( 11737, "GUNTHAR")) 
""
IF((CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 19)||(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 20)||(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21))
	Conversation
	INTL( 11764, "The High Priest? He had to leave to take care of some important matters. You should talk "
	"to Brother Kiran if you need more details.")
ELSE
	Conversation
	INTL( 11765, "High Priest Gunthar is probably in his study room behind the temple.") 
ENDIF 

Command(INTL( 483, "NAME"))
INTL( 1590, "People are nice around here. If you need to know someone's \"name\", just ask "
"them. It's the same for their \"work\" too. Most of them will tell you without "
"any complaints.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 1591, "Balork's brand is a terrible curse he bestows upon those foolish enough "
"to dare challenge him.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1592, "Annabelle has a peculiar healing touch.")

Command(INTL( 489, "WORK"))
INTL( 1593, "I'm a priestess of \"Artherk\". Sometimes I \"teach\" new spells to those "
"I deem worthy of such responsibility. I'm not the only one doing this. There "
"are many practitioners around the world which will teach you about almost "
"any skill you can possibly think of. All you must do is choose a path, or several "
"paths to take and try to find the people willing to aid you in those fields. "
"Artherk has also blessed me with the Gift of \"sanctuary\".")

Command(INTL( 1243, "ARTHERK"))
INTL( 1594, "Artherk is a wonderful god. If you have any questions, I will do my best to "
"answer them. On the other hand, if you feel that the conversation is over and "
"you have no need of anything else, you can always say \"goodbye\" and be on "
"your way.")

Command2(INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 1595, "Priests are people who specialize in the art of healing and treating wounds "
"and the like. This is achieved by the use of certain spells which deal with "
"the elements of earth and water. Once you have learned these spells, you can "
"always call upon their power to aid you. Unlike skills, spells need not be "
"practiced and achieve full effectiveness as soon as you learn them. Because "
"of this, the price to pay tends to be significantly higher than with skills. "
"As you gain experience in battle, you will be able to increase your abilities "
"as well as learn new skills and spells. If you wish, I can teach you one of the "
"most basic spells available. It is the \"light\" spell, which will help you see in "
"the darkness. Do you wish to learn it now?")
SetYesNo(LIGHT)

YES(LIGHT)
	CreateSkillList
      AddTeachSkill (__SPELL_LIGHT, 5, 233)
	SendTeachSkillList
NO(LIGHT)
	Conversation
	INTL( 1604, "I see, very well then.")
YesNoELSE(LIGHT)
	Conversation
	INTL( 715, "Do you wish to learn it now?")
	SetYesNo(LIGHT)

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 1607, "Lighthaven is the name of our fair city.")

Command(INTL( 514, "WINDHOWL"))
INTL( 1608, "Windhowl is located on the western side of the island.")

Command3(INTL( 1609, "DEATH"),INTL( 1610, "DIE"),INTL( 1611, "KILLED"))
INTL( 1612, "It is always unfortunate to face death, but those who wear a "
"Gem of Destiny can set a \"Sanctuary\" where they will reappear "
"when they get killed.")

Command(INTL( 1613, "SANCTUARY"))
INTL( 1614, "The Sanctuary is where your body and soul are restored by the "
"Gem of Destiny if you have been killed. Do you wish to set "
"the Temple of Lighthaven as your sanctuary?")
SetYesNo(SANCTUARY)

YES(SANCTUARY)
IF (Gold < 1500 )
   Conversation
   INTL( 1615, "I would be glad to comply, but my order would require a donation "
   "of 1500 gold pieces, which you do not appear to have. Perhaps you "
   "should come again later, when you are more fortunate.")
ELSE
   Conversation
   INTL( 1616, "Very well. My order requires a donation of 1500 gold pieces, however. "
   "Do you accept to pay that amount?")
   SetYesNo(DONATION)
ENDIF

NO(SANCTUARY)
Conversation
INTL( 1617, "Ah. Very well, then.")

YesNoELSE(SANCTUARY)
Conversation
INTL( 1617, "Ah. Very well, then.")

YES(DONATION)
IF (Gold < 1500)  // Had to put another check to prevent a user from 
   Conversation   // dropping gold after the 1st check. 
   INTL( 1618, "I would be glad to comply, but my order would require a donation "
   "of 1500 gold pieces, which you do not appear to have. Perhaps you "
   "should come again later, when you are more fortuned.")
ELSE
   Conversation
   INTL( 1619, "It is done, then. Your body and soul shall return here if you "
   "unfortunately happen to die.")
   TakeGold(1500)
   SetDeathLocation( 2941,1062,0 )  // Temple of LightHaven
	CastSpellTarget(__SPELL_NPC_CANTRIP_BLUE_WIPE)
	PRIVATE_SYSTEM_MESSAGE(INTL( 7518, "You give 1500 gold to Kilhiam.")) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 7519, "Your spirit is now anchored here.")) 
ENDIF

NO(DONATION)
Conversation
INTL( 1620, "I understand. You need to think about this further. Come back "
"when you are ready.")

YesNoELSE(DONATION)
Conversation
INTL( 1621, "I... um... Was that a yes or a no?")
SetYesNo(DONATION)

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 1622, "Farewell, my friend.") BREAK

Default
INTL( 1623, "I cannot help you with this.")

EndTalk
/* ;}
                           ;}else{
                                CString csMsg;
                                /*if( self->GetTarget() )*//*{
                                    csMsg.Format( INTL( 1624, "Sorry but I am currently talking to another person.") );
                                }
                                target->SendPrivateMessage( csMsg, self, npc.dwTextColor );	                            
                                TFCPacket sending;
	                            sending << (RQ_SIZE)RQ_BreakConversation;
	                            target->SendPlayerMessage( sending );
                                output.Empty();
                            }
                           ;if( !output.IsEmpty() ){
                                if( self->IsPrivateTalk() ){
                                    target->SendPrivateMessage( output, self, npc.dwTextColor );
                                }else{
                                    self->Talk( (LPCTSTR)output, npc.dwTextColor, target );
                                }
                           }else{
                               CString csMsg = "";
                               target->SendPrivateMessage( csMsg, self, npc.dwTextColor );
                           }
						} */
}

//////////////////////////////////////////////////////////////////////////////////////////
void Kilhiam::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Kilhiam data function
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_LIGHT, 5, 233)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE
