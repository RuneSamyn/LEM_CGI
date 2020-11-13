#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Print a basic HTTP header. */

static void
print_http_header (const char * content_type)
{
    printf ("Content-Type: %s\n\n", content_type);
}

static void
include_stylesheet (const char * filePath)
{
    printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"%s\">\n", filePath);
}

static void
include_script (const char * filePath)
{
    printf("<script src=\"%s\"></script>\n", filePath);
}

int 
main ()
{
    int i;
    print_http_header ("text/html");
    include_stylesheet("https://getbootstrap.com/docs/4.0/dist/css/bootstrap.min.css");
    include_script("https://code.jquery.com/jquery-3.2.1.slim.min.js");
    include_script("https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js");
    include_script("https://getbootstrap.com/docs/4.0/dist/css/bootstrap.min.js");
    printf("<h1>Environment variables</h1>\n");
    printf("<div class=\"container\">\n");
    printf("<table class=\"table\">\n");
    printf("<thead><tr>\n");
    printf("<th scope=\"col\">#</th>\n");
    printf("<th scope=\"col\">Voornaam</th>\n");
    printf("<th scope=\"col\">Naam</th>\n");
    printf("<th scope=\"col\">Job</th>\n");
    printf("<th scope=\"col\">tel nr</th>\n");
    printf("</tr></thead>\n");
    for (i = 0; i <5; i++) {
        printf("<th scope=\"row\">%d</th>\n", i);
        printf ("<td></td>\n");
        printf ("<td></td>\n");
        printf ("<td></td>\n");
        printf ("<td></td><tr>\n");
    }
    printf ("</table>");
    printf("</div>");
    return 0;
}