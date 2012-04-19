#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dishinfodialog.h"
#include "cbdishesscanner.h"
#include "cbmenuitemsset.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _engine(NULL)
{
    ui->setupUi(this);

    initTabWidget();
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
    ui->tableWidget->clear();

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
    dialog.exec();
}

void MainWindow::on_buttonEdit_clicked()
{
    DishInfoDialog dialog;
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
