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
	@param[out] Output adb命令的输出信息
	*/
	void GetOutput(std::string& Output) const;

	/** 设置adb命令的输出信息
	@param[in] nOutput 当前adb命令的输出信息
	*/
	void SetOutput(const std::string& Output);

	/** 读取管道内容
	@param[in] hRead 需要读取的管道句柄
	@param[in] IsPrintOutput 是否边读边打印输出 
	*/
	static std::string ReadFromPipe(HANDLE hRead, bool IsPrintOutput = true);

	/** adb命令执行函数，内部调用的是DoExecute
	*/
	virtual void Execute();

protected:
	/** 构造函数
	*/
	RCCommand();

private:

	/** 初始化函数，用来获取设置adb命令以及相关参数，在Execute之前必须要调用Init()
	*/
	virtual void Init() = 0;

	/** adb命令执行函数
	@param[in] CmdLine 需要执行的adb完整命令行信息
	*/
	virtual void DoExecute(const std::string& CmdLine);

	/** 读取进程的输出信息
	@param[in] hRead 管道读端句柄
	@param[in] hProcess 需要读取输出信息的目标进程
	*/
	virtual void ReadOutput(HANDLE hRead, HANDLE hProcess);

protected:
	/** m_CmdLine 当前Command执行的命令行参数
	*/
	std::string m_CmdLine;

private:
	/** m_output 用来存放当前命令执行的一些输出信息
	*/
	std::string m_Output;

	/** m_hOutputEvent 用户控制m_Output同步的事件
	*/
	HANDLE m_hOutputEvent;
};


#endif