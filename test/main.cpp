#include "qqrencodetestsuite.h"
#include "testrunner.h"

#include <QCoreApplication>
#include <QtTest>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
#endif

    // Perform tests
    TestRunner runner(QStringList(), &app);
    /**
      * Add tests here
      */
    runner.addTest(new QQREncodeTestSuite(&app));
    QObject::connect(&runner, &TestRunner::finished, [&] (int result)
    {
        qDebug() << "Overall Result: " << (result == 0 ? "PASS" : "FAIL");
        app.quit();
    });
    QTimer::singleShot(0, &runner, SLOT(run()));

    return app.exec();
}

