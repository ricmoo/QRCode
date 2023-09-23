//
// Created by dongnom on 24.09.23.
//
// test to run qrcode generation on linux cli
//

#include <sys/time.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>

#include "../src/qrcode.h"

uint64_t millis() {
    struct timeval tp;
    gettimeofday(&tp, NULL);

    return tp.tv_sec * 1000 + tp.tv_usec / 1000; //get current timestamp in milliseconds
}

int main(void) {
#ifdef TEST_LARGE
    const char *data = " et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. \n"
                       "\n"
                       "Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dol";
#else
    const char * data = "Hello World!";
#endif


    // Start time
    uint64_t dt = millis();

    // Create the QR code
    QRCode qrcode;
    uint8_t version = findFittingVersion_text(ECC_HIGH, data);
    printf("fitting version: %" PRIu8 "\n", version);
    if (version == 0) {
        printf("No fitting version found! falling back to 3\n");
        version = 3;
    }
    uint8_t qrcodeData[qrcode_getBufferSize(version)];
    qrcode_initText(&qrcode, qrcodeData, version, ECC_LOW, data);

    // Delta time
    dt = millis() - dt;
    printf("QR Code Generation Time: %" PRIu64 "ms\n", dt);

    // Top quiet zone
    printf("\n\n\n\n");

    for (uint8_t y = 0; y < qrcode.size; y++) {

        // Left quiet zone
        printf("        ");

        // Each horizontal module
        for (uint8_t x = 0; x < qrcode.size; x++) {

            // Print each module (UTF-8 \u2588 is a solid block)
            printf(qrcode_getModule(&qrcode, x, y) ? "\u2588\u2588": "  ");

        }

        printf("\n");
    }

    // Bottom quiet zone
    printf("\n\n\n\n");
}
