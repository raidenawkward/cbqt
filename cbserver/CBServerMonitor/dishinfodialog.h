#ifndef DISHINFODIALOG_H
#define DISHINFODIALOG_H

#include <QDialog>

namespace Ui {
class DishInfoDialog;
}

class DishInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DishInfoDialog(QWidget *parent = 0);
    ~DishInfoDialog();

private slots:
    void on_toolButtonThumb_clicked();

    void on_toolButtonPicture_clicked();

private:
    Ui::DishInfoDialog *ui;
};

#endif // DISHINFODIALOG_H
