#include <QDebug>
#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QMainWindow>
#include <QSplashScreen>
#include <QPixmap>

#include "i_wsCore.h"
#include "wsCore.h"
#include "wsSettingsCore.h"

WSCore* core(QSplashScreen splashScreen)
{	
	qApp->setOrganizationName("API Service");
	qApp->setApplicationName("Launcher");

	i_wsSettingsCore* wsSettingsCore = Q_NULLPTR;
	wsSettingsCore = new WSSettingsCore();		
	
	if (wsSettingsCore != Q_NULLPTR)
	{
		WSCore* wsCore = Q_NULLPTR;
		wsCore = WSCore::create(wsSettingsCore);
		
		if (wsCore != Q_NULLPTR)
		{		
			int countPlugin = wsCore->loadPlugins(wsCore, &splashScreen);
			return wsCore;
		}		
	}
	return Q_NULLPTR;
}

int main(int argc, char *argv[])
{
	bool flagGui = true;
		
	// Если есть аргументы
	if (argc > 0)
	{
		for (int i = 0; i < argc; i++)
		{
			if (QString(argv[i]) == QString("-notgui"))
				flagGui = false;
		}
	}
	
	if ( flagGui == false )
	{
		QCoreApplication a(argc, argv);
		core(Q_NULLPTR);			
		return a.exec();
	}
	else
	{
		QApplication a(argc, argv);

		QPixmap splashScreenPixmap(":/launcher/Resources/SplashScreen.png");
		QSplashScreen splashScreen(splashScreenPixmap);
		splashScreen.show();

		WSCore* wsCore = Q_NULLPTR;
		wsCore = core(&splashScreen);
		if (wsCore != Q_NULLPTR)
		{
			QMainWindow* mainWindow = Q_NULLPTR;
			mainWindow = wsCore->getMainWindow();
			if (mainWindow != Q_NULLPTR)
				mainWindow->show();
		}
		return a.exec();
	}
	return 0;
}
