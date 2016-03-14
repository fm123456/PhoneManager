/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#include "UploadCommand.h"
#include <iostream>

RCUploadCommand::RCUploadCommand()
{

}

RCUploadCommand::~RCUploadCommand()
{

}

void RCUploadCommand::Execute()
{
	std::string nLocalPath;
	std::string nRemotePath;

	std::cout << "please input local path：";
	std::cin >> nLocalPath;

	std::cout << "please input remote device path:";
	std::cin >> nRemotePath;

	std::string nCmdLine = "adb push " + nLocalPath + " " + nRemotePath;
	std::cout << "Execute Command: " << nCmdLine << std::endl;

	DoExecute(nCmdLine);
}