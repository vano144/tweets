#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T17:02:00
#
#-------------------------------------------------

QT       += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tweets
TEMPLATE = app


SOURCES += main.cpp \
    train_tweet.cpp \
    porter_qt.cpp \
    dictionaryword.cpp

HEADERS  += \
    train_tweet.h \
#    porter.h \
    porter_qt.h \
    dictionaryword.h \
    apitweets.h






INCLUDEPATH += /usr/local/Cellar/boost/1.58.0/include
LIBS += -L/usr/local/Cellar/boost/1.58.0/lib
macx: LIBS += -lboost_regex
