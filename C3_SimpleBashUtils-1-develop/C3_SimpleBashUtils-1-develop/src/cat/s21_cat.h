#ifndef S21_CAT_H
#define S21_CAT_H
#include <getopt.h>
#include <stdio.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} opt;

opt options = {0};

void parser(int argc, char *argv[], opt *options);
void fileOpen(char *path, opt *options);
void fileRead(FILE *file, opt *options);

#endif