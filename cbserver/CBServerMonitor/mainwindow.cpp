#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dishinfodialog.h"
#include "cbdishesscanner.h"
#include "cbmenuitemsset.h"

#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _engine(NULL)
{
    ui->setupUi(this);
    refreshMenuItemList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setEngine(CBEngine* engine)
{
    _engine = engine;
}

void MainWindow::showEvent(QShowEvent *)
{
    this->refreshTabWidget();
}

QTableWidgetItem* MainWindow::generateTableItem(CBMenuItem *item, DISH_TABLE_HEADER header)
{
    if (!item)
        return NULL;

    CBDish dish = item->getDish();
    QString content;

    switch (header)
    {
    case DISH_TABLE_ID:
        content = dish.getId().toString();
        break;
    case DISH_TABLE_NAME:
        content = dish.getName();
        break;
    case DISH_TABLE_PRICE:
        content = QString::number(dish.getPrice());
        break;
    case DISH_TABLE_SCORE:
        content = QString::number(dish.getScore());
        break;
    case DISH_TABLE_TAGS:
        content = dish.getTagsSet().toString(CBDISH_TAG_TAGS_SPLITER);
        break;
    case DISH_TABLE_SUMMARY:
        content = dish.getSummary();
        break;
    case DISH_TABLE_DETAIL:
        content = dish.getDetail();
        break;
    case DISH_TABLE_THUMB:
        content = dish.getThumb();
        break;
    case DISH_TABLE_PICTURE:
        content = dish.getPicture();
        break;
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
    QString res = QString();
    switch (header)
    {
    case DISH_TABLE_ID:
        res = tr("编号");
        break;
    case DISH_TABLE_NAME:
        res = tr("名称");
        break;
    case DISH_TABLE_PRICE:
        res = tr("单价");
        break;
    case DISH_TABLE_SCORE:
        res = tr("评分");
        break;
    case DISH_TABLE_TAGS:
        res = tr("标签");
        break;
    case DISH_TABLE_SUMMARY:
        res = tr("简介");
        break;
    case DISH_TABLE_DETAIL:
        res = tr("详细介绍");
        break;
    case DISH_TABLE_THUMB:
        res = tr("缩略图");
        break;
    case DISH_TABLE_PICTURE:
        res = tr("大图片");
        break;
    case DISH_TABLE_UNKNOWN:
    default:
        break;
    }

    return res;
}

void MainWindow::refreshTabWidget()
{
    ui->tableWidget->clear();
    initTabWidget();

    if (!_engine)
        return;

    if (!_engine->getMenuItemsSet())
        return;

    int rowCount = _engine->getMenuItemsSet()->count();
    ui->tableWidget->setRowCount(rowCount);

    for (int i = 0; i < rowCount; ++i)
    {
        CBMenuItem *item = _engine->getMenuItemsSet()->get(i);
        if (!item)
            continue;

        for (int j = DISH_TABLE_ID; j < DISH_TABLE_UNKNOWN; ++j)
        {
            QTableWidgetItem *tabItem = generateTableItem(item, (DISH_TABLE_HEADER)j);
            ui->tableWidget->setItem(i, j, tabItem);
        }
    }

    ui->tableWidget->setCurrentCell(0, 0);
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
    if (_engine)
        _engine->loadMenuItems(CBSERVERMONITOR_DISHES_DIR);
}

void MainWindow::on_buttonAdd_clicked()
{
    DishInfoDialog dialog;
    dialog.setWindowTitle(tr("添加"));
    dialog.exec();
}

void MainWindow::on_buttonEdit_clicked()
{
    DishInfoDialog dialog;
    dialog.setWindowTitle(tr("编辑"));
    int index = ui->tableWidget->currentRow();
    CBMenuItem *item = _engine->getMenuItemsSet()->get(index);
    dialog.setMenuItem(item);
    dialog.exec();
}

void MainWindow::on_buttonRefresh_clicked()
{
    refreshMenuItemList();
    refreshTabWidget();
}

void MainWindow::on_tableWidget_cellDoubleClicked(int, int)
{
    on_buttonEdit_clicked();
}

void MainWindow::on_buttonRemove_clicked()
{
    int index = ui->tableWidget->currentRow();
    CBMenuItem *item = _engine->getMenuItemsSet()->get(index);

    QString content = tr("确定要删除\"");
    content += item->getDish().getName();
    content += tr("\"的信息?");
    QMessageBox::StandardButton res = QMessageBox::question(this,
                                     tr("删除确认"),
                                     content,
                                     QMessageBox::Yes | QMessageBox::No,
                                     QMessageBox::Yes);

    if(res == QMessageBox::Yes)
    {

    }
}
