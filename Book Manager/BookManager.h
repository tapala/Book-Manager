#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BookManager.h"
#include "../Book Manager Logic/pub.h"
#include "../Book Manager Logic/logger.h"
#include <QUuid>

class BookManager : public QMainWindow
{
    Q_OBJECT

public:
    BookManager(QWidget *parent = nullptr);
    ~BookManager();
    void handleSaveLoadButton();
    void updateListWidgetFromList();
    void addBook(bool editable = false);
    void delBook();

    void CreateMessage(QString title, QString information);

private:
    Ui::BookManagerClass ui;
    PublicationList bookList;
};
