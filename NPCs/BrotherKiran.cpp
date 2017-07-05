//////////////////////////////////////////////////////////////////////
// BrotherKiran.cpp: implementation of the BrotherKiran class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "BrotherKiran.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BrotherKiran::BrotherKiran()
{}

BrotherKiran::~BrotherKiran()
{}

extern NPCstructure::NPC Priest;

void BrotherKiran::Create(){
    npc = Priest;
	SET_NPC_NAME( "[3031]Brother Kiran" );
    npc.InitialPos.X = 2955;
    npc.InitialPos.Y = 1048;
	npc.InitialPos.world = 0;
    npc.boPrivateTalk = TRUE;
}

void BrotherKiran::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT HEAL = 1;
CONSTANT SeeTheHighPriest = 2;

InitTalk

Begin
"" 
IF (CheckFlag(__FLAG_ADDON_CRIMSONSCALE_LETTER)==0)
	Conversation
	INTL( 11728, "A messenger came recently to the temple and dropped something for you. Speak to "
	"Kilhiam for more information.") 	
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 19)
	Conversation
	FORMAT(INTL( 11729, "Welcome back, %s. Were you here to see the High Priest?"), USER_NAME)
	SetYesNo(SeeTheHighPriest)
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 20)
	Conversation
	FORMAT(INTL( 11730, "Ah, %s... I see you have found the High Priest's note. He said he had some \"important\" \"things\" "
	"to take care of."), USER_NAME) 
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)
	Conversation
	INTL( 11731, "Have you been to the town hall yet? It's the big building at the end of the street southeast of here.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 11732, "Welcome to the temple, friend. You may take refuge here if you like in these troubled times.")
ELSE
	Conversation
	INTL( 11733, "Artherk be praised! It's the one who slew Olin Haad! Welcome brave adventurer. Please stay as long "
	"as you like.")
ENDIF

YES(SeeTheHighPriest)
	Conversation
	INTL( 11734, "I'm afraid you have arrived before him then. You see, right after your last meeting with him, Father "
	"Gunthar called a meeting of his own with the head of our order. It seems he had some \"important\" "
	"\"things\" to discuss with him.")
NO(SeeTheHighPriest)
	Conversation
	INTL( 11735, "Oh... well what can I do for you then?")
YesNoELSE(SeeTheHighPriest)
	Conversation
	INTL( 11736, "Were you here to see the High Priest or not?")
	SetYesNo(SeeTheHighPriest)

Command(INTL( 11737, "GUNTHAR"))
INTL( 11738, "Father Gunthar is the High Priest of Lighthaven.") 

CmdAND(INTL( 1185, "IMPORTANT"), INTL( 11739, "THING"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 19 || CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 20)
	Conversation
	INTL( 11740, "I don't know what it's about. All he told me was that he was going to the \"town\" \"hall\" for his "
	"meeting and that if you were to arrive before he did, to send you to him.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 21)
ELSE
	Conversation
	INTL( 11741, "This isn't the best time to talk about that.")
ENDIF

CmdAND(INTL( 1869, "TOWN"), INTL( 11742, "HALL"))
INTL( 11743, "It's the big building at the end of the street southeast of here. If you're not sure, look for Kirlor Dhul.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1231, "I am called Brother Kiran. I have followed the path of \"Artherk\" for many "
"years now.")

Command3(INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"),INTL( 489, "WORK"))
INTL( 1232, "I am a priest of \"Artherk\". I pray for all those who need help and "
"healing. I must ask, however, that you donate some gold pieces in exchange "
"for this service.  You must understand that our church is rather poor and "
"we can put these donations to good use.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
""
IF (CheckFlag(__BALORK_BRAND) == 1) 
	Conversation
	INTL( 3625, "Balork cursed you, you say? I'm sorry to hear that. If \"Annabelle\" the "
	"Blessed One was still here, she might be able to help you. But she's long "
	"gone, now. I hear a troll took her away to feast upon her.")
ELSE
	Conversation
	INTL( 3626, "Balork is a cruel monster who dwells under the temple.")
ENDIF

Command(INTL( 523, "ANNABELLE"))
INTL( 1234, "Young, lovely Annabelle, how we miss her! She could heal the sick and comfort "
"the downtrodden. She would hear your plight and help you, no doubt. If she "
"were still alive, that is.")

Command(INTL( 569, "HEAL"))
""
IF (USER_MAXHP == USER_HP)
    Conversation
    INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
IF (USER_LEVEL < 6)
    Conversation
    INTL( 1235, "Since you are not strong enough to acquire gold pieces on your own, "
    "I shall heal your wounds. You are now healed, my friend.")
	 CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL) 
	 PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
    HealPlayer(USER_MAXHP)
ELSE
    Conversation
    FORMAT(INTL( 1146, "Do you wish to be completely healed for %u gold pieces?"),( (USER_MAXHP-USER_HP) / 2))
    SetYesNo(HEAL)
ENDIF
ENDIF

YES(HEAL)
IF (USER_MAXHP == USER_HP)
    Conversation
    INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
    IF (Gold < ((USER_MAXHP-USER_HP)/2))
        IF (Gold > 0) 
            Conversation
            INTL( 1236, "You did not have enough gold pieces, but I have healed a few of your wounds "
            "nonetheless for what you could spare.")				
            PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7511, "You give %u gold to Kiran."), Gold) ) 
	         PRIVATE_SYSTEM_MESSAGE(INTL( 7512, "Some of your wounds have been healed!")) 	 				
				CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)            
				HealPlayer(Gold*2) 
				TakeGold(Gold)				
        ELSE
            Conversation
            INTL( 1237, "You do not have enough gold pieces to be healed. You will have to find "
            "the gold first.")
        ENDIF
    ELSE         
        Conversation
        INTL( 1238, "Thank you for this generous donation. Your wounds are now healed.  "
        "Please feel free to come back if you need more healing.")
		  PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7511, "You give %u gold to Kiran."), ((USER_MAXHP-USER_HP) /2) ) )
		  PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 		  
        CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		  TakeGold( ( (USER_MAXHP-USER_HP) / 2) )
		  HealPlayer(USER_MAXHP)		  
    ENDIF
ENDIF

NO(HEAL)
Conversation
INTL( 1239, "As you wish. Ask me again if you change your mind.")

YesNoELSE(HEAL)
Conversation
INTL( 1240, "I think your wounds are not only of the body, but of the mind as well. I will "
"pray for your spirit to heal so you can better answer my question next time.")

Command(INTL( 509, "BALORK"))
INTL( 1241, "Balork was once a man of good but it seems he was corrupted by an evil force. "
"An adventurer who barely escaped with his life claimed that Balork "
"is no longer human. Surely the poor adventurer has gone insane.")

Command(INTL( 882, "DUNGEON"))
INTL( 1242, "The dungeon under the temple has fallen into the hands of \"Balork\".")

Command(INTL( 1243, "ARTHERK"))
INTL( 1244, "Artherk is the god I will worship all my life. His followers have the task "
"of helping anyone they can and aid those in need. In times of war, unlike some priests, "
"we do not cower in our temples.  We go to the front lines of battle and heal the valiant "
"warriors, sometimes at the cost of our own lives. Such is the faith and devotion of our members.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1245, "May Artherk protect you.") BREAK

Default
INTL( 2401, "I do not know.")

EndTalk

}
