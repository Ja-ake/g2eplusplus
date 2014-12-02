#ifndef G2E_EVENT_EVENTLISTENER_H_
#define G2E_EVENT_EVENTLISTENER_H_

#include <g2e/event/event.h>

namespace g2e {
namespace event {

class EventListener {
public:
	EventListener();
	virtual ~EventListener();

	virtual void onEvent(g2e::event::Event*)=0;
};

} /* namespace event */
} /* namespace g2e */

#endif /* G2E_EVENT_EVENTLISTENER_H_ */
