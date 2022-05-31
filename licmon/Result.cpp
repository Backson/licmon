#include "Result.hpp"

namespace licmon {

const char *Result::GetDescription() const {
	switch (code) {
	case ResultCode::Success:
		return "Success";
	case ResultCode::UnknownError:
		return "Unknown error";
	case ResultCode::InvalidArgument:
		return "Invalid argument";
	case ResultCode::ArgumentMustBePositive:
		return "Argument must be positive";
	case ResultCode::UnknownLicenseName:
		return "Unknown license name";
	case ResultCode::NotEnoughLicenses:
		return "No enough licenses";
	}

	return "UnknownError";
}

} // namespace licmon
