#ifndef WSPLUGINCORE_H
#define WSPLUGINCORE_H

#include <QObject>
#include "i_wsCore.h"
#include "wscore_global.h"

class WSCORE_EXPORT WSPluginCore : public QObject, public virtual i_wsPluginCore, public virtual i_wsPtr
{
	Q_OBJECT
	Q_INTERFACES(i_wsPluginCore i_wsPtr)
	DECLARE_SMARTPOINTER

public:
	WSPluginCore();
	~WSPluginCore();

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
		true - ���� ������ ��������
	*/
	bool checkLoadReference(QObject* plugin);

private:

	struct SDATA;
	SDATA* m_data;
};

#endif // WSPLUGINCORE_H
