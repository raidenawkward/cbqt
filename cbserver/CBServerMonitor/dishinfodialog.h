#ifndef DISHINFODIALOG_H
#define DISHINFODIALOG_H

#include <QDialog>
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

protected:
    void setPreviewImage(const QString path);

private slots:
    void on_toolButtonThumb_clicked();
    void on_toolButtonPicture_clicked();

private:
    void setTags(CBTagsSet set);

private:
    Ui::DishInfoDialog *ui;
    CBMenuItem* _menuItem;
};

#endif // DISHINFODIALOG_H
