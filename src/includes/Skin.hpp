#ifndef SKIN_HPP
#define SKIN_HPP

#include <QtWidgets>

class Skin
{
    public slots:
        static void init(QWidget *parent = nullptr);

    private slots:
        static QString readFile(QString fileName);
        static QString parseCSS(const QString css);
        static void loadFonts();
};

#endif // SKIN_HPP
