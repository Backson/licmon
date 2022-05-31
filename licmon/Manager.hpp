#ifndef MANAGER_HPP_
#define MANAGER_HPP_

#include <string>
#include <map>

#include "Result.hpp"

namespace licmon {

class Manager {
public:
	Manager() = default;

	// copy
	Manager(const Manager &) = delete;
	Manager &operator = (const Manager &) = delete;

	// move
	Manager(Manager &&) = delete;
	Manager &operator = (Manager &&) = delete;

	Result Add(std::string name, int number = 1);
	Result Remove(std::string name, int number = 1);
	Result Allocate(std::string name, int number = 1);
	Result Free(std::string name, int number = 1);

	int Available(std::string name);

private:
	// persistent state of a single license
	typedef struct {
		// how many exist of this license
		int total;
		// how many of these are already in use
		int committed;
	} entry_t;
	// state of all licenses
	std::map<std::string, entry_t> mMap;
};

} // namespace licmon

#endif // MANAGER_HPP_
