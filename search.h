#ifndef SEARCH_H
#define SEARCH_H
#include <QObject>
#include <QDialog>

class QPushButton;
class QRadioButton;
class QComboBox;
class QLineEdit;
class QLabel;
class QTableWidget;
class QWebView;

class Search : public QObject
{
    Q_OBJECT
private:
    QPushButton * okButton,*cancelButton;
    QComboBox *choice1,*choice2;
    QDialog *dialog;
    QRadioButton *radio1, *radio2;
    QLabel *label1, *label2, *label3;
    QLineEdit *field1, *field2, *field3;
    QLabel *lbl1;
    QTableWidget * table;

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

    QWebView *map;
    QString selectedUsername,username;

public:
    Search(QString ID);
public slots:
    void enable_choice1();
    void enable_choice2();
    void show_results();
    void Make_Report();
    void View_Profile();
    void Set_Profile_Info();

};

#endif // SEARCH_H
