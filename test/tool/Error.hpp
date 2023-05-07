#ifndef ERROR_HPP
# define ERROR_HPP

#include <string>

class Error
{
private:
	/* data */
	std::string _message;

public:
	Error();
	Error(std::string errormessege);
	~Error() throw();

	virtual const char* what() const throw();
};

#endif
