#include "s21_cat.h"

int main(int argc, char *argv[]) {
  parser(argc, argv, &options);
  for (int i = optind; i < argc; i++) fileOpen(argv[i], &options);
  return 0;
}

void parser(int argc, char *argv[], opt *options) {
  int optionIndex = 0;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {"number", 0, 0, 'n'},
                                         {0, 0, 0, 0}};

  const char *optstring = "+benstvTE";
  int opt;
  while ((opt = getopt_long(argc, argv, optstring, long_options,
                            &optionIndex)) != -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      default:
        fprintf(stderr, "Usage: cat [OPTION]... [FILE]...\n");
        break;
    }
  }
  if (options->b) options->n = 0;
}

void fileOpen(char *path, opt *options) {
  FILE *file = fopen(path, "r");
  if (file == NULL)
    printf("cat: %s: No such file or directory", path);
  else
    fileRead(file, options);
  fclose(file);
}

void fileRead(FILE *file, opt *options) {
  int strCount = 0, emptyCount = 0, ch = 0, prev = 0;
  while ((ch = fgetc(file)) && ch != EOF) {
    if (!(options->s && ch == '\n' && prev == '\n' && emptyCount)) {
      if (ch == '\n' && prev == '\n')
        emptyCount = 1;
      else
        emptyCount = 0;

      if (options->e && options->b &&
          ((ch == '\n' && prev == '\n') || (strCount == 0 && ch == '\n')))
        printf("      \t");

      if (((options->b && prev == '\n') || (options->b && strCount == 0)) &&
          ch != '\n')
        printf("%6d\t", ++strCount);

      if ((options->n && prev == '\n') || (options->n && strCount == 0))
        printf("%6d\t", ++strCount);

      if (options->e && ch == '\n') printf("$");

      if (options->v) {
        if ((ch < 32) && ch != '\t' && ch != '\n') {
          printf("^");
          ch += 64;
        }
        if (ch == 127) {
          printf("^");
          ch = '?';
        }
        if ((ch >= 128 && ch <= 160) && ch != 10 && ch != 9) {
          printf("M-");
          ch -= 64;
        }
      }

      if (options->t && ch == '\t') {
        printf("^");
        ch = 'I';
      }
      fputc(ch, stdout);
    }
    prev = ch;
  }
}
