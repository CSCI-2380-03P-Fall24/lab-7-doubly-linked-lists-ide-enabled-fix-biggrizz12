#include "StudentList.h"
#include <iostream>
using namespace std;

// constructor
StudentList::StudentList() {
    head = nullptr;
    tail = nullptr;
    numStudents = 0;
}

// return number of students
int StudentList::listSize() {
    return numStudents;
}

// add to front
void StudentList::addFront(Student s) {
    Node* newNode = new Node;
    newNode->data = s;
    newNode->prev = nullptr;
    newNode->next = head;

    if (head != nullptr)
        head->prev = newNode;
    else
        tail = newNode;

    head = newNode;
    numStudents++;
}

// add to back
void StudentList::addBack(Student s) {
    Node* newNode = new Node;
    newNode->data = s;
    newNode->next = nullptr;
    newNode->prev = tail;

    if (tail != nullptr)
        tail->next = newNode;
    else
        head = newNode;

    tail = newNode;
    numStudents++;
}

// print list
void StudentList::printList() {
    Node* curr = head;

    while (curr != nullptr) {
        cout << curr->data.getName() << endl;
        curr = curr->next;
    }
}

// remove last
void StudentList::popBack() {
    if (tail == nullptr) {
        cout << "List is empty\n";
        return;
    }

    Node* temp = tail;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete temp;
    numStudents--;
}

// remove first
void StudentList::popFront() {
    if (head == nullptr) {
        cout << "List is empty\n";
        return;
    }

    Node* temp = head;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }

    delete temp;
    numStudents--;
}

// insert at index
void StudentList::insertStudent(Student s, int index) {

    if (index <= 0) {
        addFront(s);
        return;
    }

    if (index >= numStudents) {
        cout << "Index out of range, inserting at back\n";
        addBack(s);
        return;
    }

    Node* curr = head;

    for (int i = 0; i < index; i++)
        curr = curr->next;

    Node* newNode = new Node;
    newNode->data = s;

    newNode->prev = curr->prev;
    newNode->next = curr;

    curr->prev->next = newNode;
    curr->prev = newNode;

    numStudents++;
}

// retrieve student by id
Student StudentList::retrieveStudent(int idNum) {

    Node* curr = head;

    while (curr != nullptr) {

        if (curr->data.getId() == idNum)
            return curr->data;

        curr = curr->next;
    }

    cout << "Student not found\n";

    Student dummy;
    return dummy;
}

// remove student by id
void StudentList::removeStudentById(int idNum) {

    Node* curr = head;

    while (curr != nullptr) {

        if (curr->data.getId() == idNum) {

            if (curr == head)
                popFront();
            else if (curr == tail)
                popBack();
            else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
                numStudents--;
            }

            return;
        }

        curr = curr->next;
    }

    cout << "Student not found\n";
}

// update GPA
void StudentList::updateGPA(int idNum, float newGPA) {

    Node* curr = head;

    while (curr != nullptr) {

        if (curr->data.getId() == idNum) {
            curr->data.setGPA(newGPA);
            return;
        }

        curr = curr->next;
    }

    cout << "Student not found\n";
}

// merge lists
void StudentList::mergeList(StudentList &otherList) {

    if (otherList.head == nullptr)
        return;

    if (head == nullptr) {
        head = otherList.head;
        tail = otherList.tail;
    }
    else {
        tail->next = otherList.head;
        otherList.head->prev = tail;
        tail = otherList.tail;
    }

    numStudents += otherList.numStudents;

    otherList.head = nullptr;
    otherList.tail = nullptr;
    otherList.numStudents = 0;
}

// honor roll list
StudentList StudentList::honorRoll(float minGPA) {

    StudentList result;

    Node* curr = head;

    while (curr != nullptr) {

        if (curr->data.getGPA() >= minGPA)
            result.addBack(curr->data);

        curr = curr->next;
    }

    return result;
}

// remove students below GPA
void StudentList::removeBelowGPA(float threshold) {

    if (head == nullptr) {
        cout << "List is empty\n";
        return;
    }

    Node* curr = head;

    while (curr != nullptr) {

        Node* nextNode = curr->next;

        if (curr->data.getGPA() < threshold)
            removeStudentById(curr->data.getId());

        curr = nextNode;
    }
}