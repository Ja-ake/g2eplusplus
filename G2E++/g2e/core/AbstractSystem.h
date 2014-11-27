/*
 * AbstractSystem.h
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#ifndef G2E_CORE_ABSTRACTSYSTEM_H_
#define G2E_CORE_ABSTRACTSYSTEM_H_

#include <string>
#include <vector>
#include "../../g2e/core/AbstractEntity.h"
#include "../../g2e/util/Reflective.h"

namespace g2e {

class AbstractSystem : public g2e::util::Reflective {
public:
	virtual std::string getClass()=0;

	AbstractSystem();
	virtual ~AbstractSystem();

	virtual void initialize(g2e::AbstractEntity*)=0;
	virtual void initialize()=0;
	virtual void update(g2e::AbstractEntity*)=0;
	virtual void update()=0;

	void add(AbstractEntity*);
	void remove(AbstractEntity*);
	void clear(std::string);
	void clear();

	std::vector<AbstractEntity*>& getEntityList();
public:
	std::vector<AbstractEntity*> entities;
};

} /* namespace g2e */

#endif /* G2E_CORE_ABSTRACTSYSTEM_H_ */
