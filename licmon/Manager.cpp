#include "Manager.hpp"

namespace licmon {

Result Manager::Add(std::string name, int number) {
	if (number <= 0)
		return ResultCode::ArgumentMustBePositive;

	mMap[name].total += number;
	return ResultCode::Success;
}

Result Manager::Remove(std::string name, int number) {
	if (number <= 0)
		return ResultCode::ArgumentMustBePositive;

	auto iter = mMap.find(name);
	if (iter == mMap.end())
		return ResultCode::UnknownLicenseName;

	auto &entry = iter->second;

	if (entry.total < number) {
		return ResultCode::NotEnoughLicenses;
	}

	if (entry.total == number) {
		mMap.erase(iter);
	}
	else /* if (entry.total > number) */ {
		entry.total -= number;
	}

	return ResultCode::Success;
}

Result Manager::Allocate(std::string name, int number) {
	if (number <= 0)
		return ResultCode::ArgumentMustBePositive;

	auto iter = mMap.find(name);
	if (iter == mMap.end())
		return ResultCode::UnknownLicenseName;

	auto &entry = iter->second;

	if (entry.committed + number > entry.total) {
		return ResultCode::NotEnoughLicenses;
	}

	entry.committed += number;
	return ResultCode::Success;
}

Result Manager::Free(std::string name, int number) {
	if (number <= 0)
		return ResultCode::ArgumentMustBePositive;

	auto iter = mMap.find(name);
	if (iter == mMap.end())
		return ResultCode::UnknownLicenseName;

	auto &entry = iter->second;

	if (entry.committed < number) {
		return ResultCode::NotEnoughLicenses;
	}

	entry.committed -= number;
	return ResultCode::Success;
}

int Manager::Available(std::string name) {
	auto iter = mMap.find(name);
	if (iter == mMap.end())
		return 0;

	auto &entry = iter->second;
	return entry.total - entry.committed;
}


} // namespace licmon
