// testASIOServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ASIOServer.h"

int main()
{
	try
	{
		int s = sizeof(float);
		int m = sizeof(double);
		float lon = 111.123456;
		printf("%.6f,", lon);
		cout << "Server start." << endl;
		CASIOServer srv;
		srv.run();
	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
	}
	return 0;
}

