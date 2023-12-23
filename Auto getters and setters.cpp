#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

struct var
{
    string type;
    string name;
};

//for better code reading
string firstSymbol2Upper(string other)
{
    if(other[0] >= 97)    other[0] = other[0] - 32;
    return other;
}

void GetterVarDeclare(var other)
{
    cout << other.type + " get" + firstSymbol2Upper(other.name) + "();" << endl;
}
void SetterVarDeclare(var other)
{
    cout << "void set" + firstSymbol2Upper(other.name) + "(" + other.type + " " + other.name + ");" << endl;
}

void GetterVarOpinion(var other, string className)
{
    cout << other.type + " " + className + "::get" + firstSymbol2Upper(other.name) + "()" << endl;
    cout << "{\n" << "   return " + other.name + ";\n" << "}" << endl;
}
void SetterVarOpinion(var other, string className)
{
    cout << "void " + className + "::set" + firstSymbol2Upper(other.name) + "(" + other.type + " " + other.name + ")" << endl;
    cout << "{\n" << "   this-> " + other.name + " = " + other.name + ";\n" << "}" << endl;
}

int main()
{
    bool isType = 1, isNotEquality = 1;
    string className, variables = "";
    string holder, TypeHolder, NameHolder;
    // vector[i][j] => j == 0(Getter) j == 1(Setter) i - just variable
    vector<var> vars;

    cout << "Name of class: ";
    cin >> className;

    cout << "All variables(at the end just put @):\n";
    do
    {
        cin >> holder;
        variables += (" " + holder);
    } while (holder[holder.size() - 1] != "@"[0]);

    holder = "";
    variables.pop_back();

    //Managing variables
    for (int i = 0; i < variables.size(); i++)
    {
        if (variables[i] == " "[0] && isType && holder != "")
        {
            TypeHolder = holder;
            holder = "";
            isType = 0;
        }
        else if ((variables[i] == " "[0] or variables[i] == ","[0]) && holder != "")
        {
            if(isNotEquality)   vars.push_back({ TypeHolder, holder });
            holder = "";
            isNotEquality = 1;
        }
        else if (variables[i] == "="[0])    isNotEquality = 0;
        else if (variables[i] == ";"[0])
        {
            if (isNotEquality)   vars.push_back({ TypeHolder, holder });
            TypeHolder = holder = "";
            isNotEquality = isType = 1;
        }
        else if (variables[i] != " "[0] && variables[i] != ","[0])
        {
            holder += variables[i];
        }
    }
    
    //Printing getters & setters declare
    cout << endl << "Getters & Setters declare(put it in .h)\n"<< endl << "//getters\n";
    for (int i = 0; i < vars.size(); i++)
    {
        GetterVarDeclare(vars[i]);
    }

    cout << endl << "//setters\n";
    for (int i = 0; i < vars.size(); i++)
    {
        SetterVarDeclare(vars[i]);
    }
    
    cout << endl << "Getters & Setters opinion(put it in .cpp)\n" << endl;
    for (int i = 0; i < vars.size(); i++)
    {
        GetterVarOpinion(vars[i], className);
    }

    for (int i = 0; i < vars.size(); i++)
    {
        SetterVarOpinion(vars[i], className);
    }
    system("pause");
}
