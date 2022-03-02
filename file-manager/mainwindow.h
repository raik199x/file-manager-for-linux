#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QListViewExplorerModel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refresh_folder();

private slots:
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_list_clicked();

    void on_icon_list_clicked();

    void on_lineEdit_editingFinished();

    void on_Copy_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_Create_clicked();

    void on_Delete_clicked();

    void on_actionRussian_triggered();

    void on_actionEnglish_triggered();

    void execute_event_translate();

    void on_Move_button_clicked();

    void copyPath(QString src, QString dst, QString untouched);

    void on_Insert_button_clicked();

private:
    Ui::MainWindow *ui;
    QFileInfoList *aDirList;
    QListViewExplorerModel *model;
    QModelIndex MyIndex;
    QString path;
    QString buffer;
    QTranslator Translator;
};
#endif // MAINWINDOW_H
