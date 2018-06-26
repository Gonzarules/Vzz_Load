#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QVector>
#include <algorithm>

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();



    void makePlot(int n, QVector<double> xlist, QVector<double> ylist, QString graphTitle, QString xLabel, QString yLabel, QColor color);

    void closeWindow();

    //void showPointToolTip(QMouseEvent *event);

private:
    Ui::PlotWindow *ui;
};

#endif // PLOTWINDOW_H
