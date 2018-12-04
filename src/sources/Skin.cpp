#include "Skin.hpp"

void Skin::init(QWidget *parent)
{
    // Loading fonts
    Skin::loadFonts();

    // Loading & parsing CSS
    QString css = Skin::readFile(":/skin/main.css");
    parent->setStyleSheet(Skin::parseCSS(css));
}

QString Skin::readFile(QString fileName)
{
    QFile file;
    file.setFileName(QString(fileName));
    QString text = "";
    if(file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        text = file.readAll();
        file.close();
    }
    else
        qDebug()<< "Skin: Unable to open file '"+fileName+"'";

    return text;
}

QString Skin::parseCSS(const QString css)
{
    QColor themeColor = QColor(0,100,177);
    QString res = css;

    // Parsing for .themeColor(param: value)
    QRegExp rx("\\.themeColor\\(([\\w]+): ?([\\w]+)\\)"); //          \.themeColor\(([\w]+): ?([\w]+)\)
    while (rx.indexIn(res, 0) != -1) {
        QString arg = rx.cap(1);
        QString val = rx.cap(2);
        if(arg.compare("light"))
            res.replace(QRegExp("\\.themeColor\\("+arg+": ?"+val+"\\)"), themeColor.lighter(100+val.toInt()).name());
        else if(arg.compare("dark"))
            res.replace(QRegExp("\\.themeColor\\("+arg+": ?"+val+"\\)"), themeColor.lighter(100-val.toInt()).name());
    }

    res.replace(".themeColor", themeColor.name());
    return res;
}

void Skin::loadFonts()
{
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-Black.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-BlackItalic.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-Bold.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-BoldItalic.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-ExtraBold.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-ExtraBoldItalic.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-ExtraLight.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-ExtraLightItalic.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-Italic.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-Light.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-LightItalic.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-Medium.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-MediumItalic.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-Regular.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-RegularItalic.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-SemiBold.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-SemiBoldItalic.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-Thin.ttf");
    QFontDatabase::addApplicationFont("://font/Montserrat/Montserrat-ThinItalic.ttf");
}
