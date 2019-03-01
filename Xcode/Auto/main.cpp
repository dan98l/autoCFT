//
//  main.cpp
//  Auto
//
//  Created by Daniil G on 28/02/2019.
//  Copyright © 2019 Daniil G. All rights reserved.
//
//


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

//vector<string> poleCars;
//vector<string> cars;
list<string> poleList;
list<string> carsList;
int countCars = 0;

void poleAndCars(){
    
    fstream file("pole.txt");
    while (!file.eof()) {
        string tmp = "";
        file >> tmp;
        poleList.push_back(tmp);
    }
    
    fstream files("cars.txt");
    while (!files.eof()) {
        string tmp = "";
        files >> tmp;
        carsList.push_back(tmp);
    }
}

void save(){
    ofstream in("cars.txt");
    string tmp = "";
    countCars++;
    int indexPole = 0;
    tmp = "";
    int countEnter = 0;
    for(list<string>::iterator iter=carsList.begin();iter!=carsList.end();++iter){
        if (countEnter == poleList.size()-1) {
            tmp = tmp + *iter;
        } else {
            tmp = tmp + *iter + " ";
        }
        countEnter++;
        if (countEnter == poleList.size()) {
            countEnter = 0;
            if (indexPole != carsList.size()-1) {
                in << tmp + "\n";
                tmp = "";
            } else {
                in << tmp;
                tmp = "";
            }
        }
        indexPole++;
    }
}

void add(int countCars) {
    string inPole = "";
    string tmp = "";
    getline (cin, inPole);
    for (list<string>::iterator iter=poleList.begin();iter!=poleList.end();++iter) {
        cout << "Vvedide " << *iter << ": ";
        
        getline (cin, inPole);
        
        
        string pole = inPole;
        for (int j = 0; j < pole.size(); j++) {
            if (pole[j] != 32) {
                tmp = tmp + pole[j];
            } else {
                tmp = tmp + "/";
            }
            if (j == pole.size()-1) {
                carsList.push_back(tmp);
                tmp = "";
            }
        }
    }
    
    for (list<string>::iterator iter=carsList.begin();iter!=carsList.end();++iter) {
        string pole = *iter;
        string tmp = "";
        for (int j = 0; j < pole.size(); j++) {
            if (pole[j] != 32) {
                tmp = tmp + pole[j];
            } else {
                tmp = tmp + "/";
            }
            if (j == pole.size()-1) {
                *iter = tmp;
                tmp = "";
            }
        }
    }
    save();
    countCars++;
}


void view(int countCars){
    int indexPole = 0;
    list<string>::iterator indexIter=poleList.begin();indexIter!=poleList.end();
    int _countCars = 1;
    cout << "Car #" << _countCars << " " << endl;
    for (list<string>::iterator iter=carsList.begin();iter!=carsList.end();++iter) {
        string pole = *iter;
        string tmp = "";
        for (int j = 0; j < pole.size(); j++) {
            if (pole[j] != 47) {
                tmp = tmp + pole[j];
            } else {
                tmp = tmp + " ";
            }
            if (j == pole.size()-1) {
                *iter = tmp;
                tmp = "";
            }
        }
        
        cout << *indexIter  << ": " << *iter << endl;
        indexIter++;
        
       // cout << poleList.size()-1 << endl;
        
        if (indexPole == poleList.size()-1) {
            indexPole = 0;
            indexIter = poleList.begin();
            cout << endl;
            if (_countCars < countCars) {
                _countCars++;
                cout << "Car #" << _countCars << " " << endl;
            }
        } else {
            indexPole++;
        }
    }
}

void dell (int countCars){
    cout << "Vibirete kakoe auto dellite? " << endl;
    int del = 0;
    cin >> del;
    while(del > countCars && del > 0) {
        cout << "Error!" << endl;
        cout << "Vibirete kakoe auto dellite? ";
        cin >> del;
    }
    
    int beginDel = (del-1) * poleList.size();
   
    list<string>::iterator it=carsList.begin();
 
    it = next(it, beginDel);
    for (int i = 0; i < poleList.size(); i++) {
        carsList.erase(it);
        it = next(it, 1);
    }
    
    cout << "Ok! Car #" << del << " delite." << endl;
    
    for (list<string>::iterator iter=carsList.begin();iter!=carsList.end();++iter) {
        string pole = *iter;
        string tmp = "";
        for (int j = 0; j < pole.size(); j++) {
            if (pole[j] != 32) {
                tmp = tmp + pole[j];
            } else {
                tmp = tmp + "/";
            }
            if (j == pole.size()-1) {
                *iter = tmp;
                tmp = "";
            }
        }
    }
    save();
}

void edit(){
    cout << "Vibirete kakoe auto edit? ";
    int edit = 0;
    cin >> edit;
    while(edit > countCars && edit > 0) {
        cout << "Error!" << endl;
        cout << "Vibirete kakoe auto edit? ";
        cin >> edit;
    }
    
    cout << "Vibirete kakoe pole edit? " << endl;
    int countPole = 0;
    for (list<string>::iterator iter=poleList.begin();iter!=poleList.end();++iter) {
        cout << countPole+1 << ". " << *iter << endl;
        countPole++;
    }
    
    int editPole = 0;
    cin >> editPole;
    while(editPole > poleList.size() && editPole > 0) {
        cout << "Error!" << endl;
        cout << "Vibirete kakoe auto edit? ";
        cin >> editPole;
    }
    
    cout << "Vvedide new znachenie: ";
    string newPole = "";
    getline (cin, newPole);
    getline (cin, newPole);
    
    int itBegin = ((edit-1) * poleList.size())+editPole-1;
    
    list<string>::iterator it=carsList.begin();
    it = next(it, itBegin);
    *it = newPole;
    
    for (list<string>::iterator iter=carsList.begin();iter!=carsList.end();++iter) {
        string pole = *iter;
        string tmp = "";
        for (int j = 0; j < pole.size(); j++) {
            if (pole[j] != 32) {
                tmp = tmp + pole[j];
            } else {
                tmp = tmp + "/";
            }
            if (j == pole.size()-1) {
                *iter = tmp;
                tmp = "";
            }
        }
    }
    save();
}

void menu (){
    cout << "-----------------------" << endl;
    cout << "1. Add auto:" << endl;
    cout << "2. Delete auto:" << endl;
    cout << "3. View cars:" << endl;
    cout << "4. Edit auto:" << endl;
    cout << "5. Exit:" << endl;
    
    int chousePunktMenu = 0;
    cout << "Vvedite vash vibor: ";cin >> chousePunktMenu;
    
    switch(chousePunktMenu){
        case 1: cout << "Add auto:" << endl;
            add(countCars);
            break;
        case 2: cout << "Delete auto:" << endl;
            dell(countCars);
            break;
        case 3: cout << "View cars:" << endl << endl;
            view (countCars);
            break;
        case 4: cout << "Edit auto:" << endl;
            edit();
            break;
        case 5: exit(0);
        default: cout << "Error! Please enter number 1-5" << endl;
    }
}

int main() {
    poleAndCars();
    while (1) {
         countCars = carsList.size()/poleList.size();
        menu();
    }
    
    return 0;
}
