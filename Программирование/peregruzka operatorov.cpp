#include <iostream>
using namespace std;
class vec{
	float x;
	float y; 
	float z;
public:	
	vec() = default;
	vec(int x,int y,int z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	static const void view(vec &a){
		cout<<"X: "<< a.x << endl;
		cout<<"Y: "<< a.y << endl;
		cout<<"Z: "<< a.z << endl;
	}
	
	
	//vec& operator+(vec& other){
	//	vec temp(this->x + other.x,this->y + other.y,this->z + other.z);
	//	return temp;
	//}

	vec& operator-(vec& other){
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
		}
		
	vec& operator*(vec& other){
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		return *this;
		}
	
	vec& operator/(vec& other){
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		return *this;
		}
};
	
int main(){
	vec a(1, 2, 3);
	vec b(2, 3, 4);
	//vec::view(a+b);
	vec::view(a/b);
	return 0;
	}
