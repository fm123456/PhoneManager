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

RCCommandFactory::RCCommandFactory()
{

}

RCCommandFactory::~RCCommandFactory()
{

}

RCCommandFactory* RCCommandFactory::Instance()
{
	static RCCommandFactory g_nFactory;
	return &g_nFactory;
}

RCCommand* RCCommandFactory::CreateCommand(TCommandId nCmdId)
{
	RCCommand* cmd = NULL;
	switch (nCmdId)
	{
	case CheckConnectionCmd:
		cmd = new RCCheckConnectionCommand();
		break;
	case InstallCmd:
		cmd = new RCInstallCommand();
		break;
	case UninstallCmd:
		cmd = new RCUninstallCommand();
		break;
	case UploadCmd:
		cmd = new RCUploadCommand();
		break;
	case DownLoadCmd:
		cmd = new RCDownloadCommand();
		break;
	case BackupCmd:
		cmd = new RCBackupCommand();
		break;
	case RestoreCmd:
		cmd = new RCRestoreCommand();
		break;
	default:
		break;
	}
	return cmd;
}