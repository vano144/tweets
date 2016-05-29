#include "porter_qt.h"
QRegExp REFLEXIVE("сь$|ся$");
QRegExp PERFECTIVEGEROUND("((ив|ивши|ившись|ыв|ывши|ывшись)|((?<=а|я)(в|вши|вшись)))$");
QRegExp ADJECTIVE("(ее|ие|ые|ое|ими|ыми|ей|ий|ый|ой|ем|им|ым|ом|его|ого|ему|ому|их|ых|ую|юю|ая|яя|ою|ею)$");
QRegExp PARTICIPLE ("((ивш|ывш|ующ)|((?<=а|я)(ем|нн|вш|ющ|щ)))$");
QRegExp VERB ("((ила|ыла|ена|ейте|уйте|ите|или|ыли|ей|уй|ил|ыл|им|ым|ен|ило|ыло|ено|ят|ует|уют|ит|ыт|ены|ить|ыть|ишь|ую|ю)|((?<=а|я)(ла|на|ете|йте|ли|й|л|ем|н|ло|но|ет|ют|ны|ть|ешь|нно)))$");
QRegExp NOUN ("(а|ев|ов|ие|ье|е|иями|ями|ами|еи|ии|и|ией|ей|ой|ий|й|иям|ям|ием|ем|ам|ом|о|у|ах|иях|ях|ы|ь|ию|ью|ю|ия|ья|я)$");
QRegExp SUPERLATIVE("(ейш|ейше)$");
QRegExp DERIVATIONAL("(ост|ость)$");
QRegExp I("и$");
QRegExp NN("((?<=н)н)$");
QRegExp SOFT("$ь");
QRegExp RV("(^.*?(?=и|у|е|э|о|а|ы|я|ю))");
void step1(QString &str) {
    QString check=str;
    //check=boost::regex_replace(*str, RV, "");
    //check=regex_replace(RV,str,"");
    check=check.replace(RV,"");
    //qDebug()<<check;
//    if (boost::regex_search(check,PERFECTIVEGEROUND)) {
//        *str=boost::regex_replace(*str, PERFECTIVEGEROUND, "");
//    } else {
//        *str=boost::regex_replace(*str, REFLEXIVE, "");
//    }
    if (check.contains(PERFECTIVEGEROUND)) {
        str=str.replace(PERFECTIVEGEROUND,"");
    } else {
        str=str.replace(REFLEXIVE,"");
    }
//    check=boost::regex_replace(*str, RV, "");
    check=str;
    check=check.replace(RV,"");
//    if (boost::regex_search(check,ADJECTIVE)) {
//        *str=boost::regex_replace(*str, ADJECTIVE, "");
//        return;
//    }
    if (check.contains(ADJECTIVE)) {
        str=str.replace(ADJECTIVE,"");
        return ;
    }
//    if (boost::regex_search(check,VERB)) {
//        *str=boost::regex_replace(*str, VERB, "");
//        return;
//    }
//    if (boost::regex_search(check,NOUN)) {
//        *str=boost::regex_replace(*str, NOUN, "");
//        return;
//    }
    if (check.contains(VERB)) {
        str=str.replace(VERB,"");
        return ;
    }
    if (check.contains(NOUN)) {
        str=str.replace(NOUN,"");
        return ;
    }
    return ;
}
void step2(QString &str) {
    QString check=str;
    //check=boost::regex_replace(*str, RV, "");
    check=check.replace(RV,"");
    if (check.contains(I)) {
        str=str.replace(I,"");
        return ;
    }
    return ;
}
void step3(QString& str) {
    QString check=str;
//    check=boost::regex_replace(*str, RV, "");
//    check=boost::regex_replace(check, RV, "");
//    check=boost::regex_replace(check, RV, "");
    check=check.replace(RV,"");
    check=check.replace(RV,"");
    //check=ckeck.replace(RV,"");
//    if (boost::regex_search(check,DERIVATIONAL)) {
//        *str=boost::regex_replace(*str, DERIVATIONAL, "");
//        return;
//    }
    if (check.contains(DERIVATIONAL)) {
        str=str.replace(DERIVATIONAL,"");
        return ;
    }
    return ;
}
void step4(QString& str) {
    QString check;
    check=check.replace(RV,"");
//    if (boost::regex_search(check,NN)) {
//        *str=boost::regex_replace(*str, NN, "");
//        return;
//    }
    if (check.contains(NN)) {
        str=str.replace(NN,"");
        return ;
    }
//    if (boost::regex_search(check,SUPERLATIVE)) {
//        *str=boost::regex_replace(*str, SUPERLATIVE, "");
//        return;
//    }
    if (check.contains(SUPERLATIVE)) {
        str=str.replace(SUPERLATIVE,"");
        return ;
    }
//    if (boost::regex_search(check,SOFT)) {
//        *str=boost::regex_replace(*str, SOFT, "");
//        return;
//    }
    if (check.contains(SOFT)) {
        str=str.replace(SOFT,"");
        return ;
    }
    return ;
}

void cleaning(QString& str)
{
    QRegExp r("[\"''“«»#\\n]");
    while (r.indexIn(str)!=-1)
    {
        str.remove(r.indexIn(str),1);
    }
}

bool porter_qt(QString& str) {
    str=str.toLower();
    QRegExp eng("[A-z0-9]");
    if (eng.indexIn(str)!=-1) return false;
    cleaning(str);
    step1(str);
    step2(str);
    step3(str);
    step4(str);
    return true;
}


