#include "QListViewExplorerModel.h"

#include <QPixmap>
#include <QDesktopServices>
#include <QListView>

QListViewExplorerModel::QListViewExplorerModel(QObject *parent):QAbstractListModel(parent){
}

void QListViewExplorerModel::getFolderList(QString folderPath, QFileInfoList *dirList){
    QDir dir = QDir(folderPath);
    *dirList = dir.entryInfoList(QDir::NoDot | QDir::Files | QDir::Dirs, QDir::DirsFirst | QDir::Name);
    this->beginResetModel();
        this->aDirList = dirList;
    this->endResetModel();

}

int QListViewExplorerModel::rowCount(const QModelIndex &) const{
    return this->aDirList->count();
}

QVariant QListViewExplorerModel::data( const QModelIndex &index, int role ) const
{

    QVariant value;

        switch ( role )
        {
            case Qt::DisplayRole: //string
            {
                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            case Qt::DecorationRole: //icon
            {
                if (this->aDirList->at(index.row()).isDir()) {
                    QPixmap icon = QPixmap(":/ico/img/ico/Folder.png");
                    QPixmap tmp = icon.scaled(30, 30, Qt::KeepAspectRatio);
                    value = tmp;
                    break;
                }

                if (this->aDirList->at(index.row()).isFile()) {
                    QString fileExt = this->aDirList->at(index.row()).completeSuffix();

                    while(true){
                        bool is_point = false; int pos = -1;

                        for(int i = 0; i < fileExt.length();i++)
                            if(fileExt[i] == '.'){
                                is_point = true;
                                pos = i+1;
                                break;
                            }
                        if (is_point == false)
                            break;
                        else{
                            QString text;
                            while(pos != fileExt.length()){
                                text+=fileExt[pos];
                                pos++;
                            }
                            fileExt = text;
                        }
                    }

                    QPixmap icon;
                    if (fileExt == "zip")
                        icon = QPixmap(":/ico/img/ico/zip.png");
                    else if (fileExt == "c")
                        icon = QPixmap(":/ico/img/ico/c.png");
                    else if (fileExt == "cpp")
                        icon = QPixmap(":/ico/img/ico/cpp.png");
                    else if (fileExt == "dat")
                        icon = QPixmap(":/ico/img/ico/dat.png");
                    else if (fileExt == "doc")
                        icon = QPixmap(":/ico/img/ico/doc.png");
                    else if (fileExt == "docx")
                        icon = QPixmap(":/ico/img/ico/docx.png");
                    else if (fileExt == "exe")
                        icon = QPixmap(":/ico/img/ico/exe.png");
                    else if (fileExt == "html")
                        icon = QPixmap(":/ico/img/ico/html.png");
                    else if (fileExt == "jpg")
                        icon = QPixmap(":/ico/img/ico/jpg.png");
                    else if (fileExt == "mp3")
                        icon = QPixmap(":/ico/img/ico/mp3.png");
                    else if (fileExt == "mp4")
                        icon = QPixmap(":/ico/img/ico/mp4.png");
                    else if (fileExt == "odt")
                        icon = QPixmap(":/ico/img/ico/odt.png");
                    else if (fileExt == "pdf")
                        icon = QPixmap(":/ico/img/ico/pdf.png");
                    else if (fileExt == "png")
                        icon = QPixmap(":/ico/img/ico/png.png");
                    else if (fileExt == "py")
                        icon = QPixmap(":/ico/img/ico/py.png");
                    else if (fileExt == "qt")
                        icon = QPixmap(":/ico/img/ico/qt.png");
                    else if (fileExt == "rar")
                        icon = QPixmap(":/ico/img/ico/rar.png");
                    else if (fileExt == "txt")
                        icon = QPixmap(":/ico/img/ico/txt.png");
                    else if (fileExt == "xls")
                        icon = QPixmap(":/ico/img/ico/xls.png");
                    else if (fileExt == "zip")
                        icon = QPixmap(":/ico/img/ico/zip.png");
                    else if (fileExt == "ovpn")
                        icon = QPixmap(":/ico/img/ico/openvpn.png");
                    else if (fileExt == "o")
                        icon = QPixmap(":/ico/img/ico/O.png");
                    else if (fileExt == "h")
                        icon = QPixmap(":/ico/img/ico/h.png");
                    else if (fileExt == "jar")
                        icon = QPixmap(":/ico/img/ico/java.png");
                    else if (fileExt == "xlsx")
                        icon = QPixmap(":/ico/img/ico/xlsx.png");
                    else if (fileExt == "xml")
                        icon = QPixmap(":/ico/img/ico/xml.png");
                    else if (fileExt == "csv")
                        icon = QPixmap(":/ico/img/ico/csv.png");
                    else if (fileExt == "sh")
                        icon = QPixmap(":/ico/img/ico/sh.jpeg");
                    else if (fileExt == "json")
                        icon = QPixmap(":/ico/img/ico/json.png");
                    else if (fileExt == "yaml")
                        icon = QPixmap(":/ico/img/ico/yaml.png");
                    else if (fileExt == "bin")
                        icon = QPixmap(":/ico/img/ico/binary.png");
                    else
                        icon = QPixmap(":/ico/img/ico/file.png");

                    QPixmap tmp = icon.scaled(30, 30, Qt::KeepAspectRatio);
                    value = tmp;
                    break;
                }

                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            case Qt::UserRole: //data
            {
                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            default:
                break;
        }

    return value;
}
