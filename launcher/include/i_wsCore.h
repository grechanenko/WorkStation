#ifndef IWORKSTATION_H
#define IWORKSTATION_H

#include <QList>

#include "i_wsPtr.h"
#include "i_wsDescriptionSetting.h"


class QObject;
class QMainWindow;
class QMenu;
class QToolBar;

class QDockWidget;
class i_wsGuiPlugin;

class i_wsGuiCore
{
public:
	virtual ~i_wsGuiCore() {};

	/*!
		Возвращает центральный виджет
	*/
	virtual QWidget* getCentralWidget() = 0;


	/*!
		Установить центральный виджет
	*/
	virtual void setCentralWidget(QWidget*) = 0;


	/*!
		Добавить GUI
	*/
	virtual void addGui(i_wsGuiPlugin*) = 0;


	/*!
		Возвращает меню по названию
	*/
	virtual QMenu* getMenu(const QString name ) = 0;


	/*!
		Возвращает список наименований меню
	*/
	virtual QStringList getMenuNames() = 0;


	/*!
		Возвращает панель по названию
	*/
	virtual QToolBar* getToolBar(const QString name) = 0;

	
	/*!
		Возвращает список наименований панелей
	*/
	virtual QStringList getToolBarNames() = 0;


	/*!
		Возвращает dockWidget по названию
	*/
	virtual QDockWidget* getDockWidget(const QString name) = 0;

	
	/*!
		Возвращает список наименований dockWidget
	*/
	virtual QStringList getdockWidgetNames() = 0;	
	
};
Q_DECLARE_INTERFACE(i_wsGuiCore, "ws.launcher.i_wsGuiCore/1.0")



class i_wsSettingsCore
{
public:
	virtual ~i_wsSettingsCore() {};

	/*!
		Создать параметр
	*/
	virtual void createSetting(const QString& key, const QVariant& value, const bool visible = true) = 0;


	/*!
		Создать параметр
	*/
	virtual void createSetting(i_wsDescriptionSetting* wsDS) = 0;


	/*!
		Возвращает список параметров
	*/
	virtual QList<i_wsDescriptionSetting*> getSettingsList() const = 0;


	/*!
		Возвращает значение параметра
	*/
	virtual QVariant getSetting(const QString& name) const = 0;

	
	/*!
		Изменить значение параметра
	*/
	virtual void setSetting(const QString& name, const QVariant& value) = 0;


	/*!
		Загрузить файл перевода
	*/
	virtual void addTranslator(const QString& filePath) = 0;
};
Q_DECLARE_INTERFACE(i_wsSettingsCore, "ws.launcher.i_wsSettingsCore/1.0")



class i_wsPluginCore
{
public:

	virtual ~i_wsPluginCore() {};


	/*!
		Загрузить плагины
		Возвращает количество загруженных
	*/
	virtual int loadPlugins(QObject* ws, QObject* splash = Q_NULLPTR) = 0;


	/*!
		Возвращает названия загруженных плагинов
	*/
	virtual QStringList getPluginNames() const = 0;


	/*!
		Возвращает плагин по названию
	*/
	virtual QObject* getPlugin(QString name) const = 0;
};
Q_DECLARE_INTERFACE(i_wsPluginCore, "ws.launcher.i_wsPluginCore/1.0")


class i_wsCore : public virtual i_wsPtr,
				 public virtual i_wsGuiCore,
				 public virtual i_wsSettingsCore,
				 public virtual i_wsPluginCore
				 
{
	Q_INTERFACES(i_wsPointer i_wsGuiCore i_wsSettingsCore i_wsPluginCore)
public:
	virtual ~i_wsCore() {}
};
Q_DECLARE_INTERFACE(i_wsCore, "ws.launcher.i_wsCore/1.0")

#endif // VWORKSTATION_H