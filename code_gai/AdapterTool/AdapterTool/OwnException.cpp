#include "stdafx.h"
#include "OwnException.h"


OwnException::OwnException()
{
}

OwnException::OwnException(std::string StrErr)
{
	_strerr = StrErr;
	_listerr.push_back(_strerr);
}

OwnException::~OwnException()
{
}

const char * OwnException::what() const throw()
{
	return _strerr.c_str();
}
