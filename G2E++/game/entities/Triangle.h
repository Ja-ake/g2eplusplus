#ifndef ENTITIES_TRIANGLE_H_
#define ENTITIES_TRIANGLE_H_

#include <g2e/core/abstractentity.h>

class Triangle : public g2e::AbstractEntity {
public:
	Triangle();
	virtual ~Triangle();
	virtual std::string getClass() { return "Triangle"; }

	virtual void initialize();
};

#endif /* ENTITIES_TRIANGLE_H_ */
