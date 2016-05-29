#include "train_tweet.h"

train_tweet::train_tweet()
{
    text="";
    ratio=-100;
    isFilled=false;
}

void train_tweet::setText(const QString& str)
{
    text =str;
}

void train_tweet::setRatio(const QString& value)
{
    if (isFilled)
    {
        ratio=+value.toInt();
        return;
    }
    ratio=value.toInt();
    isFilled=true;
}
void train_tweet::setRatio(const int& value)
{
    if (isFilled)
    {
        ratio=+value;
        return;
    }
    ratio=value;
    isFilled=true;
}

QString train_tweet::getText()
{
    return text;
}

int train_tweet::getRatio()
{
//    int temp;
//    int sum=0;
//    foreach (temp, ratio) {
//        sum+=temp;
//    }
//    return sum;
    return ratio;
}

int train_tweet::getLine()
{
    return line;
}

void train_tweet::setLine(const int& lineNumber)
{
    line=lineNumber;
}





