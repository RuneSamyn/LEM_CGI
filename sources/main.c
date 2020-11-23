#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXLEN 600
#define MAXINPUT 600

struct Persoon
{
  char Voornaam[25];
  char Naam[25];
  char Job[25];
  char Tel[15];
  long TimeStamp;
};

static void print_http_header(const char *content_type)
{
  printf("Content-Type: %s\n\n", content_type);
}

void unencode(char *src, char *last, char *dest)
{
  for (; src != last; src++, dest++)
    if (*src == '+')
      *dest = ' ';
    else if (*src == '%')
    {
      int code;
      if (sscanf(src + 1, "%2x", &code) != 1)
        code = '?';
      *dest = code;
      src += 2;
    }
    else
      *dest = *src;
  *dest = '\n';
  *++dest = '\0';
}

int printFile(FILE *f)
{
  int c;
  if (f != NULL)
  {
    while ((c = getc(f)) != EOF)
      printf("%c", c);
    fclose(f);
  }
}

char *findInString(char in[600], char name[10])
{
  char s[30];
  snprintf(s, 30,"name=\"%s\"", name); // name="voornaam" => search after this kind of string
  char e[10] = "\r\n------";
  // Extract the first substring
  char *subString; 
  subString = strtok(in, e);
  // loop through the string to extract all substrings
  int nextIsAnser = 0;
  while( subString != NULL ) {
    if(nextIsAnser == 1) {
      return (char*)subString;
      nextIsAnser = 0;
    }
    if(strstr(subString, s) != NULL) {
      nextIsAnser = 1;
    }
    subString = strtok(NULL, e);
  }
  return NULL;
}

int post_handler()
{
  char *lenstr;
  long len;
  lenstr = getenv("CONTENT_LENGTH");
  if (lenstr == NULL || sscanf(lenstr, "%ld", &len) != 1 || MAXLEN > 1000)
  {
    printf("<P>No post request.</p>");
    return 0;
  }
  char input[len];
  int i = 0;
  while (i <= len)    // read the post data
    input[i++] = getc(stdin);
  struct Persoon p;
  // strcpy(p.Voornaam, "Rune");
  // printf(p.Voornaam);
  char *cpy = strdup(input);
  strcpy(p.Voornaam, findInString(cpy, (char*)"voornaam"));
  cpy = strdup(input);
  strcpy(p.Naam, findInString(cpy, (char*)"naam"));
  cpy = strdup(input);
  strcpy(p.Job, findInString(cpy, (char*)"job"));
  cpy = strdup(input);
  strcpy(p.Tel, findInString(cpy, (char*)"tel"));
  p.TimeStamp = (int)time(NULL);
  printf("<P>Thank you! Your contribution has been stored.");
  return 0;
}

int main()
{
  print_http_header("text/html");
  FILE *html = fopen("/usr/lib/cgi-bin/index.html", "r");
  printFile(html);
  post_handler();
  // char input[600] = "hallo name=\"voornaam\"\r\n\r\nRune\r\n-----------";
  // char naam[10] = "voornaam";
  // findInString(input, naam);
  
  FILE *f = fopen("/var/www/html/test.json", "a");
  if(f == NULL)
      printf("<P>Sorry, cannot store your data.");
  else
    fputs("hello world", f);
    printf("hello world");
  fclose(f);
  return 0;
}