#pragma hdrstop
#include "Custodian.h"

Custodian::Custodian()
{}

Custodian::~Custodian()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void Custodian::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12728]Custodian");
	npc.InitialPos.X = 1080;
	npc.InitialPos.Y = 1400;
	npc.InitialPos.world = 0;
}

void Custodian::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void Custodian::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void Custodian::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Phrase1 = 1;
CONSTANT Phrase2 = 2;
CONSTANT Phrase3 = 3;
CONSTANT Phrase4 = 4;
CONSTANT Ready = 5;
CONSTANT GoUp = 6;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 34)
	Conversation
	INTL( 11950, "This is as far as you'll go. The top floor is not for barbarians such as yourself.")
	BREAK
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 34)
	Conversation
	INTL( 11951, "This is as far as you'll go. The top floor is not for \"barbarians\" such as yourself!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 35)
	Conversation
	INTL( 11952, "Well? Do you know what the Rite of Passage means?")
	SetYesNo(Ready) 
ELSEIF(CheckFlag(__FLAG_ADDON_CUSTODIAN_ACCESS)==1)
	Conversation
	INTL( 11953, "Welcome back to the Great Library of Althea. Would you like to go up to the fourth floor right now?")
	SetYesNo(GoUp)
ELSE
	Conversation
	INTL( 11954, "Welcome back to the Great Library of Althea. News of your great deeds has reached even this far. We "
	"have started to collect information about your exploits so that we can add them to the Althean "
	"history records... if you don't mind of course.")
ENDIF

Command(INTL( 11955, "BARBARIAN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 34)
	Conversation
	INTL( 11956, "This library is exclusively for scholars. It's because of \"uneducated\" people like you that "
	"books don't last forever. I will not tolerate your presence any longer.")
ELSE
	Conversation
	INTL( 11957, "I can't talk about that right now.")
ENDIF

Command(INTL( 11958, "UNEDUCATED"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 34)
	Conversation
	INTL( 11959, "Alright, so you think you're smart huh? Let's see if you can pass the \"Rite\" \"of\" \"Passage\" then.")
ELSE
	Conversation
	INTL( 11957, "I can't talk about that right now.")
ENDIF

CmdAND(INTL( 11960, "RITE"), INTL( 11961, "PASSAGE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 34)
	Conversation
	INTL( 11962, "\"Dos\" \"vaneslae\" \"navidal\", \"Kadrim\" \"lok\" \"ungrim\" \"dok\", \"Somalina\" \"oundi\" "
	"\"inesora\", \"Tharrgra\" \"nethdrovar\". If you can tell me what it means, "
	"then not only will I grant you access to the top floor, but I might actually be nice about it. Oh, and "
	"here's a hint. You don't stand a chance at solving this little puzzle if you don't visit the library's "
	"basement.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 35)
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 35)
	Conversation
	INTL( 11963, "The four phrases are: \"Dos\" \"vaneslae\" \"navidal\", \"Kadrim\" \"lok\" \"ungrim\" \"dok\", "
	"\"Somalina\" \"oundi\" \"inesora\", \"Tharrgra\" \"nethdrovar\". Tell me what they mean and I will "
	"grant you access to the top floor,")
ELSE
	Conversation
	INTL( 11957, "I can't talk about that right now.")
ENDIF

Command4(INTL( 11964, "DOS VANESLAE NAVIDAL"), INTL( 11965, "KADRIM LOK UNGRIM DOK"), INTL( 11966, "SOMALINA OUNDI INESORA"), INTL( 11967, "THARRGRA NETHDROVAR"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 35)
	Conversation
	INTL( 11968, "Don't just repeat what I said back at me! I want you to tell me what all this means! These four phrases "
	"are the key to passing the Rite of Passage. Tell me what it means or you can forget about ever seeing the "
	"upper floor of the library.")
ELSE
	Conversation
	INTL( 11957, "I can't talk about that right now.")
ENDIF

YES(Ready)
	Conversation
	INTL( 11969, "Really? Then tell me, what does the first phrase mean?")
	SetYesNo(Phrase1)
NO(Ready)
	Conversation
	INTL( 11970, "Well then what are you doing here? You must pass the \"Rite\" \"of\" \"Passage\" before I will let you "
	"go up to the top floor.")
YesNoELSE(Ready)
	Conversation
	INTL( 11971, "Do you know what the Rite of Passage means or not?")
	SetYesNo(Ready)

;} else if( ( msg.Find(INTL( 11972, "TO LOOK UPON ONE")) != -1 ) && ( msg.Find(INTL( 11973, "SELF")) != -1 ) && YesNo == Phrase1) {;YesNo = Phrase2;
	Conversation
	INTL( 11974, "Interesting... now tell me, what does the second phrase mean?")

;} else if(YesNo == Phrase1) {;
	Conversation
	INTL( 11975, "I knew it... a barbarian, through and through.")
	BREAK

;} else if( ( msg.Find(INTL( 11976, "ONE MUST ONLY HAVE EYES")) != -1 ) && YesNo == Phrase2) {;YesNo = Phrase3;
	Conversation
	INTL( 11977, "Not bad... now tell me, what does the third phrase mean?")

;} else if(YesNo == Phrase2) {;
	Conversation
	INTL( 11975, "I knew it... a barbarian, through and through.")
	BREAK

;} else if( ( msg.Find(INTL( 11978, "TO RECOGNIZE ONE")) != -1 ) && ( msg.Find(INTL( 11979, "OWN IGNORANCE")) != -1 ) &&  YesNo == Phrase3) {;YesNo = Phrase4;
	Conversation
	INTL( 11980, "Very good! You might actually make it... now tell me, what does the last phrase mean?")

;} else if(YesNo == Phrase3) {;
	Conversation
	INTL( 11975, "I knew it... a barbarian, through and through.")
	BREAK

;} else if( ( msg.Find(INTL( 11981, "ONE MUST OPEN THESE EYES")) != -1 ) && YesNo == Phrase4) {;YesNo = 0;
	Conversation
	INTL( 11982, "Excellent! Nicely done! You have surpassed my expectations... for a barbarian that is. Alright, as "
	"promised, I now grant you full \"access\" to the library. The librarians should be able to answer "
	"questions you have.")
	GiveFlag(__FLAG_ADDON_CUSTODIAN_ACCESS, 1) 	

;} else if(YesNo == Phrase4) {;
	Conversation
	INTL( 11975, "I knew it... a barbarian, through and through.")
	BREAK

Command(INTL( 11983, "ACCESS"))
""
IF(CheckFlag(__FLAG_ADDON_CUSTODIAN_ACCESS) == 1)
	Conversation
	INTL( 11984, "Would you like to go up to the fourth floor right now?")
	SetYesNo(GoUp)
ELSE
	Conversation
	INTL( 11957, "I can't talk about that right now.")
ENDIF
 
YES(GoUp)
	Conversation
	INTL( 11985, "Very well, there you go! And don't damage any of the books!")
	TELEPORT(1081, 1465, 0)
	BREAK
NO(GoUp)
	Conversation
	INTL( 11986, "Very well. Let me know when you want to go up then.")
	BREAK
YesNoELSE(GoUp)
	Conversation
	INTL( 11987, "Would you like to go up to the fourth floor or not?")
	SetYesNo(GoUp)

Command(INTL( 483, "NAME"))
INTL( 11988, "I am the custodian of this library.")

Command(INTL( 489, "WORK"))
INTL( 11989, "I make certain the top floor stays clean and in order... and the best way to do that is to keep people "
"like you from going up there!")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 11990, "And not a moment too soon!")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 11991, "If you can't speak correctly, then don't open your mouth at all!")
ELSE
	Conversation
	INTL( 11992, "Someone should teach you to speak properly... barbarian!")
ENDIF

EndTalk
}