#include "Util.h"
#include <iostream>
#include <assert.h>



Util::Util(std::string FilePath)
	:_filePath(FilePath)
	,_stream(nullptr)
{
}

Util::~Util()
{
	if (_stream 
		&& _stream->is_open())
	{
		_stream->close();
	}
}

std::ofstream& Util::Stream()
{
	if (nullptr == _stream)
	{
		_stream = new std::ofstream;
		_stream->open(_filePath.c_str(), std::ios::in | std::ios::app);
		if (!_stream->is_open())
		{
			std::cout << "打开文件失败!" << _filePath.c_str() << std::endl;
			//return nullptr;
		}
	}

	assert(_stream);
	return *_stream;
}

std::ofstream& Util::operator<<(std::string str)
{
	if (nullptr == _stream)
	{
		_stream = new std::ofstream;
		_stream->open(_filePath.c_str(), std::ios::in | std::ios::app);
		if (!_stream->is_open())
		{
			std::cout << "打开文件失败!" << _filePath.c_str() << std::endl;
			//return nullptr;
		}
	}

	assert(_stream);
	return *_stream;
}
