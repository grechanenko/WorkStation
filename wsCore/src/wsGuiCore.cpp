#include <QDebug>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QDockWidget>

#include "i_wsGuiPlugin.h"
#include "wsGuiCore.h"

IMPLEMENT_SMARTPOINTER(WSGuiCore)
// ----------------------------------------------------------------
struct WSGuiCore::SDATA
{
	QMainWindow* mainWindow = Q_NULLPTR;
	QMenuBar* menuBar = Q_NULLPTR;

	QList<QMenu*> listMenu;
	QList<QToolBar*> listToolBar;
	QList<QDockWidget*> listDockWidget;
};
// ----------------------------------------------------------------
WSGuiCore::WSGuiCore()
{
	m_data = Q_NULLPTR;
	m_data = new SDATA;
	if (m_data == Q_NULLPTR)
		return;

	m_data->mainWindow = new QMainWindow();
}
// ----------------------------------------------------------------
WSGuiCore::~WSGuiCore()
{
	if (m_data != Q_NULLPTR)
	{
		if (m_data->listMenu.size() > 0)
		{
			for (int i = 0; i < m_data->listMenu.size(); i++)
			{
				if (m_data->listMenu.at(i) != Q_NULLPTR)
				{
					delete m_data->listMenu[i];
					m_data->listMenu[i] = Q_NULLPTR;
				}
			}
		}
		QList<QToolBar*> listToolBar;
		QList<QDockWidget*> listDockWidget;

		delete m_data;
		m_data = Q_NULLPTR;
	}
}
// ----------------------------------------------------------------
QWidget* WSGuiCore::getCentralWidget()
{
	if (m_data != Q_NULLPTR)
		if (m_data->mainWindow != Q_NULLPTR)
			return m_data->mainWindow->centralWidget();
	return Q_NULLPTR;
}
// ----------------------------------------------------------------
void WSGuiCore::setCentralWidget(QWidget* widget)
{
	if (widget == Q_NULLPTR)
		return;

	if (m_data != Q_NULLPTR)
		if (m_data->mainWindow != Q_NULLPTR)
			m_data->mainWindow->setCentralWidget(widget);
}
// ----------------------------------------------------------------
void WSGuiCore::addGui(i_wsGuiPlugin* newGui)
{	
	if (m_data == Q_NULLPTR)
		return;

	if (m_data->mainWindow == Q_NULLPTR)
		return;

	if (newGui == Q_NULLPTR)
		return;
	
	QMenu* menu = newGui->getMenu();
	QToolBar* toolBar = newGui->getToolBar();
	QDockWidget* dockWidget = newGui->getDockWidget();

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
QMenu* WSGuiCore::getMenu(const QString name)
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
				qDebug() << "GetMenu menuName = " << m->objectName();
				break;
			}
		}
	}
	return menu;
}
// ----------------------------------------------------------------
QStringList WSGuiCore::getMenuNames()
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
QToolBar* WSGuiCore::getToolBar(const QString name)
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
QStringList WSGuiCore::getToolBarNames()
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
QDockWidget* WSGuiCore::getDockWidget(const QString name)
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
QStringList WSGuiCore::getdockWidgetNames()
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