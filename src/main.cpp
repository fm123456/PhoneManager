/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#include "CommandFactory.h"
#include "CheckConnectionCommand.h"

#include <windows.h>
#include <tchar.h>

#include <string>
#include <iostream>

/**定时检测设备是否连接的函数
*/
DWORD WINAPI CheckThread(LPVOID pM)
{
	RCCheckConnectionCommand* pCheckCmd = (RCCheckConnectionCommand*)RCCommandFactory::Instance()->CreateCommand(CheckConnectionCmd);
	if (!pCheckCmd)
	{
		return 1;
	}

	bool PreConnectionFlag = false;

	while (::WaitForSingleObject(RCCommandFactory::g_hExitEvent, 0) == 0)
	{
		pCheckCmd->Execute();
		bool HasConnect = pCheckCmd->HasConnected();

		if (HasConnect != PreConnectionFlag)
		{
			if (HasConnect)
			{
				std::cout << "Connect successfully !" << std::endl;
				::SetEvent(RCCommandFactory::g_hConnectEvent);
			}
			else
			{
				std::cout << "connection has been broken! waiting for connect..." << std::endl;
				::ResetEvent(RCCommandFactory::g_hConnectEvent);
			}
			PreConnectionFlag = HasConnect;
		}

		Sleep(1000);  //每隔一秒检查一次
	}

	delete pCheckCmd;
	pCheckCmd = NULL;
	
	return 0;
}

int main(int argc, char** argv)
{
	std::cout << "waiting for connect..." << std::endl;

	//创建定时检测线程
	HANDLE hCheakThread  = ::CreateThread(NULL, 0, CheckThread, NULL, 0, NULL);


	std::string FunctionStr;
	

	while (true)
	{
		//如果连接关闭则会一直等待连接
		::WaitForSingleObject(RCCommandFactory::g_hConnectEvent, INFINITE);

		std::cout << "------------------------------------------" << std::endl;
		std::cout << "        |    1、Install        |" << std::endl;
		std::cout << "        |    2、Uninstall      |" << std::endl;
		std::cout << "        |    3、Upload         |" << std::endl;
		std::cout << "        |    4、Download       |" << std::endl;
		std::cout << "        |    5、Backup         |" << std::endl;
		std::cout << "        |    6、Restore        |" << std::endl;
		std::cout << "        |    7、Exit           |" << std::endl;
		std::cout << "------------------------------------------" << std::endl;

		std::cout << "please Chose the Function:";
		std::cin >> FunctionStr;
		
		if (FunctionStr.length() != 1 || FunctionStr[0] > '7' || FunctionStr[0] < '1')
		{
			std::cout << "input value is invalid " << std::endl;
			continue;
		}

		TCommandId FunctionId = TCommandId(atoi(FunctionStr.c_str()));
		if (FunctionId == ExitCmd)
		{
			::ResetEvent(RCCommandFactory::g_hExitEvent);
			break;
		}

		RCCommand* pCmd = RCCommandFactory::Instance()->CreateCommand(FunctionId);
		if (pCmd)
		{
			pCmd->Execute();
			delete pCmd;
			pCmd = NULL;
		}
	}
	
	//等待检测线程结束
	::WaitForSingleObject(hCheakThread, INFINITE);
	::CloseHandle(hCheakThread);
	return 0;
}