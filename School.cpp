#include <iostream>
#include <cstring>
#include "School.h"

using namespace std;

//////////Student//////////
Student::Student(string name, int floorNo, int classNo, string pos) 
    : name(name), floorNo(floorNo), classNo(classNo), pos("Outside of School") {

    cout << "A New Student has been created!\n\t\t\t->" << name 
        << "FloorNo:" << floorNo << " ClassNo:" << classNo << endl;
}

Student::~Student(){
    cout << "A Student to be destroyed!\t->" << name << "\n"
            << "FloorNo:" << floorNo << " ClassNo:" << classNo 
                << " Current position:" << pos << endl;
}

string Student::get_name() const{
    return name;
}

int Student::get_floorNo() const{
    return floorNo;
}

int Student::get_classNo() const{
    return classNo;
}

void Student::set_pos(string pos){
    this->pos = pos;
}

void Student::print() const{
    cout << name << endl;
}

//////////Teacher//////////
Teacher::Teacher(string name, int floorNo, int classNo, bool inClass)
    : name(name), floorNo(floorNo), classNo(classNo), inClass(false){
        cout << "A New Teacher has been created!\n\t\t\t" << name
            << "FloorNo:" << floorNo << " ClassNo:" << classNo << endl;
}

Teacher::~Teacher(){
    cout << "A Teacher to be destroyed!\t->" << name << "\n"
        << "FloorNo:" << floorNo << " ClassNo:" << classNo << endl;
}

string Teacher::get_name() const{
    return name; 
}

int Teacher::get_floorNo() const{
    return floorNo;
}

int Teacher::get_classNo() const{
    return classNo;
}

bool Teacher::set_inClass(){
    this->inClass = true; 
}

void Teacher::print() const{
    cout << "The teacher is: " << name << "\n" << endl;
}

//////////Yard//////////
Yard::Yard(int Cyard) : Cyard(Cyard){ 
    students = new Student*[Cyard];
    cout << "A New Schoolyard has been created!" << endl;
}

Yard::~Yard(){
    cout << "A Schoolyard to be destroyed!" << endl;
    delete[] students;
}

int Yard::get_counter() const{
    return counter;
}

void Yard::enter(Student* student){
    if(counter < Cyard){
        students[counter] = student;
        counter++;
        cout << "\n" << student->get_name() << "\t\t" << " enters school!" << endl;
        cout << student->get_name() << "\t\t" << " enters schoolyard!" << endl;
        student->set_pos("Schoolyard");
    }
    else{
        student->set_pos("Outside of school");
    }    
}

void Yard::exit(Student* student){
    cout << student->get_name() << "\t\t" << " exits schoolyard!" << endl;
    counter--;
    students[counter] = nullptr;
}

void Yard::print() const{
    cout << "People in schoolyard are: " << endl;
    for(int i = 0; i < counter; i++){
        students[i]->print();
    }
    cout << "\n";
}

//////////Stairs//////////
Stairs::Stairs(int Cstairs) : Cstairs(Cstairs){
    students = new Student*[Cstairs];
    cout << "New Stairs have been created!" << endl;
}

Stairs::~Stairs(){
    cout << "Stairs to be destroyed!" << endl;
    delete[] students;
}

int Stairs::get_counter() const{
    return counter;
}

void Stairs::enter(Student* student){
    if(counter < Cstairs){
        students[counter] = student;
        counter++;
        student->set_pos("Stairs");
        cout << student->get_name() << "\t\t" << " enters stairs!" << endl;
    }
    else{
        student->set_pos("Schoolyard");
    }
}

void Stairs::exit(Student* student){
    cout << student->get_name() << "\t\t" << " exits stairs!" << endl;
    counter--;
    students[counter] = nullptr;
}

void Stairs::print() const{
    cout << "People in stairs are: " << endl;
    for(int i = 0; i < counter; i++){
        students[i]->print();
    }
    cout << "\n";
}

//////////Corridor//////////
Corridor::Corridor(int Ccorr) : Ccorr(Ccorr){
    students = new Student*[Ccorr];
    cout << "A New Corridor has been created!" << endl;
}

Corridor::~Corridor(){
    cout << "A Corridor to be destroyed!" << endl;
    delete[] students;
}

int Corridor::get_counter() const{
    return counter;
}

void Corridor::enter(Student* student){
    if(counter < Ccorr){
        students[counter] = student;
        counter++;
        cout << student->get_name() << "\t\t" << " enters corridor!" << endl;
        student->set_pos("Corridor");            
    }
    else{
        student->set_pos("Stairs");
    }
}

void Corridor::exit(Student* student){
    cout << student->get_name() << "\t\t" << " exits corridor!" << endl;
    counter--;
    students[counter] = NULL;
}

void Corridor::print() const{
    cout << "People in corridor are: " << endl;
    for(int i = 0; i < counter; i++){
        students[i]->print();
    }
    cout << "\n";
}

//////////Classroom//////////
Classroom::Classroom(int Cclass, int classNo, int floorNo, bool inClass) 
    : Cclass(Cclass), classNo(classNo), floorNo(floorNo), inClass(false){
        students = new Student*[Cclass];
        teacher = NULL;
        cout << "A New Classroom has been created!" << endl;
}

Classroom::~Classroom(){
    cout << "A Classroom to be destroyed!" << endl;
    delete[] students;
    teacher = NULL;
    delete teacher;
}

int Classroom::get_classNo() const{
    return classNo;
}

int Classroom::get_counter() const{
    return counter;
}

bool Classroom::get_inClass() const{
    return inClass;
}

void Classroom::enter(Student* student){
    students[counter] = student;
    counter++;
    cout << student->get_name() << "\t\t" << " enters classroom!" 
        << "No: " << classNo << endl;
    student->set_pos("Classroom");
}

void Classroom::set_teacher(Teacher* teacher){
    this->teacher = teacher;
    teacher->set_inClass();
    inClass = true;
}

void Classroom::place(Teacher* teacher){
    set_teacher(teacher);
}

void Classroom::print() const{
    cout << "People in classroom " << classNo << " are:" << endl;
    for(int i = 0; i < counter; i++){
        students[i]->print();
    }
    cout << "\n";
    if(teacher != NULL){  //Check if the classroom has a teacher
        cout << "The teacher is: " << teacher->get_name() << "\t\t\n" << endl;
    }
}

//////////Floor//////////
Floor::Floor(int Cclass, int Ccorr, int floorNo) 
    : Cclass(Cclass), Ccorr(Ccorr), floorNo(floorNo){
        this->corridor = new Corridor(Ccorr);
        for(int i = 0; i < 6; i++){  //I want 6 classrooms for each floor
            classes[i] = new Classroom(Cclass, (i+1), floorNo, false);  //But i don't want a classroom with number 0
        }
        cout << "A New Floor has been created!" << endl;
}

Floor::~Floor(){
    cout << "A Floor to be destroyed!" << endl;
    for(int i = 0; i < 6; i++){
        delete classes[i];
    }
    delete corridor;
}

int Floor::get_floorNo() const{
    return floorNo;
}

int Floor::get_counter() const{
    return corridor->get_counter();
}

void Floor::enter(Student* student){
    counter = corridor->get_counter();
    if(counter < Ccorr){  //Condition for student to enter floor
        cout << student->get_name() << "\t\t" << " enters floor!" << "No: " << floorNo << endl;
        corridor->enter(student);
        for(int i = 0; i < 6; i++){
            if(student->get_classNo() == classes[i]->get_classNo()){  //Student must enter correct classroom
                if(classes[i]->get_counter() < Cclass){ //If classroom isn't full
                    if(classes[i]->get_inClass() == false){ //If the teacher hasn't arrived yet
                        corridor->exit(student);
                        classes[i]->enter(student);
                    }
                    else{
                        cout << "Teacher already in classroom!" << endl;
                    }
                }
            }
        }
    }
}

void Floor::place(Teacher* teacher){
    int classNo = teacher->get_classNo();
    classes[classNo-1]->place(teacher); //classes[0] has classNo: 1
}

void Floor::print() const{
    cout << "Floor number " << floorNo << " contains: " << endl;
    corridor->print();
    for(int i = 0; i < 6; i++){
        classes[i]->print();
    }
}

//////////School//////////
School::School(int Cclass, int Cyard, int Cstairs, int Ccorr) 
    : Cclass(Cclass), Cyard(Cyard), Cstairs(Cstairs), Ccorr(Ccorr){
        this->yard = new Yard(Cyard);
        counter = this->yard->get_counter();
        this->stairs = new Stairs(Cstairs);
        for(int i = 0; i < 3; i++){  //I want to make 3 floors
            floors[i] = new Floor(Cclass, Ccorr, (i+1));  //But i don't want a floor with number 0
        }
        cout << "A New School has been created!" << endl;
}

School::~School(){
    for(int i = 0; i < 3; i++){
        delete floors[i];
    }
    delete stairs;
    delete yard;       
    cout << "A School to be destroyed!" << endl;
}

int School::get_counter() const{
    return counter;
}

void School::place(Teacher* teacher){
    int floorNo = teacher->get_floorNo();
    floors[floorNo-1]->place(teacher);  //floors[0] has floorNo: 1
}

void School::single_enter(Student* student){
    if(counter < Cyard){  //If schoolyard isn't full
        yard->enter(student);
        if(stairs->get_counter() < Cstairs){  //If stairs aren't full
            yard->exit(student);
            stairs->enter(student);
            for(int i = 0; i < 3; i++){ //For every floor
                if(floors[i]->get_counter() < Ccorr){  //If corridor isn't full
                    if(student->get_floorNo() == floors[i]->get_floorNo()){  //Student must enter the correct floor
                        stairs->exit(student);
                        floors[i]->enter(student);
                    }
                }
            }
        }
    }
}

void School::multi_enter(Student** students, int size){
    if(size <= Cyard){  //As many as possible
        for(int i = 0; i < size; i++){
            single_enter(students[i]);
        }
    }
    else{
        for(int i = 0; i < Cyard; i++){  //As many as possible
            single_enter(students[i]);
        }
    }
}

void School::print() const{
    cout << "\nSchool life consists of: " << endl;
    yard->print();
    stairs->print();
    for(int i = 0; i < 3; i++){
        floors[i]->print();
    }
}
