#include "view/mainwindow.h"
#include "presenter/mainwindowpresenter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow viewMain;
    MainWindowPresenter presenterMain(&viewMain);

    viewMain.show();

    return a.exec();
}
