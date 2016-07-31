#ifndef NOTEPAD_H
#define NOTEPAD_H
#include "filesystem.h"
#include <QDialog>

const int maxLen = 8192;

namespace Ui {
class Notepad;
}

class Notepad : public QDialog
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = 0);
    ~Notepad();
    void showFile(QString content, FileAccess facc);
    QString getFilePath();
    QString getFileContent();
    void setPath(string path);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Notepad *ui;
    QString filePath;
};

#endif // NOTEPAD_H
