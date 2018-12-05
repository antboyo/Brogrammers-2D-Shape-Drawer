#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <QTextStream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    //***** WE MAY NEED TO MOVE THIS BLOCK OF CODE SO THAT IT UPDATES WHEN SHAPES ARE ADDED/DELETED
    //this block works with the permimeter and area reports, it puts the items in the widget

    //this for loop iterates through the whole vector
    for(int i = 0; i < ui->renderWidget->getShapes()->size(); i++ )
    {
        //if statement checks if the shape has a perimeter, and outputs it if it does
        if(ui->renderWidget->getShapes()->operator [](i)->perimeter() != -1)
        {
            ui->idListWidget       ->addItem(ui->renderWidget->getShapes()->operator [](i)->getDictionary()["ShapeId"]);
            ui->typeListWidget     ->addItem(ui->renderWidget->getShapes()->operator [](i)->getDictionary()["ShapeType"]);
            ui->perimeterListWidget->addItem(QString::number(ui->renderWidget->getShapes()->operator [](i)->perimeter()));
        }

        //if statement checks if the shape has an area and outputs it if it does
        if(ui->renderWidget->getShapes()->operator [](i)->area() != -1)
        {
            ui->idListWidget_2     ->addItem(ui->renderWidget->getShapes()->operator [](i)->getDictionary()["ShapeId"]);
            ui->typeListWidget_2   ->addItem(ui->renderWidget->getShapes()->operator [](i)->getDictionary()["ShapeType"]);
            ui->areaListWidget->addItem(QString::number(ui->renderWidget->getShapes()->operator [](i)->area()));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLogin_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_loginButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username == "admin" && password == "admin")
    {
        //accept login
        ui->stackedWidget->setCurrentIndex(2);
        loginType = "admin";
    }
    else if(username == "user" && password == "user")
    {
        //reject login
        ui->stackedWidget->setCurrentIndex(3);
        loginType = "user";
    }
    else
    {
        QMessageBox::warning(this, "warning", "Invalid Credentials!");
    }
}

void MainWindow::on_addShapeButton_clicked()
{

    //ui->renderWidget->shapes.push_back(pointer to new shape);
}

void MainWindow::on_actionPerimeters_triggered()
{
    //report on the perimeters of the objects in the vector
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_actionAreas_triggered()
{
    //report on areas of the objects in the vector
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_actionOur_Information_triggered()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_returnButton_clicked()
{
    if(loginType == "admin")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if(loginType == "user")
    {
        ui->stackedWidget->setCurrentIndex(3);
    }
}

void MainWindow::on_returnButton_2_clicked()
{
    if(loginType == "admin")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if(loginType == "user")
    {
        ui->stackedWidget->setCurrentIndex(3);
    }
}

void MainWindow::on_horizSpinBox_valueChanged(int arg1)
{
    //find corresponding shape id and call move function
    bool found = false;
    int count = 0;
    while(count < ui->renderWidget->getShapes()->size() && !found)
    {
        //find the shape
        if(ui->moveShapeID->text() == ui->renderWidget->getShapes()->operator [](count)->getDictionary()["ShapeId"])
        {
            found = true;

            //call the move function to move the shape
            ui->renderWidget->getShapes()->operator [](count)->move(arg1, ui->vertSpinBox->value());

            ui->renderWidget->update();
        }
        else
        {
            count++;
        }
    }
}

void MainWindow::on_vertSpinBox_valueChanged(int arg1)
{
    //find corresponding shape id and call move function
    bool found = false;
    int count = 0;
    while(count < ui->renderWidget->getShapes()->size() && !found)
    {
        //find the shape
        if(ui->moveShapeID->text() == ui->renderWidget->getShapes()->operator [](count)->getDictionary()["ShapeId"])
        {
            found = true;

            //call the move function to move the shape
            ui->renderWidget->getShapes()->operator [](count)->move(ui->horizSpinBox->value(), arg1);

            ui->renderWidget->update();
        }
        else
        {
            count++;
        }
    }
}

void MainWindow::on_moveShapeID_editingFinished()
{
    //reset the spin boxes values to 0
    ui->horizSpinBox->setValue(0);
    ui->vertSpinBox->setValue(0);
}
