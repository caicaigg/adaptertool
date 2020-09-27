// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

/************************************************************************/
/*���������� boost exceptionʹ��ʵ��                                    */
/*����    �� kernel_main                                                */
/*����ʱ�䣺 2014.6.8                                                   */
/************************************************************************/
#include <iostream>
#include <exception>

#include <boost/exception/all.hpp>

struct my_exception :         /* �Զ����쳣�� */
	virtual std::exception,   /* ��̳У�structĬ��public�̳� */
	virtual boost::exception  /* ��̳У�structĬ��public�̳� */
{
	my_exception(const char * err)
		:std::exception(err)
	{

	}
	/* ��ʵ�֣�����Ҫʵ�ִ��� */
};

/* �쳣��Ϣ������ */
typedef boost::error_info<struct tag_err_no, int> err_no;
typedef boost::error_info<struct tag_err_str, std::string> err_str;

int main()
{
	using namespace boost;
	try
	{
		try
		{
			/* �׳��쳣���洢������ */
			throw my_exception("fff") << err_no(10);
		}
		catch (my_exception& e) /* �����쳣��ʹ��������ʽ */
		{
			std::cout << *get_error_info<err_no>(e) << std::endl;
			std::cout << e.what() << std::endl;
			e << err_str("other info"); /* ���쳣׷����Ϣ */
			throw; /* �ٴ��׳��쳣 */
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

