/*
 * AbstractSystem.h
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#ifndef CORE_ABSTRACTSYSTEM_H_
#define CORE_ABSTRACTSYSTEM_H_

#include "util/reflective.h"
#include "core/abstractentity.h"

#include <string>
#include <vector>

namespace g2e {

class AbstractSystem : public g2e::util::Reflective {
public:
	virtual std::string getClass()=0;

	AbstractSystem();
	virtual ~AbstractSystem();

	virtual void initialize()=0;
	virtual void execute(g2e::AbstractEntity*)=0;
	virtual void update()=0;

	void add(AbstractEntity*...);
	void remove(AbstractEntity*...);
	void clear(std::string...);
	void clear();

	std::vector<AbstractEntity*> getEntityList(std::string);
	std::vector<AbstractEntity*> getEntityList();
public:
	std::vector<AbstractEntity*> entities;
};

} /* namespace g2e */

#endif /* CORE_ABSTRACTSYSTEM_H_ */
