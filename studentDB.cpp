//
// Created by Jose Guerrero on 1/30/20.
//


#include <string>
#include <vector>
#include "studentDB.h"
#include "math.h"

namespace cop3530 {

    student_info::student_info() {
        name = "default";
        gpa = 0.0;
    }
    student_info::student_info(std::string name, double gpa) : name(name), gpa(gpa) {
        this->name = name;
        this->gpa = gpa;

    }

    std::string student_info::get_name() const {
        return name;
    }

    double student_info::get_gpa() const {
        return gpa;
    }

    bool student_info::operator==(const student_info& other) const {
        return name == other.name && abs(gpa - other.gpa) < 0.000000001;
    }

    student_db::student_db() {






    }

    student_db::~student_db() {

    }

    void student_db::insert(const int student_id, const std::string& student_name, const double gpa) {
        student_info insertThisStudent(student_name, gpa);
        myBst.insert(student_id, insertThisStudent);
    }

    void student_db::erase(const int student_id) {
        myBst.erase(student_id);

    }

    student_info& student_db::lookup(const int student_id) {


        return  myBst.at(student_id);

    }

    bool student_db::empty() const {
        return myBst.empty();
    }

    size_t student_db::size() const {
        return myBst.size();
    }

    std::vector<std::pair<int, student_info>> student_db::get_all_students() {


        return  myBst.inorder_contents();
    }

}