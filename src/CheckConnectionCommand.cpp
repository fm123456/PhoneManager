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

void RCCheckConnectionCommand::Init()
{
	m_CmdLine = "adb devices";
}

void RCCheckConnectionCommand::Execute()
{
	RCCommand::Execute();

	std::string Output;
	GetOutput(Output);
	if (Output.empty())
	{
		return;
	}

	m_nConnection = CheckConnection(Output);
}

void RCCheckConnectionCommand::ReadOutput(HANDLE hRead, HANDLE hProcess)
{
	SetOutput(RCCommand::ReadFromPipe(hRead, false));
}

bool RCCheckConnectionCommand::CheckConnection(const std::string& nContent)
{
	std::string Content = nContent;
	bool IsConnect = false;

	while (!Content.empty())
	{
		std::string::size_type p = Content.find("\r\n");
		if (p != std::string::npos)
		{
			std::string TempContent = Content.substr(0, p);
			if (TempContent == g_nConnectString)
			{
				std::string nNextContent = Content.substr(p + 2);
				p = nNextContent.find("\r\n");

				if (p != std::string::npos && !nNextContent.substr(0,p).empty())
				{
					IsConnect = true;
				}
				break;
			}
			Content = Content.substr(p + 2);
		}
		else
		{
			Content = "";
		}
	}

	return IsConnect;
}