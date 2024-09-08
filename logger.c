#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

void logw(FILE *fp, const char *format, ...)
{

    struct timeval tv;
    gettimeofday(&tv, NULL);

    char buffer[1024] = {0};
    struct tm *lt;
    time_t now = tv.tv_sec;
    lt = localtime(&now);
    char tstr[26] = {0};
    strftime(tstr, sizeof(tstr) - 1, "%Y-%m-%d %H:%M:%S", lt);
    snprintf(buffer, sizeof(buffer), "[%s.%03ld] ", tstr, tv.tv_usec / 1000);

    va_list ap;
    va_start(ap, format);
    int len = strlen(buffer);
    vsnprintf(buffer + len, sizeof(buffer) - len, format, ap);
    va_end(ap);

    fprintf(fp, "%s\n", buffer);

}

int main(void)
{
    FILE *fp = fopen("TMP.LOG", "w");
    logw(fp, "This is %s log! :%d", "REAL", 123);
    fclose(fp);
    return 0;
}
