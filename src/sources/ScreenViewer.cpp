#include "ScreenViewer.hpp"
#include "Skin.hpp"

ScreenViewer::ScreenViewer(QWidget *parent) :
    QMainWindow(parent)
{
	setWindowTitle(tr("Screenshot"));
	setWindowIcon(QIcon(":images/screen.png"));

    Skin::init(this);
    QGraphicsScene *scene = new QGraphicsScene;

    m_item = new QGraphicsPixmapItem;
    m_item->setPixmap(QPixmap(":images/background.png"));
    scene->addItem(m_item);

    m_view = new QGraphicsView;
    m_view->setScene(scene);
    m_view->scale(.75,.75);

    genActs();
    genToolBar();

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->setSpacing(0);
    centralLayout->addWidget(m_toolBar);
    centralLayout->addWidget(m_view);

    QWidget *center = new QWidget;
    center->setLayout(centralLayout);

    setCentralWidget(center);
}

void ScreenViewer::genActs()
{
    m_actSave = new QAction(QIcon(":images/save.png"), tr("Save screenshot"),this);
    m_actSave->setShortcut(QKeySequence::Save);
    connect(m_actSave,SIGNAL(triggered()),this,SLOT(saveFile()));

    m_actZoomIn = new QAction(QIcon(":images/zoom-in.png"), tr("Zoom +"),this);
    m_actZoomIn->setShortcut(QKeySequence("Ctrl++"));
    connect(m_actZoomIn,SIGNAL(triggered()),this,SLOT(editZoom()));

    m_actZoomOut = new QAction(QIcon(":images/zoom-out.png"), tr("Zoom -"),this);
    m_actZoomOut->setShortcut(QKeySequence("Ctrl+-"));
    connect(m_actZoomOut,SIGNAL(triggered()),this,SLOT(editZoom()));
}

void ScreenViewer::genToolBar()
{
    m_toolBar = new QToolBar;
    m_toolBar->setIconSize(QSize(18,18));

    m_toolBar->addAction(m_actSave);

    QWidget *spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Ignored);
    m_toolBar->addWidget(spacer);

    m_sliderZoom = new QSlider(Qt::Horizontal);
    m_sliderZoom->setMaximumWidth(200);
    m_sliderZoom->setMinimum(0);
    m_sliderZoom->setMaximum(200);
    m_sliderZoom->setValue(75);
    m_sliderZoom->setTickInterval(50);
    m_sliderZoom->setPageStep(50);
    m_sliderZoom->setSingleStep(50);
    m_sliderZoom->setTickPosition(QSlider::TicksBothSides);
    connect(m_sliderZoom,SIGNAL(valueChanged(int)),this,SLOT(updateZoom()));

    m_lblZoom = new QLabel("75%");

    m_toolBar->addAction(m_actZoomOut);
    m_toolBar->addWidget(m_sliderZoom);
    m_toolBar->addAction(m_actZoomIn);
    m_toolBar->addWidget(m_lblZoom);
}

void ScreenViewer::setScreen(QPixmap screen, QString name)
{
    m_image = screen;
    m_fileName = name;
    m_isSaved = false;

    m_item->setPixmap(screen);
    m_view->setSceneRect(m_item->boundingRect());

    QPropertyAnimation *animation = new QPropertyAnimation(m_sliderZoom,"value");
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->setStartValue(100);
    animation->setEndValue(75);
    animation->start();
}

void ScreenViewer::updateZoom()
{
    double zoom(m_sliderZoom->value()*.01);
    m_lblZoom->setText(QString::number(m_sliderZoom->value())+"%");

    m_view->resetMatrix();
    m_view->scale(zoom,zoom);
}

void ScreenViewer::editZoom()
{
    int range(25);

    if(sender()==m_actZoomIn)
        m_sliderZoom->setValue(m_sliderZoom->value()+range);
    else if(sender()==m_actZoomOut)
        m_sliderZoom->setValue(m_sliderZoom->value()-range);
}

void ScreenViewer::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save Screenshot"), QString(QDir::homePath()+QDir::separator()+m_fileName), tr("PNG Files (*.png);;BMP Files (*.bmp);;GIF Files (*.gif);;All Files (*)"));
    if (!path.isEmpty())
    {
        QFile file(path);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            m_image.save(path);
            m_isSaved = true;
        }
    }
}
