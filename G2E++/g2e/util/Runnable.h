/*
 * Runnable.h
 *
 *  Created on: Nov 18, 2014
 *      Author: Jake
 */

#ifndef RUNNABLE_H_
#define RUNNABLE_H_

namespace g2e {
namespace util {

class Runnable {
public:
	Runnable();
	virtual ~Runnable();
	virtual void run() = 0;
};

} /* namespace util */
} /* namespace g2e */

#endif /* RUNNABLE_H_ */
