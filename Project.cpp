#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<vector>

bool Record=false;

using namespace std;

float avgGrade(string line);
void addStudent();
void addCourse();
void AcademicRecord();
void searchbyName();
void searchbyID();
void listAllStudents();
void AcademicRecord_score(string line);
void sortbyGrade();
void sortbyMajor();
void print(string informations);
void sort(vector<string> &sortline ,int count);

int main(){
    while(true){
    cout<<"\nPlease Choose an Option.\n\n";
    cout<<"1.Add a Student Information.\n";
    cout<<"2.Search by Name.\n";
    cout<<"3.Search by ID.\n";
    cout<<"4.List Students.\n";
    cout<<"5.Academic record of a student.\n";
    cout<<"6.Exit.\n";
    cout<<"Your choice:";
    int choice;
    cin>>choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<"\nError(Invalid choice)!\nPlease try again.\n";
        continue;
    }
    switch(choice){
        case 1: addStudent();
            break;
        case 2: searchbyName();
            break;
        case 3: searchbyID();
            break;
        case 4: listAllStudents();
            break;
        case 5: AcademicRecord();
            break;
        case 6: 
            return 0;
        default: cout<<"\nError(Invalid choice)!\nPlease try again.\n";
            break;
    }
    }
}

void addStudent(){
    fstream students;
    students.open("students.txt",ios::app);
    if(!students){
        cout<<"\nError!.\nFile doesn't exist.";
        return;
    }
  string fullName,studentID,major;
  cout<<"Enter the Full Name of The student:";
  cin.ignore();
  getline(cin,fullName);
  cout<<"Enter the Student ID:";
  cin>>studentID;
  cout<<"Enter the Major of The student:";
   cin.ignore();
  getline(cin,major);
  students<<"!"<<fullName<<"@"<<studentID<<"#"<<major<<"$";
  students.close();
  while(true){
    cout<<"\n1.Adding a course";
    cout<<"\n2.exit";
    cout<<"\nYour choice:";
    int choice;
    cin>>choice;
     if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<"\nError(Invalid choice)!\nPlease try again.\n";
        continue;
     }
    switch(choice){
        case 1: addCourse();
            break;
        case 2:students.open("students.txt",ios::app);
            students<<"\n";
            students.close();
            return;
        default: cout<<"\nError(Invalid choice)!\nPlease try again.\n";
            break;
        
    }
  }
  
}

void addCourse(){
    fstream students;
    students.open("students.txt",ios::app);
    if(!students){
        cout<<"\nError!.\nFile doesn't exist.";
        return;
    }
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
    
    fstream students;
    students.open("students.txt",ios::app); 
    while(true){
        cout<<"\nGive one of the following information about the student.\nChoose one !\n";
        cout<<"1.Name of student.\n";
        cout<<"2.ID of student.\n";
        cout<<"3.Exit.\n";
        cout<<"Your choice:";
        int choice;
        cin>>choice;
        if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<"\nError(Invalid choice)!\nPlease try again.\n";
        continue;
        }
        switch(choice){
            case 1: Record=true;
            searchbyName();
            Record=false;
                break;
            case 2: Record=true;
            searchbyID();
            Record=false;
                break;
            case 3:
                return;
            default: cout<<"\nError(Invalid choice)!\nPlease try again.\n";
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

void searchbyName(){
    ifstream students;
    students.open("students.txt");
    if(!students){
        cout<<"\nError!.\nFile doesn't exist.";
        return;
    }
    string nameToSearch,line;
    cout<<"Enter Name to search:";
    cin.ignore();
    getline(cin,nameToSearch);
    bool flag=false;
    while(getline(students,line)){
        int i=1;
        string  fullName="";
        while(line[i]!='@'){
            fullName+=line[i];
            i++;
        }
        if(fullName==nameToSearch){
            flag=true;
            print(line);
            if(Record){;
            AcademicRecord_score(line);
            cout<<"\n***************************************************\n";
            }
       }
    }
    if(!flag){ cout<<"No one was found with given name !\n";return;}
}

void searchbyID(){
   ifstream students;
    students.open("students.txt");
    if(!students){
        cout<<"\nError!.\nFile doesn't exist.";
        return;
    }
    string IDToSearch,line;
    cout<<"Enter ID to search:";
    cin.ignore();
    getline(cin,IDToSearch);
    bool flag=false;
    while(getline(students,line)){
        int i=1+line.find('@');
        string  ID="";
        while(line[i]!='#'){
            ID+=line[i];
            i++;
        }
        if(ID==IDToSearch){
            flag=true;
            print(line);
             if(Record){
            AcademicRecord_score(line);
            }
    }
    }
    if(!flag){ cout<<"No one was found with given ID !\n";return;}
}

void listAllStudents(){
    while(true){
    cout<<"\nPlease Choose an Option\n\n";
    cout<<"1.Sorting by Grade. \n";
    cout<<"2.Sorting by Major. \n";
    cout<<"3.Exit\n";
    cout<<"Your choice:";
    int choice;
    cin>>choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout<<"\nError(Invalid choice)!\nPlease try again.\n";
        continue;
    }
    switch(choice){
        case 1: sortbyGrade();
            break;
        case 2:  sortbyMajor();
            break;
        case 3:
            return;
        default: cout<<"\nError(Invalid choice)!\nPlease try again.\n";
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
    
        cout<<" _________________________________________________________________________________\n|\n|"<<" Name:"<<fullName<<"  "<<"Student ID:"<<ID<<"  "<<"Major:"<<major<<"  "<<"Average Grade:"<<avgGrade(line)<<"\n|_________________________________________________________________________________\n";
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
    ifstream students;
    students.open("students.txt");
    if(!students){
        cout<<"\nError!.\nFile doesn't exist.";
        return;
        }

    vector<string> sortline;
    string line;
    while(getline(students,line)){
        sortline.push_back(line);
    }
    int count = sortline.size();
    
    if (count == 0) {
        cout << "No data to sort." << endl;}
    
    sort(sortline,count);
}

void sortbyMajor(){
      ifstream students;
    students.open("students.txt");
    if(!students){
        cout<<"\nError!.\nFile doesn't exist.";
        return;
        } 
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
        cout << "No data to sort." << endl;}
    
    sort(sortline,count);
}

void AcademicRecord_score(string line){
    
       int i=1+line.find('$');
   string s="";
   cout<<" _________________________________________________";
   cout<<"\n|\n|\tCourse(Credit)=Grade\n|\n";
   while(line[i]!='\0'){
        if(line[i]!=','){
            s+=line[i];
        }
        else{
            cout<<"|\t"<<s<<'\n';

            s="";
        }
        i++;
   }

cout<<"|_________________________________________________\n";

}