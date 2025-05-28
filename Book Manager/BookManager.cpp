#include "BookManager.h"
#include "AddBookDialog.h"
#include <QMessageBox>
#include "pub.h"

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
}

BookManager::~BookManager()
{}

void BookManager::addBook(bool editable) {
    AddBookDialog dialog(this);
    QListWidgetItem* item = ui.listWidget->currentItem();
    if (editable && item) {
        QStringList cols = item->text().split("|");
        for (QString& str : cols) { str = str.trimmed(); };
        dialog.setAll(cols[0], cols[1],cols[2],cols[3].split(", "), ((cols[4] == "Przeczytane") ? true : false));
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
                CreateMessage("Sukces","Edytowano wybrana ksiazke");
                item->setText(rowText);
            }
        }
        else {
            CreateMessage("Sukces", "Dodano nowa ksiazke");
            ui.listWidget->addItem(rowText);
        }
    }
}

void BookManager::delBook() {
    QListWidgetItem* item = ui.listWidget->currentItem();
    if (item) {
        CreateMessage("Sukces", "Usunieto wybrana ksiazke");
        delete item;
    }
}

void BookManager::CreateMessage(QString title, QString information) {
    QMessageBox::information(this, title, information);
}
