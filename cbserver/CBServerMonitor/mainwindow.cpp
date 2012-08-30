#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dishinfodialog.h"
#include "cbdishesscanner.h"
#include "cbmenuitemsset.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QDir>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _engine(NULL)
{
    ui->setupUi(this);
    initDeviceCharSetComboBox();
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
    ui->tableWidgetDish->clear();
    initTabWidget();

    if (!_engine)
        return;

    if (!_engine->getMenuItemsSet())
        return;

    int rowCount = _engine->getMenuItemsSet()->count();
    ui->tableWidgetDish->setRowCount(rowCount);

    for (int i = 0; i < rowCount; ++i)
    {
        CBMenuItem *item = _engine->getMenuItemsSet()->get(i);
        if (!item)
            continue;

        for (int j = DISH_TABLE_ID; j < DISH_TABLE_UNKNOWN; ++j)
        {
            QTableWidgetItem *tabItem = generateTableItem(item, (DISH_TABLE_HEADER)j);
            tabItem->setToolTip(item->getDish().getName());
            ui->tableWidgetDish->setItem(i, j, tabItem);
        }
    }

    ui->tableWidgetDish->setCurrentCell(0, 0);
}

void MainWindow::initTabWidget()
{
    QStringList headers;
    for (int i = DISH_TABLE_ID; i < DISH_TABLE_UNKNOWN; ++i)
    {
        headers<<generateTableString((DISH_TABLE_HEADER)i);
    }

    ui->tableWidgetDish->setColumnCount(headers.count());
    ui->tableWidgetDish->setHorizontalHeaderLabels(headers);
    ui->tableWidgetDish->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetDish->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetDish->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetDish->setAlternatingRowColors(true);
    ui->tableWidgetDish->resizeColumnToContents (0);
    ui->tableWidgetDish->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

void MainWindow::refreshMenuItemList()
{
    if (_engine)
        _engine->loadMenuItems(CBSERVERMONITOR_DISHES_DIR);
}

void MainWindow::slt_menuItemUpdate(CBMenuItem* item)
{
    if (!item)
        return;

    if (!_engine)
        return;

    _engine->getMenuItemsSet()->add(item);

    QModelIndex index = ui->tableWidgetDish->currentIndex();
    //on_buttonRefresh_clicked();
    ui->tableWidgetDish->setCurrentIndex(index);
    refreshTabWidget();
}

void MainWindow::on_buttonAdd_clicked()
{
    DishInfoDialog dialog;
    dialog.setWindowTitle(tr("添加"));
    dialog.setMenuItem(NULL);
    connect(&dialog,SIGNAL(sig_itemChanged(CBMenuItem*)), this, SLOT(slt_menuItemUpdate(CBMenuItem*)));
    dialog.exec();
}

void MainWindow::on_buttonEdit_clicked()
{
    DishInfoDialog dialog;
    dialog.setWindowTitle(tr("编辑"));
    int index = ui->tableWidgetDish->currentRow();
    CBMenuItem *item = _engine->getMenuItemsSet()->get(index);
    dialog.setMenuItem(item);
    connect(&dialog,SIGNAL(sig_itemChanged(CBMenuItem*)), this, SLOT(slt_menuItemUpdate(CBMenuItem*)));
    dialog.exec();
}

void MainWindow::on_tableWidgetDish_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    on_buttonEdit_clicked();
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
    int index = ui->tableWidgetDish->currentRow();
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
        if (_engine->getMenuItemsSet()->remove(index))
        {
            CBGlobal::removeMenuItem(item);
            this->refreshTabWidget();
        }
    }
}

bool MainWindow::exportDir(const QString dir)
{
    bool res = false;
    QString name = CBGlobal::getFileName(CBSERVERMONITOR_DISHES_DIR);
    qDebug()<<CBGlobal::combinePath(dir, name);
    if (!dir.isEmpty())
    {
        res = CBGlobal::copyDir(CBSERVERMONITOR_DISHES_DIR, CBGlobal::combinePath(dir, name), true);
    }

    return res;
}

void MainWindow::on_buttonExport_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                            tr("选择导出路径"),
                                            tr("."));

    if (path.isEmpty())
        return;

    bool res = exportDir(path);
    if (!res)
    {
        QMessageBox::critical(this,
                              tr("错误"),
                              tr("在导出过程出发生错误"),
                              QMessageBox::Ok);
    }
}

void MainWindow::on_pushButtonNewTag_clicked()
{
    bool ok = false;
    QString tag = QInputDialog::getText(this,
                                tr("添加标签"),
                                tr("新标签名称:"),
                                QLineEdit::Normal,
                                QString(),
                                &ok);

    if (ok)
    {
        ui->listWidgetLeftButtons->addItem(tag);
    }
}

void MainWindow::on_listWidgetLeftButtons_doubleClicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    if (!ui->listWidgetLeftButtons->currentItem())
        return;

    bool ok = false;
    QString text = ui->listWidgetLeftButtons->currentItem()->text();
    QString tag = QInputDialog::getText(this,
                                tr("修改标签"),
                                tr("标签名称:"),
                                QLineEdit::Normal,
                                text,
                                &ok);

    if (ok)
    {
        ui->listWidgetLeftButtons->currentItem()->setText(tag);
    }
}

void MainWindow::on_pushButtonDelTag_clicked()
{
    if (!ui->listWidgetLeftButtons->currentItem())
        return;

    QString content = tr("确定要删除标签\"");
    content += ui->listWidgetLeftButtons->currentItem()->text();
    content += tr("\"吗?");
    QMessageBox::StandardButton res = QMessageBox::question(this,
                                     tr("删除确认"),
                                     content,
                                     QMessageBox::Yes | QMessageBox::No,
                                     QMessageBox::Yes);

    if(res == QMessageBox::Yes)
    {
        ui->listWidgetLeftButtons->takeItem(ui->listWidgetLeftButtons->currentIndex().row());
    }
}

void MainWindow::on_pushButtonTagUp_clicked()
{
    QListWidgetItem *currentItem = ui->listWidgetLeftButtons->currentItem();
    if (currentItem == NULL)
        return;

    int row = ui->listWidgetLeftButtons->currentRow();
    if (row == 0)
        return;

    ui->listWidgetLeftButtons->takeItem(row);
    ui->listWidgetLeftButtons->insertItem(--row, currentItem);
    ui->listWidgetLeftButtons->setCurrentRow(row);
}

void MainWindow::on_pushButtonTagDown_clicked()
{
    QListWidgetItem *currentItem = ui->listWidgetLeftButtons->currentItem();
    if (currentItem == NULL)
        return;

    int row = ui->listWidgetLeftButtons->currentRow();
    if (row == ui->listWidgetLeftButtons->count() - 1)
        return;

    ui->listWidgetLeftButtons->takeItem(row);
    ui->listWidgetLeftButtons->insertItem(++row, currentItem);
    ui->listWidgetLeftButtons->setCurrentRow(row);
}

void MainWindow::initDeviceCharSetComboBox()
{
    ui->comboBoxDeviceCharSet->clear();
    for (size_t i = 0; i < CB_DEVICE_CHARSET_COUNT; ++i) {
        if (s_cb_device_charset[i] != NULL)
            ui->comboBoxDeviceCharSet->addItem(QString(s_cb_device_charset[i]));
        else
            break;
    }
    ui->comboBoxDeviceCharSet->setEditText(CB_DEFAULT_DEVICE_CHARSET);
}

void MainWindow::on_pushButtonNewLocation_clicked()
{
    bool ok = false;
    QString tag = QInputDialog::getText(this,
                                tr("添加标签"),
                                tr("新标签名称:"),
                                QLineEdit::Normal,
                                QString(),
                                &ok);

    if (ok)
    {
        ui->listWidgetLocations->addItem(tag);
    }
}

void MainWindow::on_pushButtonDelLocation_clicked()
{
    if (!ui->listWidgetLocations->currentItem())
        return;

    QString content = tr("确定要删除标签\"");
    content += ui->listWidgetLocations->currentItem()->text();
    content += tr("\"吗?");
    QMessageBox::StandardButton res = QMessageBox::question(this,
                                     tr("删除确认"),
                                     content,
                                     QMessageBox::Yes | QMessageBox::No,
                                     QMessageBox::Yes);

    if(res == QMessageBox::Yes)
    {
        ui->listWidgetLocations->takeItem(ui->listWidgetLocations->currentIndex().row());
    }
}

void MainWindow::on_pushButtonLocationUp_clicked()
{
    QListWidgetItem *currentItem = ui->listWidgetLocations->currentItem();
    if (currentItem == NULL)
        return;

    int row = ui->listWidgetLocations->currentRow();
    if (row == 0)
        return;

    ui->listWidgetLocations->takeItem(row);
    ui->listWidgetLocations->insertItem(--row, currentItem);
    ui->listWidgetLocations->setCurrentRow(row);
}

void MainWindow::on_pushButtonLocationDown_clicked()
{
    QListWidgetItem *currentItem = ui->listWidgetLocations->currentItem();
    if (currentItem == NULL)
        return;

    int row = ui->listWidgetLocations->currentRow();
    if (row == ui->listWidgetLocations->count() - 1)
        return;

    ui->listWidgetLocations->takeItem(row);
    ui->listWidgetLocations->insertItem(++row, currentItem);
    ui->listWidgetLocations->setCurrentRow(row);
}

void MainWindow::on_pushButtonTagSettingExport_clicked()
{

}

void MainWindow::on_pushButtonLocationSettingExport_clicked()
{

}

void MainWindow::on_pushButtonResetToDefaultValue_clicked()
{
    QString content = tr("确定恢复默认设置， 并将标签与位置信息恢复到修改前吗?");
    QMessageBox::StandardButton res = QMessageBox::question(this,
                                     tr("确认"),
                                     content,
                                     QMessageBox::Yes | QMessageBox::No,
                                     QMessageBox::Yes);

    if(res != QMessageBox::Yes)
        return;

    ui->spinBoxFontSizeLeftButton->setValue(CB_DEFAULT_LEFT_BUTTON_FONT_SIZE);
    ui->spinBoxMenuItemCol->setValue(CB_DEFAULT_ITEM_COL);
    ui->spinBoxMaxItemOrderedCount->setValue(CB_DEFAULT_DISH_ITEM_ORDER_MAX_COUNT);
    initDeviceCharSetComboBox();
}

void MainWindow::on_buttonExportSettings_clicked()
{

}

void MainWindow::on_pushButtonDeviceSettingsSave_clicked()
{

}

void MainWindow::on_pushButtonDeviceSettingsRefresh_clicked()
{

}

void MainWindow::refreshDeviceSettings()
{

}

bool MainWindow::loadDeviceSettings()
{
    return false;
}

bool MainWindow::saveDeviceSettings()
{
    return false;
}
