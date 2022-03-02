#ifndef NEWFILE_H
#define NEWFILE_H

#include <QDialog>

namespace Ui {
class NewFile;
}

class NewFile : public QDialog
{
    Q_OBJECT

public:
    explicit NewFile(QWidget *parent = nullptr);
    ~NewFile();
    QString path;
private slots:
    void on_cancel_clicked();

    void on_create_clicked();

private:
    Ui::NewFile *ui;
};

#endif // NEWFILE_H
