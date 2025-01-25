#include "dialog.h"
#include <string.h>

int dialog = 0;

char* content[1024];

int has_dialog() {
    return dialog;
}

void close_dialog() {
    dialog = 0;
}

void show_dialog(const char* msg) {
    strcpy(content, msg);
    dialog = 1;
}

char* get_dialog() {
    return content;
}