#include <g2e/resource/ResourceLoaderService.h>

using std::string;
using std::ifstream;

namespace g2e {
namespace io {

ResourceLoaderService::ResourceLoaderService(string folder) {
	this->resourcefolder = folder;
}

ResourceLoaderService::~ResourceLoaderService() {
}

const char* ResourceLoaderService::loadFile(string path) {
	ifstream file;

	try {
		file.open((resourcefolder + path).c_str());
		int cnt;
		while (!file.eof()) {
			file.get();
			++cnt;
		}
		file.close();
		file.open((resourcefolder + path).c_str());
		char* data = new char[cnt];
		for (int i = 0; i <= cnt; ++i) {
			if (!file.eof()) data[i] = file.get();
			else break;
		}
		//data[cnt] = '\0';
		file.close();
		return (const char*) data;
	} catch (...) {
		std::cerr << "There was an error reading file " << path << std::endl;
	}

	file.close();
	return (const char*) nullptr;
}

} /* namespace io */
} /* namespace g2e */
