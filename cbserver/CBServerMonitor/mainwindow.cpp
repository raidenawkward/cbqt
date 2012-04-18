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
    refreshMenuItemList();
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

QTableWidgetItem* MainWindow::generateTableItem(CBDish &dish, DISH_TABLE_HEADER header)
{
    QString content;
    switch (header)
    {
    case DISH_TABLE_ID:
        content = dish.getId().toString();
    case DISH_TABLE_NAME:
        content = dish.getName();
    case DISH_TABLE_PRICE:
        content = QString::number(dish.getPrice());
    case DISH_TABLE_SCORE:
        content = QString::number(dish.getScore());
    case DISH_TABLE_TAGS:
        content = dish.getTagsSet().toString(CBDISH_TAG_TAGS_SPLITER);
    case DISH_TABLE_SUMMARY:
        content = dish.getSummary();
    case DISH_TABLE_DETAIL:
        content = dish.getDetail();
    case DISH_TABLE_THUMB:
        content = dish.getThumb();
    case DISH_TABLE_PICTURE:
        content = dish.getPicture();
    case DISH_TABLE_UNKNOWN:
    default:
        break;
    }
    QTableWidgetItem *tabItem = new QTableWidgetItem(content);
    tabItem->setTextAlignment(Qt::AlignCenter);

    return tabItem;
}

QString MainWindow::generateTableString(DISH_TABLE_HEADER header)
{
    switch (header)
    {
    case DISH_TABLE_ID:
        return tr("编号");
    case DISH_TABLE_NAME:
        return tr("名称");
    case DISH_TABLE_PRICE:
        return tr("单价");
    case DISH_TABLE_SCORE:
        return tr("评分");
    case DISH_TABLE_TAGS:
        return tr("标签");
    case DISH_TABLE_SUMMARY:
        return tr("简介");
    case DISH_TABLE_DETAIL:
        return tr("详细介绍");
    case DISH_TABLE_THUMB:
        return tr("缩略图");
    case DISH_TABLE_PICTURE:
        return tr("大图片");
    case DISH_TABLE_UNKNOWN:
    default:
        break;
    }

    return QString();
}

void MainWindow::refreshTabWidget()
{
    int rowCount = _menuItemSet.count();
    ui->tableWidget->setRowCount(rowCount);

    for (int i = 0; i < rowCount; ++i)
    {
        CBMenuItem *item = _menuItemSet.get(i);
        if (!item)
            continue;

        CBDish dish = item->getDish();

        for (int j = DISH_TABLE_ID; j < DISH_TABLE_UNKNOWN; ++j)
        {
            QTableWidgetItem *tabItem = generateTableItem(dish, (DISH_TABLE_HEADER)j);
            ui->tableWidget->setItem(i, j, tabItem);
        }
    }
}

void MainWindow::initTabWidget()
{
    QStringList headers;
    for (int i = DISH_TABLE_ID; i < DISH_TABLE_UNKNOWN; ++i)
        headers<<generateTableString((DISH_TABLE_HEADER)i);

    ui->tableWidget->setColumnCount(headers.count());
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

void MainWindow::showEvent(QShowEvent *)
{
    this->refreshTabWidget();
}
