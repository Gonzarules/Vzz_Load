#ifndef PARWINDOW_H
#define PARWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include <algorithm>
#include <stdlib.h>
#include <QStringRef>
#include <QListWidgetItem>
#include <QTemporaryDir>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSettings>
#include <QJsonArray>
#include <QVector>
#include <QLinkedList>

namespace Ui {
class ParWindow;
}

class ParWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ParWindow(QWidget *parent = 0);
    ~ParWindow();

//void setText(QString numero);
void setFile(QString parname, QString tile);


//  private slots:

//        void fillText();




private:
    Ui::ParWindow *ui;



    QString numero;
    QStringList *parametersList;
    QString parname;
    QString titleAll;
    int *cmbTemp;

};

#endif // PARWINDOW_H
