
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Record {
    string name;
    int ID;
    string major;
    int hours;
    double GPA;
    string status;
    Record(string name, int ID, string major, int hours, double GPA, string status) {
        this->name = name;
        this->ID = ID;
        this->major = major;
        this->hours = hours;
        this->GPA = GPA;
        this->status = status;
    }
};

// Returns the average GPA of a list of records
double gpaAverage(vector<Record> list) {
    double sum = 0;
    for (int i = 0; i < list.size(); i++) {
        sum += list[i].GPA;
    }
    return sum / list.size();
}

int main() {
    
    // Hash Map with full names of major abbreviations
    unordered_map<string, string> fullMajorNameFor;
    fullMajorNameFor["CS"] = "Computer Science";
    fullMajorNameFor["MATH"] = "Mathematics";
    fullMajorNameFor["BADMIN"] = "Business Administration";
    fullMajorNameFor["IT"] = "Industrial Technology";
    fullMajorNameFor["CHEM"] = "Chemistry";
    fullMajorNameFor["BIOLG"] = "Biology";
    
    // Hash Map to store list of records grouped according to thier majors
    unordered_map<string, vector<Record>> listOfRecordsFor;
    
    fstream in;
    string line;
    in.open("data.in");
    
    while (!in.eof()) {
        string word;
        vector<string> listOfWords;
        
        getline(in, line);
        
        // Splits the string line into words
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ' ') {
                listOfWords.push_back(word);
                word = "";
            }
            else {
                word += line[i];
            }
        }
        listOfWords.push_back(word);
        
        // Convert to appropriate data type as in the struct record
        string name = listOfWords[0] + " " + listOfWords[1];
        int ID = stoi(listOfWords[2]);
        string major = listOfWords[3];
        int hours = stoi(listOfWords[4]);
        double GPA = stod(listOfWords[5]);
        string status = listOfWords[6];
        
        Record studentInfo(name, ID, major, hours, GPA, status);
        
        major = fullMajorNameFor[major];
        
        listOfRecordsFor[major].push_back(studentInfo);
    }
    
    // Displays and writes into 'student.dat' list of records for each major in 'data.in
    // Calculates and displays average GPA and total number of students for each major
    fstream out;
    out.open("student.txt");
    
    for (auto x : listOfRecordsFor) {
        cout << "---------------------------------------------------------------" << endl;
        out << "---------------------------------------------------------------" << endl;
        
        cout << "\t\t\t" << x.first << "\n\n";
        out << "\t\t\t" << x.first << "\n\n";
        
        for (int i = 0; i < x.second.size(); i++) {
            cout << x.second[i].name << " " << x.second[i].ID << " " << x.second[i].major << " " << x.second[i].hours << " " << x.second[i].GPA << " " << x.second[i].status << endl;
            
            out << x.second[i].name << " " << x.second[i].ID << " " << x.second[i].major << " " << x.second[i].hours << " " << x.second[i].GPA << " " << x.second[i].status << endl;
            
        }
        
        cout << endl;
        out << endl;
        
        cout << "Average GPA: " << gpaAverage(x.second) << endl;
        out << "Average GPA: " << gpaAverage(x.second) << endl;
        
        cout << "Total number of students: " << x.second.size() << endl;
        out << "Total number of students: " << x.second.size() << endl;
        
        cout << endl;
        out << endl;
    }
    
    out.close();
    
    return 0;
}

