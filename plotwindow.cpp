#include "plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);

    //PlotWindow::makePlot(QStringList xlist, QStringList ylist, QString graphTitle);
}

PlotWindow::~PlotWindow()
{
    delete ui;
}


void PlotWindow::closeWindow()
{

   delete ui;

}





void PlotWindow::makePlot(int n, QVector<double> xList, QVector<double> yList, QString graphTitle, QString xLabel, QString yLabel, QColor color)
{





this->setWindowTitle(graphTitle);

    //ui->customPlot->installEventFilter(this);

    //connverster as listas de parametros para vectores

QVector<double> x(xList.size()), y(yList.size());
QVector<double> x1(xList.size()), y1(yList.size());
QVector<double> x_black(1), y_black(1);


 x= xList;
 y= yList;


x_black[0]= xList.at(n);
y_black[0]= yList.at(n);






//  ##############################  ALL PLOT  ######################3
    // create graph and assign data to it:


ui->customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));


//ui->customPlot->legend->setVisible(true);
//ui->customPlot->legend->setFont(QFont("Helvetica",9));
//ui->customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));






ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);



//QPainter painter(this);
QPen pen;  // creates a default pen

pen.setStyle(Qt::DashLine);
pen.setWidth(1);
pen.setBrush(color);
//pen.setCapStyle(Qt::RoundCap);
//pen.setJoinStyle(Qt::RoundJoin);

//ui->customPlot->graph(0)->setPen(pen);

    ui->customPlot->addGraph();

   ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8));
  // ui->customPlot->graph(0)->setPen(QPen(color));
   ui->customPlot->graph(0)->setPen(pen);



//   //  ##############################  BLACK POINT  ######################3
   // setup for graph 4: key axis right, value axis top
   // will contain parabolically distributed data points with some random perturbance
   //ui->customPlot->addGraph(ui->customPlot->yAxis2, ui->customPlot->xAxis2);
   ui->customPlot->addGraph();
   ui->customPlot->graph(1)->setPen(QColor(50, 50, 50, 255));

   ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
   ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));



       ui->customPlot->graph(0)->setData(x, y);
       ui->customPlot->graph(1)->setData(x_black, y_black);

//           ui->customPlot->xAxis->setRange(0,1000);
//           ui->customPlot->yAxis->setRange(0,200);

//           ui->customPlot->xAxis2->setRange(0,1000);
//           ui->customPlot->yAxis2->setRange(0,200);


      ui->customPlot->xAxis2->setVisible(true);
      ui->customPlot->yAxis2->setVisible(true);


      ui->customPlot->xAxis->setLabel(xLabel);
      ui->customPlot->yAxis->setLabel(yLabel);



        //ui->customPlot->graph(0)->rescaleAxes();
        ui->customPlot->graph(0)->rescaleValueAxis();
        ui->customPlot->graph(1)->rescaleValueAxis();
        ui->customPlot->graph(0)->rescaleAxes();
        ui->customPlot->graph(1)->rescaleAxes(true);



        ui->customPlot->yAxis->scaleRange(1.1, ui->customPlot->yAxis->range().center());
        ui->customPlot->xAxis->scaleRange(1.1, ui->customPlot->xAxis->range().center());

         ui->customPlot->replot();

ui->customPlot->axisRect()->setupFullAxesBox();

//qDebug() << ui->customPlot->xAxis->pixelToCoord(mouseEvent->pos().x()) << ui->customPlot->yAxis->pixelToCoord(mouseEvent->pos().y());













}
