/***********************************************************************************
** MIT License                                                                    **
**                                                                                **
** Copyright (c) 2018 Victor DENIS (victordenis01@gmail.com)                      **
**                                                                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
***********************************************************************************/

#pragma once
#ifndef ARCSCREEN_HPP
#define ARCSCREEN_HPP

#include "Plugins/PluginInterface.hpp"

#include <QObject>

#include <QPointer> 

#include "ArcScreenToolButton.hpp"
#include "Widgets/NavigationBar.hpp"

class ArcScreenSideBar;

namespace Sn
{
    class WebView;

    //! Interface of the Plugin
    /*!
     * This is the interface of the plugin. It inehrite from both QObject and PluginInterface.
     * 
     * Since PluginInterface is an abstract class, this one have to override 4 functions:
     *  - `pluginProps()` which give to Sielo all informations needed about the plugin.
     *  - `init(InitState state, const QString& settingsPath)` which is called at the loading of the plugin.
     *  - `unload()` which is called when the plugin is unloaded.
     *  - `testPlugin()` who allows Sielo to check if it can load the plugin or not.
     *  
     * Some other function can be overrided. I advice you to check the base "PluginInterface" class or go read 
     * the wiki here : https://github.com/SieloBrowser/SieloBrowser/wiki/%5BFR%5D-2.0-Introduction-:-cr%C3%A9ation-de-plugin
     */
    class ArcScreen: public QObject, public PluginInterface 
    {
        Q_OBJECT
        Q_INTERFACES(Sn::PluginInterface) // Load the interface. It **has to** be "Sn::PluginInterface".
        Q_PLUGIN_METADATA(IID "xyz.doocode.arc.ArcScreen") // Set a unique identifier for your plugin. 

        public:
            /*!
             * Constructor. Don't do anything expensive in constructor! It will be called even if user doesn't 
             * have the plugin allowed.
             */
            ArcScreen();

            // Abstract override

            /*!
             * Set all information about the plugin. Icon is not an obligation.
             */
            PluginProp pluginProp();

            /*! 
             * This function is called right after plugin is loaded it will be called even if we return false 
             * from testPlugin() so it is recommended not to call any Sielo function here
             * 
             * Settings path is PROFILE/extensions (without trailign slash), in this directory you can use global 
             * .ini file for QSettings named "extensions.ini" or create new folder for your plugin and save in it 
             * anything you want
             * 
             * State can be either StartupInitState or LateInitState, and it indicates when the plugin have been 
             * loaded. Currently, it can be from preferences, or automatically at startup.
             * 
             * Plugins are loaded before first BrowserWindow is created.
             * 
             * @param state Indicate when the plugin have been loaded (at startup or after).
             * @param settingsPath Indicate the directory where you can store data.
             */
            void init(InitState state, const QString& settingsPath);

            /*!
             * This function will be called when unloading plugin it will be also called if we return false from 
             * testPlugin().
             */
            void unload();

            /*! 
             * This function is called right after init(). There should be some testing if plugin is loaded 
             * correctly. If this function returns false, plugin is automatically unloaded.
             */
            bool testPlugin();

            // Other override
            /*!
             * This function will be called from Preferences after clicking on Settings button. Settings button 
             * will be enabled if PluginProp.hasSettings == true.
             * @param parent Parent widget.
             */
            void showSettings(QWidget* parent = nullptr);

            /*!
             * Called from WebView when creating context menu.
             * @parma menu The menu where to add actions.
             * @param view The view from where the signal comes.
             * @param result Description of what was is under the cursor (link, image, etc.)
             */
            void populateWebViewMenu(QMenu* menu, WebView* view, const WebHitTestResult& result);

            /*!
             * This function will be called when the user click on an element.
             * @param objName Type of the object who raised the event (Window, WebView, TabsSpace, etc.).
             * @param obj The object itself.
             * @parama event The event.
             */
            bool mousePress(const Application::ObjectName& objName, QObject* obj, QMouseEvent* event);

            QWidget* navigationBarButton(Sn::TabWidget* tabWidget);

            // Custom
        private slots:
            void actionSlot();

        private:
            QPointer<QDialog> m_settings;
            QString m_settingsPath{};

            WebView* m_view{nullptr};

            ArcScreenSideBar* m_sideBar{nullptr};
            QList<ArcScreenToolButton*> m_navigationBarButtons{};
    };
}

#endif // ARCSCREEN_HPP
