#include "dishinfodialog.h"
#include "ui_dishinfodialog.h"
#include <QFileDialog>
#include <QPixmap>
#include <QDebug>
#include <QModelIndex>
#include <QMessageBox>
#include <QInputDialog>

DishInfoDialog::DishInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DishInfoDialog),
    _menuItem(NULL)
{
    ui->setupUi(this);
    QRegExp regx("[0-9]*[.]?[0-9]*");
    QValidator *validator = new QRegExpValidator(regx, this);
    ui->lineEditPrice->setValidator(validator);
    ui->lineEditScore->setValidator(validator);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    ui->labelWarning->setPalette(pe);

    connect(ui->buttonBox->button(QDialogButtonBox::Save), SIGNAL(clicked()),this,SLOT(slt_save()));
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()),this,SLOT(slt_apply()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()),this,SLOT(slt_cancel()));
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()),this,SLOT(slt_reset()));
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

    ui->lineEditThumb->setText(fileName);
    this->setPreviewImage(fileName);
}

void DishInfoDialog::on_toolButtonPicture_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("选择图片"),
                                                    tr("."),
                                                    tr("图片文件 (*.jpg *.png *.bmp)"));

    ui->lineEditPicture->setText(fileName);
}

void DishInfoDialog::setTags(CBTagsSet set)
{
    for (int i = 0; i < set.count(); ++i)
    {
        ui->listWidgetTags->addItem(set.get(i));
    }
}

void DishInfoDialog::showWarning(const QString warning)
{
    ui->labelWarning->setText(warning);
}

bool DishInfoDialog::checkResult()
{
    if (ui->lineEditId->text().isEmpty())
    {
        showWarning(tr("编号不能为空!"));
        return false;
    }

    if (ui->lineEditName->text().isEmpty())
    {
        showWarning(tr("名称不能为空!"));
        return false;
    }

    if (ui->lineEditPrice->text().isEmpty())
    {
        showWarning(tr("价格不能为空!"));
        return false;
    }

    if (ui->lineEditThumb->text().isEmpty())
    {
        showWarning(tr("缩略图不能为空!"));
        return false;
    }

    if (ui->lineEditPicture->text().isEmpty())
    {
        showWarning(tr("图片路径不能为空!"));
        return false;
    }

    return true;
}

void DishInfoDialog::setPreviewImage(const QString path)
{
    QPixmap pixmap(path, CBGlobal::getFileExt(path).toUpper().toUtf8().constData());

    ui->labelPreview->setPixmap(pixmap);
}

void DishInfoDialog::setMenuItem(CBMenuItem* item)
{
    if (!item)
        return;

    ui->listWidgetTags->clear();

    CBDish dish = item->getDish();

    ui->lineEditId->setText(dish.getId().toString());
    ui->lineEditName->setText(dish.getName());

    setTags(dish.getTagsSet());

    ui->lineEditPrice->setText(QString::number(dish.getPrice()));
    ui->lineEditScore->setText(QString::number(dish.getScore()));
    ui->lineEditSummary->setText(dish.getSummary());
    ui->textEditDetail->setText(dish.getDetail());

    QString thumbPath = CBGlobal::getFileDir(item->getRecordPath()) + dish.getThumb();
    QString picturePath = CBGlobal::getFileDir(item->getRecordPath()) + dish.getPicture();

    ui->lineEditThumb->setText(thumbPath);
    ui->lineEditPicture->setText(picturePath);

    setPreviewImage(thumbPath);

    this->_menuItem = item;
}

CBMenuItem* DishInfoDialog::getMenuItem()
{
    return _menuItem;
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

    this->close();
}

void DishInfoDialog::slt_apply()
{
    if (!this->checkResult())
        return;
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
}
