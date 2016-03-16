#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>

#include <time.h>

#define SHOWHOST

void showtime(time_t);
void show_info(struct utmp*);

int count = 0;

int main()
{

struct utmp *utbufp, *utmp_next();

if(utmp_open(UTMP_FILE) == -1 ){
perror(UTMP_FILE);
exit(1);
}

while((utbufp=utmp_next()) != ((struct utmp*) NULL))
{
show_info(utbufp);
count++;
}

utmp_close();
printf("%d", count);
printf("\n");
return 0;

}

void show_info(struct utmp *utbufp)
{

if(utbufp->ut_type != USER_PROCESS)
return;

printf("%-8.8s", utbufp->ut_name);
printf(" ");

printf("%-8.8s", utbufp->ut_line);
printf(" ");

showtime(utbufp->ut_time);

#ifdef SHOWHOST
if(utbufp->ut_host[0] != '\0')
printf("(%s)", utbufp->ut_host);
#endif
printf("\n");
}

void showtime(time_t timeval)
{
char *ctime();
char *cp;

cp=ctime(&timeval);

printf("%12.12s", cp+4);

}

