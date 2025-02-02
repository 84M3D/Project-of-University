#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<vector>
#define Red "\033[1;31m"
#define Green "\033[1;32m"
#define Yellow "\033[1;33m"
#define Blue "\033[1;34m"
#define Default "\033[0m"

using namespace std;

fstream openFile(const string& mode);
float avgGrade(string line);
bool checkValid(string studentID);
void addStudent();
void addCourse();
void AcademicRecord();
void searchStudents(int searchType ,bool reportMode);
void listAllStudents();
void AcademicRecord_score(string line);
void sortbyGrade();
void sortbyMajor();
void print(string informations);
void sort(vector<string> &sortline ,int count);

int main(){
    while(true){
    cout<<"\n\n"<<Green<<"Please Choose an Option."<<Default<<"\n";
    cout<<"1.Add a Student Information.\n";
    cout<<"2.Search by Name.\n";
    cout<<"3.Search by ID.\n";
    cout<<"4.List Students.\n";
    cout<<"5.Academic record of a student.\n";
    cout<<Red<<"6.Exit.\n"<<Default;
    cout<<Blue<<"Your choice:";
    int choice;
    cin>>choice;
    cout<<Default;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<Red<<"\nError(Invalid choice)!\nPlease try again.\n"<<Default;
        continue;
    }
    switch(choice){
        case 1: addStudent();
            break;
        case 2: searchStudents(1,false);
            break;
        case 3: searchStudents(2,false);
            break;
        case 4: listAllStudents();
            break;
        case 5: AcademicRecord();
            break;
        case 6: 
            return 0;
        default: cout<<Red<<"\nError(Invalid choice)!\nPlease try again.\n"<<Default;
            break;
    }
    }
}

fstream openFile(const string& mode) {
    fstream students;
    ios_base::openmode fileMode=(mode == "in") ? ios::in : ios::app;
    students.open("students.txt", fileMode);
    if (!students) {
        cout<<Red<<"\nError!.\nFile doesn't exist."<<Default;
        exit(1);
    }
    return students;
}

void addStudent(){
    fstream students = openFile("out");

  string fullName,studentID,major;
  cout<<"Enter the Full Name of The student:";
  cin.ignore();
  getline(cin,fullName);
  bool valid=false;
  while(!valid){
  cout<<"Enter the Student ID:";
  cin>>studentID;
  if(checkValid(studentID)) valid=true;
  else cout<<Red<<"\nThis ID belongs to another student!\nPlease try again and enter a valid ID.\n"<<Default;
  }
  cout<<"Enter the Major of The student:";
   cin.ignore();
  getline(cin,major);
  students<<"!"<<fullName<<"@"<<studentID<<"#"<<major<<"$";
  students.close();
  while(true){
    cout<<"\n1.Adding a course";
    cout<<Red<<"\n2.exit"<<Default;
    cout<<Blue<<"\nYour choice:";
    int choice;
    cin>>choice;
    cout<<Default;
     if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<Red<<"\nError(Invalid choice)!\nPlease try again.\n"<<Default;
        continue;
     }
    switch(choice){
        case 1: addCourse();
            break;
        case 2:students.open("students.txt",ios::app);
            students<<"\n";
            students.close();
            return;
        default: cout<<Red<<"\nError(Invalid choice)!\nPlease try again.\n"<<Default;
            break;
        
    }
  }
  
}

void addCourse(){
    fstream students = openFile("out");

    string courseTitle;
    int courseCredit;
    float Grade;
    cout<<"Enter the Name of Course:";
    cin.ignore();
    getline(cin,courseTitle);
    cout<<"Enter the Course Credit:";
    cin>>courseCredit;
    cout<<"Enter the Grade of "<<courseTitle<<":";
    cin>>Grade;
    students<<courseTitle<<"("<<courseCredit<<")"<<"="<<Grade<<",";
}

void AcademicRecord(){
    fstream students = openFile("in");
    while(true){
        cout<<Green<<"\n\nGive one of the following information about the student.\nChoose one !\n"<<Default;
        cout<<"1.Name of student.\n";
        cout<<"2.ID of student.\n";
        cout<<Red<<"3.Exit.\n"<<Default;
        cout<<Blue<<"Your choice:";
        int choice;
        cin>>choice;
        cout<<Default;
        if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<Red<<"\nError(Invalid choice)!\nPlease try again.\n"<<Default;
        continue;
        }

        switch(choice){
            case 1:  searchStudents(1,true);
                break;
            case 2:  searchStudents(2,true);
                break;
            case 3: students.close();
                return;
            default: cout<<Red<<"\nError(Invalid choice)!\nPlease try again.\n"<<Default;
                break;
        }
    }

}

float avgGrade(string line){
    int i{},j{},count{};
    float avg{};
    string s="",sumCredit="";
    vector<int> Credit;
    vector<float> Grade;


     while(line[i]!='\0'){
     if(line[i]=='('){
        i++;
        while(line[i]!=')'){
    sumCredit+=line[i];
    i++;
    }
    Credit.push_back(stoi(sumCredit));
    sumCredit="";
     }
   i++;
   }


    while(line[j]!='\0'){
        if(line[j]=='='){
        j++;
            while(line[j]!=','){
                s+=line[j];
                j++;
            }
            Grade.push_back(stof(s));
            count++;
            s="";
        }
        j++;
    }

    int sum{};
    for(int k=0;k<count;k++)
        sum+=Credit[k];
    
    for(int k=0;k<count;k++){
        avg+=Credit[k]*Grade[k];
    }
    avg/=sum;
    if(sum<=0) return 0;
    return avg;

}

void searchStudents(int searchType , bool reportMode){
    fstream students = openFile("in");

    string whatWeWant,type=(searchType==2)? "ID":"Name";
    cout<<"Please enter the "<<type<<" of Student:";
    cin.ignore();
    getline(cin,whatWeWant);

    string line;
    bool found=false;
    while(getline(students,line)){
        int i=line.find('@');
        int j=line.find('#');
        string name=line.substr(1,i-1);
        string ID=line.substr(i+1,j-i-1);

        if((searchType==1 && name==whatWeWant) || (searchType==2 && ID==whatWeWant)){
            print(line);
            found=true;

        if(reportMode){
            AcademicRecord_score(line);
            cout<<Red<<"\n**********************************************************************************\n"<<Default;
          }
      }
  }
    if(!found) { cout<<Red<<"No one was found with given ID !\n"<<Default;return;}
}

void listAllStudents(){
    while(true){
    cout<<Green<<"\n\nPlease Choose an Option\n"<<Default;
    cout<<"1.Sorting by Grade. \n";
    cout<<"2.Sorting by Major. \n";
    cout<<Red<<"3.Exit\n"<<Default;
    cout<<Blue<<"Your choice:";
    int choice;
    cin>>choice;
    cout<<Default;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<Red<<"\nError(Invalid choice)!\nPlease try again.\n"<<Default;
        continue;
    }
    switch(choice){
        case 1: sortbyGrade();
            break;
        case 2:  sortbyMajor();
            break;
        case 3:
            return;
        default: cout<<Red<<"\nError(Invalid choice)!\nPlease try again.\n"<<Default;
            break;
    }
    }
    
}

void print(string line){
        int i=1;
        string  fullName="";
        while(line[i]!='@'){
            fullName+=line[i];
            i++;
        }
        
        i++;
        string ID="";
        while(line[i]!='#'){
            ID+=line[i];
            i++;
        }
        i++;
        string major="";
        while(line[i]!='$'){
            major+=line[i];
            i++;
        }
    
        cout<<Yellow<<" _________________________________________________________________________________\n|\n|"<<Default<<" Name:"<<fullName<<"  "<<"Student ID:"<<ID<<"  "<<"Major:"<<major<<"  "<<"Average Grade:"<<avgGrade(line)<<Yellow<<"\n|_________________________________________________________________________________\n"<<Default;
}

void sort(vector<string> &sortline ,int count){
    int i{},j{};
    string temp="";
    for(i=0;i<count;i++){
        for(j=0;j<count-1-i;j++){
            if(avgGrade(sortline[j+1])>avgGrade(sortline[j])){
                temp=sortline[j];
                sortline[j]=sortline[j+1];
                sortline[j+1]=temp;
            }
        }
    }
    for(int k=0;k<count;k++)
      print(sortline[k]);
}

void sortbyGrade(){
    fstream students = openFile("in");

    vector<string> sortline;
    string line;
    while(getline(students,line)){
        sortline.push_back(line);
    }
    int count = sortline.size();
    
    if (count == 0) {
        cout <<Red<< "No data to sort." <<Default<< endl;
        }
    
    sort(sortline,count);
}

void sortbyMajor(){
      fstream students = openFile("in");

    cout<<"Enter the name of the Major you want to search for:";
    string major,s="";
    cin.ignore();
    getline(cin,major);
    vector<string> sortline;
    string line;
    while(getline(students,line)){
        int i=1+line.find('#');
        while(line[i]!='$'){
            s+=line[i];
            i++;
        }
        if(s==major)
        sortline.push_back(line);
        s="";
    }
    int count = sortline.size();
    
    if (count == 0) {
        cout <<Red<< "No data to sort." <<Default<< endl;}
    
    sort(sortline,count);
}

void AcademicRecord_score(string line){
    
       int i=1+line.find('$');
   string s="";
   cout<<Yellow<<" _________________________________________________";
   cout<<"\n|\n|"<<Red<<"\tCourse(Credit)=Grade\n"<<Yellow<<"|\n";
   while(line[i]!='\0'){
        if(line[i]!=','){
            s+=line[i];
        }
        else{
            cout<<Yellow<<"|\t"<<Default<<s<<'\n';

            s="";
        }
        i++;
   }

cout<<Yellow<<"|_________________________________________________\n"<<Default;

}

bool checkValid(string studentID){
    fstream students = openFile("in");

    string line,s="";
    while(getline(students,line)){
        int i=1+line.find('@');

        while(line[i]!='#'){
            s+=line[i];
            i++;
        }
        if(studentID==s) return false;
        else s="";
}
    return true;
}