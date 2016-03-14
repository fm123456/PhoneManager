﻿/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#include "InstallCommand.h"
#include <iostream>

RCInstallCommand::RCInstallCommand()
{

}

RCInstallCommand::~RCInstallCommand()
{

}

void RCInstallCommand::Execute()
{
	std::string nApkPath;
	
	std::cout << "please input the path of apk:";
	std::cin >> nApkPath;

	std::string nCmdLine = "adb install " + nApkPath;
	std::cout << "Execute Command: " << nCmdLine << std::endl;

	DoExecute(nCmdLine);
}