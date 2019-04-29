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
		�������� ���������
	*/
	virtual QString getDescription() const;


	/*!
		��� ������
	*/
	virtual QVariant::Type getType();


	/*!
		���������� ����
	*/
	virtual QString getKey() const;


	/*!
		�������� �� ���������
	*/	
	virtual QVariant getDefaultValue();


	/*!
		������� ��������
	*/
	virtual QVariant getValue();


	/*!
		���������� ����� ��������
	*/
	virtual void setValue(const QVariant&);


	/*!
		���������� ��������� ��� ������������
	*/
	virtual void setVisible(const bool flag);
	

	/*!
		true - ���� ������ �� ������������
	*/
	virtual bool isVisible() const;
	

	/*!
		������ ��� ��������������
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
		������� ��������
	*/	
	virtual void createSetting(const QString& key, const QVariant& value, const bool visible = true);


	/*!
		������� ��������
	*/
	virtual void createSetting(i_wsDescriptionSetting* wsDS);


	/*!
		���������� ������ ����������
	*/	
	virtual QList<i_wsDescriptionSetting*> getSettingsList() const;


	/*!
		���������� �������� ���������
	*/
	virtual QVariant getSetting(const QString& key) const;


	/*!
		�������� �������� ���������
	*/
	virtual void setSetting(const QString& key, const QVariant& value);


	/*!
		��������� ���� ��������
	*/
	virtual void addTranslator(const QString& file);

private:

	struct SDATA;
	SDATA* m_data;
};

#endif // WSSETTINGSCORE_H
