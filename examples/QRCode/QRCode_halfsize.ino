/**
 *  QRCode
 *
 *  A quick example of generating a QR code.
 *
 *  This prints the QR code to the serial monitor as solid blocks. Each character
 *  contains two blocks, since the monospace font used in the serial monitor
 *  is approximately twice as tall as wide.
 *
 */

#include "qrcode.h"

void setup() {
    Serial.begin(115200);

    // Start time
    uint32_t dt = millis();
  
    // Create the QR code
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(3)];
    qrcode_initText(&qrcode, qrcodeData, 3, 0, "HELLO WORLD");
  
    // Delta time
    dt = millis() - dt;
    Serial.print("QR Code Generation Time: ");
    Serial.print(dt);
    Serial.print("\n");

    // Top quiet zone
    Serial.print("\n\n\n\n");

    for (uint8_t y = 0; y < qrcode.size; y += 2) {

        // Left quiet zone
        Serial.print("        ");

        // Each horizontal module
        for (uint8_t x = 0; x < qrcode.size; x++) {
            uint8_t block = qrcode_getModule(&qrcode, x, y) << 1 | qrcode_getModule(&qrcode, x, y + 1);
            
            switch (block)
            {
                case 0b00:
                    Serial.print(" ");
                    break;
                    
                case 0b01:
                    Serial.print("\u2584"); // \u2584 lower block
                    break;
                    
                case 0b10:
                    Serial.print("\u2580"); // \u2580 upper block
                    break;
                    
                case 0b11:
                    Serial.print("\u2588"); // \u2588 both blocks
                    break;
            }
        }

        Serial.print("\n");
    }

    // Bottom quiet zone
    Serial.print("\n\n\n\n");
}

void loop() {

}
