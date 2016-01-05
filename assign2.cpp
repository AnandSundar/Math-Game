/*
Name: Anand Sundar
File: assign2.cpp
Purpose: To create a game created by a briliant mathematician
*/

#include<iostream>
#include<unistd.h>

using namespace std;
const int maxrows = 100;
const int maxcols = 100;
const char data1 = 'x';
const char data2 = '.';
const int maxsize = 100;
const int zero = 0;

void welcome();
void stageone(int &elements, int &iterations);
void rowinput(char array[][maxcols],int elements,char temp[][maxcols]);
void showuserinput(char array[][maxcols], int elements);
void populationgrowth(char array[][maxcols],int elements,int &x,char temp[][maxcols],int &y);
void checkconditionM_1(char array[][maxcols],int &cellcount, int i, int j);//middle cells
void speccondition1_1(char temp[][maxcols],int x, int i, int j);
void speccondition1_2(char temp[][maxcols],int y, int i, int j);
void checkconditionTL(char array[][maxcols],int &cellcount);//top left cell
void checkconditionBL(char array[][maxcols], int &cellcount, int elements);//bottom left cell
void checkconditionLR(char array[][maxcols], int &cellcount,int elements,int i);//left row full
void checkconditionTR(char array[][maxcols], int &cellcount, int elements);//top right cell
void checkconditionRC(char array[][maxcols],int &cellcount,int elements, int i);	//right column full
void checkconditionBR(char array[][maxcols], int &cellcount, int elements);//bottom right cell
void checkconditionLC(char array[][maxcols],int j, int &cellcount);//left column full
void checkconditionFR(char array[][maxcols],int &cellcount,int elements, int i);//first row full
void showresult(char temp[][maxcols],int elements);

int main()
{
	int elements =0, iterations =0;
	int x=0,y=0, generation = 0;
	char array[maxrows][maxcols];//original array to store the even iterations
	char temp[maxrows][maxcols];//temporary array to store the odd iterations
	for(int i=0;i<elements;i++)
	{
		for(int j=0; j<elements; j++)//allocating all the memory location to 0
		{
			array[j][i] ='0';
			temp[j][i]= '0';
		}
	}	
	//calling welcome function
	welcome();
	char input;
	cout<<"To play, press \"C\", to exit press any other key"<<endl;
	cin>>input;//stores the user input
	do{// do while loop to repeat the process till the user enters c
		if(input == 'c'|| input == 'C')//if block to check the user input value
		{
			stageone(elements,iterations);//calls stageone function
			rowinput(array,elements,temp);//calls rowinput funcion
			showuserinput(array,elements);//calls show user value
		do{
			if(generation<=iterations)//if block to generate even generations
			{
				while(generation ==0||generation==2||generation==4||generation==6||generation==8)
				{
					cout<<"\nGENERATION "<<generation<<endl;
					populationgrowth(array,elements,x,temp,y);//calls populationgrowth function
					showresult(temp,elements);
					generation++;
					sleep(2);//gives 2 second pause
				}
			}
			for(int i=0;i<elements;i++)//copies the 2D array to another 2D array
			{
				for(int j=0;j<elements;j++)
				{
					array[i][j] = temp[i][j];
				}
			}
			if(generation<=iterations)
			{
				//loop to generate odd generetions
				while(generation ==1||generation==3||generation==5||generation==7||generation==9)
				{
					if(generation == iterations)//to stop the loop from executing one extra generation
					{
						generation++;
						break;
					}
					cout<<"\nGENERATION "<<generation<<endl;
					populationgrowth(temp,elements,x,array,y);
					showresult(array,elements);
					generation++;
					sleep(2);
					
				}
			}
			for(int i=0;i<elements;i++)//copies the 2D array to another 2D array
			{
				for(int j=0;j<elements;j++)
				{
					temp[i][j] = array[i][j];	
				}
			}
		}while(generation<iterations);
		}else{
			return 0;// returns 0 if user enters anything other than c
		}
		generation=0;
		iterations =0;
		cout<<"To play, press \"C\", to exit press any other key"<<endl;
		cin>>input;
	}while(input == 'c'|| input == 'C');
}

void welcome()
{
	cout<<"Welcome to my amazing game, based on one designed by a very bright mathematician"<<endl;
	cout<<"To start, you will be asked to pick a size for the area of play"<<endl;
	cout<<"This size will be the width of a square, and must be between 1 and 10"<<endl;
	cout<<"Then you will enter the number of generations you wish to simulate"<<endl;
	cout<<"You may choose to simulate up to 9 generations"<<endl;
	cout<<"Finally, you will be asked to fill the square with either live or dead cells"<<endl;
	cout<<"Live cells are denoted by an x, and dead cells are denoted by a ."<<endl;
	cout<<"In this game, the state of a cell at each generation is decided based on"<<endl;
	cout<<"a set of simple rules, as follows:"<<endl;
	cout<<"1. Underpopulation: A living cell with less than 2 living neighbours,"<<endl;
	cout<<"dies"<<endl;
	cout<<"2. Survival: A living cell with two or three living neighbours, lives"<<endl;
	cout<<"3. Overcrowding: A living cell with more than three living neighbours,"<<endl;
	cout<<"dies"<<endl;
	cout<<"4. Reproduction: A dead cell with exactly three living neighbours,"<<endl;
	cout<<"comes to life"<<endl;

}

void stageone(int &elements, int &iterations)
{
	cout<<"Please enter a positive integer, less than 10"<<endl;
	while(!(cin>>elements))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout<<"Please enter a numeric value"<<endl;
	}
	
	while(elements<1 || elements>10)
	{
		cout<<"Please enter a positive integer, less than 10"<<endl;
		cin>>elements;
	}
	cout<<"Please enter the number of iterations you'd like to simulate"<<endl;
	while(!(cin>>iterations))
	{
		cin.clear();
		cin.ignore(10000,'\n');
		cout<<"Please enter a numeric value"<<endl;
	}
	 
}

void rowinput(char array[][maxcols], int elements,char temp[][maxcols])
{
	int row =1;
	char temps[maxsize];
	cin.clear();
	cin.ignore(10000,'\n');		
	for (int i=0; i<elements; i++)
	{
		cout<<"Please enter "<<elements<<" characters, for row "<<row<<endl;
		cout<<"Either \'x\' or \'.\'"<<endl;
		cin.getline(temps,maxsize,'\n');
		for (int j=0;j<elements; j++)
		{		
			array[j][i] = temps[j];
		}		
		row++;
	}
	for (int i=0; i<elements; i++)
	{
		for(int j=0;j<elements; j++)
		{
			temp[j][i] = array[j][i];
		}
	}	
}
void showuserinput(char array[][maxcols], int elements)
{
	cout<<endl;
	cout<<"Here is your start state"<<endl;
	for (int i=0; i<elements; i++)
	{
		for (int j=0;j<elements; j++)
		{	
			cout<<array[j][i];
		}
		cout<<endl;
	}	
}

void populationgrowth(char array[][maxcols],int elements,int &x,char temp[][maxcols],int &y)
{
	//declared seperately so that check condition can use it 
		int i=0, j=0;	
		for( i=1;i<elements-1;i++)// -1 to neglect last column in the table
		{
			for( j=1; j<elements-1; j++)
			{
				if(array[j][i] == data1)
				{
					checkconditionM_1(array,x,i,j);	//checks condition for the center cells of the table
					speccondition1_1(temp,x,i,j);//checks condition and stores the value in the temp array
					x=0;
				}
				else if(array[j][i] == data2)
				{
					checkconditionM_1(array,y,i,j);	
					speccondition1_2(temp,y,i,j);
					y=0;
					x=0;
				}
			}
		
		}	
		
		//calculation for first cell in the table
		if(array[zero][zero] ==data1)
		{
			checkconditionTL(array,x);//checks conditions for first cell in the table
			speccondition1_1(temp,x,zero,zero);//stores values in new array according to the rules
			x=0;	
		}
		else if(array[zero][zero] ==data2)
		{
			checkconditionTL(array,y);//checks conditions for first cell in the table
			speccondition1_2(temp,y,zero,zero);//stores values in new array according to the rules
			y=0;
			x=0;
		}
		//calculation for the first cell in the last row
		if(array[elements][zero] ==data1)
		{
			checkconditionBL(array,x,elements);//checks condition for bottom left cell
			speccondition1_1(temp,x,elements,zero);//stores values in new array according to the rules
			x=0;
		}
		else if(array[elements][zero] ==data2)
		{
			checkconditionBL(array,y,elements);
			speccondition1_2(temp,y,elements,zero);//stores values in new array according to the rules
			x=0;
			y=0;
		}
		//calculation for left column
		for(int j=1; j<elements-1; j++)
		{
			if(array[j][zero] == data1)
			{
				checkconditionLC(array,j,x);//checks condition for last cell in the cell
				speccondition1_1(temp,x,zero,j);//stores values in new array according to the rules
				x=0;
			}
			else if(array[j][zero] == data2)
			{
				checkconditionLC(array,j,y);
				speccondition1_2(temp,y,zero,j);//stores values in new array according to the rules
				x=0;//stores values in new array according to the rules
				y=0;
			}
		}
		//calculation for last col first cell
		if(array[zero][elements] == data1)
		{	
			checkconditionTR(array,x,elements);//checks condition for top row
			speccondition1_1(temp,x,zero,elements);//stores values in new array according to the rules
			x=0;
		}else if(array[zero][elements] ==data2){
			checkconditionTR(array,y,elements);
			speccondition1_2(temp,y,zero,elements);//stores values in new array according to the rules
			x=0;
			y=0;		
		}
		//calculation for last column
		for(int i=1; i<elements-1; i++)
		{
			if(array[i][elements] == data1)
			{
				checkconditionRC(array,x,elements,i);//checks condition for right column
				speccondition1_1(temp,x,i,elements);//stores values in new array according to the rules
				x=0;
			}else if(array[i][elements] == data2){
				checkconditionRC(array,y,elements,i);
				speccondition1_2(temp,y,i,elements);	//stores values in new array according to the rules
				x=0;
				y=0;
			}
		}
		//calcuation for last cell in the table
		if(array[elements][elements] ==data1)
		{
			checkconditionBR(array,x,elements);//checks condition for the bottom row
			speccondition1_1(temp,x,elements,elements);
			x=0;
		}else if(array[elements][elements] ==data2){
			checkconditionBR(array,y,elements);
			speccondition1_2(temp,y,elements,elements);
			x=0;
			y=0;
		}

		//calculation for last row
		for(int i=1; i<elements-1; i++)
		{
			if(array[elements][i] ==data1)
			{
				checkconditionLR(array,x,elements,i);//checks condition for last row
				speccondition1_1(temp,x,elements,i);
				x=0;
			}else if(array[elements][i] ==data2){
				checkconditionLR(array,y,elements,i);
				speccondition1_2(temp,y,elements,i);
				x=0;
				y=0;
			}
		}
		//calculation for row zero
		for(int i=1; i<elements-1; i++)
		{
			if(array[zero][i] ==data1)
			{
				checkconditionFR(array,x,elements,i);//checks condition for first row
				speccondition1_1(temp,x,i,zero);
				x=0;
			}else if(array[zero][i] ==data2){
				checkconditionFR(array,y,elements,i);
				speccondition1_2(temp,y,i,zero);
				x=0;
				y=0;
			}
		}
}
//function for checking all the middle cells	
void checkconditionM_1(char array[][maxcols],int &cellcount, int i, int j)
{
	if(array[j][i-1]==data1)
	{
		cellcount++;
	}
	if(array[j][i+1]==data1)
	{
		cellcount++;
	}
	if(array[j-1][i-1] ==data1)
	{
		cellcount++;
	}
	if(array[j-1][i+1] ==data1)
	{
		cellcount++;
	}
	if(array[j+1][i-1] ==data1)
	{
		cellcount++;
	}
	if(array[j+1][i+1] ==data1)
	{
		cellcount++;
	}
	if(array[j+1][i] ==data1)
	{
		cellcount++;
	}
	if(array[j-1][i] ==data1)	
	{
		cellcount++;
	}
}

void checkconditionTL(char array[][maxcols],int &cellcount)
{
		if(array[zero][zero+1] == data1)
		{
			cellcount++;
		}
		if(array[zero+1][zero] ==data1)
		{
			cellcount++;
		}
		if(array[zero+1][zero+1] ==data1)
		{
			cellcount++;
		}	
}

void checkconditionBL(char array[][maxcols], int &cellcount, int elements)
{
		if(array[elements][zero+1] == data1)
		{
			cellcount++;
		}
		if(array[elements-1][zero] ==data1)
		{
			cellcount++;
		}
		if(array[elements-1][zero+1]==data1)
		{
			cellcount++;
		}	
}

void checkconditionLC(char array[][maxcols], int j, int &cellcount)
{
	if(array[j][zero+1] == data1)
	{
		cellcount++;
	}
	if(array[j-1][zero] == data1)
	{
		cellcount++;
	}
	if(array[j-1][zero+1] == data1)
	{
		cellcount++;
	}
	if(array[j+1][zero] == data1)
	{
		cellcount++;
	}
	if(array[j+1][zero+1] == data1)
	{
		cellcount++;
	}
}

void checkconditionTR(char array[][maxcols],int &cellcount, int elements)
{
		if(array[zero+1][elements] ==data1)
		{
			cellcount++;
		}
		if(array[zero][elements-1]==data1)
		{
			cellcount++;
		}
		if(array[zero+1][elements-1]==data1)
		{
			cellcount++;
		}
}

void checkconditionRC(char array[][maxcols],int &cellcount,int elements, int i)
{
	if(array[i-1][elements] ==data1)
	{
		cellcount++;
	}
	if(array[i-1][elements-1] ==data1)
	{
		cellcount++;
	}
	if(array[i][elements-1] ==data1)
	{
		cellcount++;
	}
	if(array[i+1][elements] ==data1)
	{
		cellcount++;
	}
	if(array[i+1][elements-1] ==data1)
	{
		cellcount++;
	}
	
}

void checkconditionBR(char array[][maxcols], int &cellcount, int elements)
{
	if(array[elements-1][elements] ==data1)
	{
		cellcount++;
	}
	if(array[elements][elements-1]==data1)
	{
		cellcount++;
	}
	if(array[elements-1][elements-1] ==data1)
	{
		cellcount++;
	}
}

void checkconditionLR(char array[][maxcols],int &cellcount,int elements, int i)
{
	if(array[elements][i-1] == data1)
	{
		cellcount++;
	}
	if(array[elements][i+1] ==data1)
	{
		cellcount++;
	}
	if(array[elements-1][i] ==data1)
	{
		cellcount++;
	}
	if(array[elements-1][i-1] ==data1)
	{
		cellcount++;
	}
	if(array[elements-1][i+1] ==data1)
	{
		cellcount++;
	}
}

void checkconditionFR(char array[][maxcols],int &cellcount,int elements, int i)
{
	if(array[zero+1][i] ==data1)
	{
		cellcount++;
	}
	if(array[zero+1][i-1] ==data1)
	{
		cellcount++;
	}
	if(array[zero][i-1] ==data1)
	{
		cellcount++;
	}
	if(array[zero][i+1] ==data1)
	{
		cellcount++;
	}
	if(array[zero+1][i+1] ==data1)
	{
		cellcount++;
	}
}

void speccondition1_1(char temp[][maxcols],int x, int i, int j)
{
	if(x<2)
	{
		temp[j][i] = data2;//underpopulation
	}

	if(x==2||x==3)
	{
		temp[j][i] =data1;//survival
	}

	if(x>3)
	{
		temp[j][i] =data2;//crowding		
	}
}

void speccondition1_2(char temp[][maxcols],int y,int i, int j)
{
		if(y==3)
		{
			temp[j][i] =data1;//reproduction				
		}
}

void showresult(char temp[][maxcols],int elements)
{
	cout<<"\nHere is your output"<<endl;
	for(int i=0;i<elements;i++)// -1 to neglect last column in the table
	{
		for(int j=0; j<elements; j++)
		{
			cout<<temp[j][i];
		}	
		cout<<endl;
	}
}


