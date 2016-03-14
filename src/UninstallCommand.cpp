/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/
#include "UninstallCommand.h"
#include <iostream>

RCUninstallCommand::RCUninstallCommand()
{

}

RCUninstallCommand::~RCUninstallCommand()
{

}

void RCUninstallCommand::Execute()
{
	std::string nApkName;

	std::cout << "please input the name of package:";
	std::cin >> nApkName;

	std::string nCmdLine = "adb uninstall " + nApkName;
	std::cout << "Execute Command: " << nCmdLine << std::endl;

	DoExecute(nCmdLine);
}