/*
 * CCTimer.h
 *
 *  Created on: 2021��5��13��
 *      Author: dongyuqing
 */

#ifndef CCTIMER_H_
#define CCTIMER_H_

#ifndef DLLAPI
#define DLLAPI                  __declspec(dllexport)
#endif

extern "C" class DLLAPI CCTimer {
public:
	CCTimer();
	~CCTimer();
public:
	/* Wait for time(ms)*/
	void Wait(double tms);
	double RdSysTime();
};


#endif /* CCTIMER_H_ */
