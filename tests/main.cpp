#include "qqrencodetestsuite.h"
#include "testrunner.h"
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Perform tests
    TestRunner runner(QStringList(), &app);
    runner.addTest(new QQREncodeTestSuite(&app));
    QObject::connect(&runner, &TestRunner::finished, [&] (int result)
    {
        qDebug() << "Overall Result: " << (result == 0 ? "PASS" : "FAIL");
        app.quit();
    });
    QTimer::singleShot(0, &runner, SLOT(run()));

    return app.exec();
}
