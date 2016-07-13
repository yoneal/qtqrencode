#include "testrunner.h"
#include <QtTest/QTest>

TestRunner::TestRunner(QStringList args, QObject *parent) :
    QObject(parent),
    m_arguments(args)
{
}

void TestRunner::addTest(QObject *test)
{
    test->setParent(this);
    m_tests.append(test);
}


void TestRunner::run()
{
    foreach (QObject *test, m_tests)
    {
        m_overallResult = QTest::qExec(test, m_arguments);
        if (m_overallResult != 0)
        {
            break;
        }
    }
    emit finished(m_overallResult);
}
