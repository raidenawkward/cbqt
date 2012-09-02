#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dishinfodialog.h"
#include "cbdishesscanner.h"
#include "cbmenuitemsset.h"
#include "cbsetting.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QDir>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _engine(NULL),
    _settingsHasChanged(false),
    _settingsLeftButton(NULL),
    _settingsLocation(NULL),
    _settingsDeviceApp(NULL)
{
    ui->setupUi(this);
    refreshMenuItemList();

    connect(ui->actionMenuFileExportAll, SIGNAL(triggered()), this, SLOT(slt_menuFileExportAllTriggered()));

    connect(ui->actionMenuOrder, SIGNAL(triggered()), this, SLOT(slt_menuOrderTriggered()));

    connect(ui->actionMenuDish, SIGNAL(triggered()), this, SLOT(slt_menuDishTriggered()));
    connect(ui->actionMenuDishExport, SIGNAL(triggered()), this, SLOT(slt_menuDishExportTriggered()));

    connect(ui->actionMenuDevice, SIGNAL(triggered()), this, SLOT(slt_menuDeviceTriggered()));
    connect(ui->actionMenuDeviceExport, SIGNAL(triggered()), this, SLOT(slt_menuDeviceExportTriggered()));

    connect(ui->actionMenuPC, SIGNAL(triggered()), this, SLOT(slt_menuPCTriggered()));

    connect(ui->actionMenuExportDishes, SIGNAL(triggered()), this, SLOT(slt_menuDishExportTriggered()));
    connect(ui->actionMenuExportSettings, SIGNAL(triggered()), this, SLOT(slt_menuDeviceExportTriggered()));
    connect(ui->actionMenuExportExportAll, SIGNAL(triggered()), this, SLOT(slt_menuFileExportAllTriggered()));

    connect(ui->actionMenuHelp, SIGNAL(triggered()), this, SLOT(slt_menuHelpTriggered()));
    connect(ui->actionMenuHelp, SIGNAL(triggered()), this, SLOT(slt_menuAboutTriggered()));
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
    refreshTabWidget();
    initTabWidgetDeviceSettings();

    slt_setSettingsHasBeenChangedStatus(false);
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
    initTabWidgetDish();

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

void MainWindow::initTabWidgetDish()
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
    DishInfoDialog dialog(_engine);
    dialog.setWindowTitle(tr("添加"));
    dialog.setMenuItem(NULL);
    connect(&dialog,SIGNAL(sig_itemChanged(CBMenuItem*)), this, SLOT(slt_menuItemUpdate(CBMenuItem*)));
    dialog.exec();
}

void MainWindow::on_buttonEdit_clicked()
{
    DishInfoDialog dialog(_engine);
    dialog.setWindowTitle(tr("编辑"));
    int index = ui->tableWidgetDish->currentRow();
    CBMenuItem *item = _engine->getMenuItemsSet()->get(index);
    dialog.setMenuItem(item);
    connect(&dialog,SIGNAL(sig_itemChanged(CBMenuItem*)), this, SLOT(slt_menuItemUpdate(CBMenuItem*)));
    dialog.exec();
}

void MainWindow::on_buttonRefresh_clicked()
{
    refreshMenuItemList();
    refreshTabWidget();
}

void MainWindow::on_tableWidgetDish_cellDoubleClicked(int, int)
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

bool MainWindow::exportDishDir(const QString &dir)
{
    bool res = false;
    QString name = CBGlobal::getFileName(CBSERVERMONITOR_DISHES_DIR);

    if (!dir.isEmpty())
    {
        res = CBGlobal::copyDir(CBSERVERMONITOR_DISHES_DIR, CBGlobal::combinePath(dir, name), true);
    }

    return res;
}

bool MainWindow::exportLeftButtonSettingFile(const QString &dir)
{
    bool res = false;

    QString fileName = CBGlobal::getFileName(ui->lineEditTagSettingFileName->text().trimmed());
    QString source = CBGlobal::combinePath(ui->lineEditSettingsDir->text().trimmed(), fileName);

    if (!dir.isEmpty())
    {
        res = CBGlobal::copyFile(source, CBGlobal::combinePath(dir, fileName), true);
    }

    return res;
}

bool MainWindow::exportLocationsSettingFile(const QString &dir)
{
    bool res = false;

    QString fileName = CBGlobal::getFileName(ui->lineEditLocationSettingFileName->text().trimmed());
    QString source = CBGlobal::combinePath(ui->lineEditSettingsDir->text().trimmed(), fileName);

    if (!dir.isEmpty())
    {
        res = CBGlobal::copyFile(source, CBGlobal::combinePath(dir, fileName), true);
    }

    return res;
}

bool MainWindow::exportSettingsDir(const QString &dir)
{
    bool res = false;
    QString name = CBGlobal::getFileName(ui->lineEditSettingsDir->text().trimmed());
    QString source = name;

    if (!dir.isEmpty())
    {
        res = CBGlobal::copyDir(source, CBGlobal::combinePath(dir, name), true);
    }

    return res;
}

bool MainWindow::exportAll(const QString &dir)
{
    if (dir.isEmpty())
        return false;

    QString rootDirName = CBGlobal::getFileName(_settingsDeviceApp->get(CB_SETTINGS_SOURCE_DIR));
    QString targetDir = CBGlobal::combinePath(dir, rootDirName);

    if (!CBGlobal::mkdir_P(targetDir))
        return false;

    if (!exportSettingsDir(targetDir))
        return false;

    if (!exportDishDir(targetDir))
        return false;

    return true;
}

void MainWindow::on_buttonExport_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                            tr("选择导出路径"),
                                            tr("."));

    if (path.isEmpty())
        return;

    bool res = exportDishDir(path);
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
        slt_settingsHasBeenChanged();
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
        slt_settingsHasBeenChanged();
    }
}

void MainWindow::on_listWidgetLocations_doubleClicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    if (!ui->listWidgetLocations->currentItem())
        return;

    bool ok = false;
    QString text = ui->listWidgetLocations->currentItem()->text();
    QString tag = QInputDialog::getText(this,
                                tr("修改位置"),
                                tr("位置名称:"),
                                QLineEdit::Normal,
                                text,
                                &ok);

    if (ok)
    {
        ui->listWidgetLocations->currentItem()->setText(tag);
        slt_settingsHasBeenChanged();
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
        slt_settingsHasBeenChanged();
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

    slt_settingsHasBeenChanged();
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

    slt_settingsHasBeenChanged();
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
    ui->comboBoxDeviceCharSet->setEditText(CB_SETTINGS_XML_ENCODING_VAL);
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
        slt_settingsHasBeenChanged();
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
        slt_settingsHasBeenChanged();
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

    slt_settingsHasBeenChanged();
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

    slt_settingsHasBeenChanged();
}

void MainWindow::on_pushButtonTagSettingExport_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                            tr("选择导出路径"),
                                            tr("."));

    if (path.isEmpty())
        return;

    bool res = exportLeftButtonSettingFile(path);
    if (!res)
    {
        QMessageBox::critical(this,
                              tr("错误"),
                              tr("在导出过程出发生错误"),
                              QMessageBox::Ok);
    }
}

void MainWindow::on_pushButtonLocationSettingExport_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                            tr("选择导出路径"),
                                            tr("."));

    if (path.isEmpty())
        return;

    bool res = exportLocationsSettingFile(path);
    if (!res)
    {
        QMessageBox::critical(this,
                              tr("错误"),
                              tr("在导出过程出发生错误"),
                              QMessageBox::Ok);
    }
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

    ui->spinBoxFontSizeLeftButton->setValue(QString(CB_SETTINGS_LEFT_BUTTON_TEXT_SIZE_VAL).toInt());
    ui->spinBoxMenuItemCol->setValue(QString(CB_SETTINGS_GRIDVIEW_COLUMN_COUNT_VAL).toInt());
    ui->spinBoxMaxItemOrderedCount->setValue(QString(CB_SETTINGS_ORDERING_DIALOG_MAX_ITEM_COUNT_VAL).toInt());
    initDeviceCharSetComboBox();

    loadLeftButtonTags();
    loadLocationTags();
    loadDeviceAppSettings();

    slt_setSettingsHasBeenChangedStatus(false);
}

void MainWindow::on_buttonExportSettings_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                            tr("选择导出路径"),
                                            tr("."));

    if (path.isEmpty())
        return;

    bool res = exportSettingsDir(path);
    if (!res)
    {
        QMessageBox::critical(this,
                              tr("错误"),
                              tr("在导出过程出发生错误"),
                              QMessageBox::Ok);
    }
}

void MainWindow::on_pushButtonDeviceSettingsSave_clicked()
{
    if (!saveDeviceSettings())
        return;

    slt_setSettingsHasBeenChangedStatus(false);
}

void MainWindow::refreshDeviceSettings()
{

}

bool MainWindow::loadDeviceSettings()
{
    if (!loadLeftButtonTags())
        qDebug()<<"error when loading left button tags";

    if (!loadLocationTags())
        qDebug()<<"error when loading locations";

    if (!loadDeviceAppSettings())
        qDebug()<<"error when loading device settings";

    QDir dirSettings(CB_SETTINGS_SOURCE_DIR_SETTINGS_VAL);
    if (!dirSettings.exists())
    {
        qDebug()<<"settings dir not exists, saving a default copy";
        saveDeviceSettings();
        return true;
    }

    return true;
}

bool MainWindow::saveDeviceSettings()
{
    if (!_settingsHasChanged)
    {
        QDir dirSettings(CB_SETTINGS_SOURCE_DIR_SETTINGS_VAL);
        if (dirSettings.exists())
            return true;
    }

    if (!saveLeftButtonTags())
        return false;

    if (!saveLocationTags())
        return false;

    if (!saveDeviceAppSettings())
        return false;

    _settingsHasChanged = false;

    return true;
}

bool MainWindow::loadLeftButtonTags()
{
    ui->listWidgetLeftButtons->clear();

    if (_settingsLeftButton == NULL)
    {
        QString settingFilePath = ui->lineEditSettingsDir->text().trimmed()
                + QString(CBPATH_SPLITOR)
                + ui->lineEditTagSettingFileName->text().trimmed();
        _settingsLeftButton = new CBLeftButtonSetting();
        _settingsLeftButton->setSettingPath(settingFilePath);
        _settingsLeftButton->setSettingCodec(CB_DEFAULT_XML_CODED);
    }

    if (!_settingsLeftButton->load())
        return false;

    QStringList leftButtonTags = _settingsLeftButton->getTags();

    for (int i = 0; i < leftButtonTags.count(); ++i)
        ui->listWidgetLeftButtons->addItem(leftButtonTags.at(i));

    return true;
}

bool MainWindow::saveLeftButtonTags()
{
    if (_settingsLeftButton == NULL)
        return false;

    QStringList leftButtonTags;
    for (int i = 0; i < ui->listWidgetLeftButtons->count(); ++i)
        leftButtonTags.append(ui->listWidgetLeftButtons->item(i)->text().trimmed());
    _settingsLeftButton->setTags(leftButtonTags);

    if (!_settingsLeftButton->save())
        return false;

    return true;
}

bool MainWindow::loadLocationTags()
{
    ui->listWidgetLocations->clear();

    if (_settingsLocation == NULL)
    {
        QString settingFilePath = ui->lineEditSettingsDir->text().trimmed()
                + QString(CBPATH_SPLITOR)
                + ui->lineEditLocationSettingFileName->text().trimmed();
        _settingsLocation = new CBLocationSettings();
        _settingsLocation->setSettingPath(settingFilePath);
        _settingsLocation->setSettingCodec(CB_DEFAULT_XML_CODED);
    }

    if (!_settingsLocation->load())
        return false;

    QStringList locationTags = _settingsLocation->getTags();

    for (int i = 0; i < locationTags.count(); ++i)
        ui->listWidgetLocations->addItem(locationTags.at(i));

    return true;
}

bool MainWindow::saveLocationTags()
{
    if (_settingsLocation == NULL)
        return false;

    QStringList locationTags;
    for (int i = 0; i < ui->listWidgetLocations->count(); ++i)
        locationTags.append(ui->listWidgetLocations->item(i)->text().trimmed());
    _settingsLocation->setTags(locationTags);

    if (!_settingsLocation->save())
        return false;

    return true;
}

bool MainWindow::loadDeviceAppSettings()
{
    if (_settingsDeviceApp == NULL)
    {
        QString settingFilePath = ui->lineEditSettingsDir->text().trimmed()
                + QString(CBPATH_SPLITOR)
                + ui->lineEditSettingsDeviceFile->text().trimmed();
        _settingsDeviceApp = new CBDeviceAppSettings();
        _settingsDeviceApp->setSettingPath(settingFilePath);
        _settingsDeviceApp->setSettingCodec(CB_DEFAULT_XML_CODED);
    }

    if (!_settingsDeviceApp->load())
        return false;

    ui->spinBoxFontSizeLeftButton->setValue(_settingsDeviceApp->get(CB_SETTINGS_LEFT_BUTTON_TEXT_SIZE).toInt());
    ui->spinBoxMenuItemCol->setValue(_settingsDeviceApp->get(CB_SETTINGS_GRIDVIEW_COLUMN_COUNT).toInt());
    ui->spinBoxMaxItemOrderedCount->setValue(_settingsDeviceApp->get(CB_SETTINGS_ORDERING_DIALOG_MAX_ITEM_COUNT).toInt());
    for (int i = 0; i < ui->comboBoxDeviceCharSet->count(); ++i)
    {
        if (ui->comboBoxDeviceCharSet->itemText(i) == _settingsDeviceApp->get(CB_SETTINGS_XML_ENCODING))
        {
            ui->comboBoxDeviceCharSet->setCurrentIndex(i);
        }
    }

    return true;
}

bool MainWindow::saveDeviceAppSettings()
{
    if (_settingsDeviceApp == NULL)
        return false;

    _settingsDeviceApp->set(QString(CB_SETTINGS_XML_ENCODING), ui->comboBoxDeviceCharSet->currentText().trimmed());
    _settingsDeviceApp->set(QString(CB_SETTINGS_SOURCE_DIR), QString(CB_SETTINGS_SOURCE_DIR_VAL));
    _settingsDeviceApp->set(QString(CB_SETTINGS_SOURCE_DIR_DISHES), CBGlobal::combinePath(QString(CB_SETTINGS_SOURCE_DIR_VAL), QString(CB_SETTINGS_SOURCE_DIR_DISHES_VAL)));
    _settingsDeviceApp->set(QString(CB_SETTINGS_SOURCE_DIR_ORDERS), CBGlobal::combinePath(QString(CB_SETTINGS_SOURCE_DIR_VAL), QString(CB_SETTINGS_SOURCE_DIR_ORDERS_VAL)));

    QString settingsDir = CBGlobal::combinePath(QString(CB_SETTINGS_SOURCE_DIR_VAL), QString(CB_SETTINGS_SOURCE_DIR_SETTINGS_VAL));
    _settingsDeviceApp->set(QString(CB_SETTINGS_SOURCE_DIR_SETTINGS), settingsDir);

    QString leftButtonTagsFile = CBGlobal::combinePath(settingsDir, ui->lineEditTagSettingFileName->text().trimmed());
    _settingsDeviceApp->set(QString(CB_SETTINGS_LEFT_BUTTONS_TAGS_FILE), leftButtonTagsFile);

    QString locationsSettingFile = CBGlobal::combinePath(settingsDir, ui->lineEditLocationSettingFileName->text().trimmed());
    _settingsDeviceApp->set(QString(CB_SETTINGS_ORDER_LOCATIONS_FILE), locationsSettingFile);

    _settingsDeviceApp->set(QString(CB_SETTINGS_LEFT_BUTTON_TEXT_SIZE), QString::number(ui->spinBoxFontSizeLeftButton->value()));
    _settingsDeviceApp->set(QString(CB_SETTINGS_GRIDVIEW_COLUMN_COUNT), QString::number(ui->spinBoxMenuItemCol->value()));
    _settingsDeviceApp->set(QString(CB_SETTINGS_ORDERING_DIALOG_MAX_ITEM_COUNT), QString::number(ui->spinBoxMaxItemOrderedCount->value()));

    return _settingsDeviceApp->save();
}

void MainWindow::initTabWidgetDeviceSettings()
{
    initDeviceCharSetComboBox();
    loadDeviceSettings();
}

void MainWindow::on_tabMainTab_currentChanged(int)
{
    QWidget *currentTab = ui->tabMainTab->currentWidget();

    if (currentTab == ui->tabOrders)
    {

    }
    else if (currentTab == ui->tabDishes)
    {

    }
    else if (currentTab == ui->tabDeviceSettings)
    {

    }
    else if (currentTab == ui->tabPCSettings)
    {

    }

}

void MainWindow::slt_settingsHasBeenChanged()
{
    if (!_settingsHasChanged)
        _settingsHasChanged = true;

    if (_settingsHasChanged)
    {
        slt_setSettingsHasBeenChangedStatus(true);
    }
}

void MainWindow::slt_setSettingsHasBeenChangedStatus(bool hasChanged)
{
    if (hasChanged)
    {
        QString text = ui->pushButtonDeviceSettingsSave->text();
        if (!text.startsWith("*"))
        {
            text = QString("*") + text;
            ui->pushButtonDeviceSettingsSave->setText(text);
        }
    }
    else
    {
        QString text = ui->pushButtonDeviceSettingsSave->text();
        if (text.startsWith("*"))
        {
            text = text.mid(1);
            ui->pushButtonDeviceSettingsSave->setText(text);
        }
    }

}

void MainWindow::on_spinBoxFontSizeLeftButton_valueChanged(int)
{
    slt_settingsHasBeenChanged();
}

void MainWindow::on_spinBoxMenuItemCol_valueChanged(int)
{
    slt_settingsHasBeenChanged();
}

void MainWindow::on_spinBoxMaxItemOrderedCount_valueChanged(int)
{
    slt_settingsHasBeenChanged();
}

void MainWindow::on_comboBoxDeviceCharSet_currentIndexChanged(int)
{
    slt_settingsHasBeenChanged();
}

void MainWindow::on_lineEditTagSettingFileName_textChanged(const QString &)
{
    slt_settingsHasBeenChanged();
}

void MainWindow::on_lineEditSettingsDeviceFile_textChanged(const QString &)
{
    slt_settingsHasBeenChanged();
}

void MainWindow::on_lineEditSettingsDir_textChanged(const QString &)
{
    slt_settingsHasBeenChanged();
}

void MainWindow::on_lineEditLocationSettingFileName_textChanged(const QString &)
{
    slt_settingsHasBeenChanged();
}

void MainWindow::slt_menuFileExportAllTriggered()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                            tr("选择导出路径"),
                                            tr("."));

    if (path.isEmpty())
        return;

    bool res = exportAll(path);
    if (!res)
    {
        QMessageBox::critical(this,
                              tr("错误"),
                              tr("在导出过程出发生错误"),
                              QMessageBox::Ok);
    }
}

void MainWindow::slt_menuFileExitTriggered()
{
    // function not used
}

void MainWindow::slt_menuOrderTriggered()
{
    ui->tabMainTab->setCurrentWidget(ui->tabOrders);
}

void MainWindow::slt_menuDishTriggered()
{
    ui->tabMainTab->setCurrentWidget(ui->tabDishes);
}

void MainWindow::slt_menuDishExportTriggered()
{
    on_buttonExport_clicked();
}

void MainWindow::slt_menuDeviceTriggered()
{
    ui->tabMainTab->setCurrentWidget(ui->tabDeviceSettings);
}

void MainWindow::slt_menuDeviceExportTriggered()
{
    on_buttonExportSettings_clicked();
}

void MainWindow::slt_menuPCTriggered()
{
    ui->tabMainTab->setCurrentWidget(ui->tabPCSettings);
}

void MainWindow::slt_menuHelpTriggered()
{

}

void MainWindow::slt_menuAboutTriggered()
{

}
