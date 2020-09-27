// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

/************************************************************************/
/*功能描述： boost exception使用实例                                    */
/*作者    ： kernel_main                                                */
/*创建时间： 2014.6.8                                                   */
/************************************************************************/
#include <iostream>
#include <exception>

#include <boost/exception/all.hpp>

struct my_exception :         /* 自定义异常类 */
	virtual std::exception,   /* 虚继承，struct默认public继承 */
	virtual boost::exception  /* 虚继承，struct默认public继承 */
{
	my_exception(const char * err)
		:std::exception(err)
	{

	}
	/* 空实现，不需要实现代码 */
};

/* 异常信息的类型 */
typedef boost::error_info<struct tag_err_no, int> err_no;
typedef boost::error_info<struct tag_err_str, std::string> err_str;

int main()
{
	using namespace boost;
	try
	{
		try
		{
			/* 抛出异常，存储错误码 */
			throw my_exception("fff") << err_no(10);
		}
		catch (my_exception& e) /* 捕获异常，使用引用形式 */
		{
			std::cout << *get_error_info<err_no>(e) << std::endl;
			std::cout << e.what() << std::endl;
			e << err_str("other info"); /* 向异常追加信息 */
			throw; /* 再次抛出异常 */
		}
	}
	catch (my_exception& e)
	{
		std::cout << *get_error_info<err_no>(e) << std::endl;
		std::cout << *get_error_info<err_str>(e) << std::endl;
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}

