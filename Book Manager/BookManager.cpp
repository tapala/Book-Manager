#include "BookManager.h"
#include "AddBookDialog.h"
#include <QMessageBox>

BookManager::BookManager(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.addButton, &QPushButton::clicked, this, [=]() {addBook(); });
    connect(ui.editButton, &QPushButton::clicked, this, [=]() {addBook(true); });
    connect(ui.delButton, &QPushButton::clicked, this, [=]() {delBook(); });
    ui.comboBox->addItem("Zapisz");
    ui.comboBox->addItem("Wczytaj");
    connect(ui.comboBox, &QComboBox::currentTextChanged, this, [=](const QString& text) {ui.saveLoadButton->setText(text); });
    connect(ui.saveLoadButton, &QPushButton::clicked, this, [=]() {handleSaveLoadButton(); });
}

BookManager::~BookManager()
{}

void BookManager::handleSaveLoadButton() {
    
    if (ui.saveLoadButton->text() == "Zapisz") {
        savePublicationsToCSV("../data/publications.csv",bookList,false);
    }
    else {
        updateListWidgetFromList();
    }
}

void BookManager::updateListWidgetFromList() {
    ui.listWidget->clear();
    bookList.clear();
    for (auto& book : readPublicationsFromCSV("../data/publications.csv")) {
        QString rowText = QString::fromStdString(book.title).leftJustified(50) + "|        " + QString::fromStdString(book.author).leftJustified(50) + "|        " + QString::fromStdString(book.releaseDate).leftJustified(50) + "|        " + QString::fromStdString(book.genre).left(book.genre.length() - 2).leftJustified(50) + "|        " + QString::fromStdString((book.isRead) ? "Przeczytane" : "Do przeczytania").leftJustified(60);
        QListWidgetItem* newItem = new QListWidgetItem(rowText);
        bookList.addPublication(book.clone());
        newItem->setData(Qt::UserRole, QString::fromStdString(book.uuid));
        ui.listWidget->addItem(newItem);
    }
}

void BookManager::addBook(bool editable) {
    QListWidgetItem* item = ui.listWidget->currentItem();
    if((editable && item) || !editable ){
        AddBookDialog dialog(this);
        if (editable && item) {
            QStringList cols = item->text().split("|");
            for (QString& str : cols) { str = str.trimmed(); };
            dialog.setAll(cols[0], cols[1], cols[2], cols[3].split(", "), ((cols[4] == "Przeczytane") ? true : false));
        }
        if (dialog.exec() == QDialog::Accepted) {
            QStringList checkedGeneres = dialog.getCheckedGenres();
            QString generesString;
            QString isReadText;

            for (int i = 0; i < checkedGeneres.size(); ++i) {
                generesString.append(checkedGeneres[i]).append(", ");
            }

            if (dialog.getIsRead()) { isReadText = "Przeczytane"; }
            else { isReadText = "Do przeczytania"; }

            QString rowText = dialog.getTitle().leftJustified(50) + "|        " + dialog.getAuthor().leftJustified(50) + "|        " + dialog.getDate().leftJustified(50) + "|        " + generesString.left(generesString.length() - 2).leftJustified(50) + "|        " + isReadText.leftJustified(60);

            if (editable) {
                if (item) {
                    CreateMessage("Sukces", "Edytowano wybrana ksiazke");
                    string oldUuid = item->data(Qt::UserRole).toString().toStdString();
                    bookList.replaceByUuid(oldUuid, make_unique<Book>(oldUuid, dialog.getTitle().toStdString(), dialog.getAuthor().toStdString(), dialog.getDate().toStdString(), generesString.left(generesString.length() - 2).toStdString(), dialog.getIsRead()));
                    item->setText(rowText);
                }
            }
            else {
                QUuid uuid = QUuid::createUuid();
                QListWidgetItem* newItem = new QListWidgetItem(rowText);
                newItem->setData(Qt::UserRole, uuid.toString());
                CreateMessage("Sukces", "Dodano nowa ksiazke");
                bookList.addPublication(make_unique<Book>(uuid.toString().toStdString(), dialog.getTitle().toStdString(), dialog.getAuthor().toStdString(), dialog.getDate().toStdString(), generesString.left(generesString.length() - 2).toStdString(), dialog.getIsRead()));
                printList(bookList);
                ui.listWidget->addItem(newItem);
            }
        }
    }
}

void BookManager::delBook() {
    QListWidgetItem* item = ui.listWidget->currentItem();
    if (item) {
        CreateMessage("Sukces", "Usunieto wybrana ksiazke");
        bookList.removePublicationById((item->data(Qt::UserRole).toString()).toStdString());
        delete item;
    }
}

void BookManager::CreateMessage(QString title, QString information) {
    QMessageBox::information(this, title, information);
}
