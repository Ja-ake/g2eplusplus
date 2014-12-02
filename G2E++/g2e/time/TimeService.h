#ifndef TIME_TIMESERVICE_H_
#define TIME_TIMESERVICE_H_

#include <g2e/service/service.h>

namespace g2e {
namespace time {

class TimeService : public g2e::service::Service {
public:
	CLASSNAME(TimeService)

	TimeService();
	virtual ~TimeService();

	virtual void update();

	double getInterval() { return interval; }
	double getCurrent() { return current; }
private:
	double interval;
	double current, previous;
};

} /* namespace time */
} /* namespace g2e */

#endif /* TIME_TIMESERVICE_H_ */
