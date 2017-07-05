// Random.h: interface for the Random class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RANDOM_H__6EB985F3_D137_11D0_B543_C09D9B000000__INCLUDED_)
#define AFX_RANDOM_H__6EB985F3_D137_11D0_B543_C09D9B000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


// shainon pour éviter les warnings
#ifndef MAXINT
	#define MAXINT 0xFFFFFFFF 
#endif
typedef unsigned int uhyper; //__int64
//typedef __int64          hyper;

class dice{
public:
    dice( unsigned int nNewDiceCount, unsigned int nNewDiceValue, int nNewPlus = 0 ) :
        nDiceCount( nNewDiceCount ), nDiceValue( nNewDiceValue ), nPlus( nNewPlus ){};

    inline unsigned int Value( void ){ return nDiceValue; };
    inline unsigned int Count( void ){ return nDiceCount; };
    inline int Plus ( void ){ return nPlus;      };
private:
    unsigned int nDiceCount;
    unsigned int nDiceValue;
    int nPlus;
};

class EXPORT Random  
{
	public:
        Random( void ){};

		static void SetSeed(uhyper NewSeed = 0/*(unsigned long)time(NULL)*/);
				
		static int testvs( int nAttacker, int nDefender );

		signed int operator () ( uhyper NewSeed, int NewMinValue, int NewMaxValue );
		signed int operator () ( int NewMinValue, int NewMaxValue);
        signed int operator () ( dice cDice ); // ici référence sur parametre enlevee

        inline signed int roll( dice cDice ){ // ici pareil
            return (*this)( cDice );
        }
        
        static uhyper GetSeed( void );
	private:
        // Prohibit assignements and copies.
        Random( Random &cRand ){};
        Random &operator = ( Random &cRand ){ return cRand; };

		static int    LastValue;
        static uhyper Seed;

		static int Randomize( int nMin, int nMax, BOOL boSameTwice = FALSE ); //__int64
};

#endif // !defined(AFX_RANDOM_H__6EB985F3_D137_11D0_B543_C09D9B000000__INCLUDED_)
