#ifndef QQRENCODE_H
#define QQRENCODE_H

#include <QtCore>

class QREncodePrivate;

class QREncode {
    Q_GADGET
    Q_ENUMS(ErrorCorrectionLevel)

public:
    enum ErrorCorrectionLevel {
        LOW,
        MEDIUM,
        QUARTILE,
        HIGH
    };

    QREncode();
    ~QREncode();

    void setLevel(ErrorCorrectionLevel value);
    ErrorCorrectionLevel getLevel() const;
    void setVersion(int version);
    int version() const;
    void setMargin(int value);
    int margin() const;
    void setMicro(bool value);
    bool isMicro() const;
    void setBackground(QColor color);
    void setForeground(QColor color);

    bool encode(QByteArray input);
    bool encode(QString input, bool caseSensitive=true);
    bool encodeKanji(QByteArray input, bool caseSensitive=true);

    bool toSVG(QString output, int size);
    QImage toQImage(int size=0);

    // ToDo: encode structured, rle

private:
    Q_DISABLE_COPY(QREncode)
    QScopedPointer<QREncodePrivate> d_ptr;
    Q_DECLARE_PRIVATE(QREncode)
};

#endif // QQRENCODE_H
