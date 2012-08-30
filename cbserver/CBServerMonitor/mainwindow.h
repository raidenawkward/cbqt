#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "cbengine.h"
#include "cbmenuitem.h"
#include "cbglobal.h"

enum DISH_TABLE_HEADER
{
    DISH_TABLE_ID = 0,
    DISH_TABLE_NAME,
    DISH_TABLE_PRICE,
    DISH_TABLE_SCORE,
    DISH_TABLE_TAGS,
    DISH_TABLE_SUMMARY,
    DISH_TABLE_DETAIL,
    DISH_TABLE_THUMB,
    DISH_TABLE_PICTURE,
    DISH_TABLE_UNKNOWN
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setEngine(CBEngine* engine);
    void refreshTabWidget();

protected:
    void showEvent(QShowEvent *);

    static QString generateTableString(DISH_TABLE_HEADER header);
    static QTableWidgetItem* generateTableItem(CBMenuItem *item, DISH_TABLE_HEADER header);

protected slots:
    void slt_menuItemUpdate(CBMenuItem* item);

private slots:
    void on_buttonAdd_clicked();
    void on_buttonEdit_clicked();
    void on_tableWidgetDish_doubleClicked(const QModelIndex &index);
    void on_buttonRefresh_clicked();
    void on_tableWidget_cellDoubleClicked(int, int);
    void on_buttonRemove_clicked();
    void on_buttonExport_clicked();
    void on_pushButtonNewTag_clicked();
    void on_pushButtonDelTag_clicked();
    void on_pushButtonTagUp_clicked();
    void on_pushButtonTagDown_clicked();
    void on_listWidgetLeftButtons_doubleClicked(const QModelIndex &index);
    void on_pushButtonNewLocation_clicked();
    void on_pushButtonDelLocation_clicked();
    void on_pushButtonLocationUp_clicked();
    void on_pushButtonLocationDown_clicked();
    void on_pushButtonTagSettingExport_clicked();
    void on_pushButtonLocationSettingExport_clicked();
    void on_pushButtonResetToDefaultValue_clicked();
    void on_buttonExportSettings_clicked();
    void on_pushButtonDeviceSettingsSave_clicked();
    void on_pushButtonDeviceSettingsRefresh_clicked();

private:
    void initTabWidget();
    void initDeviceCharSetComboBox();
    void refreshMenuItemList();
    bool exportDir(const QString dir);

private:
    Ui::MainWindow *ui;
    CBEngine *_engine;
};

#endif // MAINWINDOW_H
