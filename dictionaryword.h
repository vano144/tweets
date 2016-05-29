#ifndef DICTIONARYWORD_H
#define DICTIONARYWORD_H
#include <QString>

class dictionaryWord
{
public:
    void increaseAmount();
    dictionaryWord();
    dictionaryWord(const QString& str,const int& rating);
    double countFinalRatio();
    QString getWord();
    QString setWord(const QString& str);
    void neutral();
    int amountWord;
    int Initratio;
    QString word;
    double finalRatio;
    int positiveAmount=0;
    int negativeAmount=0;
    int neutralAmount=0;
};

#endif // DICTIONARYWORD_H
