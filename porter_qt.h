#ifndef PORTER_QT_H
#define PORTER_QT_H




//block of regular expressions of porters'algorithm
#include <QRegExp>
#include <QString>
#include <QDebug>
void cleaning(QString &str);
void step1(QString &str);
void step2(QString &str);
void step3(QString& str);
void step4(QString& str);
bool porter_qt(QString& str);



#endif // PORTER_QT_H
