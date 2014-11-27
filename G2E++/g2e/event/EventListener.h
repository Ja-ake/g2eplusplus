#ifndef G2E_EVENT_EVENTLISTENER_H_
#define G2E_EVENT_EVENTLISTENER_H_

namespace g2e {
namespace event {

class EventListener {
public:
	EventListener();
	virtual ~EventListener();

	virtual void onEvent()=0;
};

} /* namespace event */
} /* namespace g2e */

#endif /* G2E_EVENT_EVENTLISTENER_H_ */
