//
// Created by Jose Guerrero on 1/30/20.
//
#pragma once
#ifndef SUDENT_STUDENTDB_H
#define SUDENT_STUDENTDB_H


#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include "bst.h"




namespace cop3530 {

    class student_info {
        std::string name;
        double gpa;

    public:
        student_info();
        student_info(std::string name, double gpa);
        std::string get_name() const;
        double get_gpa() const;
        bool operator==(const student_info& other) const;

    };

    class student_db {
        // your bst
        cop3530::bst<int, student_info> myBst;

    public:
        student_db();
        ~student_db();
        void insert(const int student_id, const std::string& student_name, const double gpa);
        void erase(const int student_id);
        student_info& lookup(const int student_id);
        bool empty() const;
        size_t size() const;
        std::vector<std::pair<int, student_info>> get_all_students();
    };

}


#endif //SUDENT_STUDENTDB_H
