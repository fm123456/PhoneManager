/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#include "Command.h"
#include <iostream>

HANDLE hConnectEvent = NULL;
HANDLE hExitEvent    = NULL;

typedef struct
{
	HANDLE hReadPipe;
	RCCommand* cmd;
}TReadPipeData;

/** 读管道线程函数
@param[in] pData 线程函数需要的参数数据
*/
DWORD WINAPI ReadPipeThread(LPVOID pData)
{
	TReadPipeData* pThreadData = (TReadPipeData*)pData;
	std::string nOutput = pThreadData->cmd->ReadFromPipe(pThreadData->hReadPipe);
	pThreadData->cmd->SetOutput(nOutput);

	return 0;
}

RCCommand::RCCommand()
{

}

RCCommand::~RCCommand()
{

}

const std::string& RCCommand::GetOutput() const
{
	return m_nOutput;
}

void RCCommand::SetOutput(const std::string& nOutput)
{
	m_nOutput = nOutput;
}

void RCCommand::DoExecute(const std::string& nCmdLine)
{
	m_nOutput = "";
	HANDLE out_read;
	HANDLE out_write;

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	// 创建管道
	if (!::CreatePipe(&out_read, &out_write, &sa, 0))
	{
		std::cerr << ("Unable to create stdout/stderr pipe for task process") << std::endl;
		return;
	}

	STARTUPINFO si = { sizeof(si) };
	::GetStartupInfo(&si);
	si.hStdError   = out_write;
	si.hStdOutput  = out_write;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	PROCESS_INFORMATION pi;
	::ZeroMemory(&pi, sizeof(pi));

	if (!::CreateProcess(NULL,
		(LPTSTR)nCmdLine.c_str(),
		NULL,
		NULL,
		TRUE,
		NULL,
		NULL,
		NULL,
		&si,
		&pi))
	{
		std::cout << "Failed to create process for command: " << nCmdLine << std::endl;
		::CloseHandle(out_write);
		::CloseHandle(out_read);

		std::cout << ::GetLastError() << std::endl;
		return;
	}
	::CloseHandle(out_write);
	
	TReadPipeData nThreadData = { out_read ,this};
	HANDLE hReadPipeThread = ::CreateThread(NULL, 0, ReadPipeThread, &nThreadData, 0, NULL);

	unsigned long exit_code = 0;
	while (::GetExitCodeProcess(pi.hProcess, &exit_code) && STILL_ACTIVE == exit_code)
	{
		//检测当前连接的状态
		DWORD nRet = ::WaitForSingleObject(hConnectEvent, 0);
		
		//触发被关闭，连接事件中断
		if (nRet != 0)   
		{
			std::cout << "Connection has closed.Now terminate the command process" << std::endl;
			::TerminateProcess(pi.hProcess, exit_code);
			break;
		}
		Sleep(1000);
	}

	::CloseHandle(out_read);
	::WaitForSingleObject(pi.hProcess,     INFINITE);
	::WaitForSingleObject(hReadPipeThread, INFINITE);

	::CloseHandle(pi.hProcess);
}

std::string RCCommand::ReadFromPipe(HANDLE hRead)
{
	std::string content;

	const int READ_BUFFER_SIZE = 4096;
	char buffer[READ_BUFFER_SIZE] = { 0 };
	DWORD bytes = 0;

	while (::ReadFile(hRead, buffer, READ_BUFFER_SIZE, &bytes, NULL) && bytes > 0)
	{
		std::cout << buffer << std::endl;
		content.append(buffer, bytes);

		memset(buffer, 0, bytes);
	}

	return content;
}

