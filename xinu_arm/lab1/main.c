/*  main.c  - main */

#include <xinu.h>
/*
struct Item{
	int prio;
	char value;
};*/

void pr(char* val){
	int i = 0;
	while(i < 1000){
		printf("%s", val);
		i++;
	}
}

process	main(void)
{
	pid32	shpid;		/* Shell process ID */

	printf("\n\n");

	/* Create a local file system on the RAM disk */

	lfscreate(RAM0, 40, 20480);

	kprintf("Hello there this is Eliel Vipata\n");
	resume(create(pr, 8192, 10, "myproc1",1,"A"));
	resume(create(pr, 8192, 10, "myproc2",1,"B"));
	resume(create(pr, 8192, 10, "myproc3",1,"C"));

	// For step 8: My guess is the functions processes will run in their order of creation.
	// A wil be printed 1000 times, then B, then C

	sleep(4);
	kprintf("\n\n");
	/* Run the Xinu shell */

	recvclr();
	resume(shpid = create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
	    if (receive() == shpid) {
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(shpid = create(shell, 4096, 20, "shell", 1, CONSOLE));
	    }
	}
	return OK;
}
