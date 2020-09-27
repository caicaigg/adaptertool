#pragma once
#include <exception>
#include <string>
#include <list>

class OwnException :
	public std::exception
{
public:
	OwnException();
	OwnException(std::string StrErr);
	virtual ~OwnException();

public:
	const char* what() const throw();

private:
	std::string _strerr;
	std::list<std::string> _listerr;
};

