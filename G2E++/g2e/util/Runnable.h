/*
 * Runnable.h
 *
 *  Created on: Nov 18, 2014
 *      Author: Jake
 */

#ifndef RUNNABLE_H_
#define RUNNABLE_H_

namespace g2e {

class Runnable {
public:
	Runnable();
	virtual ~Runnable();
	virtual void run() = 0;
};

} /* namespace g2e */

#endif /* RUNNABLE_H_ */
