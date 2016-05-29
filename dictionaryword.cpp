#include "dictionaryword.h"

dictionaryWord::dictionaryWord()
{
    Initratio=0;
    amountWord=1;
    word="";
}
void dictionaryWord::neutral()
{
   Initratio=0;
}

dictionaryWord::dictionaryWord(const QString& str,const int& rating)
{
    Initratio=rating;
    word=str;
    amountWord=1;
}
void dictionaryWord::increaseAmount()
{
    amountWord++;
}
double dictionaryWord::countFinalRatio()
{
    finalRatio=(double)Initratio/(double)amountWord;
    return finalRatio;
}
QString dictionaryWord::getWord()
{
    return word;
}
QString dictionaryWord::setWord(const QString& str)
{
    word=str;
}
