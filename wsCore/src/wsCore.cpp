#include <QDebug>
#include <QTextCodec>
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QDockWidget>

#include "i_wsGuiPlugin.h"


#include "wsCore.h"
#include "wsPluginCore.h"


IMPLEMENT_SMARTPOINTER(WSCore)
// ----------------------------------------------------------------
struct WSCore::SDATA
{
	i_wsSettingsCore* settings = Q_NULLPTR;
	i_wsPluginCore* plugins = Q_NULLPTR;
	
	// GUI
	QMainWindow* mainWindow = Q_NULLPTR;
	QMenuBar* menuBar = Q_NULLPTR;
	QList<QMenu*> listMenu;
	QList<QToolBar*> listToolBar;
	QList<QDockWidget*> listDockWidget;
};
// ----------------------------------------------------------------
WSCore::WSCore(i_wsSettingsCore* settings)
{		
	m_data = Q_NULLPTR;
	m_data = new SDATA;
	if (m_data == Q_NULLPTR)
		return;

	if (settings != Q_NULLPTR) 
		m_data->settings = settings;

	m_data->plugins = new WSPluginCore();	
		
	if (qobject_cast<QApplication *>(qApp) != Q_NULLPTR)
		m_data->mainWindow = new QMainWindow();
}
// ----------------------------------------------------------------
WSCore::~WSCore()
{
	if (m_data != Q_NULLPTR)
	{
		delete m_data;
		m_data = Q_NULLPTR;
	}
}
// ----------------------------------------------------------------
QMainWindow* WSCore::getMainWindow() const
{
	if (m_data == Q_NULLPTR)
		return Q_NULLPTR;

	if (m_data->mainWindow != Q_NULLPTR)
		return m_data->mainWindow;
	return Q_NULLPTR;
}
// ----------------------------------------------------------------
QWidget* WSCore::getCentralWidget()
{
	if (m_data != Q_NULLPTR)
		if (m_data->mainWindow != Q_NULLPTR)
			return m_data->mainWindow->centralWidget();
	return Q_NULLPTR;
}
// ----------------------------------------------------------------
void WSCore::setCentralWidget(QWidget* widget)
{
	if (widget == Q_NULLPTR)
		return;

	if (m_data != Q_NULLPTR)
		if (m_data->mainWindow != Q_NULLPTR)
			m_data->mainWindow->setCentralWidget(widget);
}
// ----------------------------------------------------------------
void WSCore::addGui(i_wsGuiPlugin* guiPlugin)
{	
	if (m_data == Q_NULLPTR)
		return;

	if (m_data->mainWindow == Q_NULLPTR)
		return;

	if (guiPlugin == Q_NULLPTR)
		return;

	QMenu* menu = guiPlugin->getMenu();
	QToolBar* toolBar = guiPlugin->getToolBar();
	QDockWidget* dockWidget = guiPlugin->getDockWidget();

	if (menu != Q_NULLPTR)
	{
		if (m_data->menuBar == Q_NULLPTR)
		{
			m_data->menuBar = new QMenuBar();
			m_data->mainWindow->setMenuBar(m_data->menuBar);
		}

		m_data->menuBar->addMenu(menu);
		m_data->listMenu.push_back(menu);
	}

	if (toolBar != Q_NULLPTR)
	{
		m_data->mainWindow->addToolBar(toolBar);
		m_data->listToolBar.push_back(toolBar);
	}

	if (dockWidget != Q_NULLPTR)
	{
		m_data->mainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
		m_data->listDockWidget.push_back(dockWidget);
	}
}
// ----------------------------------------------------------------
QMenu* WSCore::getMenu(const QString name)
{
	if (m_data == Q_NULLPTR)
		return Q_NULLPTR;

	if (m_data->listMenu.size() < 1)
		return Q_NULLPTR;

	QMenu* menu = Q_NULLPTR;
	for each(QMenu* m in m_data->listMenu)
	{
		if (m != Q_NULLPTR)
		{
			if (m->objectName() == name)
			{
				menu = m;				
				break;
			}
		}
	}
	return menu;
}
// ----------------------------------------------------------------
QStringList WSCore::getMenuNames()
{
	if (m_data == Q_NULLPTR)
		return QStringList();

	if (m_data->listMenu.size() < 1)
		return QStringList();

	QStringList names;
	for each(QMenu* m in m_data->listMenu)
	{
		if (m != Q_NULLPTR)
			names.push_back(m->objectName());
	}
	return names;
}
// ----------------------------------------------------------------
QToolBar* WSCore::getToolBar(const QString name)
{
	if (m_data == Q_NULLPTR)
		return Q_NULLPTR;

	if (m_data->listToolBar.size() < 1)
		return Q_NULLPTR;

	QToolBar* toolBar = Q_NULLPTR;
	for each(QToolBar* t in m_data->listToolBar)
	{
		if (t != Q_NULLPTR)
		{
			if (t->objectName() == name)
			{
				toolBar = t;
				break;
			}
		}
	}
	return toolBar;
}
// ----------------------------------------------------------------
QStringList WSCore::getToolBarNames()
{
	if (m_data == Q_NULLPTR)
		return QStringList();

	if (m_data->listToolBar.size() < 1)
		return QStringList();

	QStringList names;
	for each(QToolBar* t in m_data->listToolBar)
	{
		if (t != Q_NULLPTR)
			names.push_back(t->objectName());
	}
	return names;
}
// ----------------------------------------------------------------
QDockWidget* WSCore::getDockWidget(const QString name)
{
	if (m_data == Q_NULLPTR)
		return Q_NULLPTR;

	if (m_data->listDockWidget.size() < 1)
		return Q_NULLPTR;

	QDockWidget* dockWidget = Q_NULLPTR;
	for each(QDockWidget* dW in m_data->listDockWidget)
	{
		if (dW != Q_NULLPTR)
		{
			if (dW->objectName() == name)
			{
				dockWidget = dW;
				break;
			}
		}
	}
	return dockWidget;
}
// ----------------------------------------------------------------
QStringList WSCore::getdockWidgetNames()
{
	if (m_data == Q_NULLPTR)
		return QStringList();

	if (m_data->listDockWidget.size() < 1)
		return QStringList();

	QStringList names;
	for each(QDockWidget* dW in m_data->listDockWidget)
	{
		if (dW != Q_NULLPTR)
			names.push_back(dW->objectName());
	}
	return names;
}
// ----------------------------------------------------------------
void WSCore::createSetting(const QString& key, const QVariant& value, const bool visible)
{
	if (m_data == Q_NULLPTR)
		return;

	if (m_data->settings == Q_NULLPTR)
		return;

	if (key.isEmpty() == true)
		return;

	if (value.isValid() == false)
		return;
	
	m_data->settings->createSetting(key, value, visible);
}
// ----------------------------------------------------------------
void WSCore::createSetting(i_wsDescriptionSetting* wsDS)
{
	if (m_data == Q_NULLPTR)
		return;

	if (m_data->settings == Q_NULLPTR)
		return;

	if (wsDS == Q_NULLPTR)
		return;

	m_data->settings->createSetting(wsDS);
}
// ----------------------------------------------------------------
QList<i_wsDescriptionSetting*> WSCore::getSettingsList() const
{
	if (m_data == Q_NULLPTR)
		return QList<i_wsDescriptionSetting*>();

	if (m_data->settings == Q_NULLPTR)
		return QList<i_wsDescriptionSetting*>();

	return m_data->settings->getSettingsList();
}
// ----------------------------------------------------------------
QVariant WSCore::getSetting(const QString& key) const
{
	if (m_data == Q_NULLPTR)
		return QVariant();

	if (m_data->settings == Q_NULLPTR)
		return QVariant();

	if (key.isEmpty() == true)
		return QVariant();

	return m_data->settings->getSetting(key);
}
// ----------------------------------------------------------------
void WSCore::setSetting(const QString& key, const QVariant& value)
{
	if (m_data == Q_NULLPTR)
		return;

	if (m_data->settings == Q_NULLPTR)
		return;

	if (key.isEmpty() == true)
		return;

	if (value.isValid() == false)
		return;
	
	m_data->settings->setSetting(key, value);
}
// ----------------------------------------------------------------
void WSCore::addTranslator(const QString& file)
{	
	if (m_data == Q_NULLPTR)
		return;

	if (m_data->settings == Q_NULLPTR)
		return;

	if (file.isEmpty() == true)
		return;

	m_data->settings->addTranslator(file);
}
// ----------------------------------------------------------------
int WSCore::loadPlugins(QObject* ws, QObject* splash)
{	
	if (m_data == Q_NULLPTR)
		return 0;
	
	if (m_data->plugins == Q_NULLPTR)
		return 0;
	
	if (ws == Q_NULLPTR)
		return 0;
	
	int countPlugins = m_data->plugins->loadPlugins(ws, splash);
	return countPlugins;
}
// ----------------------------------------------------------------
QStringList WSCore::getPluginNames() const
{
	if (m_data == Q_NULLPTR)
		return QStringList();

	if (m_data->plugins == Q_NULLPTR)
		return QStringList();

	return m_data->plugins->getPluginNames();
}
// ----------------------------------------------------------------
QObject* WSCore::getPlugin(QString name) const
{
	if (m_data == Q_NULLPTR)
		return Q_NULLPTR;

	if (m_data->plugins == Q_NULLPTR)
		return Q_NULLPTR;

	if (name.isEmpty() == true)
		return Q_NULLPTR;

	return m_data->plugins->getPlugin(name);
}
// ----------------------------------------------------------------
WSCore* WSCore::create(i_wsSettingsCore* wsSettingsCore)
{	
	if (wsSettingsCore == Q_NULLPTR)
		return Q_NULLPTR;	
	return( new WSCore(wsSettingsCore));
}
// ----------------------------------------------------------------