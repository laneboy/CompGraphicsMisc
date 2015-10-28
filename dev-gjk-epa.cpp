#include <iostream>
#include <vector>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


;typedef std::vector<std::vector<int> > Polygon;
;typedef std::vector<int> Point;


bool containesOrigin(Polygon& simplex, Point& d);

/* Support Function
 * Tested this method thoughly
 */
Point Support(Polygon& s, Point& d){
	int dotproduct=0;
	int maxp = -1000000;//Maybe I should do something A little more reasonable lol<--Vector Out of Bonds Errors tend to occure here -> if error occurs use 'bigger' negative numner
	std::vector<int> max;
	for(std::vector<std::vector<int> >::iterator i = s.begin(); i != s.end(); ++i){
		std::cout<<"(";
		for(std::vector<int>::iterator j = (*i).begin(); j!=(*i).end();++j){
			std::cout<<*j<<",";
		}
		std::cout<<"\b)";
		dotproduct = d[0]*(*i).at(0) + d[1]*(*i).at(1); 
		std::cout<<"\t"<<dotproduct<<"\n";
		if(dotproduct>maxp){
			maxp = dotproduct;
			max = (*i);
		}
	}
	std::cout<<"Maximum Dot Product = "<<maxp<<"\nWith Point P = ("<<max.at(0)<<","<<max.at(1)<<")\n";
	return max;
}
Point neg(Point& p){
 p[0] = -p[0];
 p[1] = -p[1];
 return p;
}
/* Creates a Negitive Clone of Point P (i.e XY Flip)
 * Tested Throughly
 */
Point negClone(Point p){
	Point n(2);
	n[0] = -p[0];
	n[1] = -p[1];
	return n;
}
/* PointSub Functions takes in two points P1 & P2
 * and calculates the difference of P1-P2 i.e P2P1
 * Tested Throughly
 */
Point pointSub(Point p1, Point p2){
	Point p(2);
	p[0] = p1[0] - p2[0];
	p[1] = p1[1] - p2[1];
	return p;
}
int dot(Point p1, Point p2){
	return p1[0]*p2[0]+p1[1]*p2[1];
}
void XZprojection(Polygon& p){//SteerSim uses 3D Points and My Implementation of the GJK Algorithm uses 2D points of the form (x,y) not (x,0,z)
	for(std::vector<std::vector<int> >::iterator i = p.begin(); i != p.end(); ++i){
		(*i).erase((*i).begin()+1);//remove the y=0 cordinate
	}
}
bool GJK_intersection(Polygon& p, Polygon& q, Point& initD){
	bool Containes_origen = false;
	Point Neg = negClone(initD);

	Point A = pointSub(Support(p,initD) , Support(q, Neg ));
	//return false;
	Polygon Simplex(1);
	Simplex[0] = A;
	Point D = negClone(A);
	std::cout<<"Initzation of GJK was a success!\n";
	//return false;
	while(true){
		Neg = negClone(D);
		A = pointSub(Support(p,D) , Support(q, Neg ));
		if(dot(A,D)<0){//some sites say <=
			return false;
		}
		Simplex.push_back(A);
		//[S D Contains_origen] = NearestSimplex(s);
		Containes_origen = containesOrigin(Simplex,D);
		if(Containes_origen){
			return true;
		}
	}
}
void scalePoint(Point& p, int s){
	p[0]*=s;
	p[1]*=s;
}
void setPoint(Point& pset, Point prev){
	pset[0] = prev[0];
	pset[1] = prev[1];
}
Point tripleProduct(Point a, Point b, Point c){
	scalePoint(b,dot(a,c));
	scalePoint(c,dot(a,b));
	return pointSub(b,c);
}
bool containesOrigin(Polygon& simplex, Point& d){
	Point A = simplex.back();
	Point AO= negClone(A);
	if(simplex.size() == 3){//Triangle Case
		Point B = simplex[1];
		Point C = simplex[0];
		//Compute the Edges
		Point AB = pointSub(B,A);
		Point AC = pointSub(C,A);
		//Compute the Norms
		Point ABperp = tripleProduct(AC,AB,AB);
		Point ACperp = tripleProduct(AB,AC,AC);
		//Is the Origin in Region 4?
		if(dot(ABperp,AO) > 0){
			//Remove Point C
			simplex.erase(simplex.begin());
			setPoint(d,ABperp);
		}
		else{
			//Is the Origin in Region 3?
			if(dot(ACperp,AO) > 0){
				//remove point B
				simplex.erase(simplex.begin()+1);
			}
			else{//Then it is in Region 5 => The origen lives in the Simplex
				return true;
			}
		}
		
	}
	else{//Then its the line segment
		Point B = simplex.front();
		Point AB = pointSub(B,A);
		setPoint(d,tripleProduct(AB,AO,AB));
	}
	return false;
}
void printPoint(Point p){
	std::cout<<"("<<p[0]<<","<<p[1]<<")\n";
}
//======================================================Every Thing above is for the GJK Algorithm
#include <math.h> 
double mag(std::vector<double> p){
	return sqrt(p[0]*p[0]+p[1]*p[1]);
}
std::vector<double> normalize(std::vector<double> p){
	std::vector<double> n(2);
	double MAG = mag(p);
	n[0] = p[0]/MAG;
	n[1] = p[0]/MAG;
	
}
std::vector<double> pointSub(std::vector<double> p1, std::vector<double> p2){
	std::vector<double> p(2);
	p[0] = p1[0] - p2[0];
	p[1] = p1[1] - p2[1];
	return p;
}
double dot(std::vector<double> p1, std::vector<double> p2){
	return p1[0]*p2[0]+p1[1]*p2[1];
}
std::vector<double> intToDouble(Point p){
	std::vector<double> to(2);
	to[0] = p[0]*1.0;
	to[1] = p[1]*1.0;
}
void scalePoint(std::vector<double>& p, double s){
	p[0]*=s;
	p[1]*=s;
}
std::vector<double> tripleProduct(std::vector<double> a, std::vector<double> b, std::vector<double> c){
	scalePoint(b,dot(a,c));
	scalePoint(c,dot(a,b));
	return pointSub(b,c);
}
std::vector<double> findClosestPoint(std::vector<std::vector<double> > simplex, double& closest){
	closest = 1000000;
	std::vector<double> far;
	for(int i = 0; i < simplex.size(); i++){
		int j = i + 1 == simplex.size() ? 0 : i + 1;
		std::vector<double> a = simplex.at(i);
		std::vector<double> b = simplex.at(j);
		std::vector<double> e = pointSub(b,a);
		std::vector<double> n = tripleProduct(e,a,e);
		std::vector<double> norm = normalize(n);
		double def = dot(norm,a);
		if(def < closest){
			closest = def;
			far = n;
		}
	}
	return far;
}
std::vector<double> negClone(std::vector<double> p){
	std::vector<double> n(2);
	n[0] = -p[0];
	n[1] = -p[1];
	return n;
}
std::vector<double> Support(std::vector<std::vector<double> > s, std::vector<double> d){
	double dotproduct=0;
	double maxp = -1000000;//Maybe I should do something A little more reasonable lol<--Vector Out of Bonds Errors tend to occure here -> if error occurs use 'bigger' negative numner
	std::vector<double> max;
	for(std::vector<std::vector<double> >::iterator i = s.begin(); i != s.end(); ++i){
		std::cout<<"(";
		for(std::vector<double>::iterator j = (*i).begin(); j!=(*i).end();++j){
			std::cout<<*j<<",";
		}
		std::cout<<"\b)";
		dotproduct = d[0]*(*i).at(0) + d[1]*(*i).at(1); 
		std::cout<<"\t"<<dotproduct<<"\n";
		if(dotproduct>maxp){
			maxp = dotproduct;
			max = (*i);
		}
	}
	std::cout<<"Maximum Dot Product = "<<maxp<<"\nWith Point P = ("<<max.at(0)<<","<<max.at(1)<<")\n";
	return max;
}
//returns the depth
#define TOLERANCE 0.0001
double EPA(std::vector<std::vector<double> >& simplex,std::vector<double>& e, std::vector<std::vector<double> > A,std::vector<std::vector<double> > B){
	double distance = 0;
	while(true){
		std::vector<double> e = findClosestPoint(simplex,distance);
		std::vector<double> enorm = normalize(e);
		std::vector<double> nnorm = negClone(enorm);
		std::vector<double> p = pointSub(Support(A,enorm) , Support(B, nnorm ));
		double d = dot(p,enorm);
		
		if(d - distance < TOLERANCE){
			return d;
		}
		else{
			simplex.push_back(p);
		}
	}
}
//=================EPA Algorithm====================================
int main(int argc, char** argv) {
	std::cout<<"test\n";
	//Some Rotated Pentagon
	std::vector<std::vector<int> > poly1(5);
	std::vector<int> p1(2);p1[0] = 0; p1[1] = 3;
	std::vector<int> p2(2);p2[0] = 3; p2[1] = 2;
	std::vector<int> p3(2);p3[0] = 4; p3[1] = 5;
	std::vector<int> p4(2);p4[0] = 2; p4[1] = 8;
	std::vector<int> p5(2);p5[0] = -3; p5[1] = 6;
	poly1[0] = p1;
	poly1[1] = p2;
	poly1[2] = p3;
	poly1[3] = p4;
	poly1[4] = p5;
	
	//Some sqaure
	std::vector<std::vector<int> > poly2(4);
	std::vector<int> sp1(2);sp1[0] = -3; sp1[1] = 1;
	std::vector<int> sp2(2);sp2[0] = -3; sp2[1] = 4;
	std::vector<int> sp3(2);sp3[0] = 2; sp3[1] = 1;//-2
	std::vector<int> sp4(2);sp4[0] = 2; sp4[1] = 4;//-2
	poly2[0] = sp1;
	poly2[1] = sp2;
	poly2[2] = sp3;
	poly2[3] = sp4;
	
	
	
	std::vector<int> d(2); d[0] = 0; d[1] = 3;//Some Direction
	
	
	//Support(poly, d);
	
	//Testing Code
	printPoint(d);
	std::cout<<"Testing Negitive Function\n";
	printPoint(negClone(d));
	printPoint(d);
	
	std::cout<<"Testing Point Subtraction Function\n";
	printPoint(p1);
	printPoint(p2);
	printPoint(pointSub(p1,p2));
	printPoint(p1);
	printPoint(p2);
	
	//std::cout<<"Testing Scale Point Function";
	//printPoint(p1);
	//printPoint
	Support(poly1,d);
	Point n = negClone(d);
	Support(poly2, n );
	
	std::cout<<GJK_intersection(poly1,poly2,d);//<--Yielded Some erros Need to test
	return 0;
}
