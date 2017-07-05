#ifndef TEXTFILTER_H
#define TEXTFILTER_H

struct TFilterHashItem
{
	unsigned long Hash;
	TFilterHashItem* Next;
};
typedef TFilterHashItem* PFilterHashItem;

class TTextFilter
{
private:
	unsigned long HashSize;
	unsigned long ItemCount;
	PFilterHashItem HashList;
	char MaskChar;
	unsigned long RndTable[256];

	unsigned long ComputeHash(const char* Txt);
	void AddEntry(const unsigned long HashCode);
	void* GetItem(const unsigned long Hashcode);
public:
	TTextFilter(void);
	~TTextFilter(void);
	void Initialize(const char* FilterFileName);
	inline void SetMaskCharacter(const char c){MaskChar=c;};
	void FilterMessage(char* Message);
};

extern TTextFilter TextFilter;

#endif