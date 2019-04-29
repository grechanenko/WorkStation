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
		���������� ������� ����
	*/
	virtual QMainWindow* getMainWindow() const;

	/*!
		���������� ����������� ������
	*/
	virtual QWidget* getCentralWidget();


	/*!
		���������� ����������� ������
	*/
	virtual void setCentralWidget(QWidget*);

	
	/*!
		�������� GUI
	*/
	virtual void addGui(i_wsGuiPlugin* guiPlugin);


	/*!
		���������� ���� �� ��������
	*/
	virtual QMenu* getMenu(const QString name );


	/*!
		���������� ������ ������������ ����
	*/
	virtual QStringList getMenuNames();


	/*!
		���������� ������ �� ��������
	*/
	virtual QToolBar* getToolBar(const QString name);

	
	/*!
		���������� ������ ������������ �������
	*/
	virtual QStringList getToolBarNames();


	/*!
		���������� dockWidget �� ��������
	*/
	virtual QDockWidget* getDockWidget(const QString name);

	
	/*!
		���������� ������ ������������ dockWidget
	*/
	virtual QStringList getdockWidgetNames();
	

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


	/*!
		��������� �������
		���������� ���������� �����������
	*/
	virtual int loadPlugins(QObject* ws, QObject* splash = Q_NULLPTR);


	/*!
		���������� �������� ����������� ��������
	*/
	virtual QStringList getPluginNames() const;


	/*!
		���������� ������ �� ��������
	*/
	virtual QObject* getPlugin(QString name) const;

	/*!
		������� ����
	*/
	static WSCore* create(i_wsSettingsCore* wsSettingsCore);

private:
	struct SDATA;
	SDATA* m_data;
};

#endif // WSCORE_H
