/*
 * AbstractEntity.h
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#ifndef G2E_CORE_ABSTRACTENTITY_H_
#define G2E_CORE_ABSTRACTENTITY_H_

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "../../g2e/core/AbstractComponent.h"
#include "../../g2e/util/Reflective.h"

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

	void set(std::string, bool value);
	bool value(std::string);

	/**
	 * This function is called when an entity is added to a system,
	 * make sure to call the base function for the entity's memory
	 * management system to work properly.
	 */
	void added() { addedto++; }

	/**
	 * This function is called when an entity is removed to a
	 * system, make sure to call the base function for the entity's
	 * memory management system to work properly. To prevent entities
	 * from being deleted when they have been removed from all systems,
	 * override this function.
	 */
	void removed() {
		addedto--;
		// TODO: find a better way!
		try { if (addedto <= 0) delete this/*eek undefined behavior*/; }
		catch (...) {}
	}

	int systemCount() { return addedto; }
private:
	std::map<std::string, AbstractComponent*> components;
	std::map<std::string, bool> values;

	int addedto = 0;
};

} /* namespace g2e */

#endif /* G2E_CORE_ABSTRACTENTITY_H_ */
