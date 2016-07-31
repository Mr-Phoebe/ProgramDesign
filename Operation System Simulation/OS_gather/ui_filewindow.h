/********************************************************************************
** Form generated from reading UI file 'filewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEWINDOW_H
#define UI_FILEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fileWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTreeView *treeView;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_2;
    QTextEdit *textEdit;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QTextEdit *textEdit_4;
    QLabel *label_8;
    QPushButton *pushButton_3;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *fileWindow)
    {
        if (fileWindow->objectName().isEmpty())
            fileWindow->setObjectName(QStringLiteral("fileWindow"));
        fileWindow->resize(750, 406);
        centralwidget = new QWidget(fileWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(40, 90, 281, 21));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(330, 90, 75, 23));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(40, 150, 281, 211));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 70, 61, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 120, 71, 21));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(40, 39, 211, 21));
        lineEdit_2->setReadOnly(true);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 12, 71, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 120, 191, 21));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(650, 20, 75, 31));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(350, 150, 91, 211));
        textEdit->setReadOnly(true);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(350, 120, 54, 20));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(460, 120, 71, 21));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(460, 250, 71, 21));
        textEdit_4 = new QTextEdit(centralwidget);
        textEdit_4->setObjectName(QStringLiteral("textEdit_4"));
        textEdit_4->setGeometry(QRect(580, 150, 111, 211));
        textEdit_4->setReadOnly(true);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(580, 120, 71, 21));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(420, 90, 75, 23));
        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(460, 150, 91, 81));
        textEdit_2->setReadOnly(true);
        textEdit_3 = new QTextEdit(centralwidget);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));
        textEdit_3->setGeometry(QRect(460, 280, 91, 81));
        textEdit_3->setReadOnly(true);
        fileWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(fileWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 750, 23));
        fileWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(fileWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        fileWindow->setStatusBar(statusbar);

        retranslateUi(fileWindow);

        QMetaObject::connectSlotsByName(fileWindow);
    } // setupUi

    void retranslateUi(QMainWindow *fileWindow)
    {
        fileWindow->setWindowTitle(QApplication::translate("fileWindow", "MainWindow", 0));
        pushButton->setText(QApplication::translate("fileWindow", "\346\211\247\350\241\214", 0));
        label->setText(QApplication::translate("fileWindow", "\345\221\275\344\273\244\357\274\232", 0));
        label_2->setText(QApplication::translate("fileWindow", "\346\226\207\344\273\266\347\233\256\345\275\225\357\274\232", 0));
        label_3->setText(QApplication::translate("fileWindow", "\345\275\223\345\211\215\350\267\257\345\276\204\357\274\232", 0));
        label_4->setText(QString());
        pushButton_2->setText(QApplication::translate("fileWindow", "\351\200\200\345\207\272", 0));
        label_5->setText(QApplication::translate("fileWindow", "\347\211\251\347\220\206\345\235\227\357\274\232", 0));
        label_6->setText(QApplication::translate("fileWindow", "\345\206\205\345\255\230\351\241\265\357\274\232", 0));
        label_7->setText(QApplication::translate("fileWindow", "\350\231\232\346\213\237\345\206\205\345\255\230\351\241\265\357\274\232", 0));
        label_8->setText(QApplication::translate("fileWindow", "\346\215\242\351\241\265\346\223\215\344\275\234\357\274\232", 0));
        pushButton_3->setText(QApplication::translate("fileWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class fileWindow: public Ui_fileWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEWINDOW_H
