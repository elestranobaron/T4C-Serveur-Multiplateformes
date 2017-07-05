//////////////////////////////////////////////////////////////////////
// CaptainHarockHarr.cpp: implementation of the CaptainHarockHarr class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "CaptainHarockHarr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CaptainHarockHarr::CaptainHarockHarr()
{}

CaptainHarockHarr::~CaptainHarockHarr()
{}

extern NPCstructure::NPC PirateHarockHarr;

//Nom: Captain Harock Harr.
//Statistique: Windhowl Sailor.
//Position: 2101, 607 at the docks
//World: 0
//Description: Sailor.
//Body: Pirate.
//OnAttacked: "HAR! HAR!"

//////////////////////////////////////////////////////////////////////////////////////////
void CaptainHarockHarr::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of CaptainHarockHarr
//
{
	npc = PirateHarockHarr;
	SET_NPC_NAME( "[2999]Captain Harock Harr" );
	npc.InitialPos.X = 1583;
	npc.InitialPos.Y = 1215;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CaptainHarockHarr::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of CaptainHarockHarr
//
{
CONSTANT SAIL = 1
CONSTANT STORY = 2
CONSTANT STORYNEXT = 3 

InitTalk

Begin
INTL( 2232, "Hardy Har har! What do you want with this old sailor?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2233, "I am Harock Harr, the greatest Sailor of all time! Har! I have \"stories\", "
"I tell you, that you would never believe, but they're as true as I am here! "
"Har!")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2234, "What kind of question is this? Har! I have \"sailed\" many seas and fought "
"beasts as big as the entire village. I am a captain.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2235, "Har! By my grandfather's rotting wooden leg! Balork's curse is just a "
"fairy tale, methinks. I have fought beasts that are much stronger than "
"that weakling. Har!")

Command(INTL( 523, "ANNABELLE"))
INTL( 1158, "I do not know much about that woman.")

Command(INTL( 2236, "SAILED"))
INTL( 2237, "I have sailed across all the seas and oceans, and I even went to the end of "
"the world! Har! But to this day, I have never been able to find a flying "
"ship to go farther.")

Command(INTL( 2238, "STORIES"))
INTL( 2239, "Hardy Har har! Be forewarned, for that these stories be real, says I! Which "
"one do you wish to hear, eh? The story of the giant \"squid\" or when I "
"battled a giant \"whale\"? Or maybe the time I caught a twelve meter long "
"\"trout\"! Har! Har! Maybe I ought to tell you about when I \"drank\" the "
"whole ocean to help one of my crew members from drowning! Hardy Har har! Or "
"my personal favorite story: when I dove in water full of twenty meter, har!, "
"make it forty meter long \"sharks\", to reach an undersea treasure!")

Command(INTL( 2240, "SQUID"))
INTL( 2241, "The sea was angry on that day, I'm tellin' ya! The waves were high "
"and the wind was blowing so hard that giant whales were flying by. Har! But "
"I had a map to the secret location of a squid that had gold in its belly! "
"Har! It took great courage and leadership to brave such a dreadful day. The "
"squid finally decided to come out of its hideout to attack our great ship. I "
"took my favorite harpoon and without thinking about my own life, I charged "
"at the squid. Har! Oh, but you seem in a hurry... Do ya want to know the "
"rest of the story? Har!")
SetYesNo ( STORY )

YES ( STORY )
	Conversation
	INTL( 2242, "Har! Very well then... As I was saying, I went after the squid, but a splashing "
	"wave came over me, lifting me up, twisting me and making me lose all sense "
	"of direction. The next thing I knew, I was on the giant squid, standing "
	"just next to its gaping jaw! Har! The beast had razor sharp teeth and could have "
	"swallowed dozens of sharks in a single bite. I lost my harpoon in the "
	"turmoil so I fought with my barehands! I ripped open its belly with my own "
	"teeth! Say there, you look a bit pale. You sure you wanna hear the rest?")
	SetYesNo ( STORYNEXT )

NO (STORY)
	Conversation
	INTL( 2243, "Har! You're missing a great story!")

YesNoELSE( STORY )
	Conversation
	INTL( 2244, "Oy! This be a simple yes or no question! So ya want to hear it or "
	"not? Har!")
	SetYesNo ( STORY )

YES ( STORYNEXT )
	Conversation
	INTL( 2245, "Great! You got a good stomach, you'd make a fine sailor! Har. As I was "
	"telling ya... gold my friend... GOLD! So much that I couldn't count it all! The "
	"squid had destroyed my ship and my crew so I had to swim back home with the "
	"squid in the raging storm. I fed on the squid day after day. With my awesome "
	"bump of direction, I was back home after forty five days and nights. "
	"Hardy Har har! Ask anyone around, they will all tell you that it's all true! "
	"Har Har!")

NO ( STORYNEXT )
	Conversation
	INTL( 2243, "Har! You're missing a great story!")

YesNoELSE( STORYNEXT )
	Conversation
	INTL( 2246, "Oy! This be a simple yes or no question! So ya want to hear it or "
	"not? Har!")
	SetYesNo ( STORYNEXT )

Command(INTL( 2247, "WHALE"))
INTL( 2248, "Har! This be the story of my life! Har! I was hunting for a great white "
"whale that had twice before foiled me in combat. I survived, but not before "
"the giant beast had taken one of my legs along with it. Revenge was the only "
"thing I could think of for many years after that. Har! Well... actually, it "
"is quite a long story, but suffice it to say, I vanquished this great, twenty-"
"meter long raging white whale in a fight that shook the whole sea!")

Command(INTL( 2249, "TROUT"))
INTL( 2250, "Har! You don't believe me? I was fishing one day aboard my great vessel and "
"some giant beast grabbed my hook. For thirty days and nights I tried "
"relentlessly to get it out of the water, leading to the greatest battle of all "
"time between man and beast! Har! Har! And finally, I succeeded in taking this "
"giant thirteen-meter trout out of the sea by making it believe the air was "
"better than the water! Ya know what? The beast actually believed me! Har! "
"Har! I really AM a genius! Har!")

Command(INTL( 2251, "DRANK"))
INTL( 2252, "Har! This be a great story, my friend. One day, while me and my crew had just "
"vanquished a bunch of pirates, one of my crewmembers was drunk from the "
"festivities of our great victory and tripped on the bridge, falling into the "
"deep, dark sea. Har! har! As a good captain, I had the obligation of saving "
"the lad. Without consideration for my personal safety, I jumped in the sea, and in one "
"big gulp, I drank it all up! Har har! The crewman then boarded my ship, and "
"I spat out the entire ocean. We then sailed safely back home and were in time for "
"dinner. Hardy har har! What a story eh?")

Command(INTL( 2253, "SHARKS"))
INTL( 2254, "Hardy har har! To this day, no fight like that had even been fought before. "
"Dozens of sharks, fifty meters long, sometimes more, attacked me! My hands "
"were even tied behind my back, for I had just been thrown out into the sea "
"by pirates. I had to fight each and every one of those sharks with my teeth. "
"Har! Blood was spilled I can tell ya! Har! har! I nearly lost an arm, but "
"with my extraordinary fighting skills, I vanquished those overgrown sharks "
"and swam back ashore with only one leg left and my hands still tied up! Har!")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2255, "Farewell! Har harr!") BREAK

Default
INTL( 2256, "Aye...")

EndTalk

}