#include <iostream>
using namespace std;
int const sizeStr = 256;
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
    int groups = 0;
    int course = 0;

    char** names = nullptr;
    static const int SIZE = 10;
    static const char* namesS[List::SIZE];
    static const char* familysS[List::SIZE];
    static const char* patronimS[List::SIZE];
};

const char* List::namesS[List::SIZE]{ "Artem","Aleksandr","Maksim","Dmitriy","Matvey","Nazar","Bogdan","Mark","Vladimir","Mihail" };
const char* List::familysS[List::SIZE]{ "Shukin", "Kojevnikov", "Vinogradov", "Timofeev", "Orlov", "Baranov", "Cherkasov", "Popov", "Zinovev", "Andreev" };
const char* List::patronimS[List::SIZE]{ "Vyacheslavovich", "Yanivich", "Aleksandrovich", "Konstantinovich", "Yaroslavovich", "Platonovich", "Petrovich", "Ruslanovich", "Vasilevich", "Kirillovich" };

void createAcc(Student* stud, int sizeSub, int groups, int course, const char** names) {
    stud->sub = new Subject* [sizeSub];
    for (int a = 0; a < sizeSub; a++) {
        stud->sub[a] = new Subject;
        stud->sub[a]->name = new char[sizeStr] {};
        stud->sub[a]->sizeRating = rand() % 10 + 1;
        stud->sub[a]->rating = new int[stud->sub[a]->sizeRating] {};
        strcat_s(stud->sub[a]->name, sizeStr, names[a]);
        for (int b = 0; b < stud->sub[a]->sizeRating; b++) {
            if (rand() % 10 < 3) {
                stud->sub[a]->rating[b] = rand() % 6 + 1;
            }
            else {
                stud->sub[a]->rating[b] = rand() % 6 + 1 + 6;
            }
        }
    }
    stud->name = new char[sizeStr] {};
    stud->family = new char[sizeStr] {};
    stud->patrinim = new char[sizeStr] {};
    stud->yearBirstday = rand() % 10 + 19;
    stud->group = rand() % groups;
    stud->course = rand() % course+1;
    strcat_s(stud->name, sizeStr, List::namesS[rand() % List::SIZE]);
    strcat_s(stud->family, sizeStr, List::familysS[rand() % List::SIZE]);
    strcat_s(stud->patrinim, sizeStr, List::patronimS[rand() % List::SIZE]);
}
void createList(List* list, const char** names) {
    if (list->sizeList < 1) {
        cout << "ERROR CREATE: SIZE\n";
        return;
    }
    if (list->groups < 1) {
        cout << "ERROR CREATE: GROUP\n";
        return;
    }
    if (list->sizeSub < 1) {
        cout << "ERROR CREATE: SUBJECT\n";
        return;
    }
    list->list = new Student * [list->sizeList] {};
    for (int a = 0; a < list->sizeList; a++) {
        list->list[a] = new Student;
        createAcc(list->list[a], list->sizeSub, list->groups, list->course, names);
    }
}

void delAcc(Student* stud, int sizeSub) {
    for (int a = 0; a < sizeSub; a++) {
        delete[] stud->sub[a]->name;
        delete[] stud->sub[a]->rating;
        delete[] stud->sub[a];
    }
    delete[] stud->sub;
    delete[] stud->name;
    delete[] stud->family;
    delete[] stud->patrinim;
}
void delList(List* list) {
    if (list->sizeList < 1) {
        cout << "ERROR DELETE: SIZE\n";
        return;
    }
    for (int a = 0; a < list->sizeList; a++) {
        delAcc(list->list[a], list->sizeSub);
        delete[] list->list[a];
    }
    list->sizeList = 0;
    delete[] list;
}


char* regDown(const char* buffer) {
    char* str = new char[sizeStr] {};
    for (int a = 0; buffer[a] != '\0'; a++) {
        if (buffer[a] >= 'A' && buffer[a] <= 'Z') {
            str[a] = 'Z' - buffer[a] + 'a';
        }
        else {
            str[a] = buffer[a];
        }
    }
    return str;
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

double avgRatingGroup(List* list, int index, int group) {
    if (index < 0 || index > list->sizeSub) {
        cout << "GROUP ERROR\n";
        return 0;
    }
    if (group < 0) {
        cout << "GROUP ERROR\n";
        return 0;
    }
    double sum = 0;
    int sizeSum = 0;
    for (int a = 0; a < list->sizeList; a++) {
        if (list->list[a]->group == group) {
            for(int b = 0; b < list->list[a]->sub[index]->sizeRating; b++) {
                sizeSum++;
                sum += list->list[a]->sub[index]->rating[b];
            }
        }
    }
    if (sizeSum == 0) {
        return 0;
    }
    return sum / sizeSum;
}
void printAvgRating(List* list) {
    for (int a = 0; a < list->groups; a++) {
        cout << "Group " << a+1 << endl;
        for (int b = 0; b < list->sizeSub; b++) {
            cout << "\t" << list->list[a]->sub[b]->name << ": " << avgRatingGroup(list, b, a) << endl;
        }
    }
}

double poiskRating(Student* stud, int sizeSub) {
    double sum = 0;
    int sizeSum = 0;
    for (int a = 0; a < sizeSub; a++) {
        for (int b = 0; b < stud->sub[a]->sizeRating; b++) {
            sum += stud->sub[a]->rating[b];
            sizeSum++;
        }
    }
    if (sizeSum == 0) {
        return 0;
    }
    return sum / sizeSum;
}
void printTopRating(List* list) {
    double temp;
    double max;
    int adress;
    for (int a = 0; a < list->groups; a++) {
        cout << "Group " << a + 1 << endl; 
        adress = 0;
        max = poiskRating(list->list[0], list->sizeSub);
        for (int b = 1; b < list->sizeList; b++) {
            if (list->list[b]->group == a) {
                temp = poiskRating(list->list[b], list->sizeSub);
                if (temp > max) {
                    max = temp;
                    adress = b;
                }
            }
        }
        printf("\t%s %s %s avg ratiing is: %f\n", list->list[adress]->name, list->list[adress]->family, list->list[adress]->patrinim, max);
    }
}

typedef bool (*boolFunc)(int, int);
bool min(int age1, int age2) {
    if (age1 > age2) {
        return true;
    }
    return false;
}
bool max(int age1, int age2) {
    if (age1 < age2) {
        return true;
    }
    return false;
}

int poiskAge(List* list, boolFunc func) {
    int index = 0;
    for (int a = 1; a < list->sizeList-1; a++) {
        if (func(list->list[a]->yearBirstday, list->list[a + 1]->yearBirstday)) {
            index = a;
        }
    }
    return index;
}
int main()
{
    List* list = new List;
    list->sizeList = 100;
    list->sizeSub = 5;
    list->groups = 3;
    list->course = 5;
    const char** names = new const char*[list->sizeSub]{
    "Maths",
    "Physics",
    "Chemistry",
    "Astronomy",
    "Geography"
    };
    createList(list, names);
    cout << "\n////////////////////////////////////////////////\n";
    cout << "AVG\n";
    printAvgRating(list);
    cout << "\n////////////////////////////////////////////////\n";
    cout << "TOP_RATING\n";
    printTopRating(list);
    cout << "\n////////////////////////////////////////////////\n";

    delList(list);
}