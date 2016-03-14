/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#include "Command.h"
#include "CommandFactory.h"

#include <iostream>

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
	::WaitForSingleObject(m_hOutputEvent, INFINITE);
	m_hOutputEvent = ::CreateEvent(NULL, FALSE, TRUE, NULL);
}

RCCommand::~RCCommand()
{
	::CloseHandle(m_hOutputEvent);
}

void RCCommand::GetOutput(std::string& Output) const
{
	::WaitForSingleObject(m_hOutputEvent, INFINITE);

	Output = m_Output;

	::SetEvent(m_hOutputEvent);
}

void RCCommand::SetOutput(const std::string& Output)
{
	::WaitForSingleObject(m_hOutputEvent, INFINITE);

	m_Output = Output;

	::SetEvent(m_hOutputEvent);
}

void RCCommand::Execute()
{
	Init();
	DoExecute(m_CmdLine);
}

void RCCommand::DoExecute(const std::string& CmdLine)
{
	m_Output = "";
	HANDLE hOutRead;
	HANDLE hOutWrite;

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	// 创建管道
	if (!::CreatePipe(&hOutRead, &hOutWrite, &sa, 0))
	{
		std::cerr << ("Unable to create stdout/stderr pipe for task process") << std::endl;
		return;
	}

	STARTUPINFO si = { sizeof(si) };
	::GetStartupInfo(&si);
	si.hStdError = hOutWrite;
	si.hStdOutput = hOutWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	PROCESS_INFORMATION pi;
	::ZeroMemory(&pi, sizeof(pi));

	if (!::CreateProcess(NULL,
		(LPTSTR)CmdLine.c_str(),
		NULL,
		NULL,
		TRUE,
		NULL,
		NULL,
		NULL,
		&si,
		&pi))
	{
		std::cout << "Failed to create process for command: " << CmdLine << std::endl;
		::CloseHandle(hOutWrite);
		::CloseHandle(hOutRead);

		std::cout << ::GetLastError() << std::endl;
		return;
	}
	::CloseHandle(hOutWrite);
	
	ReadOutput(hOutRead, pi.hProcess);

	::CloseHandle(hOutRead);
	::WaitForSingleObject(pi.hProcess,     INFINITE);

	::CloseHandle(pi.hProcess);
}

void RCCommand::ReadOutput(HANDLE hRead, HANDLE hProcess)
{
	TReadPipeData nThreadData = { hRead, this };
	HANDLE hReadPipeThread = ::CreateThread(NULL, 0, ReadPipeThread, &nThreadData, 0, NULL);

	unsigned long exit_code = 0;
	while (::GetExitCodeProcess(hProcess, &exit_code) && STILL_ACTIVE == exit_code)
	{
		//检测当前连接的状态
		DWORD nRet = ::WaitForSingleObject(RCCommandFactory::g_hConnectEvent, 0);

		//触发被关闭，连接事件中断
		if (nRet != 0)
		{
			std::cout << "Connection has closed.Now terminate the command process" << std::endl;
			::TerminateProcess(hProcess, exit_code);
			break;
		}
		Sleep(1000);
	}
	::WaitForSingleObject(hReadPipeThread, INFINITE);
}

std::string RCCommand::ReadFromPipe(HANDLE hRead, bool IsPrintOutput)
{
	std::string Content;

	const int READ_BUFFER_SIZE = 4096;
	char buffer[READ_BUFFER_SIZE] = { 0 };
	DWORD bytes = 0;

	while (::ReadFile(hRead, buffer, READ_BUFFER_SIZE, &bytes, NULL) && bytes > 0)
	{
		if (IsPrintOutput)
		{
			std::cout << buffer << std::endl;
		}
		Content.append(buffer, bytes);

		memset(buffer, 0, bytes);
	}

	return Content;
}

