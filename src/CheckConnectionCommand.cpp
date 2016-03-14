/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#include "CheckConnectionCommand.h"
#include <iostream>
 
const std::string g_nConnectString = "List of devices attached ";

RCCheckConnectionCommand::RCCheckConnectionCommand():
m_nConnection(false)
{

}

RCCheckConnectionCommand::~RCCheckConnectionCommand()
{

}

bool RCCheckConnectionCommand::HasConnected() const
{
	return m_nConnection;
}

void RCCheckConnectionCommand::Execute()
{
	std::string nCmdLine = "adb devices";
	DoExecute(nCmdLine);

	const std::string& nOutput = GetOutput();
	if (nOutput.empty())
	{
		return;
	}

	m_nConnection = CheckConnection(nOutput);
}

void RCCheckConnectionCommand::DoExecute(const std::string& nCmdLine)
{
	SetOutput("");
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
	si.hStdError = out_write;
	si.hStdOutput = out_write;
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

		std::cout << GetLastError() << std::endl;
		return;
	}
	::CloseHandle(out_write);

	std::string content;
	const int READ_BUFFER_SIZE = 4096;
	char buffer[READ_BUFFER_SIZE] = { 0 };
	DWORD bytes = 0;

	while (::ReadFile(out_read, buffer, READ_BUFFER_SIZE, &bytes, NULL) && bytes > 0)
	{
		content.append(buffer,bytes);
		memset(buffer, 0, bytes);
	}
	SetOutput(content);

	::CloseHandle(out_read);
	::WaitForSingleObject(pi.hProcess, INFINITE);
	::CloseHandle(pi.hProcess);
}

bool RCCheckConnectionCommand::CheckConnection(const std::string& nContent)
{
	std::string nTempStr = nContent;
	bool nTempConnect = false;

	while (!nTempStr.empty())
	{
		std::string::size_type p = nTempStr.find("\r\n");
		if (p != std::string::npos)
		{
			std::string nTempContent = nTempStr.substr(0, p);
			if (nTempContent == g_nConnectString)
			{
				std::string nNextContent = nTempStr.substr(p + 2);
				p = nNextContent.find("\r\n");

				if (p != std::string::npos && !nNextContent.substr(0,p).empty())
				{
					nTempConnect = true;
				}
				break;
			}
			nTempStr = nTempStr.substr(p + 2);
		}
		else
		{
			nTempStr = "";
		}
	}

	return nTempConnect;
}