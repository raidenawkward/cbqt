#ifndef DISHINFODIALOG_H
#define DISHINFODIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QAbstractButton>
#include "cbmenuitem.h"
#include "cbglobal.h"

namespace Ui {
class DishInfoDialog;
}

class DishInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DishInfoDialog(QWidget *parent = 0);
    ~DishInfoDialog();

    void setMenuItem(CBMenuItem* item);
    CBMenuItem* getMenuItem();

    bool isEdited();

protected:
    void setPreviewImage(const QString path);
    bool checkResult();
    void showWarning(const QString warning);

private slots:
    void on_toolButtonThumb_clicked();
    void on_toolButtonPicture_clicked();

    void on_listWidgetTags_doubleClicked(const QModelIndex &);
    void on_buttonAddTab_clicked();
    void on_buttonEdit_clicked();
    void on_buttonDeleteTag_clicked();

    void slt_save();
    void slt_apply();
    void slt_cancel();
    void slt_reset();

private:
    void setTags(CBTagsSet set);

private:
    Ui::DishInfoDialog *ui;
    CBMenuItem* _menuItem;
};

#endif // DISHINFODIALOG_H
