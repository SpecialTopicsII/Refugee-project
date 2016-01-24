#include "userwindow.h"
#include "database.h"
#include "editprofile.h"
#include "search.h"
#include "textmessage.h"
#include "audiorecorder.h"
#include "design.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QDebug>
#include <QMenuBar>
#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextBrowser>
#include <QLineEdit>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSound>
#include <QToolBar>
#include <QPixmap>
#include <QPalette>

#include "mainwindow.h"

UserWindow::UserWindow(QWidget *parent) : QMainWindow(parent)
{

}

UserWindow::UserWindow(QString ID)
{

    username=ID;
    //LABELS
    name=new QLabel("Name: ");
    surname=new QLabel("Surname: ");
    birthdate=new QLabel("Birthdate: ");
    email=new QLabel("E-mail: ");
    currentAddress=new QLabel("Current address: ");
    currentCity=new QLabel("Current city: ");
    currentCountry=new QLabel("Current country: ");
    phoneNumber=new QLabel("Phone number: ");

    //BUTTONS
    logoutButton=new QPushButton("Log out");
    editButton=new QPushButton();
    searchButton=new QPushButton("");
    textM=new QPushButton("Text messages");
    voiceM=new QPushButton("Voice messages");
    textM->setFixedWidth(100);
    voiceM->setFixedWidth(100);
    searchButton->setFixedHeight(50);

    connect(editButton, SIGNAL(clicked(bool)), this, SLOT(edit_profile_action()));
    connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(search_action()));

    Design::setButton(searchButton,112,40,":/Buttons/images/buttons/search.jpg");

    window=new QWidget();

    //GETTING FULL LABELS
    Database *myDB=new Database();
    name->setText("Name: " + myDB->getUserInfo("name",ID));
    surname->setText("Surname: " + myDB->getUserInfo("second_name",ID));
    birthdate->setText("Birthdate: "+ myDB->getUserInfo("birth_date",ID));
    email->setText("E-mail: " + myDB->getUserInfo("email",ID) );
    currentAddress->setText("Current address: " +  myDB->getUserInfo("new_address",ID));
    currentCity->setText("Current city: " + myDB->getUserInfo("new_city",ID) );
    currentCountry->setText("Current country: "+ myDB->getUserInfo("new_country",ID));
    phoneNumber->setText("Phone number: " + myDB->getUserInfo("phone_number",ID));


    //LABEL LAYOUTS
    QVBoxLayout *lyt1=new QVBoxLayout();
    lyt1->addWidget(name);
    lyt1->addWidget(surname);
    lyt1->addWidget(birthdate);
    lyt1->addWidget(phoneNumber);
    QVBoxLayout *lyt2=new QVBoxLayout();
    lyt2->addWidget(email);
    lyt2->addWidget(currentAddress);
    lyt2->addWidget(currentCity);
    lyt2->addWidget(currentCountry);




    //Upper part
    QHBoxLayout *h1=new QHBoxLayout();
    h1->addLayout(lyt1);
    h1->addLayout(lyt2);
    QVBoxLayout *lyt4=new QVBoxLayout();
    QSpacerItem *s1=new QSpacerItem(5,255);
    lyt4->addSpacerItem(s1);
    lyt4->addWidget(editButton);
    h1->addLayout(lyt4);
    QWidget *w1=new QWidget();
    w1->setLayout(h1);
    w1->setFixedHeight(100);

    //Lower part
    QHBoxLayout *h2=new QHBoxLayout();
    QVBoxLayout *lyt5=new QVBoxLayout();
    lyt5->addWidget(textM);
    lyt5->addWidget(voiceM);
    //h2->addLayout(lyt5);
    h2->addWidget(searchButton);



    textWidget=new QWidget();
    voiceWidget=new QWidget();
    //
    QPixmap bkgnd(":/Backgrounds/images/map05.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);

    this->setPalette(palette);
    tabs=new QTabWidget();
    tabs->addTab(textWidget,"Text messages");
    tabs->addTab(voiceWidget,"Voice messages");
    h2->addWidget(tabs);



    sendTMessage=new QPushButton("");
    refreshButton1=new QPushButton("");
    openMessage1=new QPushButton("");

    Design::setButton(sendTMessage,167,36,":/Buttons/images/buttons/text.jpg");
    Design::setButton(refreshButton1,96,36,":/Buttons/images/buttons/refresh.jpg");
    Design::setButton(openMessage1,79,36,":/Buttons/images/buttons/open.jpg");

    tmTable=new QTableWidget();
    tmTable->setColumnCount(4);
    tmTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Time"));
    tmTable->setHorizontalHeaderItem(1,new QTableWidgetItem("From"));
    tmTable->setHorizontalHeaderItem(2,new QTableWidgetItem("Title"));
    tmTable->setHorizontalHeaderItem(3,new QTableWidgetItem("message ID"));


    //
    QHBoxLayout *lyt01=new QHBoxLayout();
    QHBoxLayout *lyt02=new QHBoxLayout();
    QHBoxLayout *lyt03=new QHBoxLayout();
    lyt01->addWidget(openMessage1);
    lyt02->addWidget(refreshButton1);
    lyt03->addWidget(sendTMessage);

    QVBoxLayout *lyt04=new QVBoxLayout();
    lyt04->addLayout(lyt01);
    lyt04->addLayout(lyt02);
    lyt04->addSpacerItem(new QSpacerItem(0,120));
    lyt04->addLayout(lyt03);

    QHBoxLayout *lyt05=new QHBoxLayout();
    lyt05->addWidget(tmTable);
    lyt05->addLayout(lyt04);

    textWidget->setLayout(lyt05);

    update_text_messages();


    connect(refreshButton1,SIGNAL(clicked(bool)),this,SLOT(update_text_messages()));
    connect(sendTMessage, SIGNAL(clicked(bool)), this, SLOT(Write_New_Text_Message()));
    connect(openMessage1,SIGNAL(clicked(bool)),this,SLOT(Open_Text_Message()));


    sendVMessage=new QPushButton("");
    refreshButton2=new QPushButton("");
    openMessage2=new QPushButton("");

    Design::setButton(sendVMessage,167,36,":/Buttons/images/buttons/voice.jpg");
    Design::setButton(refreshButton2,96,36,":/Buttons/images/buttons/refresh.jpg");
    Design::setButton(openMessage2,79,36,":/Buttons/images/buttons/open.jpg");

    vmTable=new QTableWidget();
    vmTable->setColumnCount(5);
    vmTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Time"));
    vmTable->setHorizontalHeaderItem(1,new QTableWidgetItem("From"));
    vmTable->setHorizontalHeaderItem(2,new QTableWidgetItem("Title"));
    vmTable->setHorizontalHeaderItem(3,new QTableWidgetItem("message ID"));
    vmTable->setHorizontalHeaderItem(4,new QTableWidgetItem("path"));
 /*   QVBoxLayout *lyt8=new QVBoxLayout();
    lyt8->addWidget(openMessage2);
    lyt8->addWidget(refreshButton2);
    lyt8->addSpacerItem(new QSpacerItem(0,140));
    lyt8->addWidget(sendVMessage);
    QHBoxLayout *lyt9=new QHBoxLayout();
    lyt9->addWidget(vmTable);
    lyt9->addLayout(lyt8);
    */

    //
    QHBoxLayout *tempLyt1=new QHBoxLayout();
    QHBoxLayout *tempLyt2=new QHBoxLayout();
    QHBoxLayout *tempLyt3=new QHBoxLayout();
    tempLyt1->addWidget(openMessage2);
    tempLyt2->addWidget(refreshButton2);
    tempLyt3->addWidget(sendVMessage);

    QVBoxLayout *tempLyt4=new QVBoxLayout();
    tempLyt4->addLayout(tempLyt1);
    tempLyt4->addLayout(tempLyt2);
    tempLyt4->addSpacerItem(new QSpacerItem(0,120));
    tempLyt4->addLayout(tempLyt3);
    QHBoxLayout *tempLyt5=new QHBoxLayout();
    tempLyt5->addWidget(vmTable);
    tempLyt5->addLayout(tempLyt4);


    voiceWidget->setLayout(tempLyt5);

    connect(sendVMessage, SIGNAL(clicked(bool)), this, SLOT(Write_New_Voice_Message()));
    Update_Voice_Messages();
    connect(openMessage2,SIGNAL(clicked(bool)),this,SLOT(Open_Voice_Message()));
    connect(refreshButton2,SIGNAL(clicked(bool)),this,SLOT(Update_Voice_Messages()));


    //OVDE IDE MENU
    QMenuBar *menubar=new QMenuBar();
    QMenu *file=new QMenu("File");
    QMenu * profile=new QMenu("Profile");
    QMenu * messages=new QMenu("Messages");
    QMenu * search=new QMenu("Search");
    QMenu * about=new QMenu("About");

    menubar->addMenu(file);
    menubar->addMenu(profile);
    menubar->addMenu(messages);
    menubar->addMenu(search);
    menubar->addMenu(about);

    QAction *signOut= file->addAction("Sign out");
    QAction *exit= file->addAction("Exit");
    QAction *editProfile= profile->addAction("Edit profile");
    QAction *newTextM= messages->addAction("New text message");
    QAction *newVoiceM= messages->addAction("New voice message");
    QAction *searchAction= search->addAction("Search for someone");
    QAction *aboutAction= about->addAction("Info");
    connect(signOut,SIGNAL(triggered(bool)),this,SLOT(Sign_Out()));
    connect(exit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(editProfile,SIGNAL(triggered(bool)),this,SLOT(Edit_Profile()));
    connect(newTextM,SIGNAL(triggered(bool)),this,SLOT(New_Text()));
    connect(newVoiceM,SIGNAL(triggered(bool)),this,SLOT(New_Voice()));
    connect(searchAction,SIGNAL(triggered(bool)),this,SLOT(Find()));
    connect(aboutAction,SIGNAL(triggered(bool)),this,SLOT(Info()));

    signOut->setIcon( QIcon(":/Toolbars/images/Toolbar/signOut.png"));
    exit->setIcon( QIcon(":/Toolbars/images/Toolbar/exit.PNG"));
    editProfile->setIcon( QIcon(":/Toolbars/images/Toolbar/edit.png"));
    newTextM->setIcon( QIcon(":/Toolbars/images/Toolbar/textMessage.png"));
    newVoiceM->setIcon( QIcon(":/Toolbars/images/Toolbar/recordMessage.png"));
    searchAction->setIcon( QIcon(":/Toolbars/images/Toolbar/search.png"));
    aboutAction->setIcon( QIcon(":/Toolbars/images/Toolbar/about.png"));

    QVBoxLayout *mainLayout=new QVBoxLayout();

    mainLayout->addWidget(w1);
    mainLayout->addLayout(h2);
    window->setLayout(mainLayout);
    setCentralWidget(window);
    this->setMenuBar(menubar);

    QToolBar *toolbar=new QToolBar();
    toolbar->insertAction(editProfile,editProfile);
    toolbar->insertAction(newTextM,newTextM);
    toolbar->insertAction(newVoiceM,newVoiceM);
    toolbar->insertAction(searchAction,searchAction);
    toolbar->insertAction(aboutAction,aboutAction);
    toolbar->insertAction(signOut,signOut);
    toolbar->insertAction(exit,exit);

    this->addToolBar(toolbar);

    setWindowTitle("Refugee Info");
    Design::setButton(editButton,125,40,":/Buttons/images/buttons/edit.jpg");

    this->setFixedSize(570,425);
    this->show();
}

void UserWindow::edit_profile_action()
{
    EditProfile * edit=new EditProfile(username);
}

void UserWindow::search_action()
{
    Search *s=new Search(username);
}

void UserWindow::Write_New_Text_Message()
{
    TextMessage *msg=new TextMessage(username);
}

void UserWindow::Write_New_Voice_Message()
{

    QDialog *dlg=new QDialog();
    QPushButton *sendB=new QPushButton("");
    QPushButton *cancelB=new QPushButton("");
    QPushButton *recB=new QPushButton("");
    QPushButton *selB=new QPushButton("");

    Design::setButton(sendB,82,37,":/Buttons/images/buttons/send.jpg");
    Design::setButton(cancelB,82,37,":/Buttons/images/buttons/done.jpg");
    Design::setButton(recB,143,37,":/Buttons/images/buttons/recordNew.jpg");
    Design::setButton(selB,172,37,":/Buttons/images/buttons/select.jpg");

    dlg->setWindowTitle("Send new text message");
    title=new QLineEdit();
    toUser=new QLineEdit();

    QGridLayout *lyt1=new QGridLayout();
    lyt1->addWidget(new QLabel("Title: "),0,0);
    lyt1->addWidget(new QLabel("To user: "),1,0);
    lyt1->addWidget(title,0,1);
    lyt1->addWidget(toUser,1,1);

    QHBoxLayout * lyt2=new QHBoxLayout();
    lyt2->addLayout(lyt1);
    lyt2->addWidget(cancelB);

    QHBoxLayout *lyt3=new QHBoxLayout();
    lyt3->addWidget(recB);
    lyt3->addWidget(selB);
    lyt3->addWidget(sendB);

    QVBoxLayout *mainLyt=new QVBoxLayout();
    mainLyt->addLayout(lyt2);
    mainLyt->addLayout(lyt3);
    dlg->setLayout(mainLyt);

    dlg->show();


    connect(cancelB,SIGNAL(clicked(bool)),dlg,SLOT(close()));
    connect(recB,SIGNAL(clicked(bool)),this,SLOT(Record_New()));
    connect(selB,SIGNAL(clicked(bool)),this,SLOT(Select_Message()));
    connect(sendB,SIGNAL(clicked(bool)),this,SLOT(Send_Recorded_Message()));

}

void UserWindow::Record_New()
{
    AudioRecorder *a=new AudioRecorder();
    a->show();
}

void UserWindow::Select_Message()
{
    QString path=QFileDialog::getOpenFileName(this,"Select file",QDir::currentPath());
    QFile *file=new QFile(path);
    voiceMessagePath=file->fileName();
    QFileInfo f(file->fileName());
    voiceMessageName=f.fileName();
}

void UserWindow::Send_Recorded_Message()
{

    Database *myDB=new Database();
    qDebug()<<"here";
    if(title->text()!="" && toUser->text()!="" &&voiceMessagePath!="")
    {
        qDebug()<<"here2";
        myDB->Send_VoiceMessage(title->text(),toUser->text(),username,voiceMessagePath);
        QMessageBox::information(this,"Success","Message is successfuly sent!");
        myDB->Make_Friends(username,toUser->text());
    }
    else
        QMessageBox::warning(this,"Error","You didn't enter everything!");

    qDebug()<<"Title:" + title->text();
    qDebug()<<"To:" + toUser->text();
    qDebug()<<"Path:" + voiceMessagePath;
    qDebug()<<"id:" + username;
}

void UserWindow::update_text_messages()
{
    Database *myDB=new Database();
    QVector<QVector <QString> > *records=myDB->get_textMessages(username);
    tmTable->setRowCount(records->size());
    if(records->size()!=0)
        for(int i=0;i<records->size();i++)
            for(int j=0;j<4;j++)
                tmTable->setItem(i,j,new QTableWidgetItem(records->at(i).at(j)));
}


void UserWindow::Open_Text_Message()
{
    QTableWidgetItem *item=tmTable->item(tmTable->currentRow(),3);

    Database* myDB=new Database();
    QDialog *dlg=new QDialog();
    dlg->setWindowTitle("Reading message");
    QLineEdit * title=new QLineEdit(myDB->Get_TextMessage_Field("title",item->text()) );
    QTextBrowser * text=new QTextBrowser( );
    QLineEdit * from=new QLineEdit(myDB->Get_TextMessage_Field("fromUser",item->text()));
    QLineEdit * time=new QLineEdit(myDB->Get_TextMessage_Field("timeSent",item->text()));
    text->setText(myDB->Get_TextMessage_Field("content",item->text()));

    QLabel *title1=new QLabel("Title:");
    title->setReadOnly(true);
    QLabel *from1=new QLabel("From user:");
    from->setReadOnly(true);
    QLabel *time1=new QLabel("Time sent:");
    time->setReadOnly(true);
    QLabel *text1=new QLabel("Text:");
    time->setReadOnly(true);

    QHBoxLayout *lyt1=new QHBoxLayout();
    lyt1->addWidget(title1);
    lyt1->addWidget(title);

    QHBoxLayout *lyt2=new QHBoxLayout();
    lyt2->addWidget(time1);
    lyt2->addWidget(time);

    QHBoxLayout *lyt3=new QHBoxLayout();
    lyt3->addWidget(from1);
    lyt3->addWidget(from);

    QHBoxLayout *lyt4=new QHBoxLayout();
    lyt4->addWidget(text1);
    lyt4->addWidget(text);

    QPushButton *okBut=new QPushButton("");
    Design::setButton(okBut,70,39,":/Buttons/images/buttons/ok.jpg");
    QHBoxLayout *lyt5=new QHBoxLayout();
    lyt4->addWidget(okBut);

    connect(okBut,SIGNAL(clicked(bool)),dlg,SLOT(close()));

    QVBoxLayout *mainLyt=new QVBoxLayout();
    mainLyt->addLayout(lyt1);
    mainLyt->addLayout(lyt2);
    mainLyt->addLayout(lyt3);
    mainLyt->addLayout(lyt4);
    mainLyt->addSpacerItem(new QSpacerItem(0,20));
    mainLyt->addLayout(lyt5);

    dlg->setLayout(mainLyt);
    dlg->show();
}

void UserWindow::Update_Voice_Messages()
{
    qDebug()<<"1";
    Database *myDB=new Database();
    QVector<QVector <QString> > *rec= myDB->get_VoiceMessages(username);
    qDebug()<<"Username is "+username;
    qDebug()<<"2,records size: "<<rec->size();
    vmTable->setRowCount(rec->size());
    if(rec->size()!=0)
        for(int i=0;i<rec->size();i++)
            for(int j=0;j<5;j++)
                vmTable->setItem(i,j,new QTableWidgetItem(rec->at(i).at(j)));

    qDebug()<<"3";
}

void UserWindow::Open_Voice_Message()
{
    QTableWidgetItem *item=vmTable->item(vmTable->currentRow(),3);
    currentVoiceMsgID=item->text();
    QDialog *dlg=new QDialog();
    dlg->setWindowTitle("Voice message");
    QLabel *from=new QLabel("From: ");
    QLabel *time=new QLabel("Time sent: ");
    QLabel *title=new QLabel("Title: ");
    QLineEdit *from1=new QLineEdit();
    QLineEdit *time1=new QLineEdit();
    QLineEdit *title1=new QLineEdit();
    Database *myDB=new Database();
    qDebug()<<"Voice message ID: " <<item->text();
    from1->setText(myDB->Get_VoiceMessage_Info(item->text(), "fromUser"));
    time1->setText(myDB->Get_VoiceMessage_Info(item->text(), "timeSent"));
    title1->setText(myDB->Get_VoiceMessage_Info(item->text(), "title"));
    qDebug()<<"Creating labels and line edits";
    QGridLayout *lyt1=new QGridLayout();
    lyt1->addWidget(from,0,0);
    lyt1->addWidget(from1,0,1);
    lyt1->addWidget(title,1,0);
    lyt1->addWidget(title1,1,1);
    lyt1->addWidget(time,2,0);
    lyt1->addWidget(time1,2,1);
    qDebug()<<"first layout done";

    from1->setReadOnly(true);
    time1->setReadOnly(true);
    title1->setReadOnly(true);

    qDebug()<<"creating buttons";
    QPushButton *listen=new QPushButton("");
    QPushButton *stop=new QPushButton("");
    QPushButton *ok=new QPushButton("");

    Design::setButton(listen,48,48,":/Buttons/images/buttons/button_grey_play.ico");
    Design::setButton(stop,48,48,":/Buttons/images/buttons/button_grey_stop.ico");
    Design::setButton(ok,82,37,":/Buttons/images/buttons/done.jpg");

    QGridLayout *lyt2=new QGridLayout();
    qDebug()<<"second layout done";
    lyt2->addWidget(listen,0,0);
    lyt2->addWidget(stop,0,1);
    lyt2->addWidget(ok,1,0);

    qDebug()<<"creating final layout";
    QHBoxLayout *mainLyt=new QHBoxLayout();
    mainLyt->addLayout(lyt1);
    mainLyt->addLayout(lyt2);

    dlg->setLayout(mainLyt);
    dlg->setModal(true);
    dlg->show();
    qDebug()<<"showing dialog and creating sound";
    sound=new QSound(myDB->Get_VoiceMessage_Info(currentVoiceMsgID,"path"));
    qDebug()<<"sound created";
    connect(ok,SIGNAL(clicked(bool)),dlg,SLOT(close()));
    connect(listen,SIGNAL(clicked(bool)),this,SLOT(Play_Message()));
    connect(stop,SIGNAL(clicked(bool)),this,SLOT(Stop_Message()));
}

void UserWindow::Play_Message()
{
    sound->play();
}

void UserWindow::Stop_Message()
{
    sound->stop();
}

void UserWindow::Info()
{
    QString t="Refugee Info is the desktop application which may be useful to refugees whose number is large and increasing in recent times. "
              "\nIt will enable refugees to freely search for their relatives and friends whose trail was lost in recent wars (especially in the Middle East). "
              "\nThe whole set of options is there to help to make searching and contacting easier and more fun.";

    QMessageBox::information(NULL,"Info",t);
}

void UserWindow::Sign_Out()
{
    MainWindow *login=new MainWindow();
    login->show();
    this->close();
}

void UserWindow::Edit_Profile()
{
    edit_profile_action();
}

void UserWindow::New_Text()
{
    Write_New_Text_Message();
}

void UserWindow::New_Voice()
{
    Write_New_Voice_Message();
}

void UserWindow::Find()
{
    search_action();
}
