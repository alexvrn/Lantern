#include "mainwindowpresenter.h"

#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <QFile>

MainWindowPresenter::MainWindowPresenter(IViewMain *view, QObject *parent) :
    QObject(parent)
{
    iview = (IViewMain*)view;

    client = new ServiceClient(this);
    QObject::connect(client, SIGNAL(data(const Package&)), this, SLOT(sltData(const Package&)));
    if(!client->openConnect("127.0.0.1", 9999))
        QMessageBox::information(0, "", "no connect");

    refreshView();
}

MainWindowPresenter::~MainWindowPresenter()
{
}

void MainWindowPresenter::refreshView()
{
    iview->setColor(model.color());
}

void MainWindowPresenter::sltData(const Package& pkg)
{
    model.setPackage(pkg);

    refreshView();
}
