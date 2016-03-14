/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#ifndef __DownloadCommand_h
#define __DownloadCommand_h

#include "Command.h"

/** RCDownloadCommand用来执行从设备中下载文件的命令
*/

class RCDownloadCommand:
	public RCCommand
{
public:
	/** 构造函数
	*/
	RCDownloadCommand();

	/** 析构函数
	*/
	virtual ~RCDownloadCommand();

private:

	/** 初始化函数，用来获取设置adb命令以及相关参数，在Execute之前必须要调用Init()
	*/
	virtual void Init();
};


#endif