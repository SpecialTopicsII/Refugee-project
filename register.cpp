#include "register.h"
#include "database.h"
#include "design.h"
#include <QDialog>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

Register::Register()
{
    myDB=new Database();
    dialog=new QDialog();
    dialog->setWindowTitle("Register");
    QLabel * name=new QLabel("Name:");
    QLabel * secondName=new QLabel("Second Name:");
    QLabel * birthDate=new QLabel("Birth Date:");
    QLabel * age=new QLabel("Age:");
    QLabel * fathersName=new QLabel("Fathers Name:");
    QLabel * mothersName=new QLabel("Mothers Name:");
    QLabel * currentAddress=new QLabel("Current Address:");
    QLabel * oldAddress=new QLabel("Old Address:");
    QLabel * currentCity=new QLabel("Current City:");
    QLabel * oldCity=new QLabel("Old Ctiy:");
    QLabel * currentCountry=new QLabel("Current Country:");
    QLabel * oldCountry=new QLabel("Old Country:");
    QLabel * phoneNumber=new QLabel("Phone Number:");
    QLabel * email=new QLabel("Email:");
    QLabel * username=new QLabel("Username:");
    QLabel * password=new QLabel("Password:");


    name1=new QLineEdit();
    secondName1=new QLineEdit();
    birthDate1=new QLineEdit();
    age1=new QLineEdit();
    fathersName1=new QLineEdit();
    mothersName1=new QLineEdit();
    currentAddress1=new QLineEdit();
    oldAddress1=new QLineEdit();
    currentCity1=new QLineEdit();
    oldCity1=new QLineEdit();
    currentCountry1=new QLineEdit();
    oldCountry1=new QLineEdit();
    phoneNumber1=new QLineEdit();
    email1=new QLineEdit();
    username1=new QLineEdit();
    password1=new QLineEdit();

    name1->setFixedWidth(200);
    secondName1->setFixedWidth(200);
    birthDate1->setFixedWidth(200);
    age1->setFixedWidth(200);
    fathersName1->setFixedWidth(200);
    mothersName1->setFixedWidth(200);
    currentAddress1->setFixedWidth(200);
    oldAddress1->setFixedWidth(200);
    currentCity1->setFixedWidth(200);
    oldCity1->setFixedWidth(200);
    currentCountry1->setFixedWidth(200);
    oldCountry1->setFixedWidth(200);
    phoneNumber1->setFixedWidth(200);
    email1->setFixedWidth(200);
    username1->setFixedWidth(200);
    password1->setFixedWidth(200);

    password1->setEchoMode(QLineEdit::Password);

    QHBoxLayout * lyt1=new QHBoxLayout();
    lyt1->addWidget(name);
    lyt1->addWidget(name1);

    QHBoxLayout * lyt2=new QHBoxLayout();
    lyt2->addWidget(secondName);
    lyt2->addWidget(secondName1);

    QHBoxLayout * lyt3=new QHBoxLayout();
    lyt3->addWidget(birthDate);
    lyt3->addWidget(birthDate1);

    QHBoxLayout * lyt4=new QHBoxLayout();
    lyt4->addWidget(age);
    lyt4->addWidget(age1);

    QHBoxLayout * lyt5=new QHBoxLayout();
    lyt5->addWidget(fathersName);
    lyt5->addWidget(fathersName1);

    QHBoxLayout * lyt6=new QHBoxLayout();
    lyt6->addWidget(mothersName);
    lyt6->addWidget(mothersName1);

    QHBoxLayout * lyt7=new QHBoxLayout();
    lyt7->addWidget(currentAddress);
    lyt7->addWidget(currentAddress1);

    QHBoxLayout * lyt8=new QHBoxLayout();
    lyt8->addWidget(oldAddress);
    lyt8->addWidget(oldAddress1);

    QHBoxLayout * lyt9=new QHBoxLayout();
    lyt9->addWidget(currentCity);
    lyt9->addWidget(currentCity1);

    QHBoxLayout * lyt10=new QHBoxLayout();
    lyt10->addWidget(oldCity);
    lyt10->addWidget(oldCity1);

    QHBoxLayout * lyt11=new QHBoxLayout();
    lyt11->addWidget(currentCountry);
    lyt11->addWidget(currentCountry1);

    QHBoxLayout * lyt12=new QHBoxLayout();
    lyt12->addWidget(oldCountry);
    lyt12->addWidget(oldCountry1);

    QHBoxLayout * lyt13=new QHBoxLayout();
    lyt13->addWidget(phoneNumber);
    lyt13->addWidget(phoneNumber1);

    QHBoxLayout * lyt14=new QHBoxLayout();
    lyt14->addWidget(email);
    lyt14->addWidget(email1);

    QHBoxLayout * lyt15=new QHBoxLayout();
    lyt15->addWidget(username);
    lyt15->addWidget(username1);

    QHBoxLayout * lyt16=new QHBoxLayout();
    lyt16->addWidget(password);
    lyt16->addWidget(password1);


    QVBoxLayout * mainlyt=new QVBoxLayout();
    mainlyt->addLayout(lyt1);
    mainlyt->addLayout(lyt2);
    mainlyt->addLayout(lyt3);
    mainlyt->addLayout(lyt4);
    mainlyt->addLayout(lyt5);
    mainlyt->addLayout(lyt6);
    mainlyt->addLayout(lyt7);
    mainlyt->addLayout(lyt8);
    mainlyt->addLayout(lyt9);
    mainlyt->addLayout(lyt10);
    mainlyt->addLayout(lyt11);
    mainlyt->addLayout(lyt12);
    mainlyt->addLayout(lyt13);
    mainlyt->addLayout(lyt14);
    mainlyt->addLayout(lyt15);
    mainlyt->addLayout(lyt16);


    okButton = new QPushButton("");
    cancelButton = new QPushButton("");

    Design::setButton(cancelButton,91,37,":/Buttons/images/buttons/cancel.jpg");
    Design::setButton(okButton,70,39,":/Buttons/images/buttons/ok.jpg");

    QHBoxLayout * lyt17=new QHBoxLayout();
    lyt17->addWidget(okButton);
    lyt17->addWidget(cancelButton);

    QObject::connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(cancel_action()));
    QObject::connect(okButton,SIGNAL(clicked(bool)),this,SLOT(ok_action()));
    mainlyt->addLayout(lyt17);

    dialog->setLayout(mainlyt);
    dialog->show();
}

void Register::cancel_action()
{
    dialog->close();
}

void Register::ok_action()
{
    if ( not_entered_allInfo())
    {
        QMessageBox::information(okButton,"Error","Please enter all fields!");
    }
    else if(myDB->if_username_exists(username1->text()))
    {
        QMessageBox::information(okButton,"Error","Username is already in use, please choose the other one!");
    }
    else
    {
        myDB->register_new_user(age1->text().toInt(),birthDate1->text(),email1->text(),fathersName1->text(),
                                mothersName1->text(),name1->text(),currentAddress1->text(),currentCity1->text(),
                                currentCountry1->text(),oldAddress1->text(),oldCity1->text(),oldCountry1->text(),
                                password1->text(),phoneNumber1->text().toInt() , secondName1->text(),username1->text());
        QMessageBox::information(okButton,"Success","You have been successfuly registered!");
        dialog->close();
    }
}

bool Register::not_entered_allInfo()
{
    if(name1->text()=="")
        return true;
    else if(secondName1->text()=="")
        return true;
    else if(birthDate1->text()=="")
        return true;
    else if(age1->text()=="")
        return true;
    else if(fathersName1->text()=="")
        return true;
    else if(mothersName1->text()=="")
        return true;
    else if(currentAddress1->text()=="")
        return true;
    else if(oldAddress1->text()=="")
        return true;
    else if(currentCity1->text()=="")
        return true;
    else if(oldCity1->text()=="")
        return true;
    else if(currentCountry1->text()=="")
        return true;
    else if(oldCountry1->text()=="")
        return true;
    else if(phoneNumber1->text()=="")
        return true;
    else if(email1->text()=="")
        return true;
    else if(username1->text()=="")
        return true;
    else if(password1->text()=="")
        return true;

    return false;
}

