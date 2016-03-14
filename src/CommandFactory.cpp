/******************************************************************************
*  版权所有（C）2008-2016，上海二三四五网络科技发展有限公司                  *
*  保留所有权利。                                                            *
******************************************************************************
*  作者 : <fangm>
*  版本 : <1.0>
*****************************************************************************/

#include "CommandFactory.h"
#include "BackupCommand.h"
#include "CheckConnectionCommand.h"
#include "DownloadCommand.h"
#include "InstallCommand.h"
#include "RestoreCommand.h"
#include "UninstallCommand.h"
#include "UploadCommand.h"

//创建是否连接事件
HANDLE RCCommandFactory::g_hConnectEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);

//创建是否退出事件
HANDLE RCCommandFactory::g_hExitEvent = ::CreateEvent(NULL, TRUE, TRUE, NULL);

RCCommandFactory::RCCommandFactory()
{

}

RCCommandFactory::~RCCommandFactory()
{
	::CloseHandle(g_hConnectEvent);
	::CloseHandle(g_hExitEvent);
}

RCCommandFactory* RCCommandFactory::Instance()
{
	static RCCommandFactory g_nFactory;
	return &g_nFactory;
}

RCCommand* RCCommandFactory::CreateCommand(TCommandId nCmdId)
{
	RCCommand* pCmd = NULL;
	switch (nCmdId)
	{
	case CheckConnectionCmd:
		pCmd = new RCCheckConnectionCommand();
		break;
	case InstallCmd:
		pCmd = new RCInstallCommand();
		break;
	case UninstallCmd:
		pCmd = new RCUninstallCommand();
		break;
	case UploadCmd:
		pCmd = new RCUploadCommand();
		break;
	case DownLoadCmd:
		pCmd = new RCDownloadCommand();
		break;
	case BackupCmd:
		pCmd = new RCBackupCommand();
		break;
	case RestoreCmd:
		pCmd = new RCRestoreCommand();
		break;
	default:
		break;
	}
	return pCmd;
}