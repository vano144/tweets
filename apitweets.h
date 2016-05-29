#ifndef APITWEETS_H
#define APITWEETS_H

#include <QXmlStreamReader>
#include <QFile>
#include "train_tweet.h"
#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include "porter_qt.h"
#include "dictionaryword.h"
#include <iostream>
#include <QMap>
#include <QStringList>
#include <fstream>
#include <QRegExp>
#include <algorithm>
#include <math.h>
QRegExp puncmark(",|\\.|!|\\?|\\\"|…|:|-|\\(|\\)|—|\\[|\\]");
using namespace std;
double AMOUNT_POS=0;
double AMOUNT_NEG=0;
double AMOUNT_NET=0;
bool isUniqWord(QString word,QMap<QString,int>* filter)
{
    if (filter->count(word))
        return false;
    return true;
}
void statistic(dictionaryWord wordFIle, QMap<QString,dictionaryWord>* store,QMap<QString,int>* filter) { //counting frequences
    QString word = wordFIle.getWord();
    if (word.contains(puncmark)) {
        word=word.replace(puncmark,"");
    }

    if (word=="" || word.length()<3 ) return;
    //if (reg.indexIn(word)!=0) return;

    if (!porter_qt(word)) return;
    if (store->count(word)==1) {                       //addition of old element
        (*store)[wordFIle.getWord()].increaseAmount();
        if (wordFIle.Initratio==0) //optimization, if word in neutral tweet, rate should be 0!
        {
            //(*store)[wordFIle.getWord()];
            //store->remove(word);
            (*store)[word].neutralAmount++;
        }
        if (wordFIle.Initratio==1)
        {
            (*store)[word].positiveAmount++;
        }
        if (wordFIle.Initratio==-1)
        {
            (*store)[word].negativeAmount++;
        }
    }
    else {
        if (isUniqWord(word, filter))
        {//addition of new element
            //wordFIle.setWord(QString::fromUtf8(h.c_str()));
            wordFIle.setWord(word);
            store->insert(word,wordFIle);
            if (wordFIle.Initratio==1)
            {
                (*store)[word].positiveAmount++;
            }
            if (wordFIle.Initratio==-1)
            {
                (*store)[word].negativeAmount++;
            }
            if (wordFIle.Initratio==0)
            {
                (*store)[word].neutralAmount++;
            }
        }
    }
}

QVector<train_tweet> getTrainSample(const QString& pathToFile)
{

    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly))
        qDebug()<<"bad";
    QDomDocument mDocument;
    if (!mDocument.setContent(&file))
    {
        qDebug()<<"bad";
    }
    QDomNodeList rates = mDocument.elementsByTagName("table");
    QVector<train_tweet> train_sample;

    for (int i = 0; i < rates.size(); i++)
    {
        train_tweet temp;
        QDomNode n = rates.item(i);
        QDomElement mElement = n.firstChildElement("column");
        while (true)
        {
            if (mElement.attribute("name")=="text")
            {
                temp.setText(mElement.text());
                temp.setLine(mElement.lineNumber());
            }
            if (mElement.text()=="1" || mElement.text()=="0" || mElement.text()=="-1")
            {
                if (mElement.text()=="1") AMOUNT_POS++;
                if (mElement.text()=="-1") AMOUNT_NEG++;
                if (mElement.text()=="0") AMOUNT_NET++;
                temp.setRatio(mElement.text());
            }
            mElement = mElement.nextSiblingElement("column");
            if (!mElement.hasAttribute("name")) break;
            if (mElement.isNull())
                continue;
        }
        train_sample.push_back(temp);
    }
    return train_sample;
}

QVector<train_tweet> getEtalonSample(const QString& pathToFile)
{

    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly))
        qDebug()<<"bad";
    QDomDocument mDocument;
    if (!mDocument.setContent(&file))
    {
        qDebug()<<"bad";
    }
    QDomNodeList rates = mDocument.elementsByTagName("table");
    QVector<train_tweet> train_sample;

    for (int i = 0; i < rates.size(); i++)
    {
        train_tweet temp;
        QDomNode n = rates.item(i);
        QDomElement mElement = n.firstChildElement("column");
        while (true)
        {
            if (mElement.attribute("name")=="text")
            {
                temp.setText(mElement.text());
                temp.setLine(mElement.lineNumber());
            }
            if (mElement.text()=="1" || mElement.text()=="0" || mElement.text()=="-1")
            {
                temp.setRatio(mElement.text());
            }
            mElement = mElement.nextSiblingElement("column");
            if (!mElement.hasAttribute("name")) break;
            if (mElement.isNull())
                continue;
        }
        train_sample.push_back(temp);
    }
    return train_sample;
}


void show(const QVector<train_tweet>& tmp)
{
    int i=0;
    train_tweet temp;
    foreach (temp, tmp) {
        i++;
        qDebug()<<"TEXT"<<temp.getText()<<"\n";
        qDebug()<<"RATIO"<<temp.getRatio()<<"\n";

        qDebug()<<"LINE"<<temp.getLine()<<"\n";
        if (i==100) break;
    }
}
void WithoutPorterstatistic(QString wordFIle, QMap<QString,int>* store) { //counting frequences
    if (wordFIle.contains(puncmark)) {
        wordFIle=wordFIle.replace(puncmark,"");
    }
    if (wordFIle=="") return;
    if (store->count(wordFIle)==1) {
        //addition of old element
        (*store)[wordFIle]++;
    }
    else {                                            //addition of new element
        store->insert (wordFIle,1);
    }
}
int countWordsPA(QMap <QString,int>* storeFile1,char filename[100]) {
    std::string wordFIle;
    std::ifstream in;
    int amount=0;
    in.open(filename);
    if (!in.is_open()) {
        std::cout<<"trouble with"<<filename<<endl;
        return -1;
    }
    while (in>>wordFIle) {
        QString str = QString::fromUtf8(wordFIle.c_str());
        WithoutPorterstatistic(str, storeFile1);
        amount++;
    }
    in.close();
    return amount;
}
QMap<QString,dictionaryWord> getDictionary(const QVector<train_tweet>& tmp)
{
    char filename2[100]="/Users/v144/Documents/fortest/cleaning.txt";
    QMap<QString,int> filter;
    countWordsPA(&filter,filename2);
    QMap<QString,dictionaryWord> dictionary;
    int i=0;
    train_tweet temp;
    foreach (temp, tmp) {
        i++;
        QStringList tweetsAfterSplit =temp.getText().split(" ");
        QString elemOfTweet;
        foreach (elemOfTweet, tweetsAfterSplit) {
            dictionaryWord wordOfTweet(elemOfTweet,temp.getRatio());
            statistic(wordOfTweet,&dictionary,&filter);
        }
    }
    return dictionary;
}
void showDictionary(QMap<QString,dictionaryWord> dictionary)
{
    int amount=0;
    foreach (QString key, dictionary.keys())
    {

        dictionaryWord value=dictionary.value(key);
        amount++;
        if (value.Initratio!=0) //{};
            qDebug() << key << ":" << (double)value.Initratio/(double)value.amountWord <<"amount woed"<< value.amountWord<<" initratio "<<value.Initratio<<" + "<<value.positiveAmount<<" - "<<value.negativeAmount<<" 0 "<<value.neutralAmount;
    }
    qDebug()<<" колслов "<<amount;

}
double tweetRate(QStringList tweet,QMap<QString,dictionaryWord> dict)
{
    double rate=0;
    double rateConst=1.5, rateConst2=0.7;
    QString elemOfTweet;
    int tweetAmount=0;
    int posAmount=0;
    int negAmount=0;
    double newrate=0;

    double p_pos=0;
    double p_neg=0;
    double p_net=0;
    double pos_CONST=log(AMOUNT_POS/(AMOUNT_NEG+AMOUNT_NET+AMOUNT_POS));
    double neg_CONST=log(AMOUNT_NEG/(AMOUNT_NEG+AMOUNT_NET+AMOUNT_POS));
    double net_CONST=log(AMOUNT_NET/(AMOUNT_NEG+AMOUNT_NET+AMOUNT_POS));
    foreach (elemOfTweet, tweet) {
        porter_qt(elemOfTweet);

        if (dict.contains(elemOfTweet))
        {
            p_pos+=log((double)(dict[elemOfTweet].positiveAmount)/AMOUNT_POS);//(double)(dict[elemOfTweet].positiveAmount+dict[elemOfTweet].negativeAmount+dict[elemOfTweet].neutralAmount);
            p_neg+=log((double)(dict[elemOfTweet].negativeAmount)/AMOUNT_NEG);//(double)(dict[elemOfTweet].positiveAmount+dict[elemOfTweet].negativeAmount+dict[elemOfTweet].neutralAmount); //classifier bayes
            p_net+=log((double)(dict[elemOfTweet].neutralAmount)/AMOUNT_NET);//(double)(dict[elemOfTweet].positiveAmount+dict[elemOfTweet].negativeAmount+dict[elemOfTweet].neutralAmount);
            tweetAmount++;
            newrate+=(double)(dict[elemOfTweet].positiveAmount-dict[elemOfTweet].negativeAmount)/(double)(dict[elemOfTweet].positiveAmount+dict[elemOfTweet].negativeAmount+dict[elemOfTweet].neutralAmount);

            if (dict[elemOfTweet].neutralAmount>5) continue;
            if ((dict[elemOfTweet].positiveAmount+dict[elemOfTweet].negativeAmount)*rateConst2<dict[elemOfTweet].neutralAmount) continue;
            //if (dict[elemOfTweet].negativeAmount*rateConst2<dict[elemOfTweet].neutralAmount) continue;
            //if ((dict[elemOfTweet].positiveAmount+dict[elemOfTweet].negativeAmount)<2) continue;
            if (dict[elemOfTweet].positiveAmount>rateConst*dict[elemOfTweet].negativeAmount)
            {
                rate+=dict[elemOfTweet].positiveAmount;//-dict[elemOfTweet].negativeAmount;//(double)dict[elemOfTweet].amountWord;
                posAmount++;

            } else if (rateConst*dict[elemOfTweet].positiveAmount<dict[elemOfTweet].negativeAmount)
            {
                rate+=-dict[elemOfTweet].negativeAmount;//+(rateConst+1)*dict[elemOfTweet].positiveAmount;//(double)dict[elemOfTweet].amountWord;
                negAmount++;
            }
        }

    }
    p_pos+=pos_CONST;
    p_neg+=neg_CONST;
    p_net+=net_CONST;
    //rate/=tweetAmount;
    //rate+=posAmount-negAmount;
    //if ((posAmount+negAmount)<=1) return 0;
    newrate/=tweetAmount;

//    if (rate>0) return 1;
//    if (rate<0) return -1;

//    if (newrate>0.13) return 1;
//    if (newrate<-0.3) return -1;

    if (p_neg>p_pos && p_neg>p_net) return -1;
    if (p_pos>p_neg && p_pos>p_net) return 1;
    return 0;
}

void isValidDictionary(QMap<QString,dictionaryWord> dict,  QVector<train_tweet> sample)
{
    train_tweet tweet;
    double matr[3][3];
    int amount=0;
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            matr[i][j]=0;
        }
    }
    foreach (tweet, sample) {
        QStringList tweetsSplit =tweet.getText().split(" ");
        amount+=1;
        int mainRate=tweet.getRatio();
        int userRate=tweetRate(tweetsSplit,dict);
        if (mainRate==-1 && userRate==-1)
        {
            matr[2][2]+=1;
            continue;
        }
        if (mainRate==-1 && userRate!=-1)
        {
            matr[2][userRate]+=1;
            continue;
        }
        if (mainRate!=-1 && userRate==-1)
        {
            matr[mainRate][2]+=1;
            continue;
        }
        matr[mainRate][userRate]+=1;
    }

    qDebug()<<0<<"   "<<1<<"     "<<-1;
    for (int i=0;i<3;i++)
    {
        qDebug()<<matr[i][0]<<" "<<matr[i][1]<<" "<<matr[i][2];
    }
    double sumCorrect=0;
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            if (i==j)
                sumCorrect+=matr[i][j];
        }
    }
    qDebug()<<sumCorrect/amount<<" %Correct ";
}



#endif // APITWEETS_H
