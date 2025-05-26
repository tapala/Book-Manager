#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include "ui_AddBookDialog.h"

class AddBookDialog : public QDialog
{
    Q_OBJECT

private slots:
    void onConfirmClicked();
public:
    explicit AddBookDialog(QWidget* parent = nullptr);
    void setAll(QString title, QString author, QString date, QStringList list, bool isRead);
    void setTitle(QString title);
    void setAuthor(QString author);
    void setDate(QString date);
    void setGenere(QStringList list);
    void setIsRead(bool isRead);
    ~AddBookDialog();
    QStringList getCheckedGenres();
    QString getAuthor();
    QString getTitle();
    QString getDate();
    bool getIsRead();
private:
    Ui::Form ui;
};

#endif