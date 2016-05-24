#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


 class Point{
       public:
      double x;  // Breadth of a box
      double y;
     int group;
     void set_coord (double,double);
     void set_group(int);
    };
void Point::set_coord(double x_coord, double y_coord)
{
    x = x_coord;
    y = y_coord;
}
void Point::set_group(int g){
group = g;
}
int  clusSize = 2;
Point centers[2] = {};


/*double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double[]  randArray(int size ,double min,double max){
    int randA[size];
    for(int k=0;k <size;k++){
        randA[k] = fRand(min,max);

    }
}*/

//second is array of vectors with a vector for each point
 vector<vector<Point>> second(10, vector<Point>(0));


//calculates the euclidean distance between any two point objects
double dist(Point first , Point second){
        double distance = pow(pow(first.x - second.x ,2) + pow(first.y - first.y, 2),.5);
        return  distance;
    }

void printVector(vector<Point> start){
    for(unsigned int i = 0;i<start.size();i++){
        cout << start[i].x;
    }


}

//this could return 0 is that okay
int nearest_cluster(Point x , Point clus[]){
     double minClus = dist(x,clus[0]);
     int minIndex = 0;

    for(int i = 0;i<clusSize;i++){
       double stuff = dist(x,clus[i]);
        if(stuff< minClus){
            minClus = stuff;
            minIndex = i;

        }

    }
   // x.set_group(i);
   return minIndex;

}
//finds the average x coordinate
//this is used to find the centroid
double avgx(vector<Point> start){
    double total = 0;
    for(int i = 0;i<start.size();i++){
        total  += start[i].x;
        }
    return total/(start.size());
}

//finds the average y coordinate
double avgy(vector<Point> start){
    double total = 0;
    for(int i = 0;i<start.size();i++){
        total  += start[i].y;
        }
    return total/(start.size());
}






//alters centers
void newcentroids(){
    //make sure this is not setting everything to the same centroid
    for(int m = 0;m<clusSize;m++){
    double x_avg = avgx(second[m]);
    double y_avg = avgy(second[m]);
   Point Centroid;
    Centroid.set_coord(x_avg,y_avg);
    centers[m] = Centroid;
    }
    }


//this places the points into
void initalize(int numPoints, Point listOfPoints[]){
    //I will define this later
    //replace six by the number of points
    for(int k = 0;k<numPoints;k++){
        int near = nearest_cluster(listOfPoints[k], centers);
        listOfPoints[k].set_group(near);
       second[near].push_back(listOfPoints[k]);



    }

}


//meausure of how good a fit the current clustering is
void cost(){
    int sum = 0;
    for(int i= 0;i<10 ;i++){
        for(int j=0;j<second[i].size();j++){
            double distance = dist(second[i][j] , centers[i]);
            sum += distance;
            }
        }

    cout<<"This is the cost"<<sum<<endl;
   }




//this function iterativly puts points in new clusters until they
//are in the optimal cluster
void Update(){
    int check = 0;
    int change = 1;
while(change != 0){
    change = 0;
    newcentroids();
    vector<vector<Point>> replace(10, vector<Point>(0));
    int change = 0;
for(int i=0;i<clusSize;i++){
    for(int j = 0;j<second[i].size();j++){
         Point p1 = second[i][j];
          int check = nearest_cluster(second[i][j], centers);
        if(check != p1.group){
            int original = p1.group;
            p1.group = check;
            change = 1;
           replace[check].push_back(p1);
            }

    }
}
    //set the new clusters equal to the old positions
    second = replace;
    check++;


}

}


//Point listPoints[6] = {};

int main() {


//set up original centroids
Point rand;
rand.set_coord(-3.5,4);
Point rand2;
rand2.set_coord(0.9,7);
centers[0] = rand;
centers[1] = rand2;
//set up points to be clustered
Point one;
one.set_coord(3,4);
Point two;
two.set_coord(5,6);
Point three;
three.set_coord(5,6);
Point four;
four.set_coord(7,8);
Point five;
five.set_coord(-.5,.5);
Point six;
six.set_coord(-4,3);
Point seven;
seven.set_coord(0,0);
Point listPoints[6] = {};
listPoints[0] = one;
listPoints[1] = two;
listPoints[2] = three;
listPoints[3] = four;
listPoints[4] = five;
listPoints[5] = six;
//this sets up the k-means classifcation
   int numberPoints = 6;

   initalize(numberPoints,listPoints);
    cost();
    cout<<"Initial";
       Update();
    cost();
       };










    
