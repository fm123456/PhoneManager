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

void RCUninstallCommand::Init()
{
	std::string nApkName;

	std::cout << "please input the name of package:";
	std::cin >> nApkName;

	m_CmdLine = "adb uninstall " + nApkName;
}