/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#ifndef __UninstallCommand_h
#define __UninstallCommand_h

#include "Command.h"

/** RCUninstallCommand用来执行在设备上卸载应用的命令
*/

class RCUninstallCommand:
	public RCCommand
{
public:
	/** 构造函数
	*/
	RCUninstallCommand();

	/** 析构函数
	*/
	virtual ~RCUninstallCommand();

	/** adb命令执行函数
	*/
	virtual void Execute();	 
};


#endif