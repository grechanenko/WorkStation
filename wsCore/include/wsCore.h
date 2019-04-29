#ifndef WSCORE_H
#define WSCORE_H

#include <QObject>

#include "wscore_global.h"
#include "i_wsCore.h"

class WSCORE_EXPORT WSCore : public QObject, public virtual i_wsCore
{
	Q_OBJECT
	Q_INTERFACES(i_wsCore)
	DECLARE_SMARTPOINTER

public:
	WSCore(i_wsSettingsCore* settings);
	~WSCore();


	/*!
		Возвращает главное окно
	*/
	virtual QMainWindow* getMainWindow() const;

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
	virtual void addGui(i_wsGuiPlugin* guiPlugin);


	/*!
		Возвращает меню по названию
	*/
	virtual QMenu* getMenu(const QString name );


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
	

	/*!
		Создать параметр
	*/
	virtual void createSetting(const QString& key, const QVariant& value, const bool visible = true);

	/*!
		Создать параметр
	*/
	virtual void createSetting(i_wsDescriptionSetting* wsDS);

	/*!
		Возвращает список параметров
	*/
	virtual QList<i_wsDescriptionSetting*> getSettingsList() const;


	/*!
		Возвращает значение параметра
	*/
	virtual QVariant getSetting(const QString& key) const;

	
	/*!
		Изменить значение параметра
	*/
	virtual void setSetting(const QString& key, const QVariant& value);


	/*!
		Загрузить файл перевода
	*/
	virtual void addTranslator(const QString& file);


	/*!
		Загрузить плагины
		Возвращает количество загруженных
	*/
	virtual int loadPlugins(QObject* ws, QObject* splash = Q_NULLPTR);


	/*!
		Возвращает названия загруженных плагинов
	*/
	virtual QStringList getPluginNames() const;


	/*!
		Возвращает плагин по названию
	*/
	virtual QObject* getPlugin(QString name) const;

	/*!
		Создает себя
	*/
	static WSCore* create(i_wsSettingsCore* wsSettingsCore);

private:
	struct SDATA;
	SDATA* m_data;
};

#endif // WSCORE_H
