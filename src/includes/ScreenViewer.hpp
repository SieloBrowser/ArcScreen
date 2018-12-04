#ifndef SCREENVIEWER_H
#define SCREENVIEWER_H

#include <QtWidgets>

class ScreenViewer: public QMainWindow
{
    Q_OBJECT

    public:
        ScreenViewer(QWidget *parent = 0);

    public slots:
        void setScreen(QPixmap screen, QString name);

    private slots:
        void genActs();
        void genToolBar();

        void updateZoom();
        void editZoom();
        void saveFile();

    private:
        QToolBar *m_toolBar;

        QSlider *m_sliderZoom;
        QLabel *m_lblZoom;
        QGraphicsView *m_view;
        QPixmap m_image;
        QString m_fileName;
        bool m_isSaved;

        QAction *m_actSave;
        QAction *m_actZoomIn;
        QAction *m_actZoomOut;

        QGraphicsPixmapItem *m_item;
};

#endif // SCREENVIEWER_H
