#include "parwindow.h"
#include "ui_parwindow.h"

ParWindow::ParWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParWindow)
{
    ui->setupUi(this);
}

ParWindow::~ParWindow()
{
    delete ui;
}


//void ParWindow::setText(QString numero)
//{
//    //We load the image
//    //image.load(path);
//    //We set the label image

//    ui->lineEdit->setText(numero);
//}

void ParWindow::setFile(QString parname, QString title)
{
              this->setWindowTitle(title);
             ui->lw_parList->clear();
             ui->lw_parList->addItem(parname);

}
