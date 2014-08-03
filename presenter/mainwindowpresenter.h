#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H

#include <QObject>
#include "service/serviceclient.h"
#include "model/mainwindowmodel.h"
#include "view/iviewmain.h"

class MainWindowPresenter : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowPresenter(IViewMain *view, QObject *parent = 0);
    ~MainWindowPresenter();

public slots:
    void sltData(const Package&);

private:
    void refreshView();

private:
    IViewMain* iview;
    MainWindowModel model;
    ServiceClient * client;
};

#endif // MAINWINDOWPRESENTER_H
