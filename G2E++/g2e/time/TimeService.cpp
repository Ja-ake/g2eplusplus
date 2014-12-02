#include <time/TimeService.h>

#include <windows.h>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;

namespace g2e {
namespace time {

TimeService::TimeService() {
	interval = 0.001f;

	LARGE_INTEGER start;
	if (::QueryPerformanceCounter(&start) == FALSE)
	    throw std::runtime_error("Could not grab clock counter");

	current = previous = static_cast<double>(start.QuadPart);
}

TimeService::~TimeService() {
}

void TimeService::update() {
	LARGE_INTEGER frequency;
	if (::QueryPerformanceFrequency(&frequency) == FALSE)
	    throw std::runtime_error("Could not grab clock frequency");

	LARGE_INTEGER start;
	if (::QueryPerformanceCounter(&start) == FALSE)
	    throw std::runtime_error("Could not grab clock counter");

	current = static_cast<double>(start.QuadPart);
	interval = (current - previous) / static_cast<double>(frequency.QuadPart);
	previous = current;

//	cout << interval << endl;
}

} /* namespace time */
} /* namespace g2e */
