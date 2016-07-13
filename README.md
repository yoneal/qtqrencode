## qtqrencode

Qt 5 wrapper and renderer for [qrencode](https://github.com/fukuchi/libqrencode) (QR Code encoding) library.

## Build

You will need [Qt 5+](http://qt-project.org/downloads), [qrencode 3.4+](http://fukuchi.org/works/qrencode) and [CMake](http://cmake.org). Clone this repo and build it using cmake:
```bash
git clone https://github.com/yoneal/qtqrencode
cd qtqrencode
mkdir build && cd build
cmake ..
make

# Optionally, you can install it:
sudo make install
```

If you want to build the tester app use:
```bash
cmake .. -DWITH_TESTS:bool=ON
```

## Usage

Just grab the library, along with the following header file *"qqrencode.h"*.

Then include it in your project like so,
```
LIBS += -lqtqrencode
```

No need to manually copy the files if you installed it in the system directories.

## Profit
```
#include <qqrencode.h>

...

QQREncode encoder;
encoder.encode(QString("abcdefghijklmnopqrstuvwxyz 1234567890$%*+-./:");
QImage qrcode = encoder.toQImage();
qrcode.scaled(150,150).save("qrcode.jpg","JPG");
```

See the [tests](tests) directory for more examples.

## Thanks

Thanks to [Kentaro Fukuchi](http://fukuchi.org) for sharing qrencode.

## License
See [LICENSE](LICENSE) file.
