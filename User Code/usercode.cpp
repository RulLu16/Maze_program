#include <stdlib.h>
#include "..\ExternDoc.h"
#include "..\UI\Zoom.h"
#include "..\UI\MsgView.h"
#include "..\Graphics\DrawFunc.h"
#include "..\Example\Example.h"

#define ERROR_NUMBER -1

//function prototype

static void drawDirect(CDC *pDC);
static void drawBuffered();

void stack_push(int i, int j);
void stack_pop();
void que_push(int i, int j);
void que_pop();

void DFS();
void BFS();

typedef struct{
	int mark; // 0 means no visit
	int right;
	int down;
}maze;

maze** marray;
int height=0;
int width=0;

typedef struct _stack{
	int x;
	int y;
	_stack* link;
}stack;

stack* top;

typedef struct _que{
	int x;
	int y;
	_que* link;
}que;

que* start;
que* end;

typedef struct _path{
	int x;
	int y;
}path;

path** p;
//Start of user code
#include <float.h>

/*****************************************************************
* function	: bool readFile(const char* filename)
* argument	: cons char* filename - filename to be opened
* return	: true if success, otherwise flase
* remark	: After read data file, phisycal view must be set;
*			  otherwise drawing will not be executed correctly.
*			  The window will be invalidated after readFile()
*			  returns true.
******************************************************************/

bool readFile(const char* filename){
	
	//setWindow(0,0,20,20,1);
	char temp;
	int check;

	int i,j;
	//start of the user code
	FILE* fp=fopen(filename,"r");
	width=0;
	height=0;
	if(fp==NULL)
	{
		printf("There are No files!!\n");
		return false;
	}
	while (1)
	{
		check=fscanf(fp,"%c",&temp);
		if(check==EOF)
			break;
		else
		{
			if(temp=='\n')
				height++;
		}
		width++;
	}
	fclose(fp);
	width=width/height;
	width=width/2-1;
	height=height/2;

	marray=(maze**)malloc(sizeof(maze*)*height);
	for(i=0;i<height;i++)
		marray[i]=(maze*)malloc(sizeof(maze)*width);
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
			marray[i][j].right=marray[i][j].down=marray[i][j].mark=0; //0 mean there are walls.
	fp=fopen(filename,"r");
	while(1)
	{
		fscanf(fp,"%c",&temp);
			if(temp=='\n')
				break;
	}
	for(i=0;i<height*2-1;i++)
	{
		fscanf(fp,"%c",&temp);
		if(i%2==0)
		{
			for(j=0;j<width*2;j++)
			{
				if(j%2==0)
					fscanf(fp,"%c",&temp);
				else
				{
					fscanf(fp,"%c",&temp);
					if(temp==' ')
						marray[i/2][j/2].right=1;
				}
			}
		}
		else
		{
			for(j=0;j<width*2;j++)
			{
				if(j%2==0)
				{
					fscanf(fp,"%c",&temp);
					if(temp==' ')
						marray[i/2][j/2].down=1;
				}
				else
					fscanf(fp,"%c",&temp);
			}
		}
		fscanf(fp,"%c",&temp);
	}
	fclose(fp);

	setWindow(0,0,width*2,height*2,1);

	return true; //edit after finish this function
	//end of usercode
	
	return true; //edit after finish this function
	//end of usercode
}

/******************************************************************
* function	: bool FreeMemory()
*
* remark	: Save user data to a file
*******************************************************************/
void freeMemory(){
	//start of the user code
	//end of usercode
	int i;
	for(i=0;i<height;i++)
		free(marray[i]);
	free(marray);
}

/**************************************************************
* function	: bool writeFile(const char* filename)
*
* argument	: const char* filename - filename to be written
* return	: true if success, otherwise false
* remark	: Save user data to a file
****************************************************************/
bool writeFile(const char* filename){
	//start of the user code
	bool flag;
	flag = 0;

	return flag;
	//end of usercode
}

/************************************************************************
* fucntion	: void drawMain(CDC* pDC)
*
* argument	: CDC* pDC - device context object pointer
* remark	: Main drawing function. Called by CMFC_MainView::OnDraw()
*************************************************************************/
void drawMain(CDC *pDC){
	//if direct drawing is defined
#if defined(GRAPHICS_DIRECT)
	drawDirect(pDC);
	//if buffered drawing is defined
#elif defined(GRAPHICS_BUFFERED)
	drawBuffered();
#endif
}

/************************************************************************
* function	: static void drawDirect(CDC *pDC
*
* argument	: CDC* pDC - device context object pointer
* remark	: Direct drawing routines here.
*************************************************************************/
static void drawDirect(CDC *pDC){
	//begin of user code
	//Nothing to write currently.
	//end of user code
}

/***********************************************************************
* function	: static void drawBuffered()
*
* argument	: CDC* pDC -0 device object pointer
* remark	: Buffered drawing routines here.
************************************************************************/
static void drawBuffered(){
	//start of the user code
	//end of the user code
	int i,j;
	int x,y;
	x=0;
	y=0;
	for(i=0;i<width*2+1;i++)
	{
		DrawSolidBox_I(x,y,x+1,y+1,2,RGB(0,0,255), RGB(0,0,255));
		x++;
	}
	
	for(i=0;i<height*2-1;i++)
	{
		x=0;
		y++;
		DrawSolidBox_I(x,y,x+1,y+1,2,RGB(0,0,255), RGB(0,0,255));
		x++;
		if(i%2==0)
		{
			for(j=0;j<width;j++)
			{
				if(marray[i/2][j].right==0)
				{
					DrawSolidBox_I(x,y,x+1,y+1,2,RGB(255,255,255), RGB(255,255,255));
					x++;
					DrawSolidBox_I(x,y,x+1,y+1,2,RGB(0,0,255), RGB(0,0,255));
					x++;
				}
				else
				{
					DrawSolidBox_I(x,y,x+1,y+1,2,RGB(255,255,255), RGB(255,255,255));
					x++;
					DrawSolidBox_I(x,y,x+1,y+1,2,RGB(255,255,255), RGB(255,255,255));
					x++;
				}					
			}
		}
		else
		{
			for(j=0;j<width;j++)
			{
				if(marray[i/2][j].down==0)
				{
					DrawSolidBox_I(x,y,x+1,y+1,2,RGB(0,0,255), RGB(0,0,255));
					x++;
					DrawSolidBox_I(x,y,x+1,y+1,2,RGB(0,0,255), RGB(0,0,255));
					x++;
				}
				else
				{
					DrawSolidBox_I(x,y,x+1,y+1,2,RGB(255,255,255), RGB(255,255,255));
					x++;
					DrawSolidBox_I(x,y,x+1,y+1,2,RGB(0,0,255), RGB(0,0,255));
					x++;
				}
			}
		}
	}
	y++;
	x=0;
	for(i=0;i<width*2+1;i++)
	{
		DrawSolidBox_I(x,y,x+1,y+1,2,RGB(0,0,255), RGB(0,0,255));
		x++;
	} // draw maze
	
	
}

void DFS()
{
	drawBuffered();
	int finish_x=height-1;
	int finish_y=width-1;
	int i,j;
	int temp_x=0;
	int temp_y=0;
	int flag=0;
	top=(stack*)malloc(sizeof(stack));
	top->x=0;
	top->y=0;
	top->link=NULL;
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
			marray[i][j].mark=0;
	marray[0][0].mark=1;
	while(1)
	{
		if(top==NULL)
			break;
		temp_x=top->x;
		temp_y=top->y;
		if( marray[temp_x][temp_y].right==1 && marray[temp_x][temp_y+1].mark==0)
		{
			if(temp_x==finish_x && temp_y+1==finish_y)
			{
				flag=1;
				break;
			}
			marray[temp_x][temp_y+1].mark=1;
			stack_push(temp_x, temp_y+1);
			i=temp_x*2+1;
			j=temp_y*2+1;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			j++;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			
		} //check right
		else if(marray[temp_x][temp_y].down==1 && marray[temp_x+1][temp_y].mark==0)
		{
			if(temp_x+1==finish_x && temp_y==finish_y)
			{
				flag=1;
				break;
			}
			marray[temp_x+1][temp_y].mark=1;
			stack_push(temp_x+1,temp_y);
			i=temp_x*2+1;
			j=temp_y*2+1;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			i++;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			
		} //check down
		else if(temp_y>0 && marray[temp_x][temp_y-1].right==1 && marray[temp_x][temp_y-1].mark==0)
		{
			marray[temp_x][temp_y-1].mark=1;
			stack_push(temp_x,temp_y-1);
			i=temp_x*2+1;
			j=temp_y*2+1;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			j--;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			
		} //check left
		else if(temp_x>0 && marray[temp_x-1][temp_y].down==1 && marray[temp_x-1][temp_y].mark==0)
		{
			marray[temp_x-1][temp_y].mark=1;
			stack_push(temp_x-1,temp_y);
			i=temp_x*2+1;
			j=temp_y*2+1;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			i--;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			
		} //check up
		else
		{
			i=temp_x*2+1;
			j=temp_y*2+1;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			stack_pop();
		}
	}
	i=finish_x*2+1;
	j=finish_y*2+1;
	if(flag==1)
	{
		while(1)
		{
			if(top==NULL)
				break;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(0,0,0), RGB(0,0,0));
			if((top->x)*2+3 == i)
			{
				i--;
				DrawSolidBox_I(j,i,j+1,i+1,2,RGB(0,0,0), RGB(0,0,0));
			}
			else if((top->x)*2-1 == i)
			{
				i++;
				DrawSolidBox_I(j,i,j+1,i+1,2,RGB(0,0,0), RGB(0,0,0));
			}
			else if((top->y)*2+3 == j)
			{
				j--;
				DrawSolidBox_I(j,i,j+1,i+1,2,RGB(0,0,0), RGB(0,0,0));
			}
			else if((top->y)*2-1 ==j)
			{
				j++;
				DrawSolidBox_I(j,i,j+1,i+1,2,RGB(0,0,0), RGB(0,0,0));
			}
			i=(top->x)*2+1;
			j=(top->y)*2+1;
			stack_pop();
		}
		DrawSolidBox_I(1,1,2,2,2,RGB(0,0,0), RGB(0,0,0));
	}
}

void stack_push(int i, int j)
{
	stack* temp=(stack*)malloc(sizeof(stack));
	temp->x=i;
	temp->y=j;
	temp->link=top;
	top=temp;
}

void stack_pop()
{
	stack* temp=top;
	top=top->link;
	free(temp);
}

void BFS()
{
	drawBuffered();
	int finish_x=height-1;
	int finish_y=width-1;
	int i,j;
	int temp_x=0;
	int temp_y=0;
	int flag=0;
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
			marray[i][j].mark=0;
	p=(path**)malloc(sizeof(path*)*height);
	for(i=0;i<height;i++)
		p[i]=(path*)malloc(sizeof(path)*width);
	start=(que*)malloc(sizeof(que));
	start->x=0;
	start->y=0;
	start->link=NULL;
	end=start;
	marray[0][0].mark=1;
	while(1)
	{
		if(start==NULL)
			break;
		temp_x=start->x;
		temp_y=start->y;
		if( marray[temp_x][temp_y].right==1 && marray[temp_x][temp_y+1].mark==0)
		{
			if(temp_x==finish_x && temp_y+1==finish_y)
			{
				p[temp_x][temp_y+1].x=temp_x;
				p[temp_x][temp_y+1].y=temp_y;
				flag=1;
				break;
			}
			marray[temp_x][temp_y+1].mark=1;
			que_push(temp_x, temp_y+1);
			p[temp_x][temp_y+1].x=temp_x;
			p[temp_x][temp_y+1].y=temp_y;
			i=temp_x*2+1;
			j=temp_y*2+1;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			j++;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			
		} //check right
		if(marray[temp_x][temp_y].down==1 && marray[temp_x+1][temp_y].mark==0)
		{
			if(temp_x+1==finish_x && temp_y==finish_y)
			{
				flag=1;
				p[temp_x+1][temp_y].x=temp_x;
				p[temp_x+1][temp_y].y=temp_y;
				break;
			}
			p[temp_x+1][temp_y].x=temp_x;
			p[temp_x+1][temp_y].y=temp_y;
			marray[temp_x+1][temp_y].mark=1;
			que_push(temp_x+1,temp_y);
			i=temp_x*2+1;
			j=temp_y*2+1;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			i++;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			
		} //check down
		if(temp_y>0 && marray[temp_x][temp_y-1].right==1 && marray[temp_x][temp_y-1].mark==0)
		{
			marray[temp_x][temp_y-1].mark=1;
			que_push(temp_x,temp_y-1);
			p[temp_x][temp_y-1].x=temp_x;
			p[temp_x][temp_y-1].y=temp_y;
			i=temp_x*2+1;
			j=temp_y*2+1;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			j--;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			
		} //check left
		if(temp_x>0 && marray[temp_x-1][temp_y].down==1 && marray[temp_x-1][temp_y].mark==0)
		{
			marray[temp_x-1][temp_y].mark=1;
			que_push(temp_x-1,temp_y);
			p[temp_x-1][temp_y].x=temp_x;
			p[temp_x-1][temp_y].y=temp_y;
			i=temp_x*2+1;
			j=temp_y*2+1;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			i--;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			
		} //check up
		else
		{
			i=temp_x*2+1;
			j=temp_y*2+1;
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(128,128,128), RGB(128,128,128));
			que_pop();
		}
	}
	i=finish_x*2+1;
	j=finish_y*2+1;
	temp_x=p[finish_x][finish_y].x;
	temp_y=p[finish_x][finish_y].y;
	if(flag==1)
	{
		while(1)
		{
			DrawSolidBox_I(j,i,j+1,i+1,2,RGB(0,0,0), RGB(0,0,0));
			if((temp_x)*2+3 == i)
			{
				i--;
				DrawSolidBox_I(j,i,j+1,i+1,2,RGB(0,0,0), RGB(0,0,0));
			}
			else if((temp_x)*2-1 == i)
			{
				i++;
				DrawSolidBox_I(j,i,j+1,i+1,2,RGB(0,0,0), RGB(0,0,0));
			}
			else if((temp_y)*2+3 == j)
			{
				j--;
				DrawSolidBox_I(j,i,j+1,i+1,2,RGB(0,0,0), RGB(0,0,0));
			}
			else if((temp_y)*2-1 ==j)
			{
				j++;
				DrawSolidBox_I(j,i,j+1,i+1,2,RGB(0,0,0), RGB(0,0,0));
			}
			i=temp_x;
			j=temp_y;
			if(i==0 && j==0)
				break;
			temp_x=p[i][j].x;
			temp_y=p[i][j].y;
			i=i*2+1;
			j=j*2+1;
		}
		DrawSolidBox_I(1,1,2,2,2,RGB(0,0,0), RGB(0,0,0));
	}
	
}

void que_push(int i, int j)
{
	que* temp=(que*)malloc(sizeof(que));
	temp->x=i;
	temp->y=j;
	temp->link=end->link;
	end->link=temp;
	end=temp;
}

void que_pop()
{
	que* temp=start;
	start=start->link;
	free(temp);
}