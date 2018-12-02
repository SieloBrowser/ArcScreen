#pragma once
#ifndef ARCSCREENTOOLBUTTON_H
#define ARCSCREENTOOLBUTTON_H

#include "Utils/ToolButton.hpp"
#include "Widgets/Tab/TabWidget.hpp"

#include "ScreenViewer.hpp"

class ArcScreenToolButton: public Sn::ToolButton 
{
	Q_OBJECT

    public:
        ArcScreenToolButton(Sn::TabWidget* tabWidget, QWidget* parent = nullptr);
        ~ArcScreenToolButton() = default;

    private slots:
        void takeScreenshot();

    private:
        Sn::TabWidget* m_tabWidget{nullptr};
};

#endif // ARCSCREENTOOLBUTTON_H
