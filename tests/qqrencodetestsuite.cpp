#include "qqrencodetestsuite.h"
#include <qqrencode.h>
#include <QTextCodec>
#include <QImage>
#include <QtTest/QTest>

const QString RESULTS_PATH = "./results/";

QQREncodeTestSuite::QQREncodeTestSuite(QObject *parent) :
    QObject(parent)
{
}

void QQREncodeTestSuite::initTestCase()
{
    QDir().rmpath(RESULTS_PATH);
    QDir().mkpath(RESULTS_PATH);
}

void QQREncodeTestSuite::accessors()
{
    QQREncode encoder;
    encoder.setLevel(QQREncode::ErrorCorrectionLevel::HIGH);
    QCOMPARE(encoder.getLevel(),QQREncode::ErrorCorrectionLevel::HIGH);
    encoder.setVersion(40);
    QCOMPARE(encoder.version(), 40);
    encoder.setMargin(8);
    QCOMPARE(encoder.margin(),8);
    encoder.setMicro(true);
    QCOMPARE(encoder.isMicro(),true);
}

void QQREncodeTestSuite::encodeAlphaNumeric()
{
    QQREncode encoder;
    QVERIFY(encoder.encode(QString("abcdefghijklmnopqrstuvwxyz 1234567890$%*+-./:")));
    encoder.toSVG(RESULTS_PATH + "alphanumeric.svg",200);
    QImage code = encoder.toQImage();
    code.scaled(200,200).save(RESULTS_PATH + "alphanumeric.png","PNG");
}

void QQREncodeTestSuite::encodeByteArray()
{
    QQREncode encoder;
    unsigned char testdata[] = {0xF3, 0xFF, 0xFE, 0xF1};
    QVERIFY(encoder.encode(QByteArray((const char*)testdata, 4)));
    encoder.toSVG(RESULTS_PATH + "bytearray.svg",200);
    QImage code = encoder.toQImage();
    code.scaled(200,200).save(RESULTS_PATH + "bytearray.png","PNG");
}

void QQREncodeTestSuite::encodeKanji()
{
    QQREncode encoder;
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QVERIFY(encoder.encodeKanji(codec->fromUnicode(QString("お疲れ様テスト。"))));
//    delete codec;
    encoder.toSVG(RESULTS_PATH + "kanji.svg",200);
    QImage code = encoder.toQImage();
    code.scaled(200,200).save(RESULTS_PATH + "kanji.png","PNG");
}
