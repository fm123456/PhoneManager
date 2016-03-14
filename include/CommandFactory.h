/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#ifndef __CommandFactory_h
#define __CommandFactory_h

/** TCommandId作为命令的枚举
*/
enum TCommandId
{
	CheckConnectionCmd = 0,
	InstallCmd,
	UninstallCmd,
	UploadCmd,
	DownLoadCmd,
	BackupCmd,
	RestoreCmd,
	ExitCmd
};

class RCCommand;

/** RCCommandFactory作为所有command的工厂类。用来创建我们
    所需要的具体的Command
*/

class RCCommandFactory
{
public:
	/** 析构函数
	*/
	virtual ~RCCommandFactory();
	
	/** 静态方法，用来返回唯一的RCCommandFactory指针
	@return 静态的RCCommandFactory对象的指针
	*/
	static RCCommandFactory* Instance();

	/** 创建Command的方法
	@param[in] nCmdId具体命令的Id
	@return 创建好的命令的指针
	*/
	RCCommand* CreateCommand(TCommandId nCmdId);

private:
	/** 构造函数
	*/
	RCCommandFactory();
	 
};


#endif