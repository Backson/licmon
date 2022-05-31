#ifndef RESULT_HPP_
#define RESULT_HPP_

namespace licmon {

enum class ResultCode {
	Success,
	UnknownError,
	InvalidArgument,
	ArgumentMustBePositive,
	UnknownLicenseName,
	NotEnoughLicenses,
};

// strongly typed enum
struct Result {
	ResultCode code;
	Result(ResultCode code) : code(code) { }
	bool Good() const { return code == ResultCode::Success; }
	operator bool() const { return code == ResultCode::Success; }
	const char *GetDescription() const;
};

} // namespace licmon

#endif // RESULT_HPP_
