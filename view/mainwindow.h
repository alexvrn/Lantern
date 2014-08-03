#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "view/iviewmain.h"

class MainWindow : public QMainWindow, public IViewMain
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setColor(const QColor&);

protected:
    void paintEvent( QPaintEvent *event );

private:
    QColor color;
};

#endif // MAINWINDOW_H
