#ifndef EDITPROFILE_H
#define EDITPROFILE_H
#include <QObject>
#include <QWidget>
class QDialog;
class QPushButton;
class QLineEdit;
class Database;

class EditProfile : public QObject
{
    Q_OBJECT
private:
    Database *myDB;
    QPushButton * cancelButton;
    QPushButton * okButton;
    QLineEdit * name1;
    QLineEdit * secondName1;
    QLineEdit * birthDate1;
    QLineEdit * age1;
    QLineEdit * fathersName1;
    QLineEdit * mothersName1;
    QLineEdit * currentAddress1;
    QLineEdit * oldAddress1;
    QLineEdit * currentCity1;
    QLineEdit * oldCity1;
    QLineEdit * currentCountry1;
    QLineEdit * oldCountry1;
    QLineEdit * phoneNumber1;
    QLineEdit * email1;
    QLineEdit * username1;
    QLineEdit * password1;
    QDialog *dialog;
    QString ID;

public:
    EditProfile(QString ID);

public slots:
    void cancel_action();
    void save_action();
};

#endif // EDITPROFILE_H
