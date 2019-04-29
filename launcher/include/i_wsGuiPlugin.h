#ifndef I_WSGUIPLUGIN_H
#define I_WSGUIPLUGIN_H

#include "i_wsPtr.h"

class QMenu;
class QToolBar;
class QDockWidget;

class i_wsGuiPlugin
{
public:

	virtual ~i_wsGuiPlugin() {}

	/*!
		Возвращает меню
	*/
	virtual QMenu* getMenu() const = 0;

	/*!
		Возвращает панель
	*/
	virtual QToolBar* getToolBar() const = 0;

	/*!
		Возвращает dockWidget
	*/
	virtual QDockWidget* getDockWidget() const = 0;
};
Q_DECLARE_INTERFACE(i_wsGuiPlugin, "ws.launcher.i_wsGuiPlugin/1.0")

#endif // I_WSGUIPLUGIN_H
