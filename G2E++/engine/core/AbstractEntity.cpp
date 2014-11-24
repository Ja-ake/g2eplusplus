/*
 * AbstractEntity.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#include <core/AbstractEntity.h>

namespace g2e {

AbstractEntity::AbstractEntity() {

}

AbstractEntity::~AbstractEntity() {
	clear();
}

void AbstractEntity::add(AbstractComponent* ncpt) {
	if (components.find(ncpt->getClass()) != components.end()) {
		components[ncpt->getClass()] = ncpt;
	}
}

void AbstractEntity::remove(AbstractComponent* cpt) {
	delete components[cpt->getClass()];
}

void AbstractEntity::remove(std::string cpt) {
	delete components[cpt];
}

void AbstractEntity::clear() {
	for (auto iter=components.begin(); iter!=components.end(); iter++) {
		remove((*iter).second);
	}
	components.clear();
}

AbstractComponent* AbstractEntity::take(std::string cptname) {
	AbstractComponent* removed = components[cptname];
	components.erase(cptname);
	return removed;
}

AbstractComponent* AbstractEntity::get(std::string cptname) {
	return components[cptname];
}

} /* namespace g2e */
