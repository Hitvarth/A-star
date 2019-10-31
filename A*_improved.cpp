#include<iostream>
using namespace std;
#include<stdlib.h>


////global variables
int M,N;


int index_closed=-1;   // storing the position of last filled element
int index_open=-1;

int start_x,start_y,end_x,end_y;



bool is_in_list(int list[][2],int i,int j,int index)
{
	for(int a=0;a<=index;a++)
	{	
		if(list[a][0]==i && list[a][1]==j)
		{
			return true;
		}
	}	
	return false;
}


class node 
{
	public:
	int parent_x,parent_y,x,y; 
	float f,g,h;
	bool is_obs;
	
	node()
	{
		h=0;is_obs=false;
	}

	void calc_gcost();


	void calc_h()
	{
		h=(abs(end_x-x)+abs(end_y-y));
	}

	void calc_f()
	{
		calc_h();
		calc_gcost();

		f=g+h;
		
	}

}n[22][22];




    void node::calc_gcost()
	{
		if(parent_x-x==1 || parent_x-x==-1)
		{	
			if(parent_y-y==1 || parent_y-y==-1)
				g=n[parent_x+1][parent_y+1].g +14;

			if(parent_y-y==0)
				g=n[parent_x+1][parent_y+1].g +10;
		}

		if(parent_x-x==0)
			g=n[parent_x+1][parent_y+1].g +10;		


	}



int main()
{	
	

 
	cout<<"\n\n THE GRID WOULD BE M(x coordinate) x N(y coordinate) "<<"\n\n ENTER M & N  :  \n";
	cin>>M>>N;

	int total_nodes;
	total_nodes=M*N;

	int closed_list[total_nodes][2];
	int open_list[total_nodes][2];
	

	for(int a=0;a<total_nodes;a++)                   // initializing the array
	{	
   	  for(int b=0;b<2;b++)
   	  {	
   	  	closed_list[a][b]=-1;
   	  	open_list[a][b]=-1;
   	  }	
   	}  

    
    
    int i,j;


   	// now making the borders with obstacles
 
   	for(i=0,j=0;j<N+2;j++)    
   	{	n[i][j].is_obs=true;
   	}	

   	for(i=1,j=N+1;i<=M;i++)
   	{	n[i][j].is_obs=true;
   	}	

   	for(i=M+1,j=0;j<N+2;j++)    
   	{	n[i][j].is_obs=true;
   	}	


   	for(i=1,j=0;i<=M;i++)
   	{	
   		n[i][j].is_obs=true;
   	}	



   	for(i=0;i<M+2;i++)                  //alloting coordinates to the nodes
   	{	
   		for(j=0;j<N+2;j++)
   		{
   			n[i][j].x=i-1;
   			n[i][j].y=j-1;
   		}	
   	}	



	int num_obs,xo,yo;
	
	cout<<"\n\n ENTER THE COORDINATES OF START (x,y)";  
	cin>>start_x>>start_y;
	n[start_x+1][start_y+1].parent_x=-1;
	n[start_x+1][start_y+1].parent_y=-1;
	n[start_x+1][start_y+1].g=0.0;
	closed_list[0][0]=start_x;
	closed_list[0][1]=start_y;
	index_closed++;
	

	cout<<"\n\n ENTER THE COORDINATES OF END (x,y)";
	cin>>end_x>>end_y;
	

	cout<<"\n\n ENTER THE NUMBER OF OBSTACLES ";
	cin>>num_obs;

	for(i=1;i<=num_obs;i++)
	{
		cout<<"\n\n\n\n ENTER THE COORDINATES OF OBSTACLES (x,y) ";
		cin>>xo>>yo;
		n[xo+1][yo+1].is_obs=true;
	}

	cout<<"hjkl";


	i=start_x;
	j=start_y;

	int min_f,min_index;  // for finding the min f in the open list and noting its index

    // for(int ii=0;ii<25;ii++)
    // {
    // 	for(int jj=0;jj<2;jj++)
    // 	{
    // 		cout<<open_list[ii][jj]<<" ";
    // 	}
    // 	cout<<endl;
    // }

    cout<<"qwert";

    while(true)
    {
    	for(int a=i-1;a<=i+1;a++)
    	{	
    		for(int b=j-1;b<=j+1;b++)
    		{	
    			if(a!=i && b!=j)
    			{	
    				if(n[a+1][b+1].is_obs==false && is_in_list(closed_list,i,j+1,index_closed)==false && is_in_list(open_list, i,j+1,index_open)==false)
        	        {	
   		   		
        			 open_list[index_open+1][0]=a;
        			 open_list[index_open+1][1]=b;
        			 index_open++;

        			 n[a+1][b+1].parent_x=i;
        			 n[a+1][b+1].parent_y=j;
        			 n[a+1][b+1].calc_f(); 
        			 //cout<<endl<<endl<<n[i][j+1].f;
        			 //break;        
        
        	        }		
        	    }    
        	}    
    	}
        
        cout<<"adsfg";

        //////////////  now checking the node with the lowest  f cost in the open list....


        min_f=99999;

        for(int a=0;a<=index_open;a++)
        {

        	if(n[open_list[a][0]+1][open_list[a][1]+1].f<min_f)    //open_list[a][0] will give the x coordinate of the node
        	{
        		min_f=n[open_list[a][0]+1][open_list[a][1]+1].f;
        		min_index=a;
        	}	
        }


        ////moving to the node with min f
        i=open_list[min_index][0];
        j=open_list[min_index][1];

        ////adding the node with minimun f to the closed list

        closed_list[index_closed+1][0]=i;// or open_list[min_index][0];   // for x 
        closed_list[index_closed+1][1]=j;//or open_list[min_index][1];	  // for y
        index_closed++;

        if(i==end_x && j==end_y)
        	break;

        ////now removing that node from the open list

        for(int a=min_index;a<=index_open-1;a++)
        {
        	open_list[a][0]=open_list[a+1][0];
        	open_list[a][1]=open_list[a+1][1];
        }
        index_open-=1;       //one element has decreased in open list	


    }


    /////we have reached the destination...
    /////so now tracing back...
   
    
    int a,b,temp;
    a=end_x;b=end_y;
    cout<<a<<" "<<b<<" ";
    for(int i=0;i<5;i++)
    {
    	for(int j=0;j<5;j++)
    	{
    		cout<<"("<<n[i][j].parent_x<<","<<n[i][j].parent_y<<")"<<" ";
    	}
    	cout<<endl;
    }


    while(a>=0 && b>=0)
    {

    	cout<<" ("<<a<<","<<b<<")"<<" --> ";//<<"("<<n[a][b].parent_x<<","<<n[a][b].parent_y<<")"<<" \n";
    	temp=a; 
    	a=n[a+1][b+1].parent_x;
    	b=n[temp+1][b+1].parent_y;
    }
    //cout<<" ("<<start_x<<","<<start_y<<") ||";

    cout<<"  || \n";

return 0;	
}

