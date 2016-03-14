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
	RCCheckConnectionCommand* nCheckCmd = (RCCheckConnectionCommand*)RCCommandFactory::Instance()->CreateCommand(CheckConnectionCmd);
	bool nConnectionFlag = false;

	while (::WaitForSingleObject(hExitEvent, 0) == 0)
	{
		nCheckCmd->Execute();
		bool nTemp = nCheckCmd->HasConnected();

		if (nTemp != nConnectionFlag)
		{
			if (nTemp)
			{
				std::cout << "Connect successfully !" << std::endl;
				::SetEvent(hConnectEvent);
			}
			else
			{
				std::cout << "connection has been broken! waiting for connect..." << std::endl;
				::ResetEvent(hConnectEvent);
			}
			nConnectionFlag = nTemp;
		}

		Sleep(1000);  //每隔一秒检查一次
	}

	delete nCheckCmd;
	nCheckCmd = NULL;
	
	return 0;
}

int main(int argc, char** argv)
{
	std::cout << "waiting for connect..." << std::endl;

	//创建是否连接事件
	hConnectEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	::WaitForSingleObject(hConnectEvent, INFINITE);
	//创建是否退出事件
	hExitEvent = ::CreateEvent(NULL, TRUE, TRUE, NULL);

	//创建定时检测线程
	HANDLE hCheakThread  = ::CreateThread(NULL, 0, CheckThread, NULL, 0, NULL);


	std::string nFunction;
	

	while (true)
	{
		//如果连接关闭则会一直等待连接
		::WaitForSingleObject(hConnectEvent, INFINITE);

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
		std::cin >> nFunction;
		
		if (nFunction.length() != 1 || nFunction[0] > '7' || nFunction[0] < '1')
		{
			std::cout << "input value is invalid " << std::endl;
			continue;
		}

		TCommandId nFunctionId = TCommandId(atoi(nFunction.c_str()));
		if (nFunctionId == ExitCmd)
		{
			::ResetEvent(hExitEvent);
			break;
		}

		RCCommand* cmd = RCCommandFactory::Instance()->CreateCommand(nFunctionId);
		if (cmd)
		{
			cmd->Execute();
			delete cmd;
			cmd = NULL;
		}
	}
	
	//等待检测线程结束
	::WaitForSingleObject(hCheakThread, INFINITE);

	::CloseHandle(hConnectEvent); 
	::CloseHandle(hExitEvent);
	::CloseHandle(hCheakThread);
	return 0;
}