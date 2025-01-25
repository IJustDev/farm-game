#ifndef DIALOG_H
#define DIALOG_H

int has_dialog();

void close_dialog();

void show_dialog(const char* msg);
char* get_dialog();

#endif