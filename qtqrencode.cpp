// Own includes
#include "qtqrencode.h"
#include "qtqrencode_p.h"

// QrEncode includes
#include <qrencode.h>

// Qt includes
#include <QDateTime>
#include <QSvgGenerator>

#define INCHES_PER_METER (100.0/2.54)

QREncodePrivate::~QREncodePrivate() {
    QRcode_free(m_code);
}

void QREncodePrivate::paint(QPainter &painter)
{
    unsigned char *row, *p;
    int x, y;

    int symwidth = m_code->width + m_margin * 2;
    painter.setClipRect(QRect(0,0,symwidth, symwidth));
    painter.setPen(m_pen);
    painter.setBrush(m_fg);

    /* Make solid background */
    painter.fillRect(QRect(0, 0, symwidth, symwidth), m_bg);

    /* Write data */
    p = m_code->data;
    for(y=0; y<m_code->width; y++) {
        row = (p+(y*m_code->width));
        /* no RLE */
        for(x=0; x<m_code->width; x++) {
            if(*(row+x)&0x1) {
                painter.drawRect(m_margin + x, m_margin + y, 1, 1);
            }
        }

    }
}

QREncode::QREncode()
    : d_ptr(new QREncodePrivate(this))
{
}

QREncode::~QREncode()
{
}

void QREncode::setLevel(QREncode::ErrorCorrectionLevel value)
{
    Q_D(QREncode);
    switch (value) {
    case ErrorCorrectionLevelLow:
        d->m_level = QR_ECLEVEL_L;
        break;
    case ErrorCorrectionLevelMedium:
        d->m_level = QR_ECLEVEL_M;
        break;
    case ErrorCorrectionLevelQuartile:
        d->m_level = QR_ECLEVEL_Q;
        break;
    case ErrorCorrectionLevelHigh:
        d->m_level = QR_ECLEVEL_H;
        break;
    }
}

QREncode::ErrorCorrectionLevel QREncode::getLevel() const
{
    Q_D(const QREncode);
    switch (d->m_level) {
    case QR_ECLEVEL_L:
        return ErrorCorrectionLevelLow;
    case QR_ECLEVEL_M:
        return ErrorCorrectionLevelMedium;
    case QR_ECLEVEL_Q:
        return ErrorCorrectionLevelQuartile;
    case QR_ECLEVEL_H:
        return ErrorCorrectionLevelHigh;
    }
    return ErrorCorrectionLevelLow;
}

//bool QQREncode::encode(QString code, QString output)
//{
//    if (code.isEmpty() || output.isEmpty()) {
//        return false;
//    }
//    QString program = "./qrencode.exe";
//    QStringList arguments;
//    arguments << "-t" << "PNG";
//    arguments << "-o" << output;
//    arguments << code;

//    QProcess *myProcess = new QProcess(this);
//    myProcess->start(program, arguments);
//    return myProcess->waitForFinished();
//}


void QREncode::setVersion(int version)
{
    Q_D(QREncode);
    // 1 - 40
    if (version > 0 && version <= 40)
        d->m_version = version;
}

int QREncode::version() const
{
    Q_D(const QREncode);
    return d->m_version;
}

void QREncode::setMargin(int value)
{
    Q_D(QREncode);
    if (value > -1)
        d->m_margin = value;
}

int QREncode::margin() const
{
    Q_D(const QREncode);
    return d->m_margin;
}

void QREncode::setMicro(bool value)
{
    Q_D(QREncode);
    d->m_micro = (value) ? 1 : 0;
}

bool QREncode::isMicro() const
{
    Q_D(const QREncode);
    return (d->m_micro == 1) ? true : false;
}

void QREncode::setBackground(QColor color)
{
    Q_D(QREncode);
    d->m_bg.setColor(color);
}

void QREncode::setForeground(QColor color)
{
    Q_D(QREncode);
    d->m_fg.setColor(color);
    d->m_pen.setColor(color);
}

bool QREncode::encode(QByteArray input)
{
    Q_D(QREncode);
    QRcode *c = NULL;
    if (input.isEmpty()) return false;
    if (d->m_micro) {
        c = QRcode_encodeDataMQR(input.size(), (const unsigned char*)input.constData(),
                                   d->m_version, d->m_level);
    } else {
        c = QRcode_encodeData(input.size(), (const unsigned char*)input.constData(),
                              d->m_version, d->m_level);
    }
    if (c == NULL) {
        return false;
    }
    if (d->m_code) QRcode_free(d->m_code);
    d->m_code = c;
    return true;
}

bool QREncode::encode(QString input, bool caseSensitive)
{
    Q_D(QREncode);
    if (input.isEmpty()) return false;
    QRcode *c = NULL;
    if (d->m_micro) {
        c = QRcode_encodeStringMQR(input.toStdString().c_str(),
                                   d->m_version,
                                   d->m_level,
                                   QR_MODE_8,
                                   (caseSensitive) ? 1 : 0);
    } else {
        c = QRcode_encodeString(input.toStdString().c_str(),
                                d->m_version,
                                d->m_level,
                                QR_MODE_8,
                                (caseSensitive) ? 1 : 0);
    }
    if (c == NULL) {
        return false;
    }
    if (d->m_code) QRcode_free(d->m_code);
    d->m_code = c;
    return true;
}

bool QREncode::encodeKanji(QByteArray input, bool caseSensitive)
{
    Q_D(QREncode);
    if (input.isEmpty()) return false;
    QRcode *c = NULL;
    if (d->m_micro) {
        c = QRcode_encodeStringMQR(input.constData(),
                                   d->m_version,
                                   d->m_level,
                                   QR_MODE_KANJI,
                                   (caseSensitive) ? 1 : 0);
    } else {
        c = QRcode_encodeString(input.constData(),
                                d->m_version,
                                d->m_level,
                                QR_MODE_KANJI,
                                (caseSensitive) ? 1 : 0);
    }
    if (c == NULL) {
        return false;
    }
    if (d->m_code) QRcode_free(d->m_code);
    d->m_code = c;
    return true;
}

bool QREncode::toSVG(QString output, int size)
{
    Q_D(QREncode);
    if (output.isEmpty() || d->m_code == NULL) {
        return false;
    }

    QSvgGenerator generator;
    generator.setFileName(output);
    generator.setSize(QSize(size, size));
    int symwidth = d->m_code->width + d->m_margin * 2;
    generator.setViewBox(QRect(0, 0, symwidth, symwidth));

    QPainter painter;
    painter.begin(&generator);
    d->paint(painter);
    painter.end();

    return true;
}

QImage QREncode::toQImage(int size)
{
    Q_D(QREncode);
    if (size < 0) throw std::invalid_argument("Invalid size");

    if (d->m_code == NULL) {
        std::logic_error("No qr code to convert");
    }

    int symwidth = d->m_code->width + d->m_margin * 2;
    QImage result(QSize(symwidth, symwidth), QImage::Format_Mono);
    result.fill(Qt::white);

    QPainter painter;
    painter.begin(&result);
    d->paint(painter);
    painter.end();

    if (size > 0)
        return result.scaled(size, size);
    return result;
}
