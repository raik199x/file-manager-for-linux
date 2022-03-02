#include "newfile.h"
#include "ui_newfile.h"
#include "QListViewExplorerModel.h"
#include "mainwindow.h"

#include <QFile>
#include <QRadioButton>
#include <QMessageBox>
#include <QDir>

NewFile::NewFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFile)
{
    this->setStyleSheet("color: white; background-color: #181b28");
    ui->setupUi(this);
    this->ui->NewFileName->setStyleSheet("color: white; background-color: #2f343f");
    this->ui->FileRadioButton->setStyleSheet("color: white; background-color: #1e2233");
    this->ui->FolderRadioButton->setStyleSheet("color: white; background-color: #1e2233");
}

NewFile::~NewFile()
{
    delete ui;
}

void NewFile::on_cancel_clicked()
{
    QWidget::close();
}


void NewFile::on_create_clicked()
{

    QString name = path+ui->NewFileName->text();
    if (!ui->FileRadioButton->isChecked() && !ui->FolderRadioButton->isChecked()){
        QMessageBox::warning(this, QObject::tr("Error"), QObject::tr("Doesn't set file or folder"));
        return;
    } else if (name == ""){
        QMessageBox::warning(this, QObject::tr("Empty name"), QObject::tr("Cant handle empty names"));
        return;
    }

    QFile fout(name);
    if(fout.exists()){
        QMessageBox::warning(this, QObject::tr("Fail"), QObject::tr("File or folder already exist"));
        return;
    }

    if (ui->FileRadioButton->isChecked()){
        QFile file(name);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox::warning(this, QObject::tr("Unknown Error"), QObject::tr("For some reason, file coundt be created"));
            return;
        }
        file.close();
    } else{
        QDir dir;
        dir.mkpath(name);
    }
    QWidget::close();
}

