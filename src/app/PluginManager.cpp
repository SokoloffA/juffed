#include <QDebug>

#include "PluginManager.h"

#include "JuffPlugin.h"
#include "Log.h"
#include "DocHandlerInt.h"
#include "PluginNotifier.h"

#include <QDir>
#include <QPluginLoader>

PluginManager::PluginManager(Juff::DocHandlerInt* handler, Juff::PluginNotifier* notifier) {
	handler_ = handler;
	notifier_ = notifier;
}

void PluginManager::loadPlugins() {
	LOGGER;
	//	user's plugins
//	QDir pluginDir(AppInfo::configDirPath() + "/plugins");
	QDir pluginDir("../plugins");
	foreach (QString fileName, pluginDir.entryList(QStringList() << "*.so", QDir::Files)) {
		QString path = pluginDir.absoluteFilePath(fileName);
		loadPlugin(path);
	}
	
	//	global plugins
/*	QDir gPluginDir(AppInfo::appDirPath() + "/plugins");
	foreach (QString fileName, gPluginDir.entryList(QDir::Files)) {
		QString path = gPluginDir.absoluteFilePath(fileName);
		loadPlugin(path);
	}*/
	
/*	foreach (QString type, pmInt_->docks_.keys()) {
		pmInt_->gui_->addDocks(type, pmInt_->docks_[type]);
	}*/
}

Juff::MenuList PluginManager::menus() const {
	Juff::MenuList menus;
	foreach (JuffPlugin* plugin, plugins_)
		menus << plugin->menu();
	return menus;
}

Juff::ActionList PluginManager::actions(Juff::MenuID) const {
}

#include "EditorSettings.h"

void PluginManager::loadPlugin(const QString& path) {
	LOGGER;

	qDebug() << "                     FONT:" << EditorSettings::font();
	
	QPluginLoader loader(path);
	if ( !loader.load() ) {
		Log::warning(QString("Plugin '%1' was NOT loaded: %2").arg(path).arg(loader.errorString()));
		return;
	}
	
	qDebug() << "                     FONT:" << EditorSettings::font();
	
	QObject *obj = loader.instance();
	if ( obj ) {
		JuffPlugin* plugin = qobject_cast<JuffPlugin*>(obj);
		if ( plugin ) {

			//	Check if we need to load it
//			if ( !PluginSettings::pluginEnabled(plugin->name()) ) {
//				pmInt_->gui_->addPluginSettingsPage(plugin->name(), 0);
//				Log::debug("Plugin is disabled in Settings");
//				return;
//			}

			//	Check if plugin with the same name was already loaded.
			//	If is was then exit.
//			if ( pluginExists(plugin->name()) )
//				return;

//			plugin->setManager(pmInt_->managerInt_);
			plugin->setHandler(handler_);
			plugin->setNotifier(notifier_);
			
			plugins_ << plugin;
//			if ( pmInt_->addPlugin(plugin) ) {
//
				Log::debug(QString("-----=====((((( Plugin '%1' was loaded successfully! )))))=====-----").arg(plugin->name()));
//
				//	context menu actions
//				QString type = plugin->targetEngine();
//				pmInt_->contextMenuActions_[type] << plugin->contextMenuActions();
//				
				//	settings page
//				pmInt_->gui_->addPluginSettingsPage(plugin->name(), plugin->settingsPage());
//			}
//			else {
//				loader.unload();
//			}
		}
		else {
			Log::warning("Error while casting to JuffPlugin type");
		}
	}
	else {
		Log::debug("Empty plugin instance");
	}
}