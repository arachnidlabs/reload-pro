/* ANSI-C code produced by gperf version 3.0.3 */
/* Command-line: gperf -m 100 tools/serial_keywords  */
/* Computed positions: -k'1' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "tools/serial_keywords"

typedef void (*command_func)(char *);

typedef struct command_def {
    const char *name;
    command_func handler;
} command_def;

void command_mode(char*);
void command_set(char *);
void command_reset(char *);
void command_read(char *);
void command_monitor(char *);
void command_debug(char *);
void command_calibrate(char *);
void command_bootloader(char *);
void command_dump(char *);
void command_version(char *);
void command_uvlo(char *);
void command_on(char *);
void command_off(char *);

#line 24 "tools/serial_keywords"
struct command_def;
#include <string.h>

#define TOTAL_KEYWORDS 13
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 7
#define MIN_HASH_VALUE 2
#define MAX_HASH_VALUE 14
/* maximum key range = 13, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
      15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
      15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
      15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
      15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
      15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
      15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
      15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
      15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
      15, 15, 15, 15, 15, 15, 15, 15, 12, 10,
       3, 15, 15, 15, 15, 15, 15, 15, 15,  2,
      15,  0, 15, 15,  0,  9, 15,  7,  3, 15,
      15, 15, 15, 15, 15, 15, 15, 15
    };
  return len + asso_values[(unsigned char)str[0]];
}

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct command_def *
in_word_set (register const char *str, register unsigned int len)
{
  static const struct command_def wordlist[] =
    {
#line 43 "tools/serial_keywords"
      {"on",command_on},
#line 44 "tools/serial_keywords"
      {"off",command_off},
#line 35 "tools/serial_keywords"
      {"read",command_read},
#line 34 "tools/serial_keywords"
      {"reset",command_reset},
#line 32 "tools/serial_keywords"
      {"mode",command_mode},
#line 40 "tools/serial_keywords"
      {"dump",command_dump},
#line 37 "tools/serial_keywords"
      {"debug",command_debug},
#line 36 "tools/serial_keywords"
      {"monitor",command_monitor},
#line 41 "tools/serial_keywords"
      {"version",command_version},
#line 42 "tools/serial_keywords"
      {"uvlo",command_uvlo},
#line 33 "tools/serial_keywords"
      {"set",command_set},
#line 38 "tools/serial_keywords"
      {"cal",command_calibrate},
#line 39 "tools/serial_keywords"
      {"bl",command_bootloader}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          register const struct command_def *resword;

          switch (key - 2)
            {
              case 0:
                resword = &wordlist[0];
                goto compare;
              case 1:
                resword = &wordlist[1];
                goto compare;
              case 2:
                resword = &wordlist[2];
                goto compare;
              case 3:
                resword = &wordlist[3];
                goto compare;
              case 4:
                resword = &wordlist[4];
                goto compare;
              case 5:
                resword = &wordlist[5];
                goto compare;
              case 6:
                resword = &wordlist[6];
                goto compare;
              case 7:
                resword = &wordlist[7];
                goto compare;
              case 8:
                resword = &wordlist[8];
                goto compare;
              case 9:
                resword = &wordlist[9];
                goto compare;
              case 10:
                resword = &wordlist[10];
                goto compare;
              case 11:
                resword = &wordlist[11];
                goto compare;
              case 12:
                resword = &wordlist[12];
                goto compare;
            }
          return 0;
        compare:
          {
            register const char *s = resword->name;

            if (*str == *s && !strcmp (str + 1, s + 1))
              return resword;
          }
        }
    }
  return 0;
}
