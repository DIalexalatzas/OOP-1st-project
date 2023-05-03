#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include "stdlib.h"
#include "School.cpp"

using namespace std;

void swap(Student** s1, Student** s2){  //Swap function for pointers
    Student* swap = *s1;
    *s1 = *s2;
    *s2 = swap;
}

//////////main//////////
int main(int argc, char** argv){  //I assign the capacities given by the command line
    int Cclass = atoi(argv[1]);
    int Cyard = atoi(argv[2]);
    int Cstairs = atoi(argv[3]);
    int Ccorr = atoi(argv[4]);
    int studcnt = Cclass * 18;  //Total number of students
    int no_to_destroy = studcnt; //Save the value to free later the memory
    int teachcnt = 0;  //Total number of teachers
    int floorNo = 1;  //Used to create students' and teachers' info properly
    int randteach = 0;  //Used to enter a random teacher out of the 18
    srand(time(NULL));
//////////Creation of School//////////
    School school(Cclass, Cyard, Cstairs, Ccorr);

//////////Creation of a names list//////////
    string nameslist[400];  //I get a list of name from a .txt file
    ifstream inFile;
    inFile.open("names.txt");
    if(inFile.is_open()){
        for(int i = 0; i < 400; i++){
            getline(inFile, nameslist[i]);
        }
        inFile.close();
    }
    else{
        cout << "Error opening file";
    }

//////////Creation of teachers//////////
    cout << "--------------------" << endl;
    cout << "Creation of teachers" << endl;
    cout << "--------------------" << endl;
    Teacher** teachers;
    teachers = new Teacher*[18];
    while(teachcnt < 18){
        for(int classNo = 0; classNo < 6; classNo++){
            teachers[teachcnt] = new Teacher(nameslist[teachcnt], floorNo, (classNo + 1), false);
            teachcnt++;
        }
        if (teachcnt % 6 == 0){  //For every 6 teachers created, move up one floor
            floorNo++;
        }
    }
    floorNo = 1;  //Floor number again equals to 1 to properly create students as well
    cout << "Teachers created: " << teachcnt << endl;
    cout << "--------------------" << endl;

//////////Creation of students//////////
    cout << "Creation of students" << endl;
    cout << "--------------------" << endl;
    Student** students;
    students = new Student*[studcnt];
    for(int i = 0; i < studcnt; ){
        for(int classNo = 1; classNo <= 6; classNo++){
            students[i] = new Student(nameslist[i+18], floorNo, classNo, "outside of school");
            i++;
        }
        if (studcnt % 6 == 0){  //For every 6 students created, move up one floor
            floorNo++;
            if (floorNo == 4) floorNo = 1; //If all students are created for the 3rd floor
        }                                 //Go back to 1st floor and create more
    }   
    cout << "--------------------" << endl;
    cout << "Students created: " << studcnt << endl;
    
///////////////////////main loop//////////////////
    

    for(int k = 0; k < studcnt; k++){ //Shuffle array of students
        int i = rand() % studcnt;
        int j = rand() % studcnt;
        swap(students[i], students[j]);
    }
    for(int k = 0; k < teachcnt; k++){ //Shuffle array of teachers
        int i = rand() % teachcnt;
        int j = rand() % teachcnt;
        swap(teachers[i], teachers[j]);
    }
    int start = Cyard;  //Assign the capacity of yard to an integer in order to enter students
    school.multi_enter(students, studcnt);  //At first enter as many as possible
    studcnt -= start;
    while(studcnt >= 0){  //While there are students to enter
        int coin = rand() % 2;
        if(start == no_to_destroy) break;  //no_to_destroy is the total number of students
        if(coin == 1 && teachcnt > 0){
            school.place(teachers[randteach]);
            randteach++;
            teachcnt--;
        }
        school.single_enter(students[start]);  //Enter the next student
        start++;
        studcnt--;
    }
    

    school.print();
//////////Free memory//////////
    cout << "Destruction of students" << endl;
    cout << "--------------------" << endl;
    for(int i = 0; i < no_to_destroy; i ++){
        delete students[i];
    }
    delete[] students;
    cout << "--------------------" << endl;

    cout << "Destruction of teachers" << endl; 
    cout << "--------------------" << endl;
    for(int i = 0; i < 18; i ++){
        delete teachers[i];
    }
    delete[] teachers;
    cout << "--------------------" << endl;

    return 0;
}