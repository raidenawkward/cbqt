#include "dishinfodialog.h"
#include "ui_dishinfodialog.h"
#include <QFileDialog>


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
}

void DishInfoDialog::on_toolButtonPicture_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("选择图片"),
                                                    tr("."),
                                                    tr("图片文件 (*.jpg *.png *.bmp)"));

    ui->lineEditPicture->setText(fileName);
}

void DishInfoDialog::setMenuItem(CBMenuItem* item)
{
    if (!item)
        return;

    CBDish dish = item->getDish();

    ui->lineEditId->setText(dish.getId().toString());
    ui->lineEditName->setText(dish.getName());
}

CBMenuItem* DishInfoDialog::getMenuItem()
{
    return _menuItem;
}
