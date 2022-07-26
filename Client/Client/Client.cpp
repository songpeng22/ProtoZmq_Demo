// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UposCashDrawerZMQClient.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int ret = UposCashDrawerZMQClient::Instance()->BUCashDrawerInit();
	//UposCashDrawerZMQClient::Instance()->BUCashDrawerOpen();

	while(true)
	{
		
	}

	return 0;
}


