#ifndef QQRENCODETESTSUITE_H
#define QQRENCODETESTSUITE_H

#include <QObject>

/**
 * For now, manual inspection of images is needed to verify the resulting QR is correct.
 * @brief The QQREncodeTestSuite class
 */
class QQREncodeTestSuite : public QObject
{
    Q_OBJECT
public:
    explicit QQREncodeTestSuite(QObject *parent = 0);

private slots:
    void initTestCase();
    void accessors();
    void encodeAlphaNumeric();
    void encodeByteArray();
    void encodeKanji();
};

#endif // QQRENCODETESTSUITE_H
