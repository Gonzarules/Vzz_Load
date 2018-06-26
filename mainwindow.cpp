#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString maintitle= "Vzz Load";
    this->setWindowTitle(maintitle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// //  ##########################################
//   ##########################
void MainWindow::changeEvent(QEvent *event)
{
QWidget::changeEvent(event);
    switch (event->type()) {
    case QEvent::LanguageChange:
    ui->retranslateUi(this);
        break;
    default:
        break;
    }

}


// //  ##########################################
// //   ##########################
void MainWindow::readParFiles(QDir dirPath)
{
    //dirPath= *Path;

    watcherFilesChanged = new QFileSystemWatcher(this);
    watcherFilesChanged->addPath(*Path);

    disconnect(watcherFilesChanged, SIGNAL(directoryChanged(QString)), this, SLOT(notifyChanges(QString)));


    dirPath.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dirPath.setSorting(QDir::Name | QDir::Reversed);

    QDir makeAbsolute(dirPath);
    ui->m_folderList->clear();


    *list = dirPath.entryInfoList();
    for(int i=0; i < list->size(); ++i )
    {
        ui->m_folderList->addItem(list->at(i).fileName());
    }

    ////    //################## //////use of watcher object to get its signals
    connect(watcherFilesChanged, SIGNAL(directoryChanged(QString)), this, SLOT(notifyChanges(QString)));
    connect(watcherFilesChanged, SIGNAL(fileChanged(QString)), this, SLOT(notifyChanges(QString)));


    ////    ////   ////////opening all .txt files in the chosen directory

    QStringList filters;
    filters << "*.txt";

    // /////////////////////////


    tempValue->clear();
    tempName->clear();

    spin.clear();
    calib.clear();
    fwhm.clear();
    npts.clear();
    ipts.clear();
    nEFGs.clear();
    cMult.clear();
    cAdd.clear();
    fase.clear();
    slope.clear();
    lambda1.clear();
    lambda2.clear();
    w01.clear();
    w02.clear();
    w03.clear();
    wb1.clear();
    wb2.clear();
    wb3.clear();
    beta1.clear();
    beta2.clear();
    beta3.clear();
    eta1.clear();
    eta2.clear();
    eta3.clear();
    delta1.clear();
    delta2.clear();
    delta3.clear();
    perc1.clear();
    perc2.clear();
    perc3.clear();



    foreach (fileName, dirPath.entryList(filters, QDir::Files))
    {


        QFile file(*Path + "/" + fileName);

        if(!file.exists())
        {

            //qDebug() << "File <i>cannot</i> be found "<<fileName;
            QMessageBox::information(this, "Information",  "file cannot be found!!");
        }else
        {
            //qDebug() << fileName<<" Opening...";
        }
        QString line;

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            while (!stream.atEnd())
            {
                line = stream.readAll();

                //qDebug() << "line: "<<line;


            }
        }

        file.close();

        *fileParList<< line;


        *tempValue << fileName.left(6);


        //qDebug()<<"complete filename" << fileName;
        //qDebug()<<"complete tempValue" << *tempValue;

        QString tempNameWithExtention = fileName.mid(8);

                tempNameWithExtention.chop(4);

        //qDebug()<<"tempName with ext" << tempNameWithExtention;

        QString tempNameWithoutExtention = tempNameWithExtention;

        *tempName << tempNameWithoutExtention;

        //qDebug()<<"complete tempName" << *tempName;


        titleAll << fileName;




        spin << line.mid(line.indexOf(", spin")-3,3);
        fwhm << line.mid(line.indexOf(", fwhm")-7,7);
        calib << line.mid(line.indexOf(", calib")-7,7);
        npts << line.mid(line.indexOf(",      npts")-3,3);
        ipts << line.mid(line.indexOf(", initial point to fit")-1,1);
        nEFGs << line.mid(line.indexOf(", n comb")-2,2);
        cMult << line.mid(line.indexOf(", cm multiplicative")-10,7);
        cAdd << line.mid(line.indexOf(", ca additive")-10,7);
        fase << line.mid(line.indexOf(", fase")-10,7);
        slope << line.mid(line.indexOf(", slope")-12,9);

        lambda1 << line.mid(line.indexOf("(Lambda1,")-14,7);
        lambda2 << line.mid(line.indexOf("(Lambda2,")-14,7);

        w01 << line.mid(line.indexOf(", w0(1)")-14,8);
        w02 << line.mid(line.indexOf(", w0(2)")-14,8);
        w03 << line.mid(line.indexOf(", w0(3)")-14,8);

        wb1 << line.mid(line.indexOf(", wb(1)")-14,8);
        wb2 << line.mid(line.indexOf(", wb(2)")-14,8);
        wb3 << line.mid(line.indexOf(", wb(3)")-14,8);


        beta1 << line.mid(line.indexOf(", beta(1)")-14,8);
        beta2 << line.mid(line.indexOf(", beta(2)")-14,8);
        beta3 << line.mid(line.indexOf(", beta(3)")-14,8);


        eta1 << line.mid(line.indexOf(", eta(1)")-14,8);
        eta2 << line.mid(line.indexOf(", eta(2)")-14,8);
        eta3 << line.mid(line.indexOf(", eta(3)")-14,8);

        delta1 << line.mid(line.indexOf(", f(1)")-146,6);
        delta2 << line.mid(line.indexOf(", f(2)")-146,6);
        delta3 << line.mid(line.indexOf(", f(3)")-146,6);

        perc1 << line.mid(line.indexOf(", f(1)")-14,8);
        perc2 << line.mid(line.indexOf(", f(2)")-14,8);
        perc3 << line.mid(line.indexOf(", f(3)")-14,8);



    }


}


// //  ##########################################
void MainWindow::writeOutFile(QString File)
{
        QFile outFile(File);

        if(!outFile.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::information(this, "Information",  "No data to Save!!");
            //qDebug() << "could not open file for writting";
            return;

        }

        QTextStream out(&outFile);
        out << "T(K)"     << '\t'
            << "spin(1)"  << '\t'
            << "FWHM(1)"  << '\t'
            << "calib(1)" << '\t'
            << "npts(1)"  << '\t'
            << "ipts(1)"  << '\t'

            << "W0(1)"	  << '\t'
            << "Wb(1)"	  << '\t'
            << "beta(1)"  << '\t'
            << "eta(1)"   << '\t'
            << "delta(1)" << '\t'
            << "phase(1)" << '\t'
            << "lambda"   << '\t'

            << "W0(2)"	  << '\t'
            << "Wb(2)"    << '\t'
            << "beta(2)"  << '\t'
            << "eta(2)"   << '\t'
            << "delta(2)" << '\t'
            << "phase(2)" << '\t'

            << "W0(3)"	  << '\t'
            << "Wb(3)"	  << '\t'
            << "beta(3)"  << '\t'
            << "eta(3)"	  << '\t'
            << "delta(3)" << '\t'
            << "phase(3)" << '\t'
            << "CM"       << '\t'
            << "CA"       << '\n';

       // int index= 0;
        for (int index = 0; index < fileParList->size(); index++) {



        out << tempValue->at(index) << '\t'
            << spin.at(index)       << '\t'
            << fwhm.at(index)       << '\t'
            << calib.at(index)      << '\t'
            << npts.at(index)       << '\t'
            << ipts.at(index)       << '\t'

            << w01.at(index)        << '\t'
            << wb1.at(index)        << '\t'
            << beta1.at(index)      << '\t'
            << eta1.at(index)       << '\t'
            << delta1.at(index)     << '\t'
            << perc1.at(index)      << '\t'
            << lambda1.at(index)    << '\t'

            << w02.at(index) << '\t'
            << wb2.at(index) << '\t'
            << beta2.at(index) << '\t'
            << eta2.at(index) << '\t'
            << delta2.at(index) << '\t'
            << perc2.at(index) << '\t'
            << lambda2.at(index) << '\t'

            << w03.at(index) << '\t'
            << wb3.at(index) << '\t'
            << beta3.at(index) << '\t'
            << eta3.at(index) << '\t'
            << delta3.at(index) << '\t'
            << perc3.at(index) << '\t'

            << cMult.at(index) << '\t'
            << cAdd.at(index) << '\t'


            << '\n'
               ;
        }


        outFile.flush();
        outFile.close();

}


// //  ##########################################
void MainWindow::on_btnBrowse_clicked()
{



    *Path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                              "/Users",
                                              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QDir dirPath = *Path;


    readParFiles(dirPath);



    // //// ### Fill the box in UI "working directory"
    ui->txtPath->setText(*Path);




    if(ui->cmbTemp->currentIndex()!=-1)
    {



        on_btn_clearAll_clicked();
        on_btnPlot_clicked();

        ui->cmbTemp->clear();

    }
    ui->cmbTemp->setCurrentIndex(-1);
    ui->cmbTemp->addItems(*tempValue);

    ui->cmbTemp->setCurrentText(tempValue->at(ui->cmbTemp->currentIndex()));

    on_cmbTemp_activated();

    //createPlots();




}

// //  ##########################################
// // ####################   implementation of function to check changes on the working folder
void MainWindow::notifyChanges(const QString &path)
{
       //qDebug() << "Signal recived!";
        QStringList oldList, newList;

        //getting the oldlist from the QListView widget
        //and the list which is the current files n the folder
        //then compare them together


                for(int i=0; i < ui->m_folderList-> count(); i++)
                {
                    QListWidgetItem *item= ui-> m_folderList -> item(i);
                    oldList << item->text();

                }
                std::sort(oldList.begin(), oldList.end());



                //now getting new status of folder
                QDir dir(path);


        dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
        dir.setSorting(QDir::Name);



        //get files and directories information on the folder
        QFileInfoList list=dir.entryInfoList();
        for(int i=0; i < list.size(); ++i )
        {
        newList<<list.at(i).fileName();
        }
        std::sort(newList.begin(), newList.end());

        //Difference between the two lists

        QSet<QString> intersection;
        if(oldList.count() > newList.count())
        {
                ui->m_folderList->clear();
                intersection=oldList.toSet().intersect(newList.toSet());
                foreach(const QString &value, intersection)
                {
                   ui->m_folderList->addItem(value);
                }
                    ui->lblResult->setText("! File REMOVED");

        }else if(oldList.count() < newList.count())
                {
                intersection=newList.toSet().subtract(oldList.toSet());
                foreach(const QString &value, intersection)
                    {
                        QListWidgetItem *wi = new QListWidgetItem;
                    wi = new QListWidgetItem;
                        wi->setText(value);
                        wi->setForeground(Qt::blue);
                        ui->m_folderList->addItem(wi);
                     }
                 ui->lblResult->setText("! File ADDED");
        }else{
                ui->lblResult->setText("! File MODIFIED");

              }
        }


// //  ##########################################
// // //////////////implementation of function to check changes ont eh combobox and adjust interface accordingly
void MainWindow::on_cmbTemp_activated()
{

            // ############## clear the name of the parameter file and place the one corresponding to the Temp.
                 ui->ledt_FileName->clear();
                 ui->ledt_FileName->setText(tempName->at(ui->cmbTemp->currentIndex()));




                 ui->ledtSpin->clear();
                 ui->ledtSpin->setText(spin.at(ui->cmbTemp->currentIndex()));

                 ui->ledtFWHM->clear();
                 ui->ledtFWHM->setText(fwhm.at(ui->cmbTemp->currentIndex()));


                 ui->ledtCalib->clear();
                 ui->ledtCalib->setText(calib.at(ui->cmbTemp->currentIndex()));

                 ui->ledtNpts->clear();
                 ui->ledtNpts->setText(npts.at(ui->cmbTemp->currentIndex()));

                 ui->ledtNEFGs->clear();
                 ui->ledtNEFGs->setText(nEFGs.at(ui->cmbTemp->currentIndex()));

                 ui->ledtCMult->clear();
                 ui->ledtCMult->setText(cMult.at(ui->cmbTemp->currentIndex()));

                 ui->ledtCAdd->clear();
                 ui->ledtCAdd->setText(cAdd.at(ui->cmbTemp->currentIndex()));

                 ui->ledtfase->clear();
                 ui->ledtfase->setText(fase.at(ui->cmbTemp->currentIndex()));

                 ui->ledtslope->clear();
                 ui->ledtslope->setText(slope.at(ui->cmbTemp->currentIndex()));

                 ui->ledtlambda1->clear();
                 ui->ledtlambda1->setText(lambda1.at(ui->cmbTemp->currentIndex()));

                 ui->ledtlambda2->clear();
                 ui->ledtlambda2->setText(lambda1.at(ui->cmbTemp->currentIndex()));





                // set values of w0
                 ui->ledtW01->clear();
                 ui->ledtW01->setText(w01.at(ui->cmbTemp->currentIndex()));

                 ui->ledtW02->clear();
                 ui->ledtW02->setText(w02.at(ui->cmbTemp->currentIndex()));

                 ui->ledtW03->clear();
                 ui->ledtW03->setText(w03.at(ui->cmbTemp->currentIndex()));

                // set values of wb
                 ui->ledtWb1->clear();
                 ui->ledtWb1->setText(wb1.at(ui->cmbTemp->currentIndex()));

                 ui->ledtWb2->clear();
                 ui->ledtWb2->setText(wb2.at(ui->cmbTemp->currentIndex()));

                 ui->ledtWb3->clear();
                 ui->ledtWb3->setText(wb3.at(ui->cmbTemp->currentIndex()));

                // set values of Beta
                 ui->ledtBeta1->clear();
                 ui->ledtBeta1->setText(beta1.at(ui->cmbTemp->currentIndex()));

                 ui->ledtBeta2->clear();
                 ui->ledtBeta2->setText(beta2.at(ui->cmbTemp->currentIndex()));

                 ui->ledtBeta3->clear();
                 ui->ledtBeta3->setText(beta3.at(ui->cmbTemp->currentIndex()));

                // set values of Eta
                 ui->ledtEta1->clear();
                 ui->ledtEta1->setText(eta1.at(ui->cmbTemp->currentIndex()));

                 ui->ledtEta2->clear();
                 ui->ledtEta2->setText(eta2.at(ui->cmbTemp->currentIndex()));

                 ui->ledtEta3->clear();
                 ui->ledtEta3->setText(eta3.at(ui->cmbTemp->currentIndex()));


                 // set values of Beta
                 ui->ledtDelta1->clear();
                 ui->ledtDelta1->setText(delta1.at(ui->cmbTemp->currentIndex()));

                 ui->ledtDelta2->clear();
                 ui->ledtDelta2->setText(delta2.at(ui->cmbTemp->currentIndex()));

                 ui->ledtDelta3->clear();
                 ui->ledtDelta3->setText(delta3.at(ui->cmbTemp->currentIndex()));

                 // set values of fase percentage %
                 ui->ledtPhase1->clear();
                 ui->ledtPhase1->setText(perc1.at(ui->cmbTemp->currentIndex()));


                 ui->ledtPhase2->clear();
                 ui->ledtPhase2->setText(perc2.at(ui->cmbTemp->currentIndex()));


                 ui->ledtPhase3->clear();
                 ui->ledtPhase3->setText(perc3.at(ui->cmbTemp->currentIndex()));


                 createPlots();

}


// //  ##########################################
// // //////////////implementation of function to view parameters files in new window
void MainWindow::on_btnViewFile_clicked()
{

    //parwindow->close();
    int value = ui->cmbTemp->currentIndex();

    //qDebug()<< "The value is"<<value;

    QSize mainWSize = this->size();
    int mainWPosX = this->x();
    int mainWPosY = this->y();

    parwindow = new ParWindow;
    int mainWwidth =mainWSize.width();
    //int width = Ui_MainWindow.width();
    //int mainWheight = mainWSize.height();

    parwindow->move(mainWPosX + mainWwidth + 5,mainWPosY);


    // if button pressd before loading data
    if (value == -1)
    {

        QMessageBox::information(this, "Information",  "Load Files first!!");

    }else{

        QString parname = fileParList->at(ui->cmbTemp->currentIndex());
        QString title = titleAll.at(ui->cmbTemp->currentIndex());
        parwindow->setFile(parname, title);
        parwindow->show();

    }


}


// //  ##########################################
void MainWindow::on_btnSave_clicked()
{

        QString output = *Path+"/"+"./Output.dat";

        writeOutFile(output);


}

// //  ##########################################
QVector<double> MainWindow::getDoubleValues(QStringList List){

    // ############################################
    // GET vector with values
    QVector<double> dvector;
    for(int i=0;i<tempValue->size();i++)
    {
        QString string = List.at(i);

        //qDebug() << "temp string is:  " << string;
        double dvalue = string.toDouble();
        dvector.append(dvalue);

    }
return dvector;

}


// //  ##########################################
void MainWindow::createPlots(){

    QSize mainWSize = this->size();
    int mainWPosX = this->x();
    int mainWPosY = this->y();
    int mainWwidth =mainWSize.width();
    //int width = Ui_MainWindow.width();
    //int mainWheight = mainWSize.height();

    // qDebug() << "before cyle:  " ;
    QVector<double> xList;



    //w01window->close();

    // ############################################
    // GET vector with values of X. temperature values
    for(int i=0;i<tempValue->size();i++)
    {
        QString string = tempValue->at(i);

        //qDebug() << "temp string is:  " << string;
        double dvalue = string.toDouble();
        xList.append(dvalue);

    }

    //  qDebug() << "templist" <<xList;



    // // ############################################
    // // GET vector with values of spin.
    QVector<double> spinList;
    spinList.clear();
    spinList = getDoubleValues(spin);
    //qDebug() << "spinlist" <<spinList;

    // // ############################################
    // // GET vector with values of calib.
    QVector<double>  calibList = getDoubleValues(calib);
    //qDebug() << "caliblist" <<calibList;

    // // ############################################
    // // GET vector with values of .fwhm
    QVector<double>  fwhmList = getDoubleValues(fwhm);
    //qDebug() << "fwhmlist" <<calibList;

    // // ############################################
    // // GET vector with values of npts.
    QVector<double>  nptsList = getDoubleValues(npts);
    //qDebug() << "nptslist" <<nptsList;

    // // ############################################
    // // GET vector with values of ipts.
    QVector<double>  iptsList = getDoubleValues(ipts);
    // qDebug() << "caliblist" <<iptsList;

    // // ############################################
    // // GET vector with values of nEFGs.
    QVector<double>  nEFGsList = getDoubleValues(nEFGs);
    //qDebug() << "nEFGslist" <<nEFGsList;

    // // ############################################
    // // GET vector with values of cMult.
    QVector<double>  cMultList = getDoubleValues(cMult);
    //qDebug() << "cMultlist" <<cMultList;

    // // ############################################
    // // GET vector with values of cAdd.
    QVector<double>  cAddList = getDoubleValues(cAdd);
    //qDebug() << "cAddlist" <<cAddList;

    // // ############################################
    // // GET vector with values of fase.
    QVector<double>  faseList = getDoubleValues(fase);
    //qDebug() << "faselist" <<faseList;

    // // ############################################
    // // GET vector with values of slope.
    QVector<double>  slopeList = getDoubleValues(slope);
    //qDebug() << "slopelist" <<slopeList;

    // // ############################################
    // // GET vector with values of lambda 1.
    QVector<double>  lambda1List = getDoubleValues(lambda1);
    //qDebug() << "lambdalist" <<lambda1List;

    // // ############################################
    // // GET vector with values of lambda2.
    QVector<double>  lambda2List = getDoubleValues(lambda2);
    //qDebug() << "lambda2list" <<lambda2List;



    // // ############################################
    // // GET vector with values of W01.
    QVector<double>  w01List = getDoubleValues(w01);
    //qDebug() << "w01list" <<w01List;

    // // ############################################
    // // GET vector with values of W02.
    QVector<double>  w02List = getDoubleValues(w02);
    //qDebug() << "w02list" <<w02List;

    // // ############################################
    // // GET vector with values of W03.
    QVector<double>  w03List = getDoubleValues(w03);
    //qDebug() << "w03list" <<w03List;




    // // ############################################
    // // GET vector with values of wb1.
    QVector<double>  wb1List = getDoubleValues(wb1);
    //qDebug() << "wb1list" <<wb1List;

    // // ############################################
    // // GET vector with values of wb2.
    QVector<double>  wb2List = getDoubleValues(wb2);
    //qDebug() << "wb2list" <<wb2List;

    // // ############################################
    // // GET vector with values of wb3.
    QVector<double>  wb3List = getDoubleValues(wb3);
    //qDebug() << "wb3list" <<wb3List;



    // // ############################################
    // // GET vector with values of beta1.
    QVector<double>  beta1List = getDoubleValues(beta1);
    // qDebug() << "wb1list" <<wb1List;

    // // ############################################
    // // GET vector with values of beta2.
    QVector<double>  beta2List = getDoubleValues(beta2);
    //qDebug() << "beta2list" <<beta2List;

    // // ############################################
    // // GET vector with values of wb3.
    QVector<double>  beta3List = getDoubleValues(beta3);
    //qDebug() << "beta3list" <<beta3List;




    // // ############################################
    // // GET vector with values of eta1.
    QVector<double>  eta1List = getDoubleValues(eta1);
    //qDebug() << "wb1list" <<eta1List;

    // // ############################################
    // // GET vector with values of eta2.
    QVector<double>  eta2List = getDoubleValues(eta2);
    // qDebug() << "eta2list" <<eta2List;

    // // ############################################
    // // GET vector with values of eta3.
    QVector<double>  eta3List = getDoubleValues(eta3);
    // qDebug() << "eta3list" <<eta3List;




    // // ############################################
    // // GET vector with values of delta1.
    QVector<double>  delta1List = getDoubleValues(delta1);
    //qDebug() << "delta1list" <<delta1List;

    // // ############################################
    // // GET vector with values of delta2.
    QVector<double>  delta2List = getDoubleValues(delta2);
    //qDebug() << "delta2list" <<delta2List;

    // // ############################################
    // // GET vector with values of delta3.
    QVector<double>  delta3List = getDoubleValues(delta3);
    //qDebug() << "delta3list" <<delta3List;



    // // ############################################
    // // GET vector with values of perc1.
    QVector<double>  perc1List = getDoubleValues(perc1);
    //qDebug() << "perc1list" <<perc1List;

    // // ############################################
    // // GET vector with values of perc2.
    QVector<double>  perc2List = getDoubleValues(perc2);
    //qDebug() << "perc2list" <<perc2List;

    // // ############################################
    // // GET vector with values of perc3.
    QVector<double>  perc3List = getDoubleValues(perc3);
    // qDebug() << "perc3list" <<perc3List;




    // //  ##########################################
    // //  ######  PLOT WO_1   ######

    w01window = new PlotWindow();
    w01window->setAttribute(Qt::WA_DeleteOnClose);
    w01window->makePlot(ui->cmbTemp->currentIndex(), xList, w01List, "W0 EFG01", "Temperature (K)", "W01 (Mrads/s)", Qt::blue);
    w01window->move(mainWPosX + mainWwidth + 5,mainWPosY);


    // //  ##########################################
    // //  ######  PLOT WO_2   ######

    w02window = new PlotWindow();
    w02window->setAttribute(Qt::WA_DeleteOnClose);
    w02window->makePlot(ui->cmbTemp->currentIndex(), xList, w02List, "W0 EFG02", "Temperature (K)", "W02 (Mrads/s)", Qt::green);
    w02window->move(mainWPosX + mainWwidth + 5,mainWPosY + 280);

    // //  ##########################################
    // //  ######  PLOT WO_3   ######

    w03window = new PlotWindow();
    w03window->setAttribute(Qt::WA_DeleteOnClose);
    w03window->makePlot(ui->cmbTemp->currentIndex(), xList, w03List, "W0 EFG03", "Temperature (K)", "W03 (Mrads/s)", Qt::darkRed);
    w03window->move(mainWPosX + mainWwidth + 5,mainWPosY + 560);


    // //  ##########################################
    // //  ######  PLOT Eta_1   ######

    eta01window = new PlotWindow();
    eta01window->setAttribute(Qt::WA_DeleteOnClose);
    eta01window->makePlot(ui->cmbTemp->currentIndex(), xList, eta1List, "Eta EFG01", "Temperature (K)", "Eta (1)", Qt::blue);
    eta01window->move(mainWPosX + mainWwidth + 350,mainWPosY);


    // //  ##########################################
    // //  ######  PLOT Eta_2   ######

    eta02window = new PlotWindow();
    eta02window->setAttribute(Qt::WA_DeleteOnClose);
    eta02window->makePlot(ui->cmbTemp->currentIndex(), xList, eta2List, "Eta EFG02", "Temperature (K)", "Eta (2)", Qt::green);
    eta02window->move(mainWPosX + mainWwidth + 350,mainWPosY+280);

    // //  ##########################################
    // //  ######  PLOT Eta_3   ######

    eta03window = new PlotWindow();
    eta03window->setAttribute(Qt::WA_DeleteOnClose);
    eta03window->makePlot(ui->cmbTemp->currentIndex(), xList, eta3List, "Eta EFG03", "Temperature (K)", "Eta (3)", Qt::darkRed);
    eta03window->move(mainWPosX + mainWwidth + 350,mainWPosY+560);


    // //  ##########################################
    // //  ######  PLOT delta_1   ######

    delta01window = new PlotWindow();
    delta01window->setAttribute(Qt::WA_DeleteOnClose);
    delta01window->makePlot(ui->cmbTemp->currentIndex(), xList, delta1List, "Delta EFG01", "Temperature (K)", "Delta (1) (%)", Qt::blue);
    delta01window->move(mainWPosX + mainWwidth + 695,mainWPosY );


    // //  ##########################################
    // //  ######  PLOT delta_2   ######

    delta02window = new PlotWindow();
    delta02window->setAttribute(Qt::WA_DeleteOnClose);
    delta02window->makePlot(ui->cmbTemp->currentIndex(), xList, delta2List, "delta EFG02", "Temperature (K)", "Delta (2) (%)", Qt::green);
    delta02window->move(mainWPosX + mainWwidth + 695,mainWPosY + 280);

    // //  ##########################################
    // //  ######  PLOT delta_3   ######

    delta03window = new PlotWindow();
    delta03window->setAttribute(Qt::WA_DeleteOnClose);
    delta03window->makePlot(ui->cmbTemp->currentIndex(), xList, delta3List, "delta EFG03", "Temperature (K)", "Deltta (3) (%)", Qt::darkRed);
    delta03window->move(mainWPosX + mainWwidth + 695,mainWPosY + 560);


    // //  ##########################################
    // //  ######  PLOT wb01   ######

    wb01window = new PlotWindow();
    wb01window->setAttribute(Qt::WA_DeleteOnClose);
    wb01window->makePlot(ui->cmbTemp->currentIndex(), xList, wb1List, "wb EFG01", "Temperature (K)", "wb (1) (Mrads/s)", Qt::blue);
    wb01window->move(mainWPosX + mainWwidth + 5,mainWPosY);


    // //  ##########################################
    // //  ######  PLOT wb_2   ######

    wb02window = new PlotWindow();
    wb02window->setAttribute(Qt::WA_DeleteOnClose);
    wb02window->makePlot(ui->cmbTemp->currentIndex(), xList, wb2List, "wb EFG02", "Temperature (K)", "wb (2) (Mrads/s)", Qt::green);
    wb02window->move(mainWPosX + mainWwidth + 5,mainWPosY+280);

    // //  ##########################################
    // //  ######  PLOT wb_3   ######

    wb03window = new PlotWindow();
    wb03window->setAttribute(Qt::WA_DeleteOnClose);
    wb03window->makePlot(ui->cmbTemp->currentIndex(), xList, wb3List, "wb EFG03", "Temperature (K)", "wb (3) (Mrads/s)", Qt::darkRed);
    wb03window->move(mainWPosX + mainWwidth + 5,mainWPosY+560);


    // //  ##########################################
    // //  ######  PLOT beta_1   ######

    beta01window = new PlotWindow();
    beta01window->setAttribute(Qt::WA_DeleteOnClose);
    beta01window->makePlot(ui->cmbTemp->currentIndex(), xList, beta1List, "beta EFG01", "Temperature (K)", "beta (1) (Mrads/s)", Qt::blue);
    beta01window->move(mainWPosX + mainWwidth + 350,mainWPosY);


    // //  ##########################################
    // //  ######  PLOT beta_2   ######

    beta02window = new PlotWindow();
    beta02window->setAttribute(Qt::WA_DeleteOnClose);
    beta02window->makePlot(ui->cmbTemp->currentIndex(), xList, beta2List, "beta EFG02", "Temperature (K)", "beta (2) (Mrads/s)", Qt::green);
    beta02window->move(mainWPosX + mainWwidth + 350,mainWPosY+280);

    // //  ##########################################
    // //  ######  PLOT beta_3   ######

    beta03window = new PlotWindow();
    beta03window->setAttribute(Qt::WA_DeleteOnClose);
    beta03window->makePlot(ui->cmbTemp->currentIndex(), xList, beta3List, "beta EFG03", "Temperature (K)", "beta (3) (Mrads/s)", Qt::darkRed);
    beta03window->move(mainWPosX + mainWwidth + 350,mainWPosY+560);


    // //  ##########################################
    // //  ######  PLOT perc_1   ######

    perc01window = new PlotWindow();
    perc01window->setAttribute(Qt::WA_DeleteOnClose);
    perc01window->makePlot(ui->cmbTemp->currentIndex(), xList, perc1List, "perc EFG01", "Temperature (K)", "perc (1) (Mrads/s)", Qt::blue);
    perc01window->move(mainWPosX + mainWwidth + 1040,mainWPosY);


    // //  ##########################################
    // //  ######  PLOT perc_2   ######

    perc02window = new PlotWindow();
    perc02window->setAttribute(Qt::WA_DeleteOnClose);
    perc02window->makePlot(ui->cmbTemp->currentIndex(), xList, perc2List, "perc EFG02", "Temperature (K)", "perc (2) (Mrads/s)", Qt::green);
    perc02window->move(mainWPosX + mainWwidth + 1040,mainWPosY+280);

    // //  ##########################################
    // //  ######  PLOT perc_3   ######

    perc03window = new PlotWindow();
    perc03window->setAttribute(Qt::WA_DeleteOnClose);
    perc03window->makePlot(ui->cmbTemp->currentIndex(), xList, perc3List, "perc EFG03", "Temperature (K)", "perc (3) (Mrads/s)", Qt::darkRed);
    perc03window->move(mainWPosX + mainWwidth + 1040,mainWPosY+560);


    // //  ##########################################
    // //  ######  PLOT lambda_1   ######

    lambda01window = new PlotWindow();
    lambda01window->setAttribute(Qt::WA_DeleteOnClose);
    lambda01window->makePlot(ui->cmbTemp->currentIndex(), xList, lambda1List, "lambda EFG01", "Temperature (K)", "lambda (1) (Mrads/s)", Qt::blue);
    lambda01window->move(mainWPosX + mainWwidth + 5,mainWPosY+840);


    // //  ##########################################
    // //  ######  PLOT lambda_2   ######

    lambda02window = new PlotWindow();
    lambda02window->setAttribute(Qt::WA_DeleteOnClose);
    lambda02window->makePlot(ui->cmbTemp->currentIndex(), xList, lambda2List, "lambda EFG02", "Temperature (K)", "lambda (2) (Mrads/s)", Qt::green);
    lambda02window->move(mainWPosX + mainWwidth + 350,mainWPosY+840);


}


// //  ##########################################
void MainWindow::on_btnPlot_clicked()
{



    if (ui->cmbTemp->currentIndex() == -1)
    {

        //qDebug() << "Load Data First" ;
        QMessageBox::information(this, "Information",  "Load files first!!");

    }else{



        // //  ##########################################
        // //  ######  PLOT WO_1   ######

        if(ui->rb_w0_1->isChecked()==true)
        {
            w01window->show();
        }

        if(ui->rb_w0_1->isChecked()==false)
        {
            w01window->hide();
        }

        // //  ##########################################
        // //  ######  PLOT WO_2   ######

        if(ui->rb_w0_2->isChecked()==true)
        {
            w02window->show();
        }

        if(ui->rb_w0_2->isChecked()==false)
        {
            w02window->hide();
        }

        // //  ##########################################
        // //  ######  PLOT WO_3   ######

        if(ui->rb_w0_3->isChecked()==true)
        {
            w03window->show();
        }

        if(ui->rb_w0_3->isChecked()==false)
        {
            w03window->hide();
        }

        // //  ##########################################
        // //  ######  PLOT eta_1   ######

        if(ui->rb_eta_1->isChecked()==true)
        {
            eta01window->show();
        }

        if(ui->rb_eta_1->isChecked()==false)
        {
            eta01window->hide();
        }

        // //  ##########################################
        // //  ######  PLOT eta_2   ######

        if(ui->rb_eta_2->isChecked()==true)
        {
            eta02window->show();
        }

        if(ui->rb_eta_2->isChecked()==false)
        {
            eta02window->hide();
        }

        // //  ##########################################
        // //  ######  PLOT eta_3   ######

        if(ui->rb_eta_3->isChecked()==true)
        {
            eta03window->show();
        }

        if(ui->rb_eta_3->isChecked()==false)
        {
            eta03window->hide();
        }

        // //  ##########################################
        // //  ######  PLOT delta_1   ######

        if(ui->rb_delta_1->isChecked()==true)
        {
            delta01window->show();
        }

        if(ui->rb_delta_1->isChecked()==false)
        {
            delta01window->hide();
        }


        // //  ##########################################
        // //  ######  PLOT delta_2   ######

        if(ui->rb_delta_2->isChecked()==true)
        {
            delta02window->show();
        }

        if(ui->rb_delta_2->isChecked()==false)
        {
            delta02window->hide();
        }


        // //  ##########################################
        // //  ######  PLOT delta_3   ######

        if(ui->rb_delta_3->isChecked()==true)
        {
            delta03window->show();
        }

        if(ui->rb_delta_3->isChecked()==false)
        {
            delta03window->hide();

        }

        // //  ##########################################
        // //  ######  PLOT wb_1   ######

        if(ui->rb_wb_1->isChecked()==true)
        {
            wb01window->show();
        }

        if(ui->rb_wb_1->isChecked()==false)
        {
            wb01window->hide();
        }


        // //  ##########################################
        // //  ######  PLOT wb_2   ######

        if(ui->rb_wb_2->isChecked()==true)
        {
            wb02window->show();
        }

        if(ui->rb_wb_2->isChecked()==false)
        {
            wb02window->hide();
        }


        // //  ##########################################
        // //  ######  PLOT wb_3   ######

        if(ui->rb_wb_3->isChecked()==true)
        {
            wb03window->show();
        }

        if(ui->rb_wb_3->isChecked()==false)
        {
            wb03window->hide();

        }


        // //  ##########################################
        // //  ######  PLOT beta_1   ######

        if(ui->rb_beta_1->isChecked()==true)
        {
            beta01window->show();
        }

        if(ui->rb_beta_1->isChecked()==false)
        {
            beta01window->hide();
        }


        // //  ##########################################
        // //  ######  PLOT beta_2   ######

        if(ui->rb_beta_2->isChecked()==true)
        {
            beta02window->show();
        }

        if(ui->rb_beta_2->isChecked()==false)
        {
            beta02window->hide();
        }


        // //  ##########################################
        // //  ######  PLOT beta_3   ######

        if(ui->rb_beta_3->isChecked()==true)
        {
            beta03window->show();
        }

        if(ui->rb_beta_3->isChecked()==false)
        {
            beta03window->hide();

        }


        // //  ##########################################
        // //  ######  PLOT perc_1   ######

        if(ui->rb_perc_1->isChecked()==true)
        {
            perc01window->show();
        }

        if(ui->rb_perc_1->isChecked()==false)
        {
            perc01window->hide();
        }


        // //  ##########################################
        // //  ######  PLOT perc_2   ######

        if(ui->rb_perc_2->isChecked()==true)
        {
            perc02window->show();
        }

        if(ui->rb_perc_2->isChecked()==false)
        {
            perc02window->hide();
        }


        // //  ##########################################
        // //  ######  PLOT perc_3   ######

        if(ui->rb_perc_3->isChecked()==true)
        {
            perc03window->show();
        }

        if(ui->rb_perc_3->isChecked()==false)
        {
            perc03window->hide();

        }



        // //  ##########################################
        // //  ######  PLOT lambda_1   ######

        if(ui->rb_lambda_1->isChecked()==true)
        {
            lambda01window->show();
        }

        if(ui->rb_lambda_1->isChecked()==false)
        {
            lambda01window->hide();
        }


        // //  ##########################################
        // //  ######  PLOT lambda_2   ######

        if(ui->rb_lambda_2->isChecked()==true)
        {
            lambda02window->show();
        }

        if(ui->rb_lambda_2->isChecked()==false)
        {
            lambda02window->hide();
        }


    }

}


// //  ##########################################
void MainWindow::on_btn_selectAll_clicked()
{



//ui->g_folderList->addItem("teste");
  // rb_test->setChecked(true);
//ui->rb_test->setChecked(true);

//qDebug() << ui->rb_test->isChecked(); // "false"

    ui->rb_w0_1->setChecked(true);
    ui->rb_w0_1->repaint();
    ui->rb_w0_2->setChecked(true);
    ui->rb_w0_2->repaint();
    ui->rb_w0_3->setChecked(true);
    ui->rb_w0_3->repaint();

    ui->rb_eta_1->setChecked(true);
    ui->rb_eta_1->repaint();
    ui->rb_eta_2->setChecked(true);
    ui->rb_eta_2->repaint();
    ui->rb_eta_3->setChecked(true);
    ui->rb_eta_3->repaint();

    ui->rb_delta_1->setChecked(true);
    ui->rb_delta_1->repaint();
    ui->rb_delta_2->setChecked(true);
    ui->rb_delta_2->repaint();
    ui->rb_delta_3->setChecked(true);
    ui->rb_delta_3->repaint();

    ui->rb_wb_1->setChecked(true);
    ui->rb_wb_1->repaint();
    ui->rb_wb_2->setChecked(true);
    ui->rb_wb_2->repaint();
    ui->rb_wb_3->setChecked(true);
    ui->rb_wb_3->repaint();

    ui->rb_beta_1->setChecked(true);
    ui->rb_beta_1->repaint();
    ui->rb_beta_2->setChecked(true);
    ui->rb_beta_2->repaint();
    ui->rb_beta_3->setChecked(true);
    ui->rb_beta_3->repaint();

    ui->rb_perc_1->setChecked(true);
    ui->rb_perc_1->repaint();
    ui->rb_perc_2->setChecked(true);
    ui->rb_perc_2->repaint();
    ui->rb_perc_3->setChecked(true);
    ui->rb_perc_3->repaint();

    ui->rb_lambda_1->setChecked(true);
    ui->rb_lambda_1->repaint();
    ui->rb_lambda_2->setChecked(true);
    ui->rb_lambda_2->repaint();


}


// //  ##########################################
void MainWindow::on_btn_clearAll_clicked()
{

    ui->rb_w0_1->setChecked(false);
    ui->rb_w0_1->repaint();
    ui->rb_w0_2->setChecked(false);
    ui->rb_w0_2->repaint();
    ui->rb_w0_3->setChecked(false);
    ui->rb_w0_3->repaint();

    ui->rb_eta_1->setChecked(false);
    ui->rb_eta_1->repaint();
    ui->rb_eta_2->setChecked(false);
    ui->rb_eta_2->repaint();
    ui->rb_eta_3->setChecked(false);
    ui->rb_eta_3->repaint();

    ui->rb_delta_1->setChecked(false);
    ui->rb_delta_1->repaint();
    ui->rb_delta_2->setChecked(false);
    ui->rb_delta_2->repaint();
    ui->rb_delta_3->setChecked(false);
    ui->rb_delta_3->repaint();

    ui->rb_wb_1->setChecked(false);
    ui->rb_wb_1->repaint();
    ui->rb_wb_2->setChecked(false);
    ui->rb_wb_2->repaint();
    ui->rb_wb_3->setChecked(false);
    ui->rb_wb_3->repaint();

    ui->rb_beta_1->setChecked(false);
    ui->rb_beta_1->repaint();
    ui->rb_beta_2->setChecked(false);
    ui->rb_beta_2->repaint();
    ui->rb_beta_3->setChecked(false);
    ui->rb_beta_3->repaint();

    ui->rb_perc_1->setChecked(false);
    ui->rb_perc_1->repaint();
    ui->rb_perc_2->setChecked(false);
    ui->rb_perc_2->repaint();
    ui->rb_perc_3->setChecked(false);
    ui->rb_perc_3->repaint();

    ui->rb_lambda_1->setChecked(false);
    ui->rb_lambda_1->repaint();
    ui->rb_lambda_2->setChecked(false);
    ui->rb_lambda_2->repaint();


}




