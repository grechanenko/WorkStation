#ifndef WSGUICORE_H
#define WSGUICORE_H

#include <QObject>
#include "i_wsCore.h"
#include "wscore_global.h"

class WSCORE_EXPORT WSGuiCore : public QObject, public virtual i_wsGuiCore
{
	Q_OBJECT
	Q_INTERFACES(i_wsGuiCore)
	DECLARE_SMARTPOINTER

public:
	WSGuiCore();
	~WSGuiCore();
	
	/*!
		Возвращает центральный виджет
	*/
	virtual QWidget* getCentralWidget();

	/*!
		Установить центральный виджет
	*/
	virtual void setCentralWidget(QWidget*);

	/*!
		Добавить GUI
	*/
	virtual void addGui(i_wsGuiPlugin*);


	/*!
		Возвращает меню по названию
	*/
	virtual QMenu* getMenu(const QString name);


	/*!
		Возвращает список наименований меню
	*/
	virtual QStringList getMenuNames();


	/*!
		Возвращает панель по названию
	*/
	virtual QToolBar* getToolBar(const QString name);

	
	/*!
		Возвращает список наименований панелей
	*/
	virtual QStringList getToolBarNames();


	/*!
		Возвращает dockWidget по названию
	*/
	virtual QDockWidget* getDockWidget(const QString name);

	
	/*!
		Возвращает список наименований dockWidget
	*/
	virtual QStringList getdockWidgetNames();

private:

	struct SDATA;
	SDATA* m_data;
};

#endif // WSGUICORE_H

