#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXLEN 600

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

struct Persoon stringToPersoon(char *input) {
  struct Persoon p;
  char *cpy = strdup(input);
  strcpy(p.Voornaam, findInString(cpy, (char*)"voornaam"));
  cpy = strdup(input);
  strcpy(p.Naam, findInString(cpy, (char*)"naam"));
  cpy = strdup(input);
  strcpy(p.Job, findInString(cpy, (char*)"job"));
  cpy = strdup(input);
  strcpy(p.Tel, findInString(cpy, (char*)"tel"));
  p.TimeStamp = (int)time(NULL);
  return p;
}

int post_handler()
{
  char *lenstr;
  long len;
  lenstr = getenv("CONTENT_LENGTH");
  if (lenstr == NULL || sscanf(lenstr, "%ld", &len) != 1 || MAXLEN > len)
  {
    return 0;
  }
  char input[len];
  int i = 0;
  while (i <= len)    // read the post data
    input[i++] = getc(stdin);
  struct Persoon p = stringToPersoon(input);
  FILE *f1 = fopen("/var/www/html/personsList.json", "r");
  FILE *f2 = fopen("/var/www/html/personsList.json.temp", "w");
  if(f1 == NULL || f2 == NULL)
    return 0;
  else {
    int c;
    while ((c = getc(f1)) != EOF){  //copy file and add new person at end of list
      if(c != ']') {
        putc(c, f2);
      } else {
        // write person to file
        char text[170];
        snprintf(text, 170,",\r\n    {\r\n\t\"voornaam\": \"%s\",\r\n\t\"naam\": \"%s\",\r\n\t\"job\": \"%s\",\r\n\t\"tel\": \"%s\",\r\n\t\"time\": %ld\r\n    }]\r\n", p.Voornaam, p.Naam, p.Job, p.Tel, p.TimeStamp);
        fputs(text, f2);
        break;
      }
    }
  }
  fclose(f1);
  fclose(f2);
  if(remove("/var/www/html/personsList.json") != 0) {
    printf("<P>Error deleting file.");
  }
  if(rename("/var/www/html/personsList.json.temp", "/var/www/html/personsList.json") != 0) {
    printf("<P>Error renaming file.");
  }
  return 0;
}

int main()
{
  print_http_header("text/html");
  post_handler();
  FILE *html = fopen("/usr/lib/cgi-bin/index.html", "r");
  printFile(html);
  return 0;
}