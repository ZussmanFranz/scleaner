#include "mainwindow.h"

#include <QApplication>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    // This forces Qt to unmute all debug messages globally
    QLoggingCategory::setFilterRules("*.debug=false\ndefault.debug=true");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
