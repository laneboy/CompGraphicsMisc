/*!
*
* \author VaHiD AzIzI
*
*/


#include "obstacles/GJK_EPA.h"


SteerLib::GJK_EPA::GJK_EPA()
{
}

//Look at the GJK_EPA.h header file for documentation and instructions
bool SteerLib::GJK_EPA::intersect(float& return_penetration_depth, Util::Vector& return_penetration_vector, const std::vector<Util::Vector>& _shapeA, const std::vector<Util::Vector>& _shapeB)
{
    return false; // There is no collision
}

//GJK Algorithm Following syntax form given in GJK_EPA.h
struct GJK{//I don't belive in returing things through arguments that is bad programing practice
	bool collision;
	Polygon simplex;//Iteritve Polygon that is contained in the Minkoski difference and containes the origen
};typedef struct* GJK GJK_Object;
;typedef const std::vector<Util::Vector>& Polygon;
;typedef const std::vector<int>& Point;
GJK_Object SteerLib::GJK_EPA::GJK(Polygon A, Polygon B){
	GJK_Object toRet = (GJK_Object)malloc(sizeof(struct GJK));
	Polygon simplex = getSimplex(A,B);
	if (!simplex){//if the simplex is not null
		if(containsOrigen(simplex)){//does the simplex contain the origen if so => collision
        		toRet->collision = true;
			toRet->simplex = simplex;
			return toRet;
		}
		else{
			toRet->collsion = false;
			free(toRet->simplex);
			toRet->simplex = NULL;
			return toRet;
		}
	}
        else{
		
		toRet->collision = false;
		toRet->simplex = NULL;
        	//return (NULL, false);
		return toRet;
	}
}
Point support(Polygon s1, Polygon s2,const std::vector d){
	Point p1 = getPointFromDirection(s1,d);
	Point p2 = getPointFromDirection(s2,inverse(d));
	Point p3 = pointSubtraction(p1,p2);
	return p3;
}
Point getPointFromDirection(Polygon s, const std::vector d){
	
	return
}
Point pointSubtraction(Point p1, Point p2){

}
Polygon getSimplex(Polygon A,Polygon B){

}
bool containesOrigen(Polygon P){

}

