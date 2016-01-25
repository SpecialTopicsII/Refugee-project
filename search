#include "search.h"
#include "database.h"
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <QWebView>
#include <QWebPage>
#include "design.h"

using namespace std;

Search::Search(QString ID)
{
    username=ID;
    dialog=new QDialog();
    dialog->setWindowTitle("Search");
    lbl1=new QLabel("Please choose what your search should be based on:");
    radio1=new QRadioButton("One parameter");
    radio2=new QRadioButton("Multiple parameters");
    QButtonGroup *group1=new QButtonGroup ();
    group1->addButton(radio1);
    group1->addButton(radio2);
    selectedUsername="";
    choice1=new QComboBox();
    choice1->addItem("name");
    choice1->addItem("surname");
    choice1->addItem("birth date");
    choice1->addItem("age");
    choice1->addItem("email");
    choice1->addItem("old address");
    choice1->addItem("new address");
    choice1->addItem("old city");
    choice1->addItem("new city");
    choice1->addItem("old country");
    choice1->addItem("new country");
    choice1->addItem("fathers name");
    choice1->addItem("mothers name");
    choice1->addItem("phone number");
    choice1->setEnabled(false);

    choice2=new QComboBox();
    choice2->addItem("name + surname");
    choice2->addItem("fathers name + mothers name");
    choice2->addItem("old address + new address");
    choice2->addItem("old city + new city");
    choice2->addItem("old country + new country");
    choice2->setEnabled(false);

    okButton=new QPushButton("");
    cancelButton=new QPushButton("");
    okButton->setEnabled(false);

    //LAYOUTS
    QVBoxLayout *lyt1=new QVBoxLayout();
    lyt1->addWidget(radio1);
    lyt1->addWidget(choice1);

    QVBoxLayout *lyt2=new QVBoxLayout();
    lyt2->addWidget(radio2);
    lyt2->addWidget(choice2);

    QHBoxLayout *lyt3=new QHBoxLayout();
    lyt3->addWidget(okButton);
    lyt3->addWidget(cancelButton);

    field1=new QLineEdit();
    field1->setEnabled(false);
    QHBoxLayout *lyt4=new QHBoxLayout();
    lyt4->addWidget(field1);

    field2=new QLineEdit();
    field3=new QLineEdit();
    field2->setEnabled(false);
    field3->setEnabled(false);
    QHBoxLayout *lyt5=new QHBoxLayout();
    lyt5->addWidget(field2);
    lyt5->addWidget(field3);

    QVBoxLayout *mainLyt=new QVBoxLayout();
    mainLyt->addWidget(lbl1);
    mainLyt->addLayout(lyt1);
    mainLyt->addLayout(lyt4);
    mainLyt->addLayout(lyt2);
    mainLyt->addLayout(lyt5);
    mainLyt->addLayout(lyt3);

    Design::setButton(cancelButton,91,37,":/Buttons/images/buttons/cancel.jpg");
    Design::setButton(okButton,70,39,":/Buttons/images/buttons/ok.jpg");


    connect(radio1,SIGNAL(clicked(bool)),this,SLOT(enable_choice1()));
    connect(radio2,SIGNAL(clicked(bool)),this,SLOT(enable_choice2()));
    connect(cancelButton,SIGNAL(clicked(bool)),dialog,SLOT(close()));
    connect(okButton,SIGNAL(clicked(bool)),this,SLOT(show_results()));
    dialog->setLayout(mainLyt);
    dialog->setModal(true);
    dialog->show();
}


void Search::enable_choice1()
{
    okButton->setEnabled(true);
    choice1->setEnabled(true);
    choice2->setEnabled(false);
    field1->setEnabled(true);
    field2->setEnabled(false);
    field3->setEnabled(false);
}

void Search::enable_choice2()
{
    okButton->setEnabled(true);
    choice1->setEnabled(false);
    choice2->setEnabled(true);
    field1->setEnabled(false);
    field2->setEnabled(true);
    field3->setEnabled(true);
}

void Search::show_results()
{
    if(radio1->isChecked())
    {
        if(field1->text() =="")
            QMessageBox::information(okButton,"Error","You did not enter any value!");
        else
        {
            Database * myDB=new Database();
            QVector< QVector<QString> > * records;


            if(choice1->currentText() == "name")
            {
                records=myDB->getAllUsers("name", field1->text());
            }
            else if(choice1->currentText() == "surname")
            {
                records=myDB->getAllUsers("second_name", field1->text());
            }
            else if(choice1->currentText() == "birth date")
            {
                records=myDB->getAllUsers("birth_date", field1->text());
            }
            else if(choice1->currentText() == "age")
            {
                records=myDB->getAllUsers("age", field1->text());
            }
            else if(choice1->currentText() == "email")
            {
                records=myDB->getAllUsers("email", field1->text());
            }
            else if(choice1->currentText() == "old address")
            {
                records=myDB->getAllUsers("old_address", field1->text());
            }
            else if(choice1->currentText() == "new address")
            {
                records=myDB->getAllUsers("new_address", field1->text());
            }
            else if(choice1->currentText() == "old city")
            {
                records=myDB->getAllUsers("old_city", field1->text());
            }
            else if(choice1->currentText() == "new city")
            {
                records=myDB->getAllUsers("new_city", field1->text());
            }
            else if(choice1->currentText() == "old country")
            {
                records=myDB->getAllUsers("old_country", field1->text());
            }
            else if(choice1->currentText() == "new country")
            {
                records=myDB->getAllUsers("new_country", field1->text());
            }
            else if(choice1->currentText() == "fathers name")
            {
                records=myDB->getAllUsers("fathers_name", field1->text());
            }
            else if(choice1->currentText() == "mothers name")
            {
                records=myDB->getAllUsers("mothers_name", field1->text());
            }
            else if(choice1->currentText() == "phone number")
            {
                records=myDB->getAllUsers("phone_number", field1->text());
            }

            table=new QTableWidget();
            table->setColumnCount(8);
            table->setHorizontalHeaderItem(0,new QTableWidgetItem("Name"));
            table->setHorizontalHeaderItem(1,new QTableWidgetItem("Surname"));
            table->setHorizontalHeaderItem(2,new QTableWidgetItem("Birthdate"));
            table->setHorizontalHeaderItem(3,new QTableWidgetItem("Old address"));
            table->setHorizontalHeaderItem(4,new QTableWidgetItem("Old city"));
            table->setHorizontalHeaderItem(5,new QTableWidgetItem("Old country"));
            table->setHorizontalHeaderItem(6,new QTableWidgetItem("Email"));
            table->setHorizontalHeaderItem(7,new QTableWidgetItem("username"));
            table->setRowCount(records->size());

            for(int i=0;i<records->size();i++)
            {
                table->setItem(i,0,new QTableWidgetItem(records->at(i).at(1)));
                table->setItem(i,1,new QTableWidgetItem(records->at(i).at(14)));
                table->setItem(i,2,new QTableWidgetItem(records->at(i).at(11)));
                table->setItem(i,3,new QTableWidgetItem(records->at(i).at(2)));
                table->setItem(i,5,new QTableWidgetItem(records->at(i).at(6)));
                table->setItem(i,6,new QTableWidgetItem(records->at(i).at(9)));
                table->setItem(i,4,new QTableWidgetItem(records->at(i).at(4)));
                table->setItem(i,7,new QTableWidgetItem(records->at(i).at(15)));
            }

            QDialog * resultsDialog=new QDialog();
            resultsDialog->setWindowTitle("Search results");
            QVBoxLayout *mainLyt2=new QVBoxLayout();
            QPushButton *okB=new QPushButton("Done");
            QPushButton *repB=new QPushButton("Make report");
            QPushButton *viewB=new QPushButton("View profile");

            connect(okB,SIGNAL(clicked(bool)),resultsDialog,SLOT(close()));
            connect(repB,SIGNAL(clicked(bool)),this,SLOT(Make_Report()));
            connect(viewB,SIGNAL(clicked(bool)),this,SLOT(View_Profile()));
            resultsDialog->setFixedWidth(750);
            QHBoxLayout *lyt1=new QHBoxLayout();
            lyt1->addSpacerItem(new QSpacerItem(300,0));
            lyt1->addWidget(viewB);
            lyt1->addWidget(repB);
            lyt1->addWidget(okB);

            mainLyt2->addWidget(table);
            mainLyt2->addLayout(lyt1);
            resultsDialog->setLayout(mainLyt2);
            resultsDialog->setModal(true);
            resultsDialog->show();
        }

    }

    else
    {
        if(field2->text() =="" || field3->text()=="")
            QMessageBox::information(okButton,"Error","You did not enter some values!");
        else
        {
            Database * myDB=new Database();
            QVector< QVector<QString> > * records;
            if(choice2->currentText() == "name + surname")
                records=myDB->getAllUsers("name","second_name",
                                          field2->text(),field3->text());
            else if(choice2->currentText() == "fathers name + mothers name")
                records=myDB->getAllUsers("fathers_name","mothers_name",
                                          field2->text(),field3->text());
            else if(choice2->currentText() == "old address + new address")
                records=myDB->getAllUsers("old_address","current_address",
                                          field2->text(),field3->text());
            else if(choice2->currentText() == "old city + new city")
                records=myDB->getAllUsers("old_city","current_city",
                                          field2->text(),field3->text());
            else if(choice2->currentText() == "old country + new country")
                records=myDB->getAllUsers("old_country","current_country",
                                          field2->text(),field3->text());


            table=new QTableWidget();
            table->setColumnCount(8);
            table->setHorizontalHeaderItem(0,new QTableWidgetItem("Name"));
            table->setHorizontalHeaderItem(1,new QTableWidgetItem("Surname"));
            table->setHorizontalHeaderItem(2,new QTableWidgetItem("Birthdate"));
            table->setHorizontalHeaderItem(3,new QTableWidgetItem("Old address"));
            table->setHorizontalHeaderItem(4,new QTableWidgetItem("Old city"));
            table->setHorizontalHeaderItem(5,new QTableWidgetItem("Old country"));
            table->setHorizontalHeaderItem(6,new QTableWidgetItem("Email"));
            table->setHorizontalHeaderItem(7,new QTableWidgetItem("username"));
            table->setRowCount(records->size());

            for(int i=0;i<records->size();i++)
            {
                table->setItem(i,0,new QTableWidgetItem(records->at(i).at(1)));
                table->setItem(i,1,new QTableWidgetItem(records->at(i).at(14)));
                table->setItem(i,2,new QTableWidgetItem(records->at(i).at(11)));
                table->setItem(i,3,new QTableWidgetItem(records->at(i).at(2)));
                table->setItem(i,5,new QTableWidgetItem(records->at(i).at(6)));
                table->setItem(i,6,new QTableWidgetItem(records->at(i).at(9)));
                table->setItem(i,4,new QTableWidgetItem(records->at(i).at(4)));
                table->setItem(i,7,new QTableWidgetItem(records->at(i).at(15)));
            }

            QDialog * resultsDialog=new QDialog();
            resultsDialog->setWindowTitle("Search results");
            QVBoxLayout *mainLyt2=new QVBoxLayout();
            QPushButton *okB=new QPushButton("Done");
            QPushButton *repB=new QPushButton("Make report");
            QPushButton *viewB=new QPushButton("View profile");

            connect(okB,SIGNAL(clicked(bool)),resultsDialog,SLOT(close()));
            connect(repB,SIGNAL(clicked(bool)),this,SLOT(Make_Report()));
            connect(viewB,SIGNAL(clicked(bool)),this,SLOT(View_Profile()));
            resultsDialog->setFixedWidth(750);
            QHBoxLayout *lyt1=new QHBoxLayout();
            lyt1->addSpacerItem(new QSpacerItem(300,0));
            lyt1->addWidget(viewB);
            lyt1->addWidget(repB);
            lyt1->addWidget(okB);


            mainLyt2->addWidget(table);
            mainLyt2->addLayout(lyt1);
            resultsDialog->setLayout(mainLyt2);
            resultsDialog->setModal(true);
            resultsDialog->show();
        }
    }
}

void Search::Make_Report()
{
    QString path=QFileDialog::getExistingDirectory(NULL,"Select destination folder",QDir::currentPath());
    path+="/search_report_";
    path+=QDateTime::currentDateTime().date().toString();
    path+=".txt";
    qDebug()<<"Path is: "<<path;

    QFile file(path);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        qDebug()<<"Writing file";
        out<<"Refugee Info "<<endl;
        out<<"Report made at ";
        out<<QDateTime::currentDateTimeUtc().time().toString();
        out<<" ";
        out<<QDateTime::currentDateTime().date().toString();
        out<<endl;
        if(table->rowCount()==0)
            out<<"No records found."<<endl;
        else
        {
            for(int i=0;i< table->rowCount();i++)
            {
                qDebug()<<"Starting the loop";
                for(int j=0;j<7;j++)
                {
                    if(table->item(i,j)->text()!="")
                    {
                        if(j==0)
                            out<<"Name: "<< table->item(i,j)->text() <<endl;
                        else if(j==1)
                            out<<"Surname: "<<table->item(i,j)->text() <<endl;
                        else if(j==2)
                            out<<"Birth date: "<<table->item(i,j)->text() <<endl;
                        else if(j==3)
                            out<<"Old address: "<<table->item(i,j)->text() <<endl;
                        else if(j==4)
                            out<<"Old city: "<<table->item(i,j)->text() <<endl;
                        else if(j==5)
                            out<<"Old country: "<<table->item(i,j)->text()<<endl;
                        else if(j==6)
                            out<<"Email: "<<table->item(i,j)->text() <<endl;
                    }
                }
                out<<endl;
            }
            out<<endl<<endl;
        }

        out<<"Thank you for using Refugee Info.";
        file.close();
        QMessageBox::information(NULL,"Success","Report saved successfuly!");

    }
    else
        qDebug()<<"Couldnt open the file";
}

void Search::View_Profile()
{

    selectedUsername=table->item(table->currentRow(),7)->text();
    QDialog *dlg=new QDialog();
    dlg->setWindowTitle("View profile");
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

    name1->setReadOnly(true);
    secondName1->setReadOnly(true);
    birthDate1->setReadOnly(true);
    age1->setReadOnly(true);
    fathersName1->setReadOnly(true);
    mothersName1->setReadOnly(true);
    currentAddress1->setReadOnly(true);
    oldAddress1->setReadOnly(true);
    currentCity1->setReadOnly(true);
    oldCity1->setReadOnly(true);
    currentCountry1->setReadOnly(true);
    oldCountry1->setReadOnly(true);
    phoneNumber1->setReadOnly(true);
    email1->setReadOnly(true);

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

    QVBoxLayout *lyt15=new QVBoxLayout();
    lyt15->addLayout(lyt1);
    lyt15->addLayout(lyt2);
    lyt15->addLayout(lyt3);
    lyt15->addLayout(lyt4);
    lyt15->addLayout(lyt5);
    lyt15->addLayout(lyt6);
    lyt15->addLayout(lyt7);
    lyt15->setSpacing(0);
    lyt15->setMargin(0);
    lyt15->setContentsMargins(0,0,0,0);
    QVBoxLayout *lyt16=new QVBoxLayout();
    lyt16->addLayout(lyt8);
    lyt16->addLayout(lyt9);
    lyt16->addLayout(lyt10);
    lyt16->addLayout(lyt11);
    lyt16->addLayout(lyt12);
    lyt16->addLayout(lyt13);
    lyt16->addLayout(lyt14);
    lyt16->setSpacing(0);
    lyt16->setMargin(0);
    lyt16->setContentsMargins(0,0,0,0);

    QGridLayout *lyt17=new QGridLayout();
    QPushButton *doneB=new QPushButton("Done");
    QPushButton *textB=new QPushButton("Text message");
    QPushButton *voiceB=new QPushButton("Voice message");
    lyt17->addWidget(textB,0,0);
    lyt17->addWidget(voiceB,0,1);
    lyt17->addWidget(doneB,1,0,1,2);

    map=new QWebView();
    map->setFixedSize(400,400);
    QVBoxLayout *lyt18=new QVBoxLayout();
    lyt18->addLayout(lyt17);
    lyt18->addSpacerItem(new QSpacerItem(0,200));
    lyt18->addWidget(map);

    map->load(QUrl("http://www.google.ba"));

    QHBoxLayout *mainLyt=new QHBoxLayout();
    mainLyt->addLayout(lyt15);
    mainLyt->addLayout(lyt16);
    mainLyt->addLayout(lyt18);

    dlg->setLayout(mainLyt);
    dlg->setModal(true);
    dlg->show();
    connect(doneB,SIGNAL(clicked(bool)),dlg,SLOT(close()));

    Set_Profile_Info();
    selectedUsername=table->item(table->currentRow(),7)->text();
    qDebug()<<"Name: "<<table->item(table->currentRow(),7)->text();
}

void Search::Set_Profile_Info()
{
    if(selectedUsername=="")
    {
        QMessageBox::warning(NULL,"Warning","You did not select any user");
        return;
    }

    Database *myDB=new Database();
    if(myDB->Is_Friend(username, selectedUsername))
    {
        qDebug()<<"Friends..";
        name1->setText(myDB->getUserInfo("name",selectedUsername));
        secondName1->setText(myDB->getUserInfo("second_name",selectedUsername));
        birthDate1->setText(myDB->getUserInfo("birth_date",selectedUsername));
        age1->setText(myDB->getUserInfo("age",selectedUsername));
        fathersName1->setText(myDB->getUserInfo("fathers_name",selectedUsername));
        mothersName1->setText(myDB->getUserInfo("mothers_name",selectedUsername));
        currentAddress1->setText(myDB->getUserInfo("new_address",selectedUsername));
        oldAddress1->setText(myDB->getUserInfo("old_address",selectedUsername));
        currentCity1->setText(myDB->getUserInfo("new_city",selectedUsername));
        oldCity1->setText(myDB->getUserInfo("old_city",selectedUsername));
        currentCountry1->setText(myDB->getUserInfo("new_country",selectedUsername));
        oldCountry1->setText(myDB->getUserInfo("old_country",selectedUsername));
        phoneNumber1->setText(myDB->getUserInfo("phone_number",selectedUsername));
        email1->setText(myDB->getUserInfo("email",selectedUsername));

        QString city=currentCity1->text();
        QString mapLink="https://maps.googleapis.com/maps/api/staticmap?center=";
        mapLink +=city;
        mapLink+="&zoom=13&size=400x400&maptype=sattelite";
        qDebug()<<mapLink;
        map->load(QUrl(mapLink));
    }
    else
    {
        qDebug()<<"not Friends..";
        name1->setText(myDB->getUserInfo("name",selectedUsername));
        secondName1->setText(myDB->getUserInfo("second_name",selectedUsername));
        birthDate1->setText(myDB->getUserInfo("birth_date",selectedUsername));
        age1->setText(myDB->getUserInfo("age",selectedUsername));
        fathersName1->setText("hidden");
        mothersName1->setText("hidden");
        currentAddress1->setText("hidden");
        oldAddress1->setText(myDB->getUserInfo("old_address",selectedUsername));
        currentCity1->setText("hidden");
        oldCity1->setText(myDB->getUserInfo("old_city",selectedUsername));
        currentCountry1->setText("hidden");
        oldCountry1->setText(myDB->getUserInfo("old_country",selectedUsername));
        phoneNumber1->setText("hidden");
        email1->setText(myDB->getUserInfo("email",selectedUsername));
    }
}
