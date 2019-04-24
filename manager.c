/* 	OPERATING SYSTEMS  LAB PROJECT
*	AKASH JAIN
*	179303013
*	DESIGNING A VIRTUAL MEMORY MANAGER
*/	


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int VM_SIZE=256;
const int PAGE_SIZE=256;
const int TLB_SIZE=16;
const int MM_SIZE=256;

int main(int argc, char* argv[])
{
	FILE *fd;
	
	if(argc<2)
	{
		printf("NOT ENOUGH AGRUMENTS\n EXITING\n");
		return 0;
	}
	fd=fopen(argv[1],"r");
	if(fd==NULL)
	{
		printf("ERROR OPENING FILE\n FILE FAILED TO OPEN\n");
		return 0;
	}
	char *value=NULL;
	size_t len=0;
	ssize_t read;
	long long page_no,offset,page_table,totalhits=0,fault=0,pages=0;
	
	int qp=0;						//to maintain the queue position
	int physicalad=0,frame,logicalad;
	
	int tlb[TLB_SIZE][2];
	int pagetable[PAGE_SIZE];

	memset(tlb,-1,TLB_SIZE*2*sizeof(tlb[0][0]));
	memset(pagetable,-1,sizeof(pagetable));
	
	int mask=255,mask1=62580,i,hit;
	
	while((read=getline(&value,&len,fd))!=-1)
	{
		pages++;
		//get page number and offset from logical address
		page_no=atoi(value);
		page_no=page_no>>8;
		page_no=page_no & mask;
		
		offset=atoi(value);
		offset=offset & mask;
		
		logicalad=atoi(value);
		//printf("%lld %lld\n",page_no,offset);
		frame=0,physicalad=0;
		
		hit=0;			//1 if found in TLB
		
		//CHECK IN TLB
		
		for(i=0;i<TLB_SIZE;i++)
		{
			if(tlb[i][0]==page_no)
			{
				hit=1;
				totalhits++;
				frame=tlb[i][1];
				break;
			}
		}
		//if present in tlb
		if(hit==1)
			printf("TLB HIT\n");
		
		//search in pagetable
		else
		{
			
			int f=0;
			for(i=0;i<PAGE_SIZE;i++)
			{
				if(pagetable[i]==page_no)
				{
					frame=i;
					fault++;
					break;
				}
				if(pagetable[i]==-1)
				{
					f=1;
					
					break;
				}
			}
			if(f==1)
			{
				pagetable[i]=page_no;
				frame=i;
			}
			//replace in tlb using fifo
			tlb[qp][0]=page_no;
			tlb[qp][1]=i;
			qp++;
			qp=qp%15;		
		}
		if(logicalad<10000)
		printf("VIRTUAL ADDRESS = %d \t\t\t",logicalad);
		else
		printf("VIRTUAL ADDRESS = %d \t\t",logicalad);
		
		physicalad=frame*PAGE_SIZE + offset;
		printf("PHYSICAL ADDRESS = %d\n",physicalad);
	}
	double hitrate=(double)totalhits/pages*100;
	double faultrate=(double)fault/pages*100;
	printf("\nTLB HIT RATE= %.2f %c", hitrate,'%');
	printf("\nTLB MISS RATE= %.2f %c",(100-hitrate),'%');
	printf("\nPAGE TABLE HIT RATE= %.2f %c", faultrate,'%');
	printf("\nPAGE TABLE MISS RATE= %.2f %c\n", (100-faultrate),'%');
}
