#include <iostream>
#include <cstring>

using namespace std;

class Student{
    private:
        string name;
        int floorNo;
        int classNo;
        string pos;
    public:
        Student(string name, int floorNo, int classNo, string pos);
        ~Student();
        
        string get_name() const;
        int get_floorNo() const;
        int get_classNo() const;
        void set_pos(string pos);
        void print() const;
};

class Teacher{
    private:
        string name;
        int floorNo;
        int classNo;
        bool inClass;
    public:
        Teacher(string name, int floorNo, int classNo , bool inClass);
        ~Teacher();
        
        string get_name() const;
        int get_floorNo() const;
        int get_classNo() const;
        bool set_inClass();
        void print() const;
};

class Yard{
    private:
        int Cyard;
        int counter = 0;  //Counts number of students already in Yard
        Student** students;
    public:
        Yard(int Cyard);
        ~Yard();

        int get_counter() const;
        void enter(Student* student);
        void exit(Student* student);
        void print() const;
};

class Stairs{
    private:
        int Cstairs;
        int counter = 0;  //Counts number of students already in Stairs
        Student** students;
    public:
        Stairs(int Cstairs);
        ~Stairs();

        int get_counter() const;
        void enter(Student* student);
        void exit(Student* student);
        void print() const;
};

class Corridor{
    private:
        int Ccorr;
        int counter = 0;  //Counts number of students already in Corridor
        Student** students;
    public:
        Corridor(int Ccorr);
        ~Corridor();

        int get_counter() const;
        void enter(Student* student);
        void exit(Student* student);
        void print() const;
};

class Classroom{
    private:
        int Cclass;
        int classNo;
        int floorNo;
        int counter = 0;  //Counts number of students already in Classroom
        bool inClass;
        Student** students;
        Teacher* teacher;
    public:
        Classroom(int Cclass, int classNo, int floorNo, bool inClass);
        ~Classroom();

        int get_classNo() const;
        int get_counter() const;
        bool get_inClass() const;
        void set_teacher(Teacher* teacher);
        void enter(Student* student);
        void place(Teacher* teacher);
        void print() const;
};

class Floor{
    private:
        int Cclass;        
        int Ccorr;
        int floorNo;
        int counter = 0;  //Floor has no capacity, I will assign corridor's counter
        Corridor* corridor;
        Classroom* classes[6];
    public:
        Floor(int Cclass, int Ccorr, int floorNo);
        ~Floor();
        
        int get_floorNo() const;
        int get_counter() const;
        void place(Teacher* teacher);
        void enter(Student* student);
        void print() const;
};

class School{
    private:
        int Cyard;
        int Cstairs;
        int Cclass;
        int Ccorr;
        int counter = 0;  //School has no capacity, I will assign Yard's counter
        Yard* yard;
        Stairs* stairs;
        Floor* floors[3];
    public:
        School(int Cyard, int Cstairs, int Cclass, int Ccorr);
        ~School();
        
        int get_counter() const;
        void place(Teacher* teacher);
        void single_enter(Student* student);
        void multi_enter(Student** students, int size);
        void print() const;
};