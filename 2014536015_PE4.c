#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

#define PATH_MAX 1024
char newpath[PATH_MAX];

void oops(char *s1,char *s2);

void main(int ac, char* av[]){

if(ac!=3){
printf("incorrect args\n");
exit(1);
}

//filename, filename
if(isadir(av[1])==0 && isadir(av[2])==0){
change_file_name(av[1],av[2]); 
}
//filename, dir
else if( isadir(av[1])==0 && isadir(av[2])==1 ){
copy_file_to_dir(av[1], av[2]);
}
//dir, dir move
else {
sprintf(newpath, "cp -r %s %s", av[1],av[2]);
system(newpath);
sprintf(newpath, "rm -rf %s", av[1]);
system(newpath);
}

}//end main

//
void change_file_name(char* old_name, char* new_name){
if(link(old_name,new_name) != -1){
unlink(old_name);
}
}

//
void copy_file_to_dir(char* file_name, char* new_dir){
int in_fd,out_fd,n_chars;
char buf[BUFFERSIZE];
/* open files */
    if((in_fd=open(file_name,O_RDONLY)) == -1){
        oops("Cannot open",file_name);
}

sprintf(newpath, "%s/%s", new_dir, file_name);//path
if((out_fd=creat(newpath, COPYMODE)) == -1){
oops("Cannot creat", newpath);
}

/* copy files */
    while((n_chars = read(in_fd,buf,BUFFERSIZE))>0)
             if(write(out_fd,buf,n_chars) != n_chars)
                       oops("write error to",new_dir);
             if(n_chars == -1)
                       oops("read error from",file_name);
/* close files */
             if(close(in_fd) == -1 || close(out_fd) == -1)
                       oops("error closing file","");
unlink(file_name);//old file del
}

//
isadir(char* name){
struct stat info;
return(stat(name,&info) != -1 && (info.st_mode &S_IFMT) == S_IFDIR);
}

//
void oops(char *s1,char *s2)
{
    fprintf(stderr,"error:%s",s1);
    perror(s2);
    exit(1);
}
//
