#include <stdio.h>
#include <signal.h>

void f(int signum){
char inputdata; 
printf("Interrupted! OK to quit (y/n)?"); 
scanf("%s", &inputdata);

if (inputdata == 'y')
exit(1);

}


main(){	
	void f(int); 
	int i;	
	signal(SIGINT,f);	
	for (i=0;i<10;i++){
		printf("Hello\n");
		sleep(1);
	}
}

