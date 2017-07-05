// Random.h: interface for the Random class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __RANDOM_H
#define __RANDOM_H

#define MAXSHRT 65535

#include <windows.h>
#include <time.h>

class EncRandom  
{
public:
	virtual ~EncRandom();

	protected:
		unsigned int Seed;
		unsigned int MinValue;
		unsigned int MaxValue;
		unsigned int SeedID;

		virtual unsigned int EncRandomize(void);
		virtual void CreateTable(void) {};

	public:
		EncRandom(unsigned int NewMinValue = 0,
				 unsigned int NewMaxValue = MAXSHRT,
				 unsigned int InitSeed = (unsigned int)time(NULL),
				 unsigned int seedNumber = 0);

		void SetSeed(unsigned int NewSeed = 0/*(unsigned long)time(NULL)*/);
		void SetMinValue(unsigned int NewMinValue = 0);
		void SetMaxValue(unsigned int NewMaxValue = MAXSHRT);
		void SetMinMaxValue(unsigned int NewMinValue = 0,
								  unsigned int NewMaxValue = MAXSHRT);
		operator int  (void);

		unsigned int operator () (unsigned int NewSeed);
		unsigned int operator () (unsigned int NewMinValue,
										  unsigned int NewMaxValue);
		unsigned int operator () (unsigned int NewSeed,
										  unsigned int NewMinValue,
										  unsigned int NewMaxValue);
};


#endif 
