#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );
    MainWindow w;
    w.show();

    QPalette palette;

    palette.setColor( QPalette::Window, Qt::black );
    palette.setColor( QPalette::WindowText, Qt::white );
    palette.setColor( QPalette::Base, QColor( 15, 15, 15 ) );
    palette.setColor( QPalette::AlternateBase, QColor( 53, 53, 53 ) );
    palette.setColor( QPalette::ToolTipBase, Qt::white );
    palette.setColor( QPalette::ToolTipText, Qt::white );
    palette.setColor( QPalette::Text, Qt::white );
    palette.setColor( QPalette::Button, QColor( 53, 53, 53) );
    palette.setColor( QPalette::ButtonText, Qt::white );
    palette.setColor( QPalette::BrightText, Qt::red );

    palette.setColor( QPalette::Highlight, QColor(142,45,197).lighter() );
    palette.setColor( QPalette::HighlightedText, Qt::black );

    palette.setColor( QPalette::Disabled, QPalette::Text, Qt::darkGray );
    palette.setColor( QPalette::Disabled, QPalette::ButtonText, Qt::darkGray );

    a.setPalette( palette );

    return a.exec();
}
