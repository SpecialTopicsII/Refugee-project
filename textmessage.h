#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H
#include <QObject>


class QPushButton;
class QPushButton;
class QLineEdit;
class QTextEdit;
class QDialog;
class TextMessage : public QObject
{
    Q_OBJECT
private:
    QString from;
    QLineEdit * title;
    QTextEdit * text;
    QLineEdit * to;
    QLineEdit * time;

    QDialog *dlg;

public:
    TextMessage(QString from);
public slots:
    void Send_Message();
};

#endif // TEXTMESSAGE_H
