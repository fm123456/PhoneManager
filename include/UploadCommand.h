﻿/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#ifndef __UploadCommand_h
#define __UploadCommand_h

#include "Command.h"

/** RCDownloadCommand用来执行往设备上载文件的命令
*/

class RCUploadCommand:
	public RCCommand
{
public:
	/** 构造函数
	*/
	RCUploadCommand();

	/** 析构函数
	*/
	virtual ~RCUploadCommand();

	/** adb命令执行函数
	*/
	virtual void Execute();

private:
	 
};


#endif