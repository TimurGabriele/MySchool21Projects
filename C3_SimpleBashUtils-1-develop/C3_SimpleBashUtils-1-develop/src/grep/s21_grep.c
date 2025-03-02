#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char pattern[BUFFER_SIZE] = {0};
  obrabotkaflagov(argc, argv, &options, pattern);
  regCompile(argv, &options, pattern);
  return 0;
}

void obrabotkaflagov(int argc, char *argv[], opt *options, char *pattern) {
  int opt;
  const char *optstring = "e:ivclnhsf:o";
  while ((opt = getopt(argc, argv, optstring)) != -1) {
    switch (opt) {
      case 'e':
        options->e = 1;
        addPattern(pattern, optarg);
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        primenenieflagaF(options, optarg, pattern);
        break;
      case 'o':
        options->o = 1;
        break;
      default:
        if (!options->s) {
          fprintf(stderr,
                  "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep "
                  "--help' for more information.\n");
          options->err++;
        }
        break;
    }
  }
  if (!options->e && !options->f && !options->e)
    addPattern(pattern, argv[optind++]);
  options->argc = argc;
}

void regCompile(char *argv[], opt *options, char *pattern) {
  if (pattern[strlen(pattern) - 1] == '|') pattern[strlen(pattern) - 1] = '\0';
  for (int i = optind; i < options->argc; i++) {
    FILE *file = NULL;
    regex_t reg;
    file = fopen(argv[i], "r");

    if (file != NULL) {
      regcomp(&reg, pattern, options->i ? REG_ICASE : REG_EXTENDED);
      primenenieflagov(options, file, reg, argv[i]);
      regfree(&reg);
      fclose(file);
    } else if (!options->err && !options->s)
      fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
  }
}

void primenenieflagov(opt *options, FILE *file, regex_t reg, char *path) {
  char file_string[BUFFER_SIZE] = {0};
  int total_lines = 0, match_lines = 0;
  regmatch_t reg_match[1];
  while (fgets(file_string, BUFFER_SIZE - 1, file) != NULL) {
    total_lines++;
    if (strchr(file_string, '\n') == NULL) strcat(file_string, "\n");
    int match = regexec(&reg, file_string, 1, reg_match, 0);
    if (match == options->v) match_lines++;
    if (!options->l && !options->c && !options->o) {
      if (!options->h && match == options->v && options->argc - optind > 1)
        printf("%s:", path);
      if (options->n && match == options->v) printf("%d:", total_lines);
      if (match == options->v) printf("%s", file_string);
    }
    if (!match && options->o && !options->l && !options->c)
      primenenieflagaO(reg, options, file_string, path, total_lines);
  }
  if (options->c && !options->l) {
    if (!options->h && options->argc - optind > 1) printf("%s:", path);
    printf("%d\n", match_lines);
  }
  if (options->l && match_lines) printf("%s\n", path);
}

void primenenieflagaF(opt *options, char *path, char *pattern) {
  char line[BUFFER_SIZE] = {0};
  FILE *file = NULL;
  file = fopen(path, "r");
  if (file != NULL) {
    while (fgets(line, BUFFER_SIZE - 1, file) != NULL) {
      addPattern(pattern, line);
    }
    fclose(file);
  } else if (!options->s)
    fprintf(stderr, "grep: %s: No such file or directory\n", path);
}

void addPattern(char *pattern, char *str) {
  int len = strlen(str);
  strncat(pattern, str, len);
  strcat(pattern, "|");
}

void primenenieflagaO(regex_t reg, opt *options, char *line, char *path,
                      int total_lines) {
  while (regexec(&reg, line, 0, NULL, 0) == options->v) {
    char *regular = (char *)calloc(strlen(line) + 1, 1);
    strcpy(regular, line);
    int end = strlen(line);
    while (regexec(&reg, regular, 0, NULL, 0) == options->v) {
      end--;
      regular[strlen(regular) - 1] = 0;
    }
    regular[strlen(regular)] = line[strlen(regular)];
    int start = 0;
    while (regexec(&reg, regular, 0, NULL, 0) == options->v &&
           strlen(regular) > 0) {
      start++;
      int j = 0;
      while (regular[j] != 0) {
        regular[j] = regular[j + 1];
        j++;
      }
    }
    start--;
    int i = strlen(regular);
    while (i != 0) {
      regular[i] = regular[i - 1];
      i--;
    }
    regular[0] = line[start];
    if ((options->argc - optind > 1 && options->n && !options->h) ||
        (options->argc - optind > 1 && !options->h))
      printf("%s:", path);
    if (options->n) printf("%d:", total_lines);
    printf("%s\n", regular);
    free(regular);
    i = start + 1;
    while (line[i] != 0) {
      line[i - start - 1] = line[i];
      i++;
    }
    line[i - start - 1] = 0;
  }
}
