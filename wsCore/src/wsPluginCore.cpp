#include <QDebug>
#include <QVector>
#include <QDir>
#include <QApplication>
#include <QSplashScreen>
#include <QPluginLoader>

#include "wsPluginCore.h"
#include "i_wsPlugin.h"

IMPLEMENT_SMARTPOINTER(WSPluginCore)

struct WSPluginCore::SDATA
{	
	QVector<QObject*> plugins;
};
// ----------------------------------------------------------------
WSPluginCore::WSPluginCore()
{
	m_data = Q_NULLPTR;
	m_data = new SDATA;
	if (m_data == Q_NULLPTR)
		return;

	m_data->plugins.clear();
}
// ----------------------------------------------------------------
WSPluginCore::~WSPluginCore()
{
	if (m_data != Q_NULLPTR)
	{
		delete m_data;
		m_data = Q_NULLPTR;
	}
}
// ----------------------------------------------------------------
int WSPluginCore::loadPlugins(QObject* ws, QObject* _splash)
{
	if (m_data == Q_NULLPTR)
	{
		qDebug() << "WSPluginCore::loadPlugins(). M_data is NULL";
		return 0;
	}

	QDir dir(QApplication::applicationDirPath());
	if (!dir.cd("plugins"))
	{
		qDebug() << "WSPluginCore::loadPlugin(). Plugins directory does not exist";
		return 0;
	}

	QStringList listFiles = dir.entryList(QDir::Files);	
	if (listFiles.size() < 1)
		return 0;	

	QSplashScreen* splash = Q_NULLPTR;
	if (_splash != Q_NULLPTR)
		splash = qobject_cast<QSplashScreen*>(_splash);

	QList<QObject*> notLoadModuleList;
	notLoadModuleList.clear();

	for (int i = 0; i < listFiles.size(); i++)
	{
		QString strFileName = listFiles.at(i);
		QPluginLoader loader(dir.absoluteFilePath(strFileName));
		QObject* obj = qobject_cast<QObject*>(loader.instance());
		
		if (obj != Q_NULLPTR)
		{
			i_wsPlugin* plugin = qobject_cast<i_wsPlugin*>(obj);
			if (plugin != Q_NULLPTR)
			{
				if (this->checkLoadReference(obj))
				{
					bool res = plugin->initialize(ws);
					if (res == true)
					{
						if (splash != Q_NULLPTR)
							splash->showMessage(plugin->getName());
						m_data->plugins.push_back(obj);
					}
				}
				else
					notLoadModuleList.push_back(obj);
			}
		}
	}

	if (notLoadModuleList.size() < 1)
		return (m_data->plugins.size());

	bool flagFinished = true;
	while (flagFinished)
	{
		flagFinished = false;
		// ѕеребор не загруженных модулей
		for each (QObject* notLoadModule in notLoadModuleList)
		{
			if (this->checkLoadReference(notLoadModule))
			{
				i_wsPlugin* plugin = qobject_cast<i_wsPlugin*>(notLoadModule);
				if (plugin != Q_NULLPTR)
				{
					bool res = plugin->initialize(ws);
					if (res == true)
					{
						if (splash != Q_NULLPTR)
							splash->showMessage(plugin->getName());
						m_data->plugins.push_back(notLoadModule);
						notLoadModuleList.removeOne(notLoadModule);
						flagFinished = true;
					}
				}
			}
		}
	}

	return (m_data->plugins.size());
}
// ----------------------------------------------------------------
QStringList WSPluginCore::getPluginNames() const
{
	if (m_data == Q_NULLPTR)
		return QStringList();

	QStringList pluginList;
	for (int i = 0; i < m_data->plugins.size(); i++)
	{
		QObject* pluginObject = m_data->plugins.at(i);
		if (pluginObject != Q_NULLPTR)
		{
			i_wsPlugin* plugin = qobject_cast<i_wsPlugin*>(pluginObject);
			if (plugin != Q_NULLPTR)
				pluginList.push_back(plugin->getName());
		}
	}
	return pluginList;
}
// ----------------------------------------------------------------
QObject* WSPluginCore::getPlugin(QString name) const
{
	if (m_data == Q_NULLPTR)
		return (new QObject());

	if (name.isEmpty() == true)
		return (new QObject());

	QObject* pluginResult = Q_NULLPTR;
	for (int i = 0; i < m_data->plugins.size(); i++)
	{
		QObject* pluginObject = m_data->plugins.at(i);
		if (pluginObject != Q_NULLPTR)
		{
			i_wsPlugin* plugin = qobject_cast<i_wsPlugin*>(pluginObject);
			if (plugin != Q_NULLPTR)
				if (plugin->getName() == name)
					pluginResult = pluginObject;
		}
	}

	return pluginResult;
}
// ----------------------------------------------------------------

bool WSPluginCore::checkLoadReference(QObject* pluginObject)
{
	if (m_data == Q_NULLPTR)
		return false;

	if (pluginObject == Q_NULLPTR)
		return false;

	i_wsPlugin* plugin = qobject_cast<i_wsPlugin*>(pluginObject);
	if (plugin == Q_NULLPTR)
		return false;

	// ≈сли нет зависимостей -, можно загружать
	QStringList references = plugin->references();
	if (references.size() < 1)
		return true;

	// ≈сли еще ничего не загружено, а зависимости есть - нельз€ загружать
	if (m_data->plugins.size() < 1)
		return false;

	// Ќабор флагов дл€ каждой зависимости
	// 0 - незагружено
	// 1 - загружено
	QList<int> loadFlag;
	for (int i = 0; i<references.size(); i++)
	{
		loadFlag.push_back(0);
	}

	// ѕеребор загруженных модулей
	for each (QObject* loadPluginObject in m_data->plugins)
	{
		i_wsPlugin* loadModule = qobject_cast<i_wsPlugin*>(loadPluginObject);
		if (loadModule != Q_NULLPTR)
		{
			QString nameLoadModule = loadModule->getName();
			// ѕеребор зависимостей
			for (int i = 0; i < references.size(); i++)
			{
				QString nameRef = references.at(i);
				if (nameRef == nameLoadModule)
					loadFlag[i] = 1;
			}
		}
	}

	// ќпредел€ем количество загруженных зависимостей
	int sum = 0;
	for (int i = 0; i < loadFlag.size(); i++)
		if (loadFlag.at(i) == 1)
			sum++;

	// ≈сли все зависимости загружены - можно загружать
	if (sum == loadFlag.size())
		return true;

	return false;
}