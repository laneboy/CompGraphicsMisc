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
	void* simplex;//not sure what this should be yet
};typedef struct* GJK GJK_Object;
;typedef const std::vector<Util::Vector>& Polygon;
GJK_Object SteerLib::GJK_EPA::GJK(Polygon A, Polygon B){
	GJK_Object toRet = (GJK_Object)malloc(sizeof(struct GJK));
	toRet->collision = false;
	toRet->simplex = NULL;
	if (A collides with B){//SUDO CODE
		toRet->collision = true;
        	//return (Simplex, true);
		return toRet;
	}
        else{
        	//return (NULL, false);
		return toRet;
	}
}





