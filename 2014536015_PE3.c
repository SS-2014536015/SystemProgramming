#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<dirent.h>

ino_t	get_inode();

int count=0;
int count2=0;
int count3=0;

int par_inode;

char temp[][50];

int main()
{
	printpathto();	
	putchar('\n');				
	return 0;
}

printpathto()
{
while(count == 0){
	
	ino_t this_inode = get_inode( "." );
	char its_name[BUFSIZ];

	chdir( ".." );					

	inum_to_name( this_inode , its_name );		

	par_inode = get_inode( "." );			

	if ( par_inode == get_inode( ".." ) ){		
	count=1;
	}

	
	strcpy(temp[count2], its_name);

	count2++;
	count3++;
}//end while
count2=count2-1;
count3=count3-1;
int i;
for(i=0; i<=count2; i++){
printf("/%s", temp[count3] );
count3--;
}


}

inum_to_name(ino_t inode_to_find , char *namebuf)
{
	DIR		*dir_ptr;		
	struct dirent	*direntp;		

	dir_ptr = opendir( "." );
	if ( dir_ptr == NULL ){
		fprintf(stderr, "cannot open a directory\n");
		exit(1);
	}

	

	while ( ( direntp = readdir( dir_ptr ) ) != NULL )
		if ( direntp->d_ino == inode_to_find )
		{
			strcpy( namebuf, direntp->d_name );
			closedir( dir_ptr );
			return 0;
		}
	fprintf(stderr, "error looking for inum %d\n", inode_to_find);
	exit(1);
}

ino_t
get_inode( char *fname )
{
	struct stat info;

	if ( stat( fname , &info ) == -1 ){
		fprintf(stderr, "Cannot stat ");
		perror(fname);
		exit(1);
	}
	return info.st_ino;
}
