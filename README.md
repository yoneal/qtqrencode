[![Qt Pods](http://qt-pods.org/assets/logo.png "Qt Pods")](http://qt-pods.org)
## qtqrencode

Qt 5 wrapper and renderer for [qrencode](https://github.com/fukuchi/libqrencode) (QR Code encoding) library.

## Build (via qt-pods)

You can add QrEncode to your project with a single click using qt-pods. Read more about qt-pods here:
https://github.com/cybercatalyst/qt-pods

## Manual build

You will need [Qt 5+](http://qt-project.org/downloads) and [qrencode 3.4+](http://fukuchi.org/works/qrencode). Clone this repo and build it with Qt's qmake:
```bash
sudo apt-get install libqrencode-dev
git clone https://github.com/yoneal/qtqrencode
cd qtqrencode
mkdir build && cd build
qmake -Wall ../qtqrencode.pro
make
# You can install it, if you want..
sudo make install
```
Or, you can just open the project using Qt Creator.

## Usage

Just grab the library, along with the following header files:

* qqrencode.h
* libqtqrencode_global.h

Then include it in your project like so,
```
LIBS += -lqtqrencode
```

No need to manually copy the files if you installed it in the system directories..

## Profit
```
#include <qqrencode.h>

...

QQREncode encoder;
encoder.encode(QString("abcdefghijklmnopqrstuvwxyz 1234567890$%*+-./:");
QImage qrcode = encoder.toQImage();
qrcode.scaled(150,150).save("qrcode.jpg","JPG");
```

See [test](test) folder for more examples.

## Thanks

Thanks to [Kentaro Fukuchi](http://fukuchi.org) for sharing qrencode.
