#ifndef G2E_EVENT_EVENTSERVICE_H_
#define G2E_EVENT_EVENTSERVICE_H_

#include <vector>
#include "../../g2e/event/Event.h"
#include "../../g2e/event/EventListener.h"
#include "../../g2e/service/Service.h"

namespace g2e {
namespace event {

class EventService : public g2e::service::Service {
public:
	virtual std::string getClass() { return "EventService"; }

	EventService();
	virtual ~EventService();

	virtual void update();

	void add(g2e::event::EventListener*);
	void remove(g2e::event::EventListener*);

private:
	std::vector<g2e::event::Event*> eventQueue;
	std::vector<g2e::event::EventListener*> listeners;
};

} /* namespace event */
} /* namespace g2e */

#endif /* G2E_EVENT_EVENTSERVICE_H_ */
