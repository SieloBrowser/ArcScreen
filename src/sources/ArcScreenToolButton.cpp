#include "ArcScreenToolButton.hpp"
#include "Web/Tab/WebTab.hpp"
#include "Web/Tab/TabbedWebView.hpp"

ArcScreenToolButton::ArcScreenToolButton(Sn::TabWidget* tabWidget, QWidget* parent) :
	Sn::ToolButton(parent),
	m_tabWidget(tabWidget)
{
	setObjectName("navigation-button-view-history");
	setToolTip(tr("Take screenshot"));
    setIcon(QIcon(":images/arc.png"));
	setToolButtonStyle(Qt::ToolButtonIconOnly);
	//m_buttonViewHistory->setToolBarButtonLook(true);
	setAutoRaise(true);
	setFocusPolicy(Qt::NoFocus);

	connect(this, &Sn::ToolButton::clicked, this, &ArcScreenToolButton::takeScreenshot);
}

void ArcScreenToolButton::takeScreenshot()
{
    // Take screenshot
    Sn::WebTab *wt = qobject_cast<Sn::WebTab *>(m_tabWidget->currentWidget());

    QPixmap pixmap(wt->width(), wt->height());
    QPainter painter(&pixmap); // msg dans debug ?
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    wt->render(&painter);

    ScreenViewer *sv = new ScreenViewer;
    sv->setScreen(pixmap, wt->webView()->title());
    m_tabWidget->addApplication(sv);
}
