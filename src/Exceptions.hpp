#ifndef SNN_EXCEPTIONS
#define SNN_EXCEPTIONS

#include <exception>

/**
 *
 */
class LoadFileException
	: public std::runtime_error
{
public:
	LoadFileException(const std::string& message)
		: runtime_error(message)
	{}
};

#endif // SNN_EXCEPTIONS