#ifndef EVENT_USER_KEYBOARDEVENT_H_
#define EVENT_USER_KEYBOARDEVENT_H_

#include "../event.h"

namespace g2e {
namespace event {

class KeyboardEvent : public g2e::event::Event {
public:
	CLASSNAME(KeyboardEvent)

	KeyboardEvent() : KeyboardEvent(0, false) {}
	KeyboardEvent(unsigned int k, bool p) : key(k), pressed(p) {}
	virtual ~KeyboardEvent();

	unsigned int key;
	bool pressed;
};

} /* namespace event */
} /* namespace g2e */

#endif /* EVENT_USER_KEYBOARDEVENT_H_ */
