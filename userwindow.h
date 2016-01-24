#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QWidget>


class QLabel;
class QPushButton;
class QTabWidget;
class QTableWidget;
class QFile;
class QLineEdit;
class QSound;

class UserWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *name,*surname,*birthdate,*email,*currentAddress,
    *currentCity,*currentCountry,*phoneNumber;
    QPushButton *logoutButton,*editButton,*searchButton,
    *textM,*voiceM;

    QWidget *window, *textWidget, *voiceWidget;
    QString username;

    QTabWidget * tabs;
    QPushButton *sendTMessage,*sendVMessage,*refreshButton1,
    *refreshButton2, *openMessage1, *openMessage2;
    QTableWidget *vmTable, *tmTable;
    QString textMessageID;

    QString voiceMessagePath, voiceMessageName;

    QLineEdit *title;
    QLineEdit *toUser;

    QString currentVoiceMsgID;
    QSound *sound;
public:
    explicit UserWindow(QWidget *parent = 0);
    UserWindow(QString ID);

signals:

public slots:
    void edit_profile_action();
    void search_action();
    void Write_New_Text_Message();
    void Write_New_Voice_Message();
    void update_text_messages();
    void Open_Text_Message();

    void Record_New();
    void Select_Message();
    void Send_Recorded_Message();
    void Update_Voice_Messages();
    void Open_Voice_Message();
    void Play_Message();
    void Stop_Message();

    void Sign_Out();
    void Edit_Profile();
    void New_Text();
    void New_Voice();
    void Find();
    void Info();

};

#endif // USERWINDOW_H
