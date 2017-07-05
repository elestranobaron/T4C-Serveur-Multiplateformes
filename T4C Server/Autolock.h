#ifndef __AUTOLOCK_H
#define __AUTOLOCH_H
#include <pthread.h>
#if defined(_MSC_VER)
class Autolock {
	public:
		Autolock(CRITICAL_SECTION *);
		~Autolock(void);
	private:
		CRITICAL_SECTION *m_cs;
};
#elif defined(__GNUC__)
class Autolock {
	public:
		Autolock(pthread_mutex_t );
		~Autolock(void);
	private:
		pthread_mutex_t m_cp;
};
#else
#endif

#endif
