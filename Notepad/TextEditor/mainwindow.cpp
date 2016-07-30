#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isSaved = false;
    curFile = tr("未命名.txt");
    setWindowTitle(curFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_TextEditor_triggered()
{
    dlg.show();
}

void MainWindow::on_action_Exit_triggered()
{
    on_actionClose_triggered();
    qApp->quit();
}

void MainWindow::do_file_New()
{
    do_file_SaveOrNot();
    isSaved = false;
    curFile = tr("未命名.txt");
    setWindowTitle(curFile);
    ui->textEdit->clear();
    ui->textEdit->setVisible(true);
}

void MainWindow::do_file_SaveOrNot(){
    if(ui->textEdit->document()->isModified()){
        QMessageBox box;
        box.setWindowTitle("警告");
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile+tr("尚未保存，是否保存？"));
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        if(box.exec() == QMessageBox::Yes)
            do_file_Save();
    }
}

void MainWindow::do_file_Open(){
    do_file_SaveOrNot();
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
        do_file_Load(fileName);
    ui->textEdit->setVisible(true);
}

bool MainWindow::do_file_Load(const QString& fileName){
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,tr("读取文件"),tr("无法读取文件 %1:\n%2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;

}

void MainWindow::do_file_Save(){
    if(isSaved)
        saveFile(curFile);
    else do_file_SaveAs();
}

void MainWindow::do_file_SaveAs(){
    QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"),curFile);
    if(!fileName.isEmpty())
        saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName){
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,tr("保存文件"),
                             tr("无法保存文件 %1:\n %2").arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out<<ui->textEdit->toPlainText();
    isSaved = true;
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}
void MainWindow::on_action_New_triggered()
{
    do_file_New();
}

void MainWindow::on_action_Save_triggered()
{
    do_file_Save();
}

void MainWindow::on_actionSave_As_triggered()
{
    do_file_SaveAs();
}

void MainWindow::on_action_Open_triggered()
{
    do_file_Open();
}

void MainWindow::on_actionClose_triggered()
{
    do_file_SaveOrNot();
    ui->textEdit->setVisible(false);
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
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

void MainWindow::on_actionFind_triggered()
{
    QDialog *findDlg = new QDialog(this);
    findDlg->setWindowTitle(tr("查找"));
    find_textEditLine = new QLineEdit(findDlg);
    QPushButton *find_Btn = new QPushButton(tr("查找下一个"),findDlg);
    QVBoxLayout *layout = new QVBoxLayout(findDlg);
    layout->addWidget(find_textEditLine);
    layout->addWidget(find_Btn);
    findDlg->show();
    connect(find_Btn,SIGNAL(clicked()),this,SLOT(show_findText()));
}

void MainWindow::show_findText(){
    QString findText = find_textEditLine->text();
    if(!ui->textEdit->find(findText,QTextDocument::FindBackward)){
        QMessageBox::warning(this,tr("查找"),tr("找不到 %1").arg(findText));
    }

}
