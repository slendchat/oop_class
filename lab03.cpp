#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;


enum compare_signs
{
  EQUAL,
  NOT_EQUAL,
  MORE,
  LESS
};
enum class Priority
{
  LOW,
  MEDIUM,
  HIGH
};

class Assignment
{
protected:
  Priority priority = Priority::MEDIUM;

public:

  Priority get_priority() const{
    return priority;
  }

  void set_priority(Priority priority){
    this->priority = priority;
  }
};

class Task
{
public:
  
    virtual void display() = 0;
    virtual bool iscompleted() = 0; 
    virtual void mark_done() = 0;

};

class Task_item : public Task, public Assignment
{
  string title;
  string description;
  bool completed;
public:

  friend bool compare_tasks(Task_item task1, Task_item task2, compare_signs sign);

  Task_item(string title, string description){
    this->title = title;
    this->description = description;   
    completed = false;
  }


  void display(){
    cout<<"Task title: "<<title<<endl;
    cout<<"Task description: "<<description<<endl;
    return;
  } 

  bool iscompleted(){
    return completed;
  }

  void mark_done(){
    completed = true;
    return;
  }

  bool operator == (const Task_item& task) const{
    return get_priority() == task.get_priority();
  }
  bool operator != (const Task_item& task) const{
    return get_priority() != task.get_priority();
  }
  bool operator > (const Task_item& task) const{
    return get_priority() > task.get_priority();
  }
    bool operator < (const Task_item& task) const{
    return get_priority() < task.get_priority();
  }

};

class Note : public Assignment
{
public:
  string content;

  Note(string content){
    this->content = content;
  }

  friend bool compare_notes(Note note1, Note note2, compare_signs sign);

  bool operator == (const Note& note) const{
    return get_priority() == note.get_priority();
  }
  bool operator != (const Note& note) const{
    return get_priority() != note.get_priority();
  }
  bool operator > (const Note& note) const{
    return get_priority() > note.get_priority();
  }
    bool operator < (const Note& note) const{
    return get_priority() < note.get_priority();
  }
   
};

class Task_list
{

  static inline int tasks_count; 

public:

  vector<Task_item> tasks;
  vector<Note> notes;
  
  void add_task(Task_item task){
    tasks.emplace_back(task);
    tasks_count++;
  } 
  void add_note(Note note){
    notes.emplace_back(note);
  }
  void display_all(){
    for(auto task: tasks){
      task.display();
      cout<<endl;
    }
    for(auto note: notes){
      cout<<note.content<<endl;
      cout<<endl;
    }
  }
  Task_item get_task(int index){

    return tasks[index];

  }
  Note get_note(int index){
    
    return notes[index];
    
  }

  static void show_amount_tasks(){
    cout<<Task_list::tasks_count<<endl;
  }

};



bool compare_tasks(Task_item task1, Task_item task2, compare_signs sign)
{
  switch (sign){
  case EQUAL:
    return task1.priority == task2.priority;
  case NOT_EQUAL:
    return task1.priority != task2.priority;
  case LESS:
    return task1.priority < task2.priority;
  case MORE:
    return task1.priority > task2.priority;
  default:
    return 0;
  }
}

bool compare_notes(Note note1, Note note2, compare_signs sign)
{
  switch (sign){
  case EQUAL:
    return note1.priority == note2.priority;
  case NOT_EQUAL:
    return note1.priority != note2.priority;
  case LESS:
    return note1.priority < note2.priority;
  case MORE:
    return note1.priority > note2.priority;
  default:
    return 0;
  }
}


int main()
{
  Task_list mylist;
  char choice = '\0';

menu:
  cin>>choice;
      string title;
      string description;
      string note_content;
  switch(choice){
    case '1':
      cin>>title;
      cin>>description;
      mylist.add_task(Task_item(title, description));
    break;
    case '2':
      cin>>note_content;
      mylist.add_note(Note(note_content));
    break;
    case '3':
      mylist.display_all();
    break;
    case '4':
      compare_tasks(mylist.get_task(0), mylist.get_task(1), EQUAL);
    break;
    case '5':
      cout<< (mylist.get_task(0) != mylist.get_task(1))<<endl; 
    case '6':
      return 0;

  goto menu;

}