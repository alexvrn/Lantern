#include "mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QLayout>
#include <QGradient>
#include <QRadialGradient>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    color = Qt::black;
}

MainWindow::~MainWindow()
{
}

void MainWindow::setColor(const QColor& colorLanter)
{
    color = colorLanter;

    repaint();
}

void MainWindow::paintEvent( QPaintEvent * )
{
    QPainter painter( this );

    QRadialGradient radGrad( QPointF(width() / 2.0, height() / 2), qMin( height()/ 2.0, width() / 2.0) );
    radGrad.setColorAt( 0, color );
    radGrad.setColorAt( 1, Qt::gray );

    QBrush brush(radGrad);

    painter.fillRect(rect(), brush);
}
