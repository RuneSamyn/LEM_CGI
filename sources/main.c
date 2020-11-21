#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 80
#define EXTRA 5
/* 4 for field name "data", 1 for "=" */
#define MAXINPUT MAXLEN+EXTRA+2
/* 1 for added line break, 1 for trailing NUL */
#define DATAFILE "data.txt"


void 
unencode(char *src, char *last, char *dest)
{
 for(; src != last; src++, dest++)
   if(*src == '+')
     *dest = ' ';
   else if(*src == '%') {
     int code;
     if(sscanf(src+1, "%2x", &code) != 1) code = '?';
     *dest = code;
     src +=2; }     
   else
     *dest = *src;
 *dest = '\n';
 *++dest = '\0';
}

int
printFile(FILE *f) {
  int c;
  if(f != NULL) {
    while ((c = getc(f)) != EOF)
      printf("%c", c);
    fclose(f);
  }
}

int 
main ()
{
    printf("Content-type: text/html\n\n");
    FILE *html = fopen("/usr/lib/cgi-bin/index.html", "r");
    printFile(html);
    // char *lenstr;
    // char input[MAXINPUT], data[MAXINPUT];
    // long len;
    // lenstr = getenv("CONTENT_LENGTH");
    // if(lenstr == NULL || sscanf(lenstr,"%ld",&len)!=1 || len > MAXLEN)
    //     printf("<P>No post request.</p>");
    // else {
    //     FILE *f;
    //     fgets(input, len+1, stdin);
    //     unencode(input+EXTRA, input+len, data);
    //     f = fopen(DATAFILE, "a");
    //     if(f == NULL)
    //         printf("<P>Sorry, cannot store your data.");
    //     else
    //         fputs(data, f);
    //     fclose(f);
    //     printf("<P>Thank you! Your contribution has been stored.");
    // }
    return 0;
}