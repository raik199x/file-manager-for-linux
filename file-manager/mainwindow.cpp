#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newfile.h"

#include <QMessageBox>
#include <QDesktopServices>
#include <QTranslator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    //color
    this->setStyleSheet("color: white; background-color: #181b28");
    this->ui->lineEdit->setStyleSheet("color: white; background-color: #2f343f");
    this->ui->listView->setStyleSheet("color: white; background-color: #2f343f");
    this->ui->Copy->setStyleSheet("color: white; background-color: #1e2233");
    this->ui->Delete->setStyleSheet("color: white; background-color: #1e2233");
    this->ui->Create->setStyleSheet("color: white; background-color: #1e2233");
    //color inactive
    this->ui->Insert_button->setStyleSheet("color: #666a73; background-color: #2f343f");
    this->ui->Move_button->setStyleSheet("color: #666a73; background-color: #2f343f");
    //main parameters
    this->aDirList = new QFileInfoList();
    this->model = new QListViewExplorerModel();
    this->model->getFolderList(".",this->aDirList);
    this->ui->listView->setModel(model);
    this->ui->lineEdit->setText(QDir::currentPath());
    this->path = QDir::currentPath();

    //starting language
    if(Translator.load(":/translations/file-manager_en.qm")){
        QApplication::installTranslator(&Translator);
        MainWindow::on_actionEnglish_triggered();
    }
    else
        qDebug() << "Translator is not working";
    this->buffer = QObject::tr("Empty");
    //setting text on buttons
    ui->Move_button->setToolTip(QObject::tr("Insert file without copy"));
    ui->Insert_button->setToolTip(QObject::tr("Insert with copy of file"));
    ui->Copy->setToolTip(this->buffer);
    //disabling some buttons
    ui->Move_button->setDisabled(true);
    ui->Insert_button->setDisabled(true);
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::refresh_folder(){
    this->statusBar()->showMessage("");
    this->model->getFolderList(this->path,this->aDirList);
    this->ui->listView->setModel(model);
    this->ui->lineEdit->setText(this->path);

    QModelIndex restart;
    this->MyIndex = restart;

}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index){
    this->statusBar()->showMessage("");
    if (this->aDirList->at(index.row()).isDir()) //changing directory
    {
        QString tmp = this->aDirList->at(index.row()).absoluteFilePath();
        this->path = tmp;
        model->getFolderList(this->aDirList->at(index.row()).absoluteFilePath(),this->aDirList);
        this->ui->lineEdit->setText(tmp);
        QModelIndex restart;
        this->MyIndex = restart;
    } else {    //open file
        QDesktopServices::openUrl(QUrl::fromLocalFile(this->aDirList->at(index.row()).absoluteFilePath()));
    }
}


void MainWindow::on_list_clicked()
{
    this->ui->listView->setUniformItemSizes(false);
    this->ui->listView->setWordWrap(true);
    this->ui->listView->setViewMode(QListView::ListMode);
}


void MainWindow::on_icon_list_clicked()
{
    this->ui->listView->setUniformItemSizes(true);
    this->ui->listView->setWordWrap(true);
    this->ui->listView->setViewMode(QListView::IconMode);
}


void MainWindow::on_lineEdit_editingFinished()
{
    QString path = ui->lineEdit->text();
     if(QDir(path).exists()){
         this->path = path;
         refresh_folder();
         return;
     } else{
         QMessageBox::warning(this,QObject::tr("Warning"), QObject::tr("No such folder!"));
         ui->lineEdit->setText(this->path);
     }
}


void MainWindow::on_Copy_clicked()
{
    QModelIndex check;
    if(MyIndex == check){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Nothing was selected"));
        this->buffer = QObject::tr("Empty");
        ui->Copy->setToolTip(this->buffer);
        ui->Move_button->setDisabled(true);
        ui->Insert_button->setDisabled(true);
        this->ui->Insert_button->setStyleSheet("color: #666a73; background-color: #2f343f");
        this->ui->Move_button->setStyleSheet("color: #666a73; background-color: #2f343f");
        return;
    }
    this->statusBar()->showMessage(QObject::tr("Copied!"));
    this->buffer = this->aDirList->at(MyIndex.row()).absoluteFilePath();

    ui->Copy->setToolTip(this->buffer);

    ui->Move_button->setDisabled(false);
    ui->Insert_button->setDisabled(false);
    this->ui->Insert_button->setStyleSheet("color: white; background-color: #1e2233");
    this->ui->Move_button->setStyleSheet("color: white; background-color: #1e2233");
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    this->MyIndex = index;
}


void MainWindow::on_Create_clicked()
{
    this->statusBar()->showMessage(QObject::tr("Creating new file"));
    NewFile* ui = new NewFile;
    ui->path = this->path+"/";
    ui->setModal(true);
    ui->exec();
    this->statusBar()->showMessage("");
    this->refresh_folder();
}


void MainWindow::on_Delete_clicked()
{
    this->statusBar()->showMessage(QObject::tr("Deleting"));
    QModelIndex check;
    if(MyIndex == check){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Nothing was selected"));
        this->statusBar()->showMessage("");
        return;
    }

    if (this->aDirList->at(MyIndex.row()).fileName() == ".."){
        QMessageBox::critical(this,QObject::tr("Fail"),QObject::tr("Restricted deleting '..'"));
        this->statusBar()->showMessage("");
        return;
    }

    QMessageBox reply;
    reply.setText(tr("Are you sure you want to delete this file?"));
    reply.setWindowTitle(tr("Confirm"));
    QAbstractButton* pButtonYes = reply.addButton(tr("Yes"), QMessageBox::YesRole);
    reply.addButton(tr("No"), QMessageBox::NoRole);
    reply.setStyleSheet("color: white; background-color: #181b28");
    reply.exec();

    if(reply.clickedButton() == pButtonYes){
        if(!QFile::exists(this->aDirList->at(MyIndex.row()).absoluteFilePath())){
            QMessageBox::critical(this,QObject::tr("Fail"),QObject::tr("File is not real"));
            this->statusBar()->showMessage("");
            return;
        } else if (this->aDirList->at(MyIndex.row()).isFile() == true){
            if(!QFile::remove(this->aDirList->at(MyIndex.row()).absoluteFilePath()))
                QMessageBox::critical(this,QObject::tr("Fail"),QObject::tr("Premission denied"));
        }
        else if (this->aDirList->at(MyIndex.row()).isFile() == false){
            QDir to_delete(this->aDirList->at(MyIndex.row()).absoluteFilePath());
            if(!to_delete.removeRecursively())
                QMessageBox::critical(this,QObject::tr("Fail"),QObject::tr("Premission denied"));

        }
        refresh_folder();
    }
    this->statusBar()->showMessage("");
    return;
}

void MainWindow::execute_event_translate(){
    setWindowTitle(tr("File Manager @raik199x"));
    ui->Copy->setText(tr("Copy"));
    ui->Create->setText(tr("Create"));
    ui->Delete->setText(tr("Delete"));
    ui->Move_button->setText(tr("Move here"));
    ui->Move_button->setToolTip(tr("insert without copy of file"));
    ui->Insert_button->setText(tr("Copy here"));
    ui->Insert_button->setToolTip(tr("insert with copy of file"));
    ui->actionEnglish->setText(tr("English"));
    ui->actionRussian->setText(tr("Russian"));
    ui->menuLanguage->setTitle(tr("Language"));
}

void MainWindow::on_actionRussian_triggered()
{
    if(this->Translator.load(":translations/file-manager_rus.qm")){
        QApplication::installTranslator(&Translator);
        execute_event_translate();
    }
}


void MainWindow::on_actionEnglish_triggered()
{
    if(this->Translator.load(":translations/file-manager_en.qm")){
        QApplication::installTranslator(&Translator);
        execute_event_translate();
    }
}


void MainWindow::copyPath(QString src, QString dst, QString untouched)
{
    QDir dir(src);

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        if (d == untouched)
            continue;
        QString dst_path = dst + QDir::separator() + d;
        if(dst_path == untouched)
            continue;
        dir.mkpath(dst_path);
        copyPath(src+ QDir::separator() + d, dst_path, untouched);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
    }
}


void MainWindow::on_Move_button_clicked()
{
    if (this->buffer == tr("Empty")){
        QMessageBox::warning(this, QObject::tr("Warning"), QObject::tr("Bufer is empty"));
        return;
    }
    //deleting name of file from buffer for "checker"
    QString check_path; int stop = 0;
    for(int i = 0; i < this->buffer.length();i++)
        if (this->buffer[i] == '/')
            stop = i;
    for(int i = 0; i < stop;i++)
        check_path+=this->buffer[i];

    if(check_path.length() == this->path.length()){
        QMessageBox::warning(this, QObject::tr("Warning"), QObject::tr("There is no point to move file/folder into the same directory"));
        return;
    }
    QDir checker1(this->buffer); QFile checker2(this->buffer); bool okay = false;
    if(!checker1.exists() && !checker2.exists()){
        QMessageBox::warning(this, QObject::tr("Warning"), QObject::tr("File in buffer is no longer exist"));
        return;
    }
    else if(!checker1.exists())
         okay = true;
    else if(checker1.exists() && this->path.length() < check_path.length()){
         okay = true;
    }

    if(okay == false){
        QMessageBox::critical(this,QObject::tr("Fail"),QObject::tr("Cant move folder"));
        return;
    }
    //copy
    QFile move2(this->buffer);
    QDir move1(this->buffer);
    if(!move1.exists() && !move2.exists()){
        QMessageBox::warning(this, QObject::tr("Warning"), QObject::tr("File/Folder in buffer is not exist anymore"));
        return;
    }
    QString name_of_file;
    int pos = 0;
    for(int i = 0 ; i < this->buffer.length();i++)
        if(this->buffer[i] == '/')
            pos = i+1;
    for(;pos < this->buffer.length();pos++)
        name_of_file+=this->buffer[pos];
    if(!move1.exists()){
        if(QFile::copy(this->buffer,this->path+"/"+name_of_file))
            qDebug() << "Done";
        else
            qDebug() << "Not done";
    } else{
        //создание папки
        QDir create(this->path);
        if(create.exists(this->path+"/"+name_of_file)){
            QMessageBox::warning(this, QObject::tr("Warning"), QObject::tr("This folder is already exists"));
            return;
        }
        if(!create.mkdir(this->path+"/"+name_of_file)){
            QMessageBox::critical(this,QObject::tr("Fail"),QObject::tr("Premission denied"));
            return;
        }
        copyPath(this->buffer,this->path+"/"+name_of_file,name_of_file);
    }
    //delete
    if (move1.exists()){
        QDir to_delete(this->buffer);
        if(!to_delete.removeRecursively())
            QMessageBox::critical(this,QObject::tr("Fail"),QObject::tr("Premission denied"));
    } else{
        if(!QFile::remove(this->buffer))
            QMessageBox::critical(this,QObject::tr("Fail"),QObject::tr("Premission denied"));
      }
    refresh_folder();
}


void MainWindow::on_Insert_button_clicked()
{
    if (this->buffer == tr("Empty")){
        QMessageBox::warning(this, QObject::tr("Warning"), QObject::tr("Bufer is empty"));
        return;
    }

    QFile move2(this->buffer);
    QDir move1(this->buffer);
    if(!move1.exists() && !move2.exists()){
        QMessageBox::warning(this, QObject::tr("Warning"), QObject::tr("File/Folder in buffer is not exist anymore"));
        return;
    }

    QString name_of_file;
    int pos = 0;
    for(int i = 0 ; i < this->buffer.length();i++)
        if(this->buffer[i] == '/')
            pos = i+1;
    for(;pos < this->buffer.length();pos++)
        name_of_file+=this->buffer[pos];

    if(!move1.exists()){
        QFile checker_exist(this->path+"/"+name_of_file);
        if(checker_exist.exists() == true){
            QMessageBox reply;
            reply.setText(tr("This file is already exist, still want to copy?"));
            reply.setWindowTitle(tr("Warning"));
            QAbstractButton* pButtonYes = reply.addButton(tr("Yes"), QMessageBox::YesRole);
            reply.addButton(tr("No"), QMessageBox::NoRole);
            reply.setStyleSheet("color: white; background-color: #181b28");
            reply.exec();

            if(!(reply.clickedButton() == pButtonYes))
                return;
            else
                while(true){
                    QString new_name; bool added = false;
                    for(int i = 0; i < name_of_file.length();i++){
                        if(name_of_file[i] == '.'){
                            new_name+="(1)";
                            added = true;
                        }
                        new_name+=name_of_file[i];
                    }
                    if (added == false)
                        new_name += "(1)";
                    name_of_file = new_name;
                    QFile test(this->path+"/"+name_of_file);
                    if(test.exists() == false)
                        break;
                }
        }
        if(QFile::copy(this->buffer,this->path+"/"+name_of_file))
            qDebug() << "Done";
        else
            qDebug() << "Not done";
    } else{
        //создание папки
        QDir create(this->path);
        if(create.exists(this->path+"/"+name_of_file)){
            QMessageBox::warning(this, QObject::tr("Warning"), QObject::tr("This folder is already exists"));
            return;
        }
        if(!create.mkdir(this->path+"/"+name_of_file)){
            QMessageBox::critical(this,QObject::tr("Fail"),QObject::tr("Premission denied"));
            return;
        }
        copyPath(this->buffer,this->path+"/"+name_of_file,name_of_file);
    }

    refresh_folder();
}

