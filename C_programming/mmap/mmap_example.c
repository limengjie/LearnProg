#include <stdio.h>
#include <stdlib.h>		//exit()
//#include <sys/types.h>
#include <sys/stat.h> 		//stat struct
#include <fcntl.h>		//open()
#include <unistd.h>		//close()
#include <sys/mman.h>		//mmap()
#include <string.h>		//strncpy()


/*
mmap is a method of memory-mapped file I/O. It creates a new mapping in the virtual address space of the calling process. 

After the mmap() call has returned, the file descriptor, fd, can be
       closed immediately without invalidating the mapping.

The mmap is used for a easy file access interface. It makes the file like a large string.
*/

int main(int argc, char * argv[]) 
{
	int fd;
	struct stat mystat; 	//store file info, such as file size
	void *pmap;

	//open file
	fd = open("test.txt", O_RDWR);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}

	//get file info(fstat)
	if(fstat(fd, &mystat) < 0)
	{
		perror("fstat");
		close(fd);
		exit(1);
	}
	
	//void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
	//addr:The starting address for the new mapping is specified in addr. If addr is NULL, then the kernel chooses the address. 
	//len:The length argument specifies the length of the mapping (which must be greater than 0).
	//prot:The prot argument describes the desired memory protection of the mapping
	//flags:The flags argument determines whether updates to the mapping are visible to other processes mapping the same region
	//fd:file descriptor
	//offset:the offset of the file. (Where start copying the file)
	pmap = mmap(NULL, mystat.st_size, PROT_READ | PROT_WRITE,
		MAP_SHARED, fd, 0);

	if(pmap == MAP_FAILED)
	{
		perror("mmap");
		close(fd);
		exit(1);
	}

	strncpy(pmap, "Hello", 5);

	close(fd);

	return 0;
}
