// QR Code

#pragma once

#include <stdbool.h>
#include "cJSON.h"


typedef struct {
    int version;
    bool **modules;
} QRCode;

/*
{
  "version": 1,
  "modules": [
    [ true, false ],
    [ false, true ]
   ]
}
*/


// Create a new `QRCdoe` struct
QRCode *QRcode_new(void);

// Initlize the `qrcode`
void QRCode_init(QRCode *qrcode, int version, bool **modules);

// Initize `qrcode` from json
void QRCode_init_from_json(QRCode *qrcode, cJSON *json);

// Create QRCode with string `data`
QRCode *QRCode_create(char *data);

// Cretae QRCode struct from `json`
QRCode *QRCode_create_from_json(cJSON *json);

// Get dimention of `qrcode`
int QRCode_get_dimention(QRCode *qrcode);

// ASCII (UTF-8 BTW) Art represantation of QR Code
char *QRCode_to_string(QRCode *qrcode);

// Same as QRCode_to_string, but splited by newlines
char **QRCode_to_string_lines(QRCode *qrcode);

// Free the `qrcode`
void QRCode_free(QRCode *qrcode);

