/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/


#ifndef __RestoreCommand_h
#define __RestoreCommand_h

#include "Command.h"

/** RCRestoreCommand用来执行设备的恢复命令
*/

class RCRestoreCommand:
	public RCCommand
{
public:
	/**构造函数
	*/
	RCRestoreCommand();

	/** 析构函数
	*/
	virtual ~RCRestoreCommand();

	/** adb命令执行函数
	*/
	virtual void Execute();
};


#endif