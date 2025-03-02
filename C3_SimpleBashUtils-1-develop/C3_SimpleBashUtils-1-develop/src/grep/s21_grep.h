#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int err;
  int argc;
} opt;

opt options = {0};

void obrabotkaflagov(int argc, char *argv[], opt *options, char *pattern);
void regCompile(char *argv[], opt *options, char *pattern);
void primenenieflagov(opt *options, FILE *file, regex_t reg, char *path);
void addPattern(char *pattern, char *str);
void primenenieflagaF(opt *options, char *path, char *pattern);
void primenenieflagaO(regex_t reg, opt *options, char *line, char *path,
                      int total_lines);

#endif
