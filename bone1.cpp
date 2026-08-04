

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

// ====================== CLASSES =======================

class Patient
{
private:
    int id;
    string name;
    int age;
    char gender;
    double height;
    double weight;

public:

    void input()
    {
        cout<<"Patient ID: ";
        cin>>id;
        cin.ignore();

        cout<<"Name: ";
        getline(cin,name);

        cout<<"Age (Years): ";
        cin>>age;

        cout<<"Gender (M/F): ";
        cin>>gender;

        cout<<"Height (cm): ";
        cin>>height;

        cout<<"Weight (kg): ";
        cin>>weight;
    }

    int getAge()
    {
        return age;
    }

    char getGender()
    {
        return gender;
    }

    string getName()
    {
        return name;
    }

    int getID()
    {
        return id;
    }

    void display()
    {
        cout<<"\n==============================\n";
        cout<<"Patient ID : "<<id<<endl;
        cout<<"Name       : "<<name<<endl;
        cout<<"Age        : "<<age<<" years"<<endl;
        cout<<"Gender     : "<<gender<<endl;
        cout<<"Height     : "<<height<<" cm"<<endl;
        cout<<"Weight     : "<<weight<<" kg"<<endl;
    }
};

//========================================================

class BoneAgeCalculator
{
private:

    double radius;
    double ulna;
    double carpals;
    double metacarpals;
    double phalanges;

public:

    void inputScores()
    {
        cout<<"\nEnter Bone Maturity Scores (0-20)\n\n";

        cout<<"Radius Score      : ";
        cin>>radius;

        cout<<"Ulna Score        : ";
        cin>>ulna;

        cout<<"Carpals Score     : ";
        cin>>carpals;

        cout<<"Metacarpals Score : ";
        cin>>metacarpals;

        cout<<"Phalanges Score   : ";
        cin>>phalanges;
    }

    double totalScore()
    {
        return radius+ulna+carpals+metacarpals+phalanges;
    }

    double calculateBoneAge(char gender)
    {
        double score=totalScore();

        if(gender=='M'||gender=='m')
            return score/5.5;

        return score/5.2;
    }

};

//========================================================

class Diagnosis
{
public:

    static string classify(double chrono,double bone)
    {
        double diff=bone-chrono;

        if(diff>2)
            return "Advanced Bone Development";

        else if(diff<-2)
            return "Delayed Bone Development";

        else
            return "Normal Bone Development";
    }

};

//========================================================

class Report
{
private:

    Patient patient;
    BoneAgeCalculator calculator;

public:

    void create()
    {
        patient.input();
        calculator.inputScores();

        double boneAge=calculator.calculateBoneAge(patient.getGender());

        patient.display();

        cout<<fixed<<setprecision(2);

        cout<<"\nBone Age          : "<<boneAge<<" Years"<<endl;

        cout<<"Diagnosis         : "
            <<Diagnosis::classify(patient.getAge(),boneAge)<<endl;

        save(patient.getID(),
             patient.getName(),
             patient.getAge(),
             boneAge,
             Diagnosis::classify(patient.getAge(),boneAge));
    }

    void save(int id,string name,int age,double bone,string result)
    {
        ofstream file("patients.txt",ios::app);

        file<<id<<" "
            <<name<<" "
            <<age<<" "
            <<bone<<" "
            <<result<<endl;

        file.close();

        cout<<"\nReport Saved Successfully.\n";
    }

};

//========================================================

class History
{
public:

    void show()
    {
        ifstream file("patients.txt");

        if(!file)
        {
            cout<<"\nNo Records Found.\n";
            return;
        }

        string line;

        cout<<"\n=========== HISTORY ===========\n\n";

        while(getline(file,line))
        {
            cout<<line<<endl;
        }

        file.close();
    }

};

//========================================================

class IdealTable
{
public:

    void show()
    {
        cout<<"\n============= IDEAL BONE SCORES =============\n\n";

        cout<<left<<setw(20)<<"Bone"<<setw(10)<<"Score"<<endl;

        cout<<"--------------------------------------"<<endl;

        cout<<setw(20)<<"Radius"<<15<<endl;
        cout<<setw(20)<<"Ulna"<<15<<endl;
        cout<<setw(20)<<"Carpals"<<18<<endl;
        cout<<setw(20)<<"Metacarpals"<<20<<endl;
        cout<<setw(20)<<"Phalanges"<<22<<endl;
    }

};

//========================================================

class Statistics
{
public:

    void show()
    {
        ifstream file("patients.txt");

        if(!file)
        {
            cout<<"\nNo Data Available.\n";
            return;
        }

        int id,age;
        string name,result;

        double bone;

        int patients=0;

        double sum=0;

        while(file>>id>>name>>age>>bone)
        {
            getline(file,result);

            patients++;

            sum+=bone;
        }

        cout<<"\n=========== Statistics ==========="<<endl;

        cout<<"Total Patients : "<<patients<<endl;

        if(patients!=0)
            cout<<"Average Bone Age : "<<sum/patients<<endl;

        file.close();
    }

};

//========================================================

class Menu
{
private:

    Report report;
    History history;
    IdealTable table;
    Statistics stats;

public:

    void start()
    {
        int choice;

        do
        {
            cout<<"\n========================================\n";
            cout<<"           BoneAge Pro"<<endl;
            cout<<"========================================\n";

            cout<<"1. New Patient"<<endl;
            cout<<"2. Patient History"<<endl;
            cout<<"3. Ideal Bone Table"<<endl;
            cout<<"4. Statistics"<<endl;
            cout<<"5. Exit"<<endl;

            cout<<"\nChoice : ";
            cin>>choice;

            switch(choice)
            {

            case 1:
                report.create();
                break;

            case 2:
                history.show();
                break;

            case 3:
                table.show();
                break;

            case 4:
                stats.show();
                break;

            case 5:
                cout<<"\nGood Bye!\n";
                break;

            default:
                cout<<"\nInvalid Choice\n";

            }

        }while(choice!=5);
    }

};

//========================================================

int main()
{
    Menu app;

    app.start();

    return 0;
}
