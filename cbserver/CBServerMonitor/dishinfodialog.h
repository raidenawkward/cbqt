#ifndef DISHINFODIALOG_H
#define DISHINFODIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QAbstractButton>
#include <QStringList>
#include "cbmenuitem.h"
#include "cbglobal.h"
#include "cbengine.h"

namespace Ui {
class DishInfoDialog;
}

class DishInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DishInfoDialog(CBEngine *engine, QWidget *parent = 0);
    ~DishInfoDialog();

    void setMenuItem(CBMenuItem* item);
    CBMenuItem* getMenuItem();

    bool isEdited();

signals:
    void sig_itemChanged(CBMenuItem *item);

protected:
    void setPreviewImage(const QString path);
    bool checkResult();
    void showWarning(const QString warning);
    void clearWarning();

private slots:
    void on_toolButtonThumb_clicked();
    void on_toolButtonPicture_clicked();

    void on_listWidgetTags_doubleClicked(const QModelIndex &);
    void on_buttonAddTab_clicked();
    void on_buttonEdit_clicked();
    void on_buttonDeleteTag_clicked();
    void on_lineEditThumb_textChanged(const QString &arg1);
    void on_lineEditId_textChanged(const QString &arg1);

    void slt_save();
    void slt_apply();
    void slt_cancel();
    void slt_reset();

private:
    void setTags(CBTagsSet set);
    QStringList getTags();
    bool saveItem();

    bool isIDConflict(const QString &id);

private:
    Ui::DishInfoDialog *ui;
    CBMenuItem* _menuItem;
    CBEngine *_engine;
};

#endif // DISHINFODIALOG_H
