/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#include "RestoreCommand.h"
#include <iostream>

RCRestoreCommand::RCRestoreCommand()
{

}

RCRestoreCommand::~RCRestoreCommand()
{

}

void RCRestoreCommand::Init()
{
	m_CmdLine = "adb restore backup.ab";
}