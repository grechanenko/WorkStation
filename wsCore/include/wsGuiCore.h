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
	virtual void addGui(i_wsGuiPlugin*);


	/*!
		���������� ���� �� ��������
	*/
	virtual QMenu* getMenu(const QString name);


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

private:

	struct SDATA;
	SDATA* m_data;
};

#endif // WSGUICORE_H

