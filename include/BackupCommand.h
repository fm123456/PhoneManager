/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#ifndef __BackupCommand_h
#define __BackupCommand_h

#include "Command.h"

/** RCBackupCommand用来执行设备的备份命令
*/

class RCBackupCommand: 
	public RCCommand
{
public:
	/** 构造函数
	*/
	RCBackupCommand();

	/** 析构函数
	*/
	virtual ~RCBackupCommand();

private:
	/** 初始化函数，用来获取设置adb命令以及相关参数，在Execute之前必须要调用Init()
	*/
	virtual void Init();
};


#endif