#include "stdafx.h"
#include "TextFilter.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TTextFilter TextFilter;

TTextFilter::TTextFilter(void)
{
	
	HashList=0;
	ItemCount=0;
	MaskChar='*';


	//arbitrary hashsize (prime)
	HashSize=1009;
	HashList=new TFilterHashItem[HashSize];

	unsigned long i,RndSeed;
	for(i=0;i<HashSize;i++)
	{
		HashList[i].Hash=0;
		HashList[i].Next=0;
	}

	
	
	RndSeed=0xd2a9f7bd;
	for (i=0;i<256;i++)
	{
		RndSeed=RndSeed*0x08088405+1;
		RndTable[i]=RndSeed;
	}
};

TTextFilter::~TTextFilter(void)
{
	///todo need a recursive destroy;
	/*

	for (unsigned long i=0;i<HashSize;i++)
	{
		PFilterHashItem CurrentItem=&HashList[i];
		while (CurrentItem!=0)
		{
			CurrentItem=CurrentItem->Next;
		}
	}*/

	if (HashList!=0)
		delete [] HashList;
};

unsigned long TTextFilter::ComputeHash(const char* Txt)
{

	unsigned long i,Result;
	const char* p;

	p=Txt;
	
	unsigned int Size=strlen(Txt);
	Result=0xFFFFFFFF;

	for (i=0;i<Size;i++)
	{
		Result=((Result << 5)+Result)^RndTable[(unsigned char)*p];
		p++;
	}
	return Result;
}


void TTextFilter::AddEntry(const unsigned long HashCode)
{
	PFilterHashItem Last=0,ActEntry;

	const unsigned long Num=HashCode%HashSize;
	
	ActEntry=&HashList[Num];
	while(1)
	{
		if (!ActEntry) 
		{
			ActEntry=new TFilterHashItem;
			ActEntry->Next=0;
			ActEntry->Hash=0;
			if (Last)
				Last->Next=ActEntry;
		}
		if (!ActEntry->Hash)
		{
			ActEntry->Hash=HashCode; 
			ItemCount++;
			return ;
		}else
		{
			if (ActEntry->Hash==HashCode)  //collision 
				return ;
			Last=ActEntry;
			ActEntry=ActEntry->Next;
		}
	}
};

void* TTextFilter::GetItem(const unsigned long Hashcode)
{
	PFilterHashItem ActEntry=0;

	const unsigned long Num=Hashcode%HashSize;

	ActEntry=&HashList[Num];

	while (1)
	{
		if (!ActEntry) 
			return 0;
		if (ActEntry->Hash==Hashcode) 
			return ActEntry;
		ActEntry=ActEntry->Next;
	}
};


void TTextFilter::Initialize(const char *FilterFileName)
{
	FILE* File;
	File=fopen(FilterFileName,"rb");
	if (File)
	{
		char NewWord[128];

		while(fscanf(File,"%s\r\n",NewWord)!=-1)
		{
			AddEntry(ComputeHash(NewWord));
		}

		fclose(File);
	}

};

void TTextFilter::FilterMessage(char* Message)
{
	char Temp[512];

	if (Message==NULL)
		return;

	const unsigned long Size=strlen(Message);
	if (Size==0) 
		return;

	char* IdxStart=Message;
	char* IdxEnd=0;

	while(1)
	{
		//skip whitespace
		while(*IdxStart==' ')
		{
			IdxStart++;
		};

		IdxEnd=IdxStart;

		while((*IdxEnd!=' ') && (*IdxEnd!=0))
		{
			IdxEnd++;
		}

		unsigned long WordSize=IdxEnd-IdxStart;
		memcpy(Temp,IdxStart,WordSize);
		Temp[WordSize]=0;

		for(unsigned int i=0;i<WordSize;i++)
			Temp[i]=tolower(Temp[i]);

		if (GetItem(ComputeHash(Temp))!=0) //we got a hit
		{
			for(unsigned int i=0;i<WordSize;i++)
				IdxStart[i]=MaskChar;
		}

		IdxStart=IdxEnd;

		if ((IdxEnd-Message)>=Size)
			break;
	}

};