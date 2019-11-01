#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include<iostream>
#include<stdlib.h>
#include</home/hitvarth/SeDriCa/A*_without_main.cpp>

using namespace std;

cv::Mat img;
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    img = cv_bridge::toCvShare(msg, "mono8")->image;
    cv::imshow("view", img);
    cv::waitKey(30);
    // cout << "Width : " << img.size() << endl;
    // cout << "Width : " << img.size().width << endl;
    // cout << "Height: " << img.size().height << endl;
     for(int j=0;j<10;j++){
      for (int i=0;i<10;i++){

        cout <<"test: "<< (img.at<uint8_t>(i,j)) << endl;
      }
    } 
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'mono8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_subscriber");
  ros::NodeHandle nh;
  cv::namedWindow("view",cv::WINDOW_AUTOSIZE);
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("static_image", 1, imageCallback);

  ros::spin();

  cv::destroyWindow("view");
  

  cout<<"\n\n THE GRID WOULD BE M(x coordinate) x N(y coordinate) "<<"\n\n ENTER M & N  :  \n";
  M = 10;
  N = 10;
  // cin>>M>>N;
  
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
    { n[i][j].is_obs=true;
    } 

    for(i=1,j=N+1;i<=M;i++)
    { n[i][j].is_obs=true;
    } 

    for(i=M+1,j=0;j<N+2;j++)    
    { n[i][j].is_obs=true;
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
  // cin>>start_x>>start_y;
  start_x = 0;
  start_y = 0;
  
  n[start_x+1][start_y+1].parent_x=-1;
  n[start_x+1][start_y+1].parent_y=-1;
  n[start_x+1][start_y+1].g=0.0;
  closed_list[0][0]=start_x;
  closed_list[0][1]=start_y;
  index_closed++;
  

  cout<<"\n\n ENTER THE COORDINATES OF END (x,y)";
  // cin>>end_x>>end_y;
  end_x = 9;
  end_y = 9;

  cout<<"\n\n ENTER THE NUMBER OF OBSTACLES ";
  // cin>>num_obs;
  
  // for(i=1;i<=num_obs;i++)
  // {
  //   cout<<"\n\n\n\n ENTER THE COORDINATES OF OBSTACLES (x,y) ";
  //   cin>>xo>>yo;
  //   n[xo+1][yo+1].is_obs=true;
  // }
  for(i=0;i<M;i++)
  {
    for(j=0;j<N;j++)
    {
      if(img.at<uchar>(i,j)==255)
      {
        n[i+1][j+1].is_obs = true;
      }
      cout<<"("<<n[i+1][j+1].is_obs<<","<<img.at<uchar>(i,j)<<") ";
    }
    cout<<endl;
  }

  i=start_x;
  j=start_y;

  int min_f,min_index;  // for finding the min f in the open list and noting its index

    while(true)
    {
    //  cout<<"0000000 "<<i<<" 88888888 "<<j<<endl;
      for(int a=i-1;a<=i+1;a++)
      { 
        for(int b=j-1;b<=j+1;b++)
        { 
          if(a!=i || b!=j)
          { 
    //      cout<<a<<" a"<<" b "<<b<<endl;
            if(n[a+1][b+1].is_obs==false && is_in_list(closed_list,a,b,index_closed)==false && is_in_list(open_list, a,b,index_open)==false)
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
        
    //    cout<<"adsfg "<<i<<" mmmmm "<<j<<" mmmmmmmm "<<index_open<<endl;

        //////////////  now checking the node with the lowest  f cost in the open list....


        min_f=99999;

        for(int a=0;a<=index_open;a++)
        {
    //      cout<<"nnnnn   "<<open_list[a][0]<<endl;
          if(n[open_list[a][0]+1][open_list[a][1]+1].f<min_f)    //open_list[a][0] will give the x coordinate of the node
          {
            min_f=n[open_list[a][0]+1][open_list[a][1]+1].f;
            min_index=a;
          } 
        }

    //    cout<<"222222 "<<i<<" mmmmm "<<j<<" bbbbbb "<<min_index<<endl;

        ////moving to the node with min f
        i=open_list[min_index][0];
        j=open_list[min_index][1];

        ////adding the node with minimun f to the closed list

        closed_list[index_closed+1][0]=i;// or open_list[min_index][0];   // for x 
        closed_list[index_closed+1][1]=j;//or open_list[min_index][1];    // for y
        index_closed++;

    //    cout<<"3333333 "<<i<<" mmmmm "<<j<<endl;

        if(i==end_x && j==end_y)
          break;

        ////now removing that node from the open list

        for(int a=min_index;a<=index_open-1;a++)
        {
          open_list[a][0]=open_list[a+1][0];
          open_list[a][1]=open_list[a+1][1];
        }
        index_open-=1;       //one element has decreased in open list 

    //    cout<<"4444444 "<<i<<" mmmmm "<<j<<endl;

    }


    /////we have reached the destination...
    /////so now tracing back...
   
    
    int a,b,temp;
    a=end_x;b=end_y;
    int counter = 0;
    while(a>=0 && b>=0)
    {
      counter++;
      cout<<" ("<<a<<","<<b<<")"<<" --> ";//<<"("<<n[a][b].parent_x<<","<<n[a][b].parent_y<<")"<<" \n";
      img.at<uchar>(a,b) = counter;
      temp=a; 
      a=n[a+1][b+1].parent_x;
      b=n[temp+1][b+1].parent_y;
    }
    //cout<<" ("<<start_x<<","<<start_y<<") ||";
    cout<<"  || \n";

  // for(i=0;i<M;i++)
  // {
  //   for(j=0;j<N;j++)
  //   {
  //     cout<<img.at<cv::Vec3b>(i,j)<<" ";
  //   }
  //   cout<<endl;
  // }
    // for( int y = 0; y < img.rows; y++ ) 
    // {
    //     for( int x = 0; x < img.cols; x++ ) 
    //     {
    //         for( int c = 0; c < img.channels(); c++ ) 
    //         {
    //             cout<<img.at<Vec3b>(y,x)[c]<<" ";
    //         }
    //     }
    //     cout<<endl;
    // }
   


}