/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#ifndef __CheckConnectionCommand_h
#define __CheckConnectionCommand_h

#include "Command.h"
#include <vector>

/** RCCheckConnectionCommand用来执行检测设备是否连接的命令
*/

class RCCheckConnectionCommand:
	public RCCommand
{
public:
	/** 构造函数
	*/
	RCCheckConnectionCommand();

	/** 析构函数
	*/
	virtual ~RCCheckConnectionCommand();

	/** 是否存在连接设备
	*/
	bool HasConnected() const;

	/** adb命令执行函数
	*/
	virtual void Execute();

private:

	/** 初始化函数，用来获取设置adb命令以及相关参数，在Execute之前必须要调用Init()
	*/
	virtual void Init();

	/** adb命令执行函数
	@param[in] CmdLine 需要执行的adb完整命令行信息
	@param[in] IsAsyn是否采用用多线程来异步的读取adb输出
	*/
	virtual void ReadOutput(HANDLE hRead, HANDLE hProcess);

private:
	/** 按行分割字符串函数
	@param[in] nContent 传入的需要解析adb命令的输出
	*/
	bool CheckConnection(const std::string& nContent);

private:
	/** m_output 当前是否存在连接
	*/
	bool        m_nConnection;
};


#endif