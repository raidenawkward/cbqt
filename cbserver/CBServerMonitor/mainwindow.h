#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cbmenuitemsset.h"

#define CBSERVERMONITOR_DISHES_DIR "dishes"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void refreshTabWidget();
    
private slots:
    void on_buttonAdd_clicked();

    void on_buttonEdit_clicked();

private:
    void initTabWidget();
    void refreshMenuItemList();

private:
    Ui::MainWindow *ui;
    CBMenuItemsSet _menuItemSet;
};

#endif // MAINWINDOW_H
