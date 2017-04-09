QRCode
======

A simple library for generating [QR codes](https://en.wikipedia.org/wiki/QR_code) in C,
optimized for processing and memory constrained systems.

**Features:**

- Stack-based (no heap necessary; but you can use heap if you want)
- Low-memory foot print (relatively)
- Compile-time stripping of unecessary logic
- MIT License; do with this as you please


Installing
----------

To install this library, download and save it to your Arduino libraries directory.

Rename the directory to QRCode (if downloaded from GitHub, the filename may be
qrcode-master; library names may not contain the hyphen, so it must be renamed)


API
---

**Generate a QR Code**

```c
// The structure to manage the QR code
QRCode qrcode;

// Allocate a chunk of memory to store the QR code
uint8_t qrcodeBytes[qrcode_getBufferSize()];

qrcode_initText(&qrcode, qrcodeBytes, 3, ECC_LOW, "HELLO WORLD");
```

**Draw a QR Code**

How a QR code is used will vary greatly from project to project. For example:

- Display on an OLED screen (128x64 nicely supports 2 side-by-side version 3 QR codes)
- Print as a bitmap on a thermal printer
- Store as a BMP (or with a some extra work, possibly a PNG) on an SD card

The following example prints a QR code to the Serial Monitor (it likely will
not be scannable, but is just for demonstration purposes).

```c
for (uint8 y = 0; y < qrcode.size; y++) {
    for (uint8 x = 0; x < qrcode.size; x++) {
        if (qrcode_getModule(&qrcode, x, y) {
            Serial.print("**");
        } else {
            Serial.print("  ");
        }
    }
    Serial.print("\n");
}
```

Special Thanks
--------------

A HUGE thank you to [nayuki](https://www.nayuki.io/) for the 
[QR code C++ library](https://github.com/nayuki/QR-Code-generator/tree/master/cpp)
which was critical in development of this library.


License
-------

MIT License.
