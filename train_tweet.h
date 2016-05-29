#ifndef TRAIN_TWEET_H
#define TRAIN_TWEET_H
#include <QString>
#include <QVector>

class train_tweet
{
public:
    train_tweet();

    void setText(const QString& str);
    void setRatio(const int& value);
    void setRatio(const QString& value);
    QString getText();
    int getRatio();
    int getLine();
    void setLine(const int& lineNumber);
private:
    QString text;
    int ratio;
    bool isFilled;
    int line;
};

#endif // TRAIN_TWEET_H
