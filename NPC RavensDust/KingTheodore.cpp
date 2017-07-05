#pragma hdrstop
#include "KingTheodore.H"

KingTheodore::KingTheodore()
{}

KingTheodore::~KingTheodore()
{}

extern NPCstructure::NPC KingTheodoreNPC;

void KingTheodore::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
    TFormat FORMAT;

    SHOUT(FORMAT(INTL( 6069, "GUARDS! %s is attempting to murder me! HEEEELP! "), USER_NAME) )
   IF (rnd.roll(dice(1, 2)) == 1)
      TELEPORT( 206, 2380, 1) // Somewhere in the prison.
   ELSE
      TELEPORT( 218, 2336, 1) // Somewhere in the prison.
   ENDIF  
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void KingTheodore::Create( void )
{
        npc = ( KingTheodoreNPC );
        SET_NPC_NAME( "[2963]King Theodore XIII" );
        npc.InitialPos.X = 1390;//848;//1405;   
        npc.InitialPos.Y = 2358;//648;//2300;
        npc.InitialPos.world = 0;//4;//0;
}

void KingTheodore::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
   self->SetCanMove( FALSE );  // I don't want to see a sleepwalker. :)
}

void KingTheodore::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT TOWN = 1;
CONSTANT SAPPHIRE = 2;

InitTalk

Begin
""
IF (TFCTime::IsEvening())   // Awake only between 18:00 and 0:00 gametime
   IF (CheckFlag(__FLAG_AUDIENCE_W_KING) == 0)
      Conversation
	INTL( 6070, "Ask my Chamberlain for an audience else I shall not talk to you.")

      BREAK
   ELSE
      RemFlag(__FLAG_AUDIENCE_W_KING)  // User must go through the process each
                                       // time he wishes to speak with the King.      
      Conversation
      INTL( 6071, "*yawn* I hope that what you have to say is of importance to me for "
      "I am extremely fatigued by this extenuating day of \"work\".")
   ENDIF
ELSE
   IF (rnd.roll(dice(1, 3) ) == 1)
      Conversation
      INTL( 6072, "ZZzzz... hmm... ZzzzZzzzzZzzz...")
   ELSEIF (rnd.roll(dice(1, 3) ) == 2)
      Conversation
      INTL( 6073, "ZzzzzzzZZzz... uh...ZzzzzzzZ...ZZzzzzz")
   ELSEIF (rnd.roll(dice(1, 3) ) == 3)
      Conversation
      INTL( 6074, "ZZzzzz...")
   ELSE
      Conversation
      INTL( 6075, "ZzzzZzz.. zZZzz... ZzzzzzzzZZzZzz")
   ENDIF
ENDIF

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 6076, "*yawn* I am not quite in the mood for some chit-chat.")

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 6077, "I am \"King\" \"Theodore\" the XIIIth, ruler of the Kingdom of \"Goldmoon\" "
"and proud father of \"Princess\" \"Delilah\".")

Command4(INTL( 3696, "WHAT DO YOU DO"),INTL( 4905, "WHAT ARE YOU"),INTL( 487, "OCCUPATION"),INTL( 489, "WORK"))
INTL( 6078, "One should think that a King has nothing to do but it is quite the opposite. "
"All day long, I have to isolate myself in my private quarters and think how "
"I could improve the life of all the people in my \"kingdom\".")

Command2(INTL( 5786, "KING THEODORE"),INTL( 6079, "HIGHNESS"))
INTL( 6080, "Indeed, I am King Theodore the XIIIth.")

Command(INTL( 754, "THEODORE"))
INTL( 6081, "Such impoliteness! If you must talk to me, do it using my rightful title!")

Command2(INTL( 6082, "DEAD BROTHER"),INTL( 6083, "BROTHERS"))
INTL( 6084, "They are dead and gone. Ghosts do not exist.")

Command(INTL( 1638, "TOURNAMENT"))
INTL( 6085, "When father passed away, it was written that my twelve \"brothers\" and I "
"had to fight to death. I shall spare you how bravely I fought my own "
"brothers... but the bottom line is that I've won. Thus, I have been crowned "
"\"King\" of \"Goldmoon\".")

Command2(INTL( 1460, "THEOPOLD"),INTL( 1443, "FATHER"))
INTL( 6086, "King Theopold was my father and a good king. I must say that I am much "
"like him and everybody in the kingdom is happy. ")

Command(INTL( 537, "CASTLE"))
INTL( 6087, "This is such as great castle. It was built by my late father, \"King\" \"Theopold\".")

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 6088, "Yet another rebel who is jealous of my throne. He does not cause much "
"of a threat to me.")

Command3(INTL( 4541, "PRINCESS"),INTL( 1005, "DELILAH"),INTL( 984, "DAUGHTER"))
INTL( 6089, "Princess Delilah is my proud daughter. Although, I fear that she may "
"have become too attached to her mentor, \"Bishop\" \"Rikken\" \"Crowbanner\". She cannot "
"bear when he falls into sickness and spends her days in prayer for his "
"recovery.")

Command3(INTL( 4546, "RIKKEN"),INTL( 4547, "CROWBANNER"),INTL( 4545, "BISHOP"))
INTL( 6090, "Ask my daughter.")

Command(INTL( 3848, "ZHAKAR"))
INTL( 6091, "Doesn't ring a bell.")

Command4(INTL( 4185, "GHUNDARG"),INTL( 4186, "RUMBLEFOOT"),INTL( 2812, " ORC "),INTL( 2813, " ORCS "))
INTL( 6092, "Please, do not speak of Ghundarg Rumblefoot in my presence. I let "
"\"Mordrick\" \"Warstone\" to deal with them, that is what he is paid for.")

Command(INTL( 5041, "SAPPHIRE"))
""
IF (CheckFlag(__QUEST_SAPPHIRE_GEM) == 0)
   Conversation
   INTL( 6093, "*yawn* Yes, I have some of those. But, I don't see why one such as "
   "you would need one.")
ELSE
   Conversation
   INTL( 6094, "Uh? Elysana Blackrose said she needed a sapphire gem? This changes "
   "everything. I am willing to give you a blue sapphire gem *IF* "
   "you bring me a tanned skin of an antelope. Does that seem fair "
   "to you?") 
   SetYesNo(SAPPHIRE) 
ENDIF

YES(SAPPHIRE)
   IF (CheckItem(__OBJ_TANNED_ANTELOPE_SKIN) == 0)
      IF (CheckItem(__OBJ_ANTELOPE_SKIN) >= 0)
         Conversation
         INTL( 6095, "I clearly said that the skin must be \"tanned\"!")
      ELSE
         Conversation
         INTL( 6096, "Are you trying to fool your Majesty? You do not "
         "have any antelope skin! Out of my sight before "
         "I throw you in jail!")
      ENDIF
   ELSE
      IF (CheckItem(__OBJ_TANNED_ANTELOPE_SKIN) > 1)
         Conversation
         INTL( 6097, "It seems that you have many tanned antelope's skins. "
         "Fine, I'll take them all in exchange for this "
         "sapphire gem. I *am* your King afterall. What I "
         "want, I take.") 
			;int nNumSkins = CheckItem(__OBJ_TANNED_ANTELOPE_SKIN); 
          FOR(0, nNumSkins )
            TakeItem(__OBJ_TANNED_ANTELOPE_SKIN)
          ENDFOR
          GiveItem(__OBJ_SAPPHIRE_GEM)
      ELSE
         Conversation
         INTL( 6098, "Fine. I'll take the skin and I give you this  "
         "sapphire gem. Now, let me sleep if you will.")
          TakeItem(__OBJ_TANNED_ANTELOPE_SKIN)
          GiveItem(__OBJ_SAPPHIRE_GEM)
      ENDIF
   ENDIF

NO(SAPPHIRE)
Conversation
INTL( 6099, "Bah. Your lost!")

YesNoELSE(SAPPHIRE)
Conversation
INTL( 6100, "Then, can I get back to sleep?")

Command(INTL( 4884, "TANNED"))
INTL( 6101, "How should know who could tan an animal's skin? I am the king, not the "
"Oracle. But.. wait.. perhaps Samuel knows someone. Ask him on my behalf.")

Command2(INTL( 6102, "MORDRICK"),INTL( 6103, "WARSTONE"))
INTL( 6104, "Mordrick Warstone is the best knight in the realm. Perhaps you might want "
"to step forward as a recruit into our army? If so, simply ask him.")

Command2(INTL( 994, "KINGDOM"),INTL( 753, "GOLDMOON"))
INTL( 6105, "When my father passed away, a \"tournament\" took place and I, Theodore "
"the XIIIth, was the sole survivor. Thus, I inherited of my father's title "
"and became the \"King\" of Goldmoon.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 6106, "Isn't a small town located somewhere in \"Arakas\"?")

YES(TOWN)
Conversation
INTL( 6107, "I knew that.")

NO(TOWN)
Conversation
INTL( 6108, "Heh Heh! Was just testing you. Everyone knows that Lighthaven is located "
"somewhere in the western islands.")

YesNoELSE(TOWN)
Conversation
INTL( 6109, "Stupid question and got a stupid answer.")

Command(INTL( 514, "WINDHOWL"))
INTL( 6110, "Windhowl? I don't have a clue about what you're referring to.")

Command(INTL( 515, "ARAKAS"))
INTL( 6111, "Arakas is an island located north of Raven's Dust. It is also part of the "
"kingdom of \"Goldmoon\".")

Command2(INTL( 1492, "DESERT"),INTL( 3865, "VULTURE'S DEN"))
INTL( 6112, "No one would want to go there and especially not me.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 3768, "Raven's Dust is the name of this island.")

Command(INTL( 1072, "KING"))
INTL( 6113, "Yes, this is my title. Or you may call me your \"Highness\".")

Command5(INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "),INTL( 6114, " COCK "),INTL( 4933, "DICK"))
INTL( 6115, "I am royally offended by such gross words! GUARDS! Bring this denizen to "
"jail NOW!!!")
IF (rnd.roll(dice(1, 2)) == 1)
   TELEPORT( 206, 2380, 1) // Somewhere in the prison.
ELSE
   TELEPORT( 218, 2336, 1) // Somewhere in the prison.
ENDIF
BREAK

Command4(INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 6116, "Our conversation has come to an end, I think it is time for a little nap.")
BREAK

Default
""
IF (rnd.roll(dice(1, 2) ))
   Conversation
   INTL( 6117, "Let me sleep on this for a while...")
ELSE
   Conversation
   INTL( 6118, "All this talking deeply bores me. Perhaps I should return to the royal bed.")
ENDIF

EndTalk
}
