/*
 * AbstractEntity.h
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#ifndef CORE_ABSTRACTENTITY_H_
#define CORE_ABSTRACTENTITY_H_

#include "util/reflective.h"
#include "core/abstractcomponent.h"

#include <string>
#include <vector>
#include <map>

namespace g2e {

class AbstractEntity : public g2e::util::Reflective {
public:
	virtual std::string getClass()=0;

	AbstractEntity();
	virtual ~AbstractEntity();

	virtual void initialize()=0;

	void add(AbstractComponent*);
	void remove(AbstractComponent*);
	void remove(std::string);
	void clear();
	AbstractComponent* take(std::string);
	AbstractComponent* get(std::string);
private:
	std::map<std::string, AbstractComponent*> components;
};

} /* namespace g2e */

#endif /* CORE_ABSTRACTENTITY_H_ */
