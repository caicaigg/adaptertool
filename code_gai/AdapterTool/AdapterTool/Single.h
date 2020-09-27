#pragma once

#include <boost/thread/mutex.hpp>

#define DECLARE_SINGLETON(ClassName) \
	friend SingleInstance<ClassName>; \
	private:\
		ClassName();\
		ClassName(ClassName & obj);\
		ClassName& operator=(ClassName & obj);\
	public:\
		~ClassName();

template<typename T>
class SingleInstance
{
public:
	static T* Instance()
	{
		if (GetObject() == nullptr)
		{
			_lock lock(*_mutex);
			if (GetObject() == nullptr)
			{
				GetObject() = CreateObject();
			}
		}
		return GetObject();
	}

protected:
	SingleInstance()
	{};
	~SingleInstance()
	{};

	static T* CreateObject()
	{
		T *t = new T;
		return t;
	}
	static  T* & GetObject()
	{
		static  T* t = nullptr;
		return t;
	}

private:
	typedef boost::unique_lock<boost::mutex> _lock;
	static boost::mutex *_mutex;
};
template<class T>
boost::mutex *SingleInstance<T>::_mutex = new boost::mutex();