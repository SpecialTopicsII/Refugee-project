#include "textmessage.h"
#include "database.h"
#include "design.h"
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>

TextMessage::TextMessage(QString from)
{
    this->from=from;

    dlg=new QDialog();
    title=new QLineEdit();
    text=new QTextEdit( );
    to=new QLineEdit();
    time=new QLineEdit();


    QLabel *title1=new QLabel("Title:");
    QLabel *from1=new QLabel("To user:");
    QLabel *text1=new QLabel("Text:");


    QHBoxLayout *lyt1=new QHBoxLayout();
    lyt1->addWidget(title1);
    lyt1->addWidget(title);


    QHBoxLayout *lyt3=new QHBoxLayout();
    lyt3->addWidget(from1);
    lyt3->addWidget(to);

    QHBoxLayout *lyt4=new QHBoxLayout();
    lyt4->addWidget(text1);
    lyt4->addWidget(text);

    QHBoxLayout *lyt5=new QHBoxLayout();
    QPushButton *okBut=new QPushButton("");
    QPushButton *cancelBut=new QPushButton("");

    Design::setButton(cancelBut,91,37,":/Buttons/images/buttons/cancel.jpg");
    Design::setButton(okBut,70,39,":/Buttons/images/buttons/ok.jpg");


    lyt5->addWidget(okBut);
    lyt5->addWidget(cancelBut);

    connect(cancelBut,SIGNAL(clicked(bool)),dlg,SLOT(close()));
    connect(okBut,SIGNAL(clicked(bool)),this,SLOT(Send_Message()));

    QVBoxLayout *mainLyt=new QVBoxLayout();
    mainLyt->addLayout(lyt1);
    mainLyt->addLayout(lyt3);
    mainLyt->addLayout(lyt4);
    mainLyt->addSpacerItem(new QSpacerItem(0,20));
    mainLyt->addLayout(lyt5);

    dlg->setLayout(mainLyt);
    dlg->show();
}

void TextMessage::Send_Message()
{
    Database *myDB=new Database();
    if(to->text()==""|| text->toPlainText()=="" || title->text()=="")
        QMessageBox::warning(to,"Error","Please enter all information!");
    else
    {
        if(myDB->if_username_exists(to->text()))
            {
                myDB->Send_TextMessage(title->text(), text->toPlainText(), to->text(), from);
                QMessageBox::information(to,"Success!","Message sent successfuly!");
                myDB->Make_Friends(from,to->text());
                dlg->close();
            }
        else
            QMessageBox::warning(to,"Error","Username does not exist!");
    }

}
