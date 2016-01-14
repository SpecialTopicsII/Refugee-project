#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSql>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QSqlRecord>
#include <QVector>


class Database
{
private:
    QSqlDatabase db;
public:
    Database();
    bool if_username_exists(QString );
    void register_new_user(int age, QString bdate, QString email,
                           QString fname, QString mname, QString name,
                           QString naddress, QString ncity, QString ncountry,
                           QString oaddress, QString ocity, QString ocountry,
                           QString pw, int phonenum, QString sname,
                           QString username);
    QString getPassword(QString ID);
    QString getUserInfo(QString field, QString ID);
    QVector<QVector<QString> > *getAllUsers(QString selectedParameter, QString value);
    QVector<QVector<QString> > *getAllUsers(QString selectedParameter1,QString selectedParameter2, QString value1, QString value2);
    void modify_field(QString newValue, QString fieldName, QString ID);

    QVector<QVector<QString> > * get_textMessages(QString ID);
    QString Get_TextMessage_Field(QString fieldName, QString messageID);
    void Send_TextMessage(QString title, QString text, QString to, QString from);
    void Send_VoiceMessage(QString title, QString to, QString from, QString path);
    QVector<QVector<QString> > *get_VoiceMessages(QString ID);

    QString Get_VoiceMessage_Info(QString messageID, QString field);
    bool Is_Friend(QString mainUser, QString targetUser);
    void Make_Friends(QString mainUser, QString targetUser);

    bool Is_Administrator(QString username, QString pw);
    void Delete_User(QString ID);
};

#endif // DATABASE_H
