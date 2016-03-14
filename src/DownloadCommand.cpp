/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#include "DownloadCommand.h"
#include <iostream>

RCDownloadCommand::RCDownloadCommand()
{

}

RCDownloadCommand::~RCDownloadCommand()
{

}

void RCDownloadCommand::Init()
{
	std::string nRemotePath;
	std::string nLocalPath;

	std::cout << "please input remote device path:";
	std::cin >> nRemotePath;

	std::cout << "please input local path：";
	std::cin >> nLocalPath;

	m_CmdLine = "adb pull " + nRemotePath + " " + nLocalPath;
}