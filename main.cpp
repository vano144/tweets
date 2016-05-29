#include <QApplication>
#include "apitweets.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<train_tweet> train_sample=getTrainSample("/Users/v144/Documents/workspace/C++/build-tweets-Desktop_Qt_5_6_0_clang_64bit-Debug/bank_train_2016.xml");

    QMap<QString,dictionaryWord> dict=getDictionary(train_sample);
    QVector<train_tweet> etalon_sample=getEtalonSample("/Users/v144/Documents/workspace/C++/build-tweets-Desktop_Qt_5_6_0_clang_64bit-Debug/banks_test_etalon.xml");
    isValidDictionary(dict,etalon_sample);

    return a.exec();
}

