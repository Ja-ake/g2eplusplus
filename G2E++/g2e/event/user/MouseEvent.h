#ifndef EVENT_USER_MOUSEEVENT_H_
#define EVENT_USER_MOUSEEVENT_H_

#include "../event.h"

namespace g2e {
namespace event {

class MouseEvent : public g2e::event::Event {
public:
	CLASSNAME(MouseEvent)

	MouseEvent() : MouseEvent(0, 0) {}
	MouseEvent(short xn, short yn) : x(xn), y(yn) {}
	virtual ~MouseEvent();

	signed short x, y;
};

} /* namespace event */
} /* namespace g2e */

#endif /* EVENT_USER_MOUSEEVENT_H_ */
