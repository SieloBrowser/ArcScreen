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

#include "ArcScreenSideBar.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

ArcScreenSideBar::ArcScreenSideBar(QObject* parent) :
	SideBarInterface(parent)
{
	// Empty
}

QString ArcScreenSideBar::title() const
{
	return tr("ArcScreen Siebar");
}

QAction* ArcScreenSideBar::createMenuAction()
{
	/*
	 * The action must be parented to some object from plugin,
	 * otherwise there may be a crash when unloading the plugin.
	 */
	QAction* action{new QAction(tr("ArcScreen Sidebar"), this)};
	action->setCheckable(true);

	return action;
}

QWidget* ArcScreenSideBar::createSideBarWidget(Sn::TabWidget* tabWidget)
{
	QWidget* widget{new QWidget()};
	QPushButton* button{new QPushButton("ArcScreen Plugin v1.0.0")};
	QLabel* label{new QLabel()};

    label->setPixmap(QPixmap(":images/screen.png"));

	QVBoxLayout* layout{new QVBoxLayout(widget)};
	layout->addWidget(label);
	layout->addWidget(button);

	return widget;
}
