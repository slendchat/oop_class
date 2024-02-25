#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Car
{
private:
  string manufacturer;
  string owner;
  int year;
  int cost;
public:
  Car(){
    manufacturer = "none";
    owner = "none";
    year = 0;
    cost = 0;
  }
  Car(string manufacturer, string owner, int year, int cost){
    this->manufacturer = manufacturer;
    this->owner = owner;
    this->year = year;
    this->cost = cost;  
  }
  ~Car(){
    this->cost=0;
    this->manufacturer.clear();
    this->owner.clear();
    this->year=0;
  }

  string get_manufacturer(){
      return this->manufacturer;
  }

  void set_manufacturer(string manufacturer) {
      this->manufacturer = manufacturer;
  }

  string get_owner(){
      return this->owner;
  }

  void set_owner(string owner) {
      this->owner = owner;
  }

  int get_year(){
      return this->year;
  }

  void set_year(int year) {
      this->year = year;
  }

  int get_cost(){
      return this->cost;
  }

  void set_cost(int cost) {
      this->cost = cost;
  }
  
  void show_car_data(){
    cout<<"manufacturer: "<<manufacturer<<" owner: "<<owner<<" year: "<<year<<" cost: "<<cost<<endl;
  }
};

  bool compare_year(Car& car1, Car& car2)
  {
    return car1.get_year() < car2.get_year();
  }

void add_car(vector<Car>& car_arr)
{
  string manufacturer;
  string owner;
  int year;
  int cost;

  cout<<"Enter car data:\n";
  cout<<"car manufacturer: ";
  cin>>manufacturer;
  cout<<"car owner: ";
  cin>>owner;
  cout<<"car year of assembly: ";
  cin>>year;
  cout<<"car cost: ";
  cin>>cost;
  cout<<endl;
  car_arr.emplace_back(manufacturer,owner,year,cost);
}

void print_cars(vector<Car>& car_arr)
{
  for(Car car:car_arr)
    car.show_car_data();
}

void sort_year(vector<Car>& car_arr)
{
  sort(car_arr.begin(),car_arr.end(),compare_year);
}

void cost_less(int cost, vector<Car>& car_arr)
{
  for(Car car:car_arr){
    if (car.get_cost() < cost){
      car.show_car_data();
    }
  }
}

void add_after(vector<Car>& car_arr, string manufacturer,string owner,int year,int cost)
{
  int i=0;
  for (i; i < car_arr.size(); i++){
    if ("none"!=car_arr[i].get_owner()){
      break;
    }
  }
  if (i == car_arr.size()-1){
    return;
  }

  auto iterator = next(car_arr.begin(),i+1);

  car_arr.emplace(iterator,manufacturer,owner,year,cost);
  
}

void clear_expensive(vector<Car>& car_arr)
{
  int cost=0;
  vector<Car>::iterator iter = car_arr.begin();

  for(int i=0; i < car_arr.size();i++){
    if (cost<car_arr[i].get_cost()){
      cost = car_arr[i].get_cost();
      iter = next(car_arr.begin(),i);
    }
  }
  car_arr.erase(iter);
}

void writefile(vector<Car>& car_arr, string file_name) {
    ofstream file(file_name);
    if (file.is_open()) {
        for (Car car:car_arr) {
            file << car.get_manufacturer() << " "
                 << car.get_owner() << " "
                 << car.get_year() << " "
                 << car.get_cost() <<endl;
        }
        file.close();
    } 
    else{
        cout << "cannot open the file for writing." << endl;
    }
}

void print_manufactured(vector<Car>& car_arr, string file_name)
{
  ifstream file(file_name);
  string line;
  string manufacture;

  if (file.is_open()){
    while (getline(file,line)){
      manufacture = line.substr(0,line.find_first_of(" "));
      if (manufacture != "none"){
        cout<<line<<endl;
      }      
    }
  }
  
  file.close();
}

int main()
{
  string out_file = "output.txt";
  vector<Car> car_arr(2);

  string manufacturer;
  string owner;
  int year;
  int cost;
  int cost_compare;
  
  int choice;
  do{
  cout << "Выберите действие:" << endl;
  cout << "1. Ввести элементы массива с клавиатуры" << endl;
  cout << "2. Вывести на экран элементы массива (объекты)" << endl;
  cout << "3. Сортировать по возрастанию по полю Год производства" << endl;
  cout << "4. Вывести на экран элементы, для которых известно что Цена меньше чем х" << endl;
  cout << "5. Добавить новый элемент после того, для которого известно Имя владельца" << endl;
  cout << "6. Удалить элементы, у которых наибольшая Цена" << endl;
  cout << "7. Записать элементы массива в файл" << endl;
  cout << "8. Вывести на экран элемент, для которого известна Марка из файла" << endl;
  cout << "9. Выйти из программы" << endl;
  cout << "Введите номер действия (1-8): ";
  cin >> choice;

switch (choice) {
    case 1:
        cout << "Выбрано: 1. Ввести элементы массива с клавиатуры" << endl;
        add_car(car_arr);
        break;
    case 2:
        cout << "Выбрано: 2. Вывести на экран элементы массива (объекты)" << endl;
        print_cars(car_arr);
        break;
    case 3:
        cout << "Выбрано: 3. Сортировать по возрастанию по полю Год производства" << endl;
        sort_year(car_arr);
        break;
    case 4:
        cout << "Выбрано: 4. Вывести на экран элементы, для которых известно что Цена меньше чем (введите х):" << endl;
        cin>>cost_compare;
        cost_less(cost_compare,car_arr);
        break;
    case 5:
        cout << "Выбрано: 5. Добавить новый элемент после того, для которого известно Имя владельца" << endl;
          cout<<"Enter car data:\n";
          cout<<"car manufacturer: ";
          cin>>manufacturer;
          cout<<"car owner: ";
          cin>>owner;
          cout<<"car year of assembly: ";
          cin>>year;
          cout<<"car cost: ";
          cin>>cost;
          cout<<endl;
        add_after(car_arr,manufacturer,owner,year,cost);
        break;
    case 6:
        cout << "Выбрано: 6. Удалить элементы, у которых наибольшая Цена" << endl;
        clear_expensive(car_arr);
        break;
    case 7:
        cout << "Выбрано: 7. Записать элементы массива в файл" << endl;
        writefile(car_arr,out_file);
        break;
    case 8:
        cout << "Выбрано: 8. Вывести на экран элемент, для которого известна Марка из файла" << endl;
        print_manufactured(car_arr,out_file);
        break;
    case 9:
        cout<<"выход"<<endl;
    break;
    default:
        cout << "Некорректный ввод. Пожалуйста, выберите действие от 1 до 8." << endl;
        break;
}
  }while(choice!=9);

  return 0;
}