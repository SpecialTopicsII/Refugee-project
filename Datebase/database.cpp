#include "database.h"
#include <iostream>
#include <QVariant>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

Database::Database()
{
    if(!db.open())
       {
           qDebug("opening database");
           db=QSqlDatabase::addDatabase("QMYSQL","db");
           db.setHostName("localhost");
           db.setDatabaseName("test");
           db.setUserName("root");
           db.setPassword("");

         /*  db.setHostName("mysql1.000webhost.com");
           db.setDatabaseName("a6270684_sep");
           db.setUserName("a6270684_zerina");
           db.setPassword("kanita2");*/
       }

       if(db.open())
           qDebug("Database opened.");
       else
       {
           qDebug("Database not opened.");
        }

}

bool Database::if_username_exists(QString username)
{
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT name FROM user WHERE username ='"+username+"'");

    int x=0;
    for(int i=0; q->next();i++)
        x++;

    if(x==0)
        return false;
    else
    {
        qDebug()<<"username exists..";
        return true;
    }

}

void Database::register_new_user(int age, QString bdate, QString email,
                                 QString fname, QString mname, QString name,
                                 QString naddress, QString ncity, QString ncountry,
                                 QString oaddress, QString ocity, QString ocountry,
                                 QString pw, int phonenum, QString sname, QString username)
{
    QSqlQuery *q=new QSqlQuery(this->db);
    q->prepare("INSERT INTO user (age, birth_date, email, fathers_name, mothers_name, name, new_address, new_city, new_country, old_address, old_city, old_country, password, phone_number, second_name, username)"
               "VALUES (:age, :birth_date, :email, :fathers_name, :mothers_name, :name, :new_address, :new_city, :new_country, :old_address, :old_city, :old_country, :password, :phone_number, :second_name, :username)");


    q->bindValue(":age",age);
    q->bindValue(":birth_date",bdate);
    q->bindValue(":email",email);
    q->bindValue(":fathers_name",fname);
    q->bindValue(":mothers_name",mname);
    q->bindValue(":name",name);
    q->bindValue(":new_address",naddress);
    q->bindValue(":new_city",ncity);
    q->bindValue(":new_country",ncountry);
    q->bindValue(":old_address",oaddress);
    q->bindValue(":old_city",ocity);
    q->bindValue(":old_country",ocountry);
    q->bindValue(":password",pw);
    q->bindValue(":phone_number",phonenum);
    q->bindValue(":second_name",sname);
    q->bindValue(":username",username);
    q->exec();
    qDebug()<<q->executedQuery();
}

QString Database::getPassword(QString ID)
{

    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT password FROM user WHERE username ='"+ID+"'");
    if(q->next())
        return q->value("password").toString();
}

QString Database::getUserInfo(QString field, QString ID)
{
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT " + field + " FROM user WHERE username ='"+ID+"'");

    qDebug()<<"QUery is: " <<q->executedQuery();

    if(q->next())
    {
        qDebug()<<"field value is: "<<q->value(field).toString();
        return q->value(field).toString();
    }

    return "";
}

void Database::modify_field(QString newValue, QString fieldName, QString ID)
{
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("UPDATE user "
            "SET "+fieldName+"='"+newValue+"' "
            "WHERE username='"+ID+"'");
}

QVector<QVector<QString> > *Database::getAllUsers(QString selectedParameter, QString value)
{
    QVector<QVector<QString> > *vec=new QVector<QVector<QString> >();
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT * FROM user WHERE "+selectedParameter+
            "='"+value+"'");
    int counter=0;
    qDebug()<< "In QVector class..\n" << q->executedQuery();

    while(q->next())
    {
        counter++;
        QVector<QString> * temp=new QVector<QString>();
        for(int i=0;i<16;i++)
        {
            temp->append(q->value(i).toString());
        }
        vec->append(*temp);
    }
    qDebug()<<counter<<" counted records.";

    return vec;
}

QVector<QVector<QString> > * Database::getAllUsers(QString selectedParameter1,
                                                  QString selectedParameter2, QString value1
                                                  , QString value2)
{
    QVector<QVector<QString> > *vec=new QVector<QVector<QString> >();
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT * FROM user WHERE "+selectedParameter1+
            "='"+value1+"' AND "+
            selectedParameter2 + "='"+ value2+"'");
    while(q->next())
    {
        QVector<QString> * temp=new QVector<QString>();
        for(int i=0;i<16;i++)
        {
            temp->append(q->value(i).toString());
        }
        vec->append(*temp);
    }
    qDebug()<< q->executedQuery();
    qDebug()<< q;
    return vec;
}

QVector<QVector<QString> > *Database::get_textMessages(QString ID)
{
    QVector<QVector<QString> > *vec=new QVector<QVector<QString> >();
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT timeSent,fromUser,Title,ID FROM textmessages WHERE toUser='"+ID+"'");
    while(q->next())
    {
        QVector<QString> * temp=new QVector<QString>();
        for(int i=0;i<4;i++)
        {
            temp->append(q->value(i).toString());
        }
        vec->append(*temp);
    }
    return vec;
}

QString Database::Get_TextMessage_Field(QString fieldName,QString messageID)
{
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT "+ fieldName +" FROM textmessages WHERE ID='"+messageID+"'");
    if(q->next())
        return q->value(fieldName).toString();
}

void Database::Send_TextMessage(QString title, QString text, QString to, QString from)
{
    QSqlQuery *q=new QSqlQuery(this->db);
    q->prepare("INSERT INTO textMessages (title,content,fromUser,toUser,timeSent)"
               "VALUES (:title,:content,:fromUser,:toUser,:timeSent)");
    QDateTime dt=QDateTime::currentDateTime();

    q->bindValue(":title",title);
    q->bindValue(":content",text);
    q->bindValue(":fromUser",from);
    q->bindValue(":toUser",to);
    q->bindValue(":timeSent",dt.time().toString()+" "+dt.date().toString());

    q->exec();
    qDebug()<<q->executedQuery();
}

void Database::Send_VoiceMessage(QString title, QString to, QString from, QString path)
{
    QSqlQuery *q=new QSqlQuery(this->db);
    q->prepare("INSERT INTO voiceMessages (title,fromUser,toUser,timeSent,path) "
               "VALUES (:title,:fromUser,:toUser,:timeSent,:path)");
    QDateTime dt=QDateTime::currentDateTime();
    qDebug()<<"Sending voice msg";
    q->bindValue(":title",title);
    q->bindValue(":fromUser",from);
    q->bindValue(":path",path);
    q->bindValue(":toUser",to);
    q->bindValue(":timeSent",dt.time().toString()+" "+dt.date().toString());

    q->exec();
    qDebug()<<q->executedQuery();

}

QVector<QVector<QString> > * Database::get_VoiceMessages(QString ID)
{
    QVector<QVector<QString> > *vec=new QVector<QVector<QString> >();
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT timeSent, fromUser, title, ID, path FROM voiceMessages WHERE toUser='"+ID+"'");
    while(q->next())
    {
        QVector<QString> * temp=new QVector<QString>();
        for(int i=0;i<5;i++)
        {
            temp->append(q->value(i).toString());
        }
        vec->append(*temp);
    }
    qDebug()<< q->executedQuery();

    qDebug()<<"Vec size here is " <<vec->size();
    return vec;
}

QString Database::Get_VoiceMessage_Info(QString messageID, QString fieldName)
{
    qDebug()<<"ID: "<<messageID;
    qDebug()<<"field name: "<<fieldName;
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT "+ fieldName +" FROM voicemessages WHERE ID='"+messageID+"'");
    if(q->next())
        return q->value(fieldName).toString();
}

bool Database::Is_Friend(QString mainUser, QString targetUser)
{
    qDebug()<<"ISFRIEND function";
    qDebug()<<"mainuser "<<mainUser;
    qDebug()<<"target user"<<targetUser;
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT * FROM friends WHERE user='"+targetUser+"' AND friendUser='"+mainUser+"'");
    if(q->next())
        return true;
    return false;
}

void Database::Make_Friends(QString mainUser, QString targetUser)
{
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("INSERT INTO friends (user, friendUser) VALUES ('"+mainUser+"', '"+targetUser+"')");
}

bool Database::Is_Administrator(QString username, QString pw)
{
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("SELECT * FROM admin");
    if(q->next())
    {
        if(q->value("username")!=username || q->value("password")!=pw)
            return false;
        return true;
    }
}

void Database::Delete_User(QString ID)
{
    QSqlQuery *q=new QSqlQuery(this->db);
    q->exec("DELETE FROM user WHERE username='"+ID+"'");
}
