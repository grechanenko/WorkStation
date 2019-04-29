#ifndef WSSETTINGSCORE_H
#define WSSETTINGSCORE_H

#include <QObject>
#include <QString>

#include "i_wsCore.h"
#include "i_wsDescriptionSetting.h"
#include "wscore_global.h"

class WSCORE_EXPORT WSDescriptionSetting : public QObject, public virtual i_wsDescriptionSetting
{
	Q_OBJECT
	Q_INTERFACES(i_wsDescriptionSetting)
	DECLARE_SMARTPOINTER

public:
	WSDescriptionSetting(const QString& key, const QVariant& value, const bool visible = true);
	~WSDescriptionSetting();


	/*!
		Описание настройки
	*/
	virtual QString getDescription() const;


	/*!
		Тип данных
	*/
	virtual QVariant::Type getType();


	/*!
		Возвращает ключ
	*/
	virtual QString getKey() const;


	/*!
		Значение по умолчанию
	*/	
	virtual QVariant getDefaultValue();


	/*!
		Текущее значение
	*/
	virtual QVariant getValue();


	/*!
		Установить новое значение
	*/
	virtual void setValue(const QVariant&);


	/*!
		Установить видимость для пользователя
	*/
	virtual void setVisible(const bool flag);
	

	/*!
		true - если скрыто от пользователя
	*/
	virtual bool isVisible() const;
	

	/*!
		Виджет для редактирования
	*/
	virtual QWidget* getWidget(QWidget* parent);

private:

	struct SDATA;
	SDATA* m_data;
};


class WSCORE_EXPORT WSSettingsCore : public QObject, public virtual i_wsSettingsCore, public virtual i_wsPtr
{
	Q_OBJECT
	Q_INTERFACES(i_wsSettingsCore i_wsPtr)
	DECLARE_SMARTPOINTER

public:
	WSSettingsCore();
	~WSSettingsCore();

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

private:

	struct SDATA;
	SDATA* m_data;
};

#endif // WSSETTINGSCORE_H
