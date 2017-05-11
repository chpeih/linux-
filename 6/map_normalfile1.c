#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
typedef struct{
		char name[4];
		int age;
}people;

int main(int argc, char **argv)
{
	int fd,i;
	people *p_map;
	char temp;
	fd = open(argv[1], O_CREAT|O_RDWR|O_TRUNC,00777);
	lseek(fd, sizeof(people)*5-1,SEEK_SET);
	write(fd, "", 1);
	p_map = (people*)mmap(NULL, sizeof(people)*10,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	temp = 'a';
	for(i = 0;i<10;i++)
	{
		temp+=1;
		memcpy((*(p_map+i)).name, &temp, 2);
		(*(p_map+i)).age = 20 + i;
	}
	printf("initializeover\n");
	sleep(5);
	printf("sleep5 change p_map[0].name=tes\n");
	memcpy((*(p_map)).name, "ab",2);
	sleep(10);
	munmap(p_map, sizeof(people)*10);
	printf("umapok\n");
	return 0;
}
