#ifndef RESOURCE_RESOURCELOADERSERVICE_H_
#define RESOURCE_RESOURCELOADERSERVICE_H_

#include <g2e/service/service.h>
#include <iostream>
#include <fstream>
#include <string>

namespace g2e {
namespace io {

class ResourceLoaderService : public g2e::service::Service {
public:
	ResourceLoaderService() : ResourceLoaderService("") {}
	ResourceLoaderService(std::string);
	virtual ~ResourceLoaderService();
	virtual std::string getClass() { return "ResourceLoaderService"; }

	const char* loadFile(std::string);

private:
	std::string resourcefolder;
};

} /* namespace io */
} /* namespace g2e */

#endif /* RESOURCE_RESOURCELOADERSERVICE_H_ */
