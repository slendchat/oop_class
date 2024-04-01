#include <iostream>

class Side
{
public:
  int side_len;
};

class Square :public Side
{
public:
  Square(int side_len){
    this->side_len = side_len;
  }
  int calc_area(){
    return side_len*side_len;
  }
};

class Cube :public Square
{
public:
  int wall_thickness;
  Cube(int side_len, int wall_thickness=0) : Square(side_len){
    this->wall_thickness = wall_thickness;
  };
  int calc_volume(){
    if(wall_thickness==0){
      return side_len*side_len*side_len;
    }
    return side_len*side_len*side_len - (side_len-2*wall_thickness)*(side_len-2*wall_thickness)*(side_len-2*wall_thickness);
  }

};

void fill_bigger_cube(Cube cube1, Cube cube2)
{
  std::cout<<cube1.calc_volume()<<std::endl;
  std::cout<<cube2.calc_volume()<<std::endl;
  float fill_times = float(cube1.calc_volume()) / float(cube2.calc_volume());
  std::cout<<"you have to fill bigger cube "<<fill_times<<" times"<<std::endl;
}

int main()
{
  Cube cube1(10);
  Cube cube2(20,2);
  if(cube1.calc_volume() > cube2.calc_volume()){
    std::cout<<"cube1 > cube2"<<std::endl;
    fill_bigger_cube(cube1, cube2);
  }
  else if (cube1.calc_volume() < cube2.calc_volume()){
    std::cout<<"cube2 > cube1"<<std::endl;
    fill_bigger_cube(cube2, cube1);
  }
  else{
    std::cout<<"cube2 = cube1"<<std::endl;
    std::cout<<"you have to fill bigger cube 1 time"<<std::endl;
  }

}