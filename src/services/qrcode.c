// QR Code

#include <stdlib.h>
#include <string.h>
#include "services/qrcode.h"
#include "utils.h"
#include "characters.h"
#include "curl/curl.h"


QRCode *QRCode_new(void) {
    QRCode *qrcode = malloc(sizeof(QRCode));
    return qrcode;
}

void QRCode_init(QRCode *qrcode, int version, bool **modules) {
    qrcode->version = version;
    int d = QRCode_get_dimention(qrcode);
    qrcode->modules = malloc(d * sizeof(bool *));
    for (int i = 0; i < d; i++) {
        qrcode->modules[i] = malloc(d * sizeof(bool));
        for (int j = 0; j < d; j++) {
            qrcode->modules[i][j] = modules[i][j];
        }
    }
}

void QRCode_init_from_json(QRCode *qrcode, cJSON *json) {
    if (!qrcode) return;
    int version = cJSON_GetObjectItem(json, "version")->valuedouble;
    cJSON *modules_object = cJSON_GetObjectItem(json, "modules"); // "modules": [[bool, ...], ...]
    cJSON *module_row_object;
    int d = cJSON_GetArraySize(modules_object);
    bool **modules = malloc(d * sizeof(bool*));
    for (int i = 0; i < d; i++) {
        module_row_object = cJSON_GetArrayItem(modules_object, i);
        modules[i] = malloc(d * sizeof(bool));
        for (int j = 0; j < d; j++) {
            bool value = cJSON_IsTrue(cJSON_GetArrayItem(module_row_object, j));
            modules[i][j] = value;
        }
    }
    QRCode_init(qrcode, version, modules);
    for (int i = 0; i < d; i++) {
        free(modules[i]);
    }
    free(modules);
}

QRCode *QRCode_create(char *data) {
    QRCode *qrcode = NULL;
    CURL *handle = curl_easy_init();
    CURLcode res_code;
    cJSON *res_json;
    char *api_url;

    api_url = make_api_url("/qr-code/json");
    append_string_to_url(api_url, "?data=");
    append_string_to_url(api_url, data);

    curl_easy_setopt(handle, CURLOPT_URL, api_url);
    res_json = curl_easy_perform_return_json(handle, &res_code);

    if (!res_json) goto end;
    if (res_code != CURLE_OK) goto end;

    qrcode = QRCode_create_from_json(res_json);

end:
    cJSON_Delete(res_json);
    curl_easy_cleanup(handle);
    free(api_url);
    return qrcode;
}

QRCode *QRCode_create_from_json(cJSON *json) {
    if (!json) return NULL;
    QRCode *qrcode = QRCode_new();
    QRCode_init_from_json(qrcode, json);
    return qrcode;
}

int QRCode_get_dimention(QRCode *qrcode) {
    return 17 + (4 * qrcode->version);
}

char *QRCode_to_string(QRCode *qrcode) {
    int offset = 0, max_size, d;
    d = QRCode_get_dimention(qrcode);
    max_size = (d * (d/2+1) * 3) + ((d/2+1) + 1);
    bool m1, m2;
    char *string = malloc(max_size);
    for (int i = 0; i < d; i += 2) {
        for (int j = 0; j < d; j++) {
            m1 = qrcode->modules[i][j];
            if (i+1 < d) {
                m2 = qrcode->modules[i+1][j];
            } else {
                m2 = false;
            }

            if (m1 && m2)   offset += sprintf(&string[offset], CH_FULL_BLOCK);
            if (m1 && !m2)  offset += sprintf(&string[offset], CH_UPPER_HALF_BLOCK);
            if (!m1 && m2)  offset += sprintf(&string[offset], CH_LOWER_HALF_BLOCK);
            if (!m1 && !m2) offset += sprintf(&string[offset], " ");
        }
        offset += sprintf(&string[offset], "\n");
    }
    string[offset] = '\0';
    return string;
}

char **QRCode_to_string_lines(QRCode *qrcode) {
    int offset, max_line_size, d;
    d = QRCode_get_dimention(qrcode);
    max_line_size = (d * 3) + 2;
    bool m1, m2;
    char *line, **lines = malloc((d/2+1) * sizeof(char*));
    for (int i = 0; i < d; i += 2) {
        line = malloc(max_line_size);
        offset = 0;
        for (int j = 0; j < d; j++) {
            m1 = qrcode->modules[i][j];
            if (i+1 < d) {
                m2 = qrcode->modules[i+1][j];
            } else {
                m2 = false;
            }

            if (m1 && m2)   offset += sprintf(&line[offset], CH_FULL_BLOCK);
            if (m1 && !m2)  offset += sprintf(&line[offset], CH_UPPER_HALF_BLOCK);
            if (!m1 && m2)  offset += sprintf(&line[offset], CH_LOWER_HALF_BLOCK);
            if (!m1 && !m2) offset += sprintf(&line[offset], " ");
        }
        line[offset] = '\0';
        lines[i/2] = line;
    }
    return lines;
}

void QRCode_free(QRCode *qrcode) {
    int d = QRCode_get_dimention(qrcode);
    for (int i = 0; i < d; i++) {
        free(qrcode->modules[i]);
    }
    free(qrcode->modules);
    free(qrcode);
}

