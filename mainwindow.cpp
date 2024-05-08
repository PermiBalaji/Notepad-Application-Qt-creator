#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QFontDialog>
#include<QFont>
#include<QColorDialog>
#include<QColor>
#include<QPrinter>
#include<QprintDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    setWindowTitle("Welcome to Permi's NotePad Application");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name= QFileDialog::getOpenFileName(this,"open the file");
    file_path=file_name;
    QFile file(file_path);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::information(this,"titie","file is not opened");
        return;
    }
    QTextStream out(&file);
    QString text_name= out.readAll();
    ui->textEdit->setText(text_name);
    file.flush();
}


void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::information(this,"title","file is not opened");
        return;
    }
    QTextStream out1(&file);
    QString text=ui->textEdit->toPlainText();
    out1<< text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"save file");
    file_path=file_name;
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::information(this,"title","file is not opened");
        return;
    }
    QTextStream out2(&file);
    QString text=ui->textEdit->toPlainText();
    out2<<text;
    file.flush();
    file.close();
}
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}
void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionAbout_triggered()
{
    QString abouttext="What is a Notepad : It is a text editor, i.e., an app specialized in editing plain text.\n";
    abouttext+="Developed on : 19-05-2023\n";
    abouttext+="Developed by : PERMI BALAJI\n";
    QMessageBox::about(this,"About the Notepad",abouttext);
}


void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font= QFontDialog::getFont(&ok, this);
    if(ok){
        ui->textEdit->setFont(font);
    }else return;
}


void MainWindow::on_actionColor_triggered()
{
    QColor color= QColorDialog::getColor(Qt::white, this, "choose color");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);}
}


void MainWindow::on_actionBackground_Color_of_text_triggered()
{
    QColor color=QColorDialog::getColor(Qt::white, this, "choose background color");
    if(color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
}


void MainWindow::on_actionBackground_color_of_text_edit_triggered()
{
    QColor clor=QColorDialog::getColor(Qt::white, this, "select background color");
    if(clor.isValid()){
        ui->textEdit->setPalette(QPalette(clor));
    }
}


void MainWindow::on_actionPrint_triggered()
{
//    QPrinter printer;
//    printer.setPrinterName("desierd printer");
//    QPrintDialog dialog(&printer,this);
//    if(dialog.exec()==QDialog::Rejected) return;
//    ui->textEdit->print(&printer);
    QPrinter printer;
    printer.setPrinterName("my printer");
    QPrintDialog dialog(&printer);
    if(dialog.exec()==QDialog::Rejected) return;
    ui->textEdit->print(&printer);
}

