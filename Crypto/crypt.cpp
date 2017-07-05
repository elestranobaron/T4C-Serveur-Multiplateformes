/******************************************************************************
Rewrite for vs2008 by Mestoph (23/04/2009)
******************************************************************************/
#include "Crypt.h"

#define HEADER_SIZE						2
#define MAX_PASS						1
#define PASS_BREAK						50
#define MIN_PASS						1
#define TYPE_MASK						0x0004

/******************************************************************************/
int TFCCrypt::DecryptS(unsigned char *&pBuffer, int &pBufferSize, unsigned int dwKey)
/******************************************************************************/
{
	if (pBufferSize < HEADER_SIZE + 1) 
	{
		return 0; ///Packet dont have Data
	}
	
	// first valid checksum...
	unsigned char cbChkSum = 0;
	int i;
	for(i=0;i<HEADER_SIZE;i++) 
	{
		cbChkSum += pBuffer[i];
		pBuffer[i] ^= XorKey1[i / /*%*/ 0x200];
	}

	unsigned short wVal;
	memcpy(&wVal,pBuffer,2);

	int dwOffset = 0;
	if(wVal & TYPE_MASK) 
	{
		dwOffset = 4;
	}

	for(i = HEADER_SIZE; i < pBufferSize - dwOffset; i++)
	{
		cbChkSum += pBuffer[i];
		pBuffer[i] ^= XorKey2[i / /*%*/ 0x200];
	}

   if(cbChkSum) 
   {
	   return -1; // invalid checksum
   }

   // En fonction de l'id on ajoute le cryptage 1.50
   if(wVal & TYPE_MASK)
   {
	   // need tu uncrypt data.... again
	   unsigned char crypt1 = pBuffer[pBufferSize - 4];
	   unsigned char crypt2 = pBuffer[pBufferSize - 3];
	   unsigned char crypt3 = pBuffer[pBufferSize - 2];
	   unsigned char crypt4 = pBuffer[pBufferSize - 1];
	   unsigned long seedNumber = 0 ^ (crypt3) ^ (crypt2 << 8) ^ (crypt4 << 16) ^ (crypt1 << 24);
	   unsigned char *pBuf = pBuffer + 2;
	   int dwlenght = pBufferSize - 3 - 4;
	   if(!TFCCrypt::DecryptS2(pBuf,dwlenght,seedNumber))
	   {
		   return -1;
	   }
	   pBufferSize -= 4; // remove seed data...
   }
   return 0;
}
/******************************************************************************/
int TFCCrypt::EncryptS(unsigned char *&pBuffer, int &pBufferSize, unsigned int dwKey)
/******************************************************************************/
{
	if (pBufferSize < HEADER_SIZE + 1) 
	{
		return 0; ///Packet dont have Data
	}

	//first calculate checksum...
	unsigned char cbChkSum = 0;
	for(int i = 0; i < pBufferSize - 1; i++)
	{
		pBuffer[i] ^= XorKey1[i / /*%*/ 0x200];
		cbChkSum += pBuffer[i];
	}
	pBuffer[pBufferSize - 1] = 256 - cbChkSum;

	return 0;
}
/******************************************************************************/
unsigned long TFCCrypt::DecryptS2(unsigned char *&pBuffer, int &pBufferSize,unsigned int dwKey)
/******************************************************************************/
{
	if (pBufferSize < 1) 
	{
		return false; // if data dont have at least 1 character, give up.
	}
	
	unsigned char *vBuffer = pBuffer;

	unsigned char crypt1 = (unsigned char)((dwKey >> 24) & 0x0FF);
	unsigned char crypt2 = (unsigned char)((dwKey >> 8 ) & 0x0FF);
	unsigned char crypt3 = (unsigned char)((dwKey      ) & 0x0FF);
	unsigned char crypt4 = (unsigned char)((dwKey >> 16) & 0x0FF);
	unsigned long seedNumber = 0 ^ (crypt3) ^ (crypt2 << 8) ^ (crypt4 << 16) ^ (crypt1 << 24);

	// seedNumber CANT be 0.
	// If someone tries to decrypt using this seed, just pick a random one and give a wrong result.
	if (seedNumber == 0) 
	{
		seedNumber = GetTickCount();
	}
	srand( seedNumber );

	int len = pBufferSize;
	unsigned long key = 0;
	unsigned char keytool[4];
	int reali = 0;
	int i = 0;
	int j = 0;
	unsigned char seed[10];
	unsigned char multiplier[10];
	int nbPasses = MAX_PASS  - ( len / PASS_BREAK );
	if( nbPasses < MIN_PASS ) 
	{
		nbPasses = MIN_PASS;
	}
	int *seedstore = 0;
	int *istore;
	int *jstore;
	seedstore = (int*)malloc( (len * nbPasses ) * sizeof( int ));
	istore = (int*)malloc( (len * nbPasses ) * sizeof( int ));
	jstore = (int*)malloc( (len * nbPasses ) * sizeof( int ));
	
	for(i = 0; i < 10; i++ )
	{
		seed[i] = rand();
		multiplier[i] = rand();
	}
	
	for(i = 0; i < len * nbPasses; i++)
	{
		seedstore[i] = (seed[rand() % 10] * multiplier[ rand() %10]) + rand();
	}

	for(i = 0; i < len * nbPasses; i++ )
	{
		reali = ( i % len );
		jstore[i] = ( rand() % len );
		if( jstore[i] == reali )
		{
			if( reali == 0)
			{
				jstore[i] = 1;
			}
			else
			{
				jstore[i] = 0;
			}
		}
		istore[i] = rand() % 21;
	}

	unsigned char byteswap1, byteswap2, byteswap3, byteswap4, inchar1, inchar2;
	for( i = (len * nbPasses ) - 1; i >= 0; i-- )
	{
		reali = ( i % len );
		j = jstore[i];
		inchar1 = vBuffer[reali];
		inchar2 = vBuffer[j];		
		switch( istore[i] )
		{
			case 0:
			{				
				byteswap1 = inchar1 & 0xF0;
				byteswap2 = inchar1 & 0x0F;
				byteswap3 = inchar2 & 0xF0;
				byteswap4 = inchar2 & 0x0F;
				vBuffer[reali] = byteswap1 | byteswap4;
				vBuffer[j] = byteswap2 | byteswap3;
				break;
			}
			case 1:
			{
				byteswap1 = inchar1 & 0xF0;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = (inchar2 & 0xF0) >> 4;											
				byteswap4 = inchar2 & 0x0F;					
				vBuffer[reali] = byteswap1 | byteswap4;
				vBuffer[j] = byteswap2 | byteswap3;
				break;
			}
			case 2:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = (inchar2 & 0xF0) >> 4;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap1 | byteswap2;
				vBuffer[j] = byteswap3 | byteswap4;
				break;
			}
			case 3:
			{
				byteswap1 = inchar1 & 0xF0;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = (inchar2 & 0xF0) >> 4;
				byteswap4 = inchar2 & 0x0F;
				vBuffer[reali] = byteswap2 | byteswap3;
				vBuffer[j] = byteswap1 | byteswap4;
				break;
			}
			case 4:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = inchar2 & 0xF0;
				byteswap4 = inchar2 & 0x0F;
				vBuffer[reali] = byteswap2 | byteswap4;
				vBuffer[j] = byteswap3 | byteswap1;
				break;
			}
			case 5:
			{				
				byteswap1 = inchar1 & 0xF0;
				byteswap2 = inchar1 & 0x0F;
				byteswap3 = (inchar2 & 0xF0) >> 4;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap1 | byteswap3;
				vBuffer[j] = byteswap2 | byteswap4;
				break;
			}
			case 6:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = (inchar2 & 0xF0) >> 4;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap2 | byteswap3;
				vBuffer[j] = byteswap1 | byteswap4;
				break;
			}
			case 7:
			{
				byteswap1 = inchar1 & 0xF0;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = (inchar2 & 0xF0) >> 4;
				byteswap4 = inchar2 & 0x0F;				
				vBuffer[reali] = byteswap1 | byteswap3;
				vBuffer[j] = byteswap2 | byteswap4;
				break;
			}
			case 8:
			{
				byteswap1 = inchar1 & 0xF0;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = (inchar2 & 0xF0) >> 4;
				byteswap4 = inchar2 & 0x0F;
				vBuffer[reali] = byteswap2 | byteswap4;
				vBuffer[j] = byteswap1 | byteswap3;
				break;
			}
			case 9:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = inchar2 & 0xF0;
				byteswap4 = inchar2 & 0x0F;
				vBuffer[reali] = byteswap1 | byteswap3;
				vBuffer[j] = byteswap2 | byteswap4;
				break;
			}
			case 10:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = inchar1 & 0x0F;
				byteswap3 = inchar2 & 0xF0;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap4 | byteswap2;
				vBuffer[j] = byteswap3 | byteswap1;
				break;
			}
			case 11:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = inchar1 & 0x0F;
				byteswap3 = inchar2 & 0xF0;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap1 | byteswap4;
				vBuffer[j] = byteswap3 | byteswap2;
				break;
			}
			case 12:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = (inchar2 & 0xF0) >> 4;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap4 | byteswap3;
				vBuffer[j] = byteswap2 | byteswap1;
				break;
			}
			case 13:
			{
				byteswap1 = inchar1 & 0xF0;
				byteswap2 = inchar1 & 0x0F;
				byteswap3 = inchar2 & 0xF0;
				byteswap4 = inchar2 & 0x0F;
				vBuffer[reali] = byteswap3 | byteswap4;
				vBuffer[j] = byteswap1 | byteswap2;
				break;
			}
			case 14:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = inchar1 & 0x0F;
				byteswap3 = inchar2 & 0xF0;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap1 | byteswap3;
				vBuffer[j] = byteswap2 | byteswap4;
				break;
			}
			case 15:
			{
				byteswap1 = inchar1 & 0xF0;
				byteswap2 = inchar1 & 0x0F;
				byteswap3 = inchar2 & 0xF0;
				byteswap4 = inchar2 & 0x0F;
				vBuffer[reali] = byteswap3 | byteswap2;
				vBuffer[j] = byteswap1 | byteswap4;
				break;
			}
			case 16:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = inchar2 & 0xF0 >> 4;
				byteswap4 = inchar2 & 0x0F << 4;
				vBuffer[reali] = byteswap4 | byteswap3;
				vBuffer[j] = byteswap1 | byteswap2;
				break;
			}
			case 17:
			{
				byteswap1 = inchar1 & 0xF0;
				byteswap2 = inchar1 & 0x0F;
				byteswap3 = (inchar2 & 0xF0) >> 4;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap4 | byteswap2;
				vBuffer[j] = byteswap3 | byteswap1;
				break;
			}
			case 18:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = (inchar1 & 0x0F) << 4;
				byteswap3 = (inchar2 & 0xF0) >> 4;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap1 | byteswap4;
				vBuffer[j] = byteswap2 | byteswap3;
				break;
			}
			case 19:
			{
				byteswap1 = inchar1 & 0xF0;
				byteswap2 = inchar1 & 0x0F;
				byteswap3 = (inchar2 & 0xF0) >> 4;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap3 | byteswap4;
				vBuffer[j] = byteswap2 | byteswap1;
				break;
			}
			case 20:
			{
				byteswap1 = (inchar1 & 0xF0) >> 4;
				byteswap2 = inchar1 & 0x0F;
				byteswap3 = inchar2 & 0xF0;
				byteswap4 = (inchar2 & 0x0F) << 4;
				vBuffer[reali] = byteswap3 | byteswap2;
				vBuffer[j] = byteswap1 | byteswap4;
				break;
			}
		}
	}

	for( i= (len * nbPasses) - 1; i >= 0; i--)
	{
		reali = ( i % len );
		key = seedstore[i];
		memcpy( keytool, &key, 4 );				
		if( reali <= len - 4)
		{
			vBuffer[reali] ^= keytool[0];			
			vBuffer[reali + 1] ^= keytool[1];				
			vBuffer[reali + 2] ^= keytool[2];				
			vBuffer[reali + 3] ^= keytool[3];				
		}
		else if( reali == len - 3)
		{
			vBuffer[reali] ^= keytool[0];			
			vBuffer[reali + 1] ^= keytool[1];				
			vBuffer[reali + 2] ^= keytool[2];					
		}
		else if( reali == len - 2)
		{
			vBuffer[reali] ^= keytool[0];			
			vBuffer[reali + 1] ^= keytool[1];				
		}
		else if( reali == len - 1)
			vBuffer[reali] ^= keytool[0];			
	}

	free( seedstore );
	free( istore);
	free( jstore);
	
	return true;
}
