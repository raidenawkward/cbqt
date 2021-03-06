#include "dishinfodialog.h"
#include "ui_dishinfodialog.h"
#include "cbmenuitemsset.h"
#include "cbmenuitem.h"

#include <QFileDialog>
#include <QPixmap>
#include <QDebug>
#include <QModelIndex>
#include <QMessageBox>
#include <QInputDialog>

DishInfoDialog::DishInfoDialog(CBEngine *engine, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DishInfoDialog),
    _menuItem(NULL)
{
    _engine = engine;

    ui->setupUi(this);
    QRegExp regx("[0-9]*[.]?[0-9]*");
    QValidator *validator = new QRegExpValidator(regx, this);
    ui->lineEditPrice->setValidator(validator);
    ui->lineEditScore->setValidator(validator);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    ui->labelWarning->setPalette(pe);

    ui->buttonBox->button(QDialogButtonBox::Save)->setText(tr("保存"));
    ui->buttonBox->button(QDialogButtonBox::Apply)->setText(tr("应用"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
    ui->buttonBox->button(QDialogButtonBox::Reset)->setText(tr("重置"));

    connect(ui->buttonBox->button(QDialogButtonBox::Save), SIGNAL(clicked()),this,SLOT(slt_save()));
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()),this,SLOT(slt_apply()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()),this,SLOT(slt_cancel()));
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()),this,SLOT(slt_reset()));

    // default dish id set here
    ui->lineEditId->setText(CBGlobal::getCurrentTimeStamp());
}

DishInfoDialog::~DishInfoDialog()
{
    delete ui;
}

void DishInfoDialog::on_toolButtonThumb_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("选择图片"),
                                                    tr("."),
                                                    tr("图片文件 (*.jpg *.png *.bmp)"));

    if (!fileName.isEmpty())
    {
        ui->lineEditThumb->setText(fileName);
        this->setPreviewImage(fileName);
    }
}

void DishInfoDialog::on_toolButtonPicture_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("选择图片"),
                                                    tr("."),
                                                    tr("图片文件 (*.jpg *.png *.bmp)"));

    if (!fileName.isEmpty())
    {
        ui->lineEditPicture->setText(fileName);
    }
}

void DishInfoDialog::setTags(CBTagsSet set)
{
    for (int i = 0; i < set.count(); ++i)
    {
        ui->listWidgetTags->addItem(set.get(i));
    }
}

QStringList DishInfoDialog::getTags()
{
    QStringList res;
    for (int i = 0; i < ui->listWidgetTags->count(); ++i)
    {
        res.append(ui->listWidgetTags->item(i)->text().trimmed());
    }

    return res;
}

bool DishInfoDialog::saveItem()
{
    QDir root(CBSERVERMONITOR_DISHES_DIR);
    if (!root.exists())
    {
        if (!root.mkdir(root.absolutePath()))
            return false;
    }

    CBId id(ui->lineEditId->text().trimmed());

    if (!_menuItem)
    {
        _menuItem = new CBMenuItem();
        _menuItem->setRecordDir(CBGlobal::combinePath(root.absolutePath(), id.toString()));
        root.mkdir(_menuItem->getRecordDir());
        _menuItem->setRecordFile(id.toString() + ".xml");
    }

    _menuItem->getDish().setId(id);
    _menuItem->getDish().setName(ui->lineEditName->text().trimmed());
    _menuItem->getDish().setPrice(ui->lineEditPrice->text().trimmed().toFloat());
    _menuItem->getDish().setScore(ui->lineEditScore->text().trimmed().toFloat());
    _menuItem->getDish().setSummary(ui->lineEditSummary->text().trimmed());
    _menuItem->getDish().setDetail(ui->textEditDetail->toPlainText().trimmed());

    QStringList tagsList = this->getTags();
    _menuItem->getDish().setTags(tagsList);

    QFile fileOldThumb(CBGlobal::combinePath(_menuItem->getRecordDir(), _menuItem->getDish().getThumb()));
    QFile fileOldPicture(CBGlobal::combinePath(_menuItem->getRecordDir(), _menuItem->getDish().getPicture()));
    QFile fileThumb(ui->lineEditThumb->text().trimmed());
    QFile filePicture(ui->lineEditPicture->text().trimmed());

    if (fileOldThumb.fileName() != fileThumb.fileName())
    {
        QFileInfo info(fileThumb);
        _menuItem->getDish().setThumb(CBGlobal::getFileName(info.fileName()));
        qDebug()<<CBGlobal::combinePath(_menuItem->getRecordDir(), _menuItem->getDish().getThumb());
        if (fileThumb.exists())
        {
            if (!fileThumb.copy(CBGlobal::combinePath(_menuItem->getRecordDir(), _menuItem->getDish().getThumb())))
                return false;
        }
        //fileOldThumb.remove();
    }

    if (fileOldPicture.fileName() != filePicture.fileName())
    {
        QFileInfo info(filePicture);
        _menuItem->getDish().setPicture(CBGlobal::getFileName(info.fileName()));

        if (filePicture.exists())
        {
            if (filePicture.copy(CBGlobal::combinePath(_menuItem->getRecordDir(), _menuItem->getDish().getPicture())))
                qDebug()<<"failed copying picture "<<_menuItem->getDish().getPicture();//fileOldPicture.remove();
        }
    }

    if (!CBGlobal::writeMenuItemXml(_menuItem))
        return false;

    emit this->sig_itemChanged(_menuItem);

    return true;
}

void DishInfoDialog::showWarning(const QString warning)
{
    ui->labelWarning->setText(warning);
}

void DishInfoDialog::clearWarning()
{
    ui->labelWarning->setText("");
}

bool DishInfoDialog::checkResult()
{
    if (ui->lineEditId->text().isEmpty())
    {
        showWarning(tr("编号不能为空!"));
        return false;
    }

    if (isIDConflict(ui->lineEditId->text().trimmed()))
    {
        showWarning("输入菜品的ID已经存在!");
        return false;
    }

    if (ui->lineEditName->text().isEmpty())
    {
        showWarning(tr("名称不能为空!"));
        ui->lineEditName->setFocus();
        return false;
    }

    if (ui->lineEditPrice->text().isEmpty())
    {
        showWarning(tr("价格不能为空!"));
        ui->lineEditPrice->setFocus();
        return false;
    }

    if (ui->lineEditThumb->text().isEmpty())
    {
        showWarning(tr("缩略图不能为空!"));
        ui->lineEditThumb->setFocus();
        return false;
    }
    else
    {
        if (!QFile(ui->lineEditThumb->text()).exists())
        {
            showWarning(tr("指定的缩略图不存在!"));
            ui->lineEditThumb->setFocus();
            ui->lineEditThumb->selectAll();
            return false;
        }
    }

    if (ui->lineEditPicture->text().isEmpty())
    {
        showWarning(tr("图片路径不能为空!"));
        ui->lineEditPicture->setFocus();
        return false;
    }
    else
    {
        if (!QFile(ui->lineEditPicture->text()).exists())
        {
            showWarning(tr("指定的图片不存在!"));
            ui->lineEditPicture->setFocus();
            ui->lineEditPicture->selectAll();
            return false;
        }
    }

    return true;
}

void DishInfoDialog::setPreviewImage(const QString path)
{
    QPixmap pixmap(path, CBGlobal::getFileExt(path).toUpper().toUtf8().constData());
    if (!pixmap.isNull())
        ui->labelPreview->setPixmap(pixmap);
    else
        ui->labelPreview->setText(tr("图片预览"));
}

void DishInfoDialog::setMenuItem(CBMenuItem* item)
{
    ui->listWidgetTags->clear();
    this->_menuItem = item;

    if (!item)
        return;

    CBDish dish = _menuItem->getDish();

    ui->lineEditId->setText(dish.getId().toString());
    ui->lineEditName->setText(dish.getName());

    setTags(dish.getTagsSet());

    ui->lineEditPrice->setText(QString::number(dish.getPrice()));
    ui->lineEditScore->setText(QString::number(dish.getScore()));
    ui->lineEditSummary->setText(dish.getSummary());
    ui->textEditDetail->setText(dish.getDetail());

    QString thumbPath = item->getRecordDir() + QString(CBPATH_SPLITOR) + dish.getThumb();
    QString picturePath = item->getRecordDir() + QString(CBPATH_SPLITOR) + dish.getPicture();

    ui->lineEditThumb->setText(thumbPath);
    ui->lineEditPicture->setText(picturePath);

    setPreviewImage(thumbPath);

    clearWarning();
}

CBMenuItem* DishInfoDialog::getMenuItem()
{
    return _menuItem;
}

bool DishInfoDialog::isEdited()
{
    if (!_menuItem)
        return false;

    CBDish dish = _menuItem->getDish();
    if (ui->lineEditId->text().trimmed() != dish.getId().toString())
        return true;

    if (ui->lineEditName->text().trimmed() != dish.getName())
        return true;

    if (ui->lineEditPrice->text().trimmed().toFloat() != dish.getPrice())
        return true;

    if (ui->lineEditScore->text().trimmed().toFloat() != dish.getScore())
        return true;

    if (ui->lineEditSummary->text().trimmed().trimmed() != dish.getSummary())
        return true;

    if (ui->lineEditThumb->text().trimmed().trimmed() != dish.getThumb())
        return true;

    if (ui->lineEditPicture->text().trimmed() != dish.getPicture())
        return true;

    if (ui->textEditDetail->toPlainText() != dish.getDetail())
        return true;

    return false;
}

void DishInfoDialog::on_listWidgetTags_doubleClicked(const QModelIndex&)
{
    on_buttonEdit_clicked();
}

void DishInfoDialog::on_buttonAddTab_clicked()
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
        ui->listWidgetTags->addItem(tag);
    }
}

void DishInfoDialog::on_buttonEdit_clicked()
{
    if (!ui->listWidgetTags->currentItem())
        return;

    bool ok = false;
    QString text = ui->listWidgetTags->currentItem()->text();
    QString tag = QInputDialog::getText(this,
                                tr("修改标签"),
                                tr("标签名称:"),
                                QLineEdit::Normal,
                                text,
                                &ok);

    if (ok)
    {
        ui->listWidgetTags->currentItem()->setText(tag);
    }
}

void DishInfoDialog::on_buttonDeleteTag_clicked()
{
    if (!ui->listWidgetTags->currentItem())
        return;

    QString content = tr("确定要删除标签\"");
    content += ui->listWidgetTags->currentItem()->text();
    content += tr("\"吗?");
    QMessageBox::StandardButton res = QMessageBox::question(this,
                                     tr("删除确认"),
                                     content,
                                     QMessageBox::Yes | QMessageBox::No,
                                     QMessageBox::Yes);

    if(res == QMessageBox::Yes)
    {
        ui->listWidgetTags->takeItem(ui->listWidgetTags->currentIndex().row());
    }
}

void DishInfoDialog::slt_save()
{
    if (!this->checkResult())
        return;

    if (saveItem())
        this->close();
}

void DishInfoDialog::slt_apply()
{
    if (!this->checkResult())
        return;

    if (saveItem())
    {
        this->setMenuItem(_menuItem);
    }
}

void DishInfoDialog::slt_cancel()
{
    this->close();
}

void DishInfoDialog::slt_reset()
{
    QString content = tr("是否放弃之前的修改?");
    QMessageBox::StandardButton res = QMessageBox::question(this,
                                     tr("重置确认"),
                                     content,
                                     QMessageBox::Yes | QMessageBox::No,
                                     QMessageBox::Yes);

    if(res == QMessageBox::Yes)
    {
        setMenuItem(this->_menuItem);
    }

    this->checkResult();
}

void DishInfoDialog::on_lineEditThumb_textChanged(const QString &arg1)
{
    this->setPreviewImage(arg1);
}

void DishInfoDialog::on_lineEditId_textChanged(const QString &arg1)
{
    if (isIDConflict(arg1))
    {
        showWarning("输入菜品的ID已经存在!");
    }
    else
    {
        clearWarning();
    }
}

bool DishInfoDialog::isIDConflict(const QString &id)
{
    if (!_engine)
        return false;

    CBMenuItemsSet *set = _engine->getMenuItemsSet();
    if (!set)
        return false;

    if (_menuItem)
    {
        if (id.trimmed() != _menuItem->getDish().getId().toString())
        {
            if (set->get(CBId(id.trimmed())) != NULL)
                return true;
        }
    }

    return false;
}
