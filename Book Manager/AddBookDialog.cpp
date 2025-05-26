#include "AddBookDialog.h"
#include <regex>
#include <QMessageBox>


AddBookDialog::AddBookDialog(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.confirmButton, &QPushButton::clicked, this, &AddBookDialog::onConfirmClicked);
}

void AddBookDialog::onConfirmClicked()
{
    if (std::regex_match(ui.lineEditAuthor->text().toStdString(), std::regex("^[A-Z][a-zA-Z]*([ ][A-Z][a-zA-Z]*){0,2}$"))) {
        accept(); 
    }
    else {
        QMessageBox::information(this, "B³¹d", "Nazwa autora mo¿e siê sk³adaæ tylko z ma³ych i wielkich liter oraz nie mo¿e byæ pusta ani zawieraæ wiêcej ni¿ 3 s³owa");
    }
}

void AddBookDialog::setAll(QString title, QString author, QString date, QStringList list, bool isRead) {
    setTitle(title);
    setAuthor(author);
    setDate(date);
    setGenere(list);
    setIsRead(isRead);
}

void AddBookDialog::setTitle(QString title) {
    ui.lineEditTitle->setText(title);
}

void AddBookDialog::setAuthor(QString author) {
    ui.lineEditAuthor->setText(author);
}

void AddBookDialog::setDate(QString date) {
    ui.dateEdit->setDate(QDate::fromString(date, "dd.MM.yyyy"));
}

void AddBookDialog::setGenere(QStringList list) {
    for (QString genere : list) {
        if (genere == "Literatura Faktu") {
            ui.checkBox_G_LF->setChecked(true);
        }
        else if (genere == "Popularnonaukowa") {
            ui.checkBox_G_PN->setChecked(true);
        }
        else if (genere == "Fantasy") {
            ui.checkBox_G_F->setChecked(true);
        }
        else if (genere == "Sci-Fi") {
            ui.checkBox_G_SF->setChecked(true);
        }
        else if (genere == "Horror") {
            ui.checkBox_G_H->setChecked(true);
        }
        else if (genere == "Dla Dzieci") {
            ui.checkBox_G_DD->setChecked(true);
        }

    }
}

void AddBookDialog::setIsRead(bool isRead) {
    ui.checkBoxIsRead->setChecked(isRead);
}

QStringList AddBookDialog::getCheckedGenres()
{
    QLayout* layout = ui.verticalLayout_10;
    QStringList checkedGenres;

    for (int i = 0; i < layout->count(); ++i) {
        QWidget* widget = layout->itemAt(i)->widget();
        if (widget) {
            QCheckBox* checkbox = qobject_cast<QCheckBox*>(widget);
            if (checkbox && checkbox->isChecked()) {
                checkedGenres.append(checkbox->text());
            }
        }
    }

    return checkedGenres;

}

QString AddBookDialog::getAuthor() {
    return ui.lineEditAuthor->text();
}

QString AddBookDialog::getTitle() {
    return ui.lineEditTitle->text();
}

QString AddBookDialog::getDate() {
    return ui.dateEdit->date().toString("dd.MM.yyyy");
}

bool AddBookDialog::getIsRead() {
    return ui.checkBoxIsRead->isChecked();
}

AddBookDialog::~AddBookDialog() {};