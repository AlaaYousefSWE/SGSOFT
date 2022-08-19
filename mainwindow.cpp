#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QStringList>
#include<QInputDialog>
#include<QTranslator>
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TextView->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QStringList languagesList; // stringList to store the languages in it
    languagesList << "English";
    languagesList << "French";

    QString selectedLanguage = QInputDialog::getItem(this,"Select Language", "Languages", languagesList);
    QTranslator tranlator;
    bool successedLoad = tranlator.load(":/" + selectedLanguage);
    if(successedLoad){
        qApp->installTranslator(&tranlator);
        ui->retranslateUi(this);
    }else{
        QMessageBox::critical(0,"Error","Failed to change language!");
    }

}


void MainWindow::on_choose_file_button_clicked()
{

    QFile file(QFileDialog::getOpenFileName(this,tr("OpenFile"),"",tr("Text Files (*.txt)")));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    QString currentText = stream.readAll();
    ui->TextView->setText(currentText);
    file.close();

    if(!currentText.isEmpty()){ // if successfully Loaded the selected text file then show it the text view
        ui->logo->setVisible(false);
        ui->TextView->setVisible(true);
        ui->choose_file_button->setVisible(false);
    }else{ // handel error
        QMessageBox::critical(0,"Error","Failed to download file!");
    }

}

