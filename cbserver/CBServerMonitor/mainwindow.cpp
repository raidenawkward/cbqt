#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dishinfodialog.h"
#include "cbdishesscanner.h"
#include "cbmenuitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initTabWidget();
    refreshTabWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAdd_clicked()
{
    DishInfoDialog dialog;
    dialog.exec();
}

void MainWindow::refreshTabWidget()
{
    for (int i = 0; i < 6; ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 0, item);
    }
}

void MainWindow::initTabWidget()
{
    QStringList headers;
    headers<<tr("编号")<<tr("名称")<<tr("单价")<<tr("评分")<<tr("标签")<<tr("简介")<<tr("详细介绍")<<tr("缩略图")<<tr("大图片");
    ui->tableWidget->setColumnCount(headers.count());
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->resizeColumnToContents (0);
}

void MainWindow::refreshMenuItemList()
{
    CBDishesScanner scanner(CBSERVERMONITOR_DISHES_DIR);
    scanner.scan();

    this->_menuItemSet = scanner.getMenuItemSet();
}

void MainWindow::on_buttonEdit_clicked()
{
    DishInfoDialog dialog;
    dialog.exec();
}
