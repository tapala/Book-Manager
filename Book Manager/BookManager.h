#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BookManager.h"

class BookManager : public QMainWindow
{
    Q_OBJECT

public:
    BookManager(QWidget *parent = nullptr);
    ~BookManager();

private:
    Ui::BookManagerClass ui;
};
