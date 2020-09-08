/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *error_text;
    QPushButton *close_btn;

    void setupUi(QWidget *dialog)
    {
        if (dialog->objectName().isEmpty())
            dialog->setObjectName(QString::fromUtf8("dialog"));
        dialog->resize(597, 117);
        dialog->setStyleSheet(QString::fromUtf8("background:rgb(229, 239, 227);"));
        verticalLayout = new QVBoxLayout(dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        error_text = new QTextEdit(dialog);
        error_text->setObjectName(QString::fromUtf8("error_text"));
        error_text->setStyleSheet(QString::fromUtf8("border:none;background:rgb(229, 239, 227);"));

        verticalLayout->addWidget(error_text);

        close_btn = new QPushButton(dialog);
        close_btn->setObjectName(QString::fromUtf8("close_btn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(close_btn->sizePolicy().hasHeightForWidth());
        close_btn->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        close_btn->setFont(font);
        close_btn->setStyleSheet(QString::fromUtf8("background:rgb(111, 115, 127);color:black;"));

        verticalLayout->addWidget(close_btn, 0, Qt::AlignRight|Qt::AlignBottom);


        retranslateUi(dialog);

        QMetaObject::connectSlotsByName(dialog);
    } // setupUi

    void retranslateUi(QWidget *dialog)
    {
        dialog->setWindowTitle(QCoreApplication::translate("dialog", "Error", nullptr));
        error_text->setHtml(QCoreApplication::translate("dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-weight:600; color:#2e3436;\">Opps! Looks like their is a error. Your amount will be refunded within 3-5 days.</span></p></body></html>", nullptr));
        error_text->setPlaceholderText(QString());
        close_btn->setText(QCoreApplication::translate("dialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
