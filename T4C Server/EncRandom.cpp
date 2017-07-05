// Random.cpp: implementation of the Random class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EncRandom.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EncRandom::~EncRandom()
{

}

EncRandom::EncRandom(unsigned int NewMinValue, unsigned int NewMaxValue,
					unsigned int InitSeed, unsigned int seedNumber) {
// Constructor
	MinValue = NewMinValue;
	MaxValue = NewMaxValue + 1;
	Seed = InitSeed;
	SeedID = seedNumber;

	CreateTable();
}

void EncRandom::SetSeed(unsigned int NewSeed) {
// Change the Seed Value.
	Seed = NewSeed;

	CreateTable();
}

void EncRandom::SetMinValue(unsigned int NewMinValue) {
// Change the Minimum Value;
	MinValue = NewMinValue;

	CreateTable();
}

void EncRandom::SetMaxValue(unsigned int NewMaxValue) {
// Change the Maximum Value;
	MaxValue = NewMaxValue + 1;

	CreateTable();
}

void EncRandom::SetMinMaxValue(unsigned int NewMinValue,
									 unsigned int NewMaxValue) {
// Change the Minimum and Maximum Value;
	MinValue = NewMinValue;
	MaxValue = NewMaxValue + 1;

	CreateTable();
}

EncRandom::operator int (void) {
// Return the EncRandom Number.
	return EncRandomize();
}

inline unsigned int EncRandom::EncRandomize(void) {
// Generate a EncRandom Number
	switch (SeedID) {
	case 0:
		Seed = Seed * 8203597 + 5 * 3;
		break;
	case 1:
		Seed = Seed * 7563921 + 1;
		break;
	}

   if (MaxValue==MinValue) 
      return MinValue;
   
   return (Seed % (MaxValue-MinValue)) + MinValue;
}

unsigned int EncRandom::operator () (unsigned int NewSeed) {
	// Return the EncRandom Number using a New Seed.
	Seed = NewSeed;

	return EncRandomize();
}

unsigned int EncRandom::operator () (unsigned int NewMinValue,
														 unsigned int NewMaxValue) {
// Return the EncRandom Number using a New Minimun and Maximum Value.
	MinValue = NewMinValue;
	MaxValue = NewMaxValue + 1;

	CreateTable();
	return EncRandomize();
}

unsigned int EncRandom::operator () (unsigned int NewSeed,
											 unsigned int NewMinValue,
											 unsigned int NewMaxValue) {
// Return the EncRandom Number using a New Seed, New Minimun and Maximum Value.
	Seed = NewSeed;
	MinValue = NewMinValue;
	MaxValue = NewMaxValue + 1;

	CreateTable();
	return EncRandomize();
}