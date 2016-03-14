/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#include <windows.h>
#include <string>

#ifndef __Command_h
#define __Command_h

extern HANDLE hConnectEvent;
extern HANDLE hExitEvent;

/** RCCommand作为所有command的基类。里面封装了命令的执
    以及获取执行命令进程的输出
*/

class RCCommand
{
public:
	/** 析构函数
	*/
	virtual ~RCCommand();

	/** 获取adb命令的输出信息
	@return 当前adb命令的输出信息
	*/
	const std::string& GetOutput() const;

	/** 设置adb命令的输出信息
	@param[in] nOutput 当前adb命令的输出信息
	*/
	void SetOutput(const std::string& nOutput);

	/** 读取管道内容
	@param[in] hRead 需要读取的管道句柄
	*/
	static std::string ReadFromPipe(HANDLE hRead);

	/** adb命令执行函数，内部调用的是DoExecute
	*/
	virtual void Execute() = 0;

protected:
	/** 构造函数
	*/
	RCCommand();

	/** adb命令执行函数
	@param[in] nCmdLine 需要执行的adb完整命令行信息
	*/
	virtual void DoExecute(const std::string& nCmdLine);

private:
	/** m_output 用来存放当前命令执行的一些输出信息
	*/
	std::string m_nOutput;
};


#endif