#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QList>
#include <QObject>
#include <QtTest>
#include <QStringList>

/**
 * @brief The TestRunner class
 * Inspired from mlvljr's TestRunner here:
 * http://stackoverflow.com/questions/1524390/what-unit-testing-framework-should-i-use-for-qt
 */
class TestRunner : public QObject
{
    Q_OBJECT
public:
    explicit TestRunner(QStringList args, QObject *parent = 0);
    
    void addTest(QObject *test);

signals:
    void finished(int result);
    
public slots:
    void run();

private:
    QStringList m_arguments;
    QList<QObject*> m_tests;
    int m_overallResult;
};

#endif // TESTRUNNER_H
