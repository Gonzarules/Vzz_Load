#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QProcess>
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
#include <iterator>
#include <QDesktopWidget>
#include <QAbstractButton>
#include <QCheckBox>
#include <QRadioButton>
#include "parwindow.h"
#include "plotwindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();




    QString *Path= new QString;
    QFileInfoList *list = new QFileInfoList;
    QString fileName;
    QStringList *fileParList = new QStringList;
    QStringList *tempValue = new QStringList;
    QStringList *tempName = new QStringList;

    int spacer = 5;


    QStringList spin, calib, fwhm , npts, ipts, nEFGs, cMult, cAdd, fase, slope;
    QStringList w01, eta1, delta1, perc1, wb1, beta1, lambda1;
    QStringList w02, eta2, delta2, perc2, wb2, beta2, lambda2;
    QStringList w03, eta3, delta3, perc3, wb3, beta3;


//public slots:
//        void yourSlotName();


protected:
        void changeEvent(QEvent *event);


private slots:

        void readParFiles(QDir dirPath);

        void writeOutFile(QString File);

        void on_btnBrowse_clicked();

        //slot to emit
        void notifyChanges(const QString &path);

        void on_cmbTemp_activated();

        void on_btnSave_clicked();

        void on_btn_selectAll_clicked();

        void on_btn_clearAll_clicked();

        QVector<double> getDoubleValues(QStringList List);



public slots:


        //This will change the image in the dialog box
        void on_btnViewFile_clicked();

        void on_btnPlot_clicked();

        void createPlots();


private:
    Ui::MainWindow *ui;

    ParWindow *parwindow;


    //PlotWindow *plotwindow;
    PlotWindow *w01window,*w02window, *w03window;
    PlotWindow *eta01window, *eta02window, *eta03window;
    PlotWindow *delta01window,*delta02window, *delta03window;
    PlotWindow *wb01window, *wb02window, *wb03window;
    PlotWindow *beta01window, *beta02window, *beta03window;
    PlotWindow *perc01window, *perc02window, *perc03window;
    PlotWindow *lambda01window, *lambda02window;


    QString numero;
    QStringList parametersList;
    int *cmbTemp;
    QStringList titleAll;

    QFileSystemWatcher *watcherFilesChanged;



};

#endif // MAINWINDOW_H
