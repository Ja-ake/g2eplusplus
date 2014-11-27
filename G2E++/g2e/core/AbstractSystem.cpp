/*
 * AbstractSystem.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#include "../../g2e/core/AbstractSystem.h"

#include <iostream>

namespace g2e {

AbstractSystem::AbstractSystem() {

}

AbstractSystem::~AbstractSystem() {

}

void AbstractSystem::add(AbstractEntity* ent) {
	entities.push_back(ent);
	if (!(ent->systemCount() > 0)) { ent->initialize(); }
	ent->added();
	this->initialize(ent);
}

void AbstractSystem::remove(AbstractEntity* ent) {
	for (auto i=entities.begin(); i!=entities.end(); i++) {
		if ((*i) == ent) entities.erase(i);
		ent->removed();
	}
}

void AbstractSystem::clear(std::string ent) {
    for (auto iter=entities.begin(); iter!=entities.end(); iter++) {
        if (((AbstractEntity*)*iter)->getClass() == ent) remove((AbstractEntity*)*iter);
    }
}

void AbstractSystem::clear() {
    for (auto iter=entities.begin(); iter!=entities.end(); iter++) {
        remove((AbstractEntity*)*iter);
    }
}

std::vector<AbstractEntity*>& AbstractSystem::getEntityList() {
    return entities;
}

} /* namespace g2e */
