#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BookManager.h"

class BookManager : public QMainWindow
{
    Q_OBJECT

public:
    BookManager(QWidget *parent = nullptr);
    ~BookManager();
    void addBook(bool editable = false);
    void delBook();

    void CreateMessage(QString title, QString information);

private:
    Ui::BookManagerClass ui;

};
