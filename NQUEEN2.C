#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#define SIZEN 14
#define SIZE 40


int graph(){
   int row,col;
   int i,j,f=1,h=50;
   int a,b=1,c,d=50,r1=0,c1=0;


   for(i=1;i<=SIZEN;i++)
   {
	a=1;
	c=50;

	for(j=1;j<=SIZEN;j++)
	{
		if((abs(r1-c1))%2!=0)
		{
		rectangle(a,b,c,d);
		a=c;
		c=c+50;

		}
		else
		{
		bar(a,b,c,d);
		a=c;
		c=c+50;

		}
		c1++;
	}
	f=f+50;
	b=f;
	h=h+50;
	d=h;
	r1++;
   }

   return 1;
}
struct giri
{
	int top;
	int arr[SIZE];
};

int myisEmpty(struct giri *s)
{
	if(s->top==-1)
		return 1;
	else
		return 0;
}
int myisFull(struct giri *s)
{
	if(s->top==SIZE-1)
		return 1;
	else
		return 0;
}
int myPush(struct giri *s,int var)
{
	if(myisFull(s)==1)
		return 0;
	else
		s->top=s->top+1;
		s->arr[s->top]=var;
		return 1;
}
int myPop(struct giri *s,int *var)
{
	if(myisEmpty(s)==1)
		return 0;
	else
	{
		*var=s->arr[s->top];
		s->top=s->top-1;
		return 1;
	}
}
int myPeek(struct giri *s,int *var)
{
	if(myisEmpty(s)==1)
		return 0;
	else
		{
		*var=s->arr[s->top];
		return 1;
		}
}

int isrowcolumnsafe(int r1,int c1,struct giri *s1)
{
	struct giri s2;
	int a[SIZEN][SIZEN]={0};
	int r2,c2,flag;
	s2.top=-1;
	if(r1==0 && r2==0 && a[r1][r2]==0)
	{
		return 1;
	}
	while(!myisEmpty(s1))
	{
		myPop(s1,&c2);
		myPop(s1,&r2);
		myPush(&s2,c2);
		myPush(&s2,r2);
		if(r1==r2 || c1==c2|| abs(r1-r2)==abs(c1-c2) || a[r1][c1]!=0)
		{
			flag=0;
			break;
		}
	}
	if(r1!=r2 && c1!=c2 && abs(r1-r2)!=abs(c1-c2) && a[r1][c1]==0)
	{
		flag=1;
	}
	while(!myisEmpty(&s2))
	{
		myPop(&s2,&r2);
		myPop(&s2,&c2);
		myPush(s1,r2);
		myPush(s1,c2);
	}
	return flag;


}

int stackrev(struct giri *s1)
{
	int i;
	if(myisEmpty(s1))
		return 1;
	myPop(s1,&i);
	stackrev(s1);
	insert(s1,i);
	return 1;
}

int insert(struct giri *s1,int i)
{
	int j;
	if(myisEmpty(s1))
	{
		myPush(s1,i);
		return 1;
	}
	myPop(s1,&j);
	insert(s1,i);
	myPush(s1,j);
	return 1;
}



void main()
{
	int gd = DETECT,gm;
	struct giri s1;
	int r1=0,c1=0,r,a[SIZEN][SIZEN],x=25,y=25,z=50; char row[10],col[10];
	int m=500,n=25;
	s1.top=-1;
	clrscr();

	initgraph(&gd,&gm,"c:\\turboc3\\BGI");
	while(r1<SIZEN && c1<SIZEN)
	{
		r=isrowcolumnsafe(r1,c1,&s1);
		if(r)
		{
			a[r1][c1]=1;
			myPush(&s1,r1);
			myPush(&s1,c1);
			r1++;
			c1=0;
		}
		else
			c1++;

		while(c1>=SIZEN)
		{
			myPop(&s1,&c1);
			myPop(&s1,&r1);
			a[r1][c1]=0;

			c1++;

		}


	}

	graph();

	stackrev(&s1);
	while(!myisEmpty(&s1))
	{
		myPop(&s1,&c1);
		myPop(&s1,&r1);
		x=x+(z*r1);
		y=y+(z*c1);
		sprintf(row,"%d",r1);
		sprintf(col,"%d",c1);
		setcolor(GREEN);
		outtextxy(m,n,col);
		outtextxy(m+25,n,row);
		if((abs(r1-c1))%2!=0)
			setcolor(WHITE);
		else
		{
			setcolor(BLACK);
		}
		outtextxy(x,y,"Q");
		n=n+25;
		x=25;
		y=25;
	}
	getch();
	closegraph();
}