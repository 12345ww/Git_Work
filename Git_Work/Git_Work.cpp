#include <iostream>
using namespace std;
int const size = 256;
struct Subject {
    char* name = nullptr;
    int* rating = nullptr;
    int sizeRating = 0;
};
struct Student {
    Subject** sub = nullptr;
    char* name = nullptr;
    char* family = nullptr;
    char* patrinim = nullptr;
    int yearBirstday = 0;
    int group = 0;
    int course = 0;
};
struct List {
    Student** list = nullptr;
    int sizeSub = 0;
    int sizeList = 0;
};
char* regDown(const char* buffer) {
    char* str = new char[size] {};
    for (int a = 0; buffer[a] != '\0'; a++) {
        if (buffer[a] >= 'A' && buffer[a] <= 'Z') {
            str[a] = 'Z' - buffer[a] + 'a';
        }
        else {
            str[a] = buffer[a];
        }
    }
}
bool provSort(const char* tempStr1, const char* tempStr2) {
    int a = 0; 
    char* str1 = regDown(tempStr1);
    char* str2 = regDown(tempStr2);
    while (str1[a] != '\0' && str2[a] != '\0') {
        if (str1[a] != str2[a]) {
            if (str1[a] > str2[a]) {
                delete[] str1;
                delete[] str2;
                return true;
            }
            delete[] str1;
            delete[] str2;
            return false;
        }
        a++;
    }
    delete[] str1;
    delete[] str2;
    return false;
}
void sortStudent(List* list) {
    int a = 0;
    int temp;
    bool prov = true;
    do {
        prov = false;
        for (int b = 0; b < list->sizeList - a - 1; b++) {
            if (list->list[b]->course > list->list[b + 1]->course) {
                temp = list->list[b + 1]->course;
                list->list[b + 1]->course = list->list[b]->course;
                list->list[b]->course = temp;
                prov = true;
            }
        }
    } while (prov);
    a = 0;
    Student* stud;
    do {
        prov = false;
        for (int b = 0; b < list->sizeList - a - 1; b++) {
            if (list->list[b]->course != list->list[b + 1]->course) {
                continue;
            }
            if (provSort(list->list[b]->name, list->list[b + 1]->name)) {
                if (provSort(list->list[b]->family, list->list[b + 1]->family)) {
                    if (provSort(list->list[b]->patrinim, list->list[b + 1]->patrinim)) {
                        stud = list->list[b+1];
                        list->list[b+1] = list->list[b];
                        list->list[b] = stud;
                        prov = true;
                    }
                }
            }
        }
    } while (prov);
}

double avgRatingStud(List* list, int index, int group) {
    if (index < 0 || index > list->sizeSub) {
        cout << "GROUP ERROR\n";
        return;
    }
    if (group < 0) {
        cout << "GROUP ERROR\n";
        return;
    }
    int sum = 0;
    int size = 0;
    for (int a = 0; list->sizeSub; a++) {
        if (list->list[a]->group == group) {
            for(int b = 0; b < list->list[a]->sub[a]->sizeRating; b++) {
                size++;
                sum += list->list[a]->sub[index]->rating[b];
            }
        }
    }
    return sum / (double)size;
}
int main()
{
    
}