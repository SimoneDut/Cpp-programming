#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

class FullName {
public:
  std::string surname;
  std::string name;
  bool operator == (const FullName& rhs) const {
    return (surname == rhs.surname) && (name == rhs.name);
  }
  bool operator != (const FullName& rhs) const {
    return !(*this == rhs);
  }
};

class BirthDate {
public:
  int year;
  int month;
  int day;
  bool operator == (const BirthDate& rhs) const {
    return (year == rhs.year) && (month == rhs.month) && (day == rhs.day);
  }
  bool operator != (const BirthDate& rhs) const {
    return !(*this == rhs);
  }
};

std::ostream& operator<< (std::ostream& stream, const std::pair<FullName, BirthDate>& person) {
  stream << person.first.surname << " " << person.first.name << " " << person.second.year << " " << person.second.month << " " << person.second.day;
  return stream;
}

std::ostream& operator<< (std::ostream& stream, const std::pair<BirthDate, FullName>& nosrep) {
  stream << nosrep.first.year << " " << nosrep.first.month << " " << nosrep.first.day << " " << nosrep.second.surname << " " << nosrep.second.name;
  return stream;
}

class OrderIgnoreCase {
public:
  bool operator() (const std::string& s1, const std::string& s2) const {
    for (size_t i = 0; (i < s1.size()) && (i < s2.size()); i++) {
      char c1 = tolower(s1[i]);
      char c2 = tolower(s2[i]);
      if (c1 != c2) {
	return c1 < c2;
      }
    }
    return s1.size() < s2.size();
  }
};

class OrderFullName {
public:
  bool operator() (const FullName& fn1, const FullName& fn2) const {
    OrderIgnoreCase app;
    if (fn1.surname != fn2.surname) {
      return app(fn1.surname, fn2.surname);
    }
    return app(fn1.name, fn2.name);
  }
};

class OrderBirthDate {
public:
  bool operator() (const BirthDate& bd1, const BirthDate& bd2) const {
    if (bd1.year != bd2.year) {
      return bd1.year < bd2.year;
    }
    if (bd1.month != bd2.month) {
      return bd1.month < bd2.month;
    }
    return bd1.day < bd2.day;
  }
};

class OrderPerson {
public:
  bool operator() (const std::pair<FullName, BirthDate>& per1, const std::pair<FullName, BirthDate>& per2) const {
    if (!((per1.first.surname == per2.first.surname)&&(per1.first.name == per2.first.name))) {
      OrderFullName app;
      return app(per1.first,per2.first);
    }
    OrderBirthDate app;
    return app(per1.second,per2.second);
  }
};

class OrderNosrep {
public:
  bool operator() (const std::pair<BirthDate, FullName>& rep1, const std::pair<BirthDate, FullName>& rep2) const {
    if (!((rep1.first.year == rep2.first.year)&&(rep1.first.month == rep2.first.month)&&(rep1.first.day == rep2.first.day))) {
      OrderBirthDate app;
      return app(rep1.first,rep2.first);
    }
    OrderFullName app;
    return app(rep1.second,rep2.second);
  }
};

std::string readString(FILE *& f, bool& endLine, bool& endFile, bool& error) {
  std::string ans;
  char c;
  bool begin = false;
  error = true;
  while((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      if (begin) {
	error = false;
      }
      endLine = true;
      return ans;
    }
    if (c == ' ') {
      if (begin) {
	error = false;
	return ans;
      }
    }
    if (!(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))) {
      error = true;
      return ans;
    }
    ans += c;
    begin = true;
  }
  error = !begin;
  endFile = true;
  return ans;
}

int readNumber(FILE *& f, bool& endLine, bool& endFile, bool& error) {
  int ans = 0;
  char c;
  bool begin = false;
  error = true;
  while((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      if (begin) {
	error = false;
      }
      endLine = true;
      return ans;
    }
    if (c == ' ') {
      if (begin) {
	error = false;
	return ans;
      }
    }
    if (!((c >= '0') && (c <= '9'))) {
      error = true;
      return ans;
    }
    ans = ans * 10 + c - '0';
    begin = true;
  }
  error = !begin;
  endFile = true;
  return ans;
}

void readElementsFile(FILE *& f, std::vector<std::pair<FullName, BirthDate> >& people_alias) {
  bool error = false;
  bool endFile = false;
  while (!endFile) {
    std::pair<FullName, BirthDate> temp;
    bool endLine = false;
    temp.first.surname = readString(f, endLine, endFile, error);
    if ((endLine)||(error)) { exit(EXIT_FAILURE); }
    temp.first.name = readString(f, endLine, endFile, error);
    if ((endLine)||(error)) { exit(EXIT_FAILURE); }
    temp.second.year = readNumber(f, endLine, endFile, error);
    if ((endLine)||(error)) { exit(EXIT_FAILURE); }
    temp.second.month = readNumber(f, endLine, endFile, error);
    if ((endLine)||(error)) { exit(EXIT_FAILURE); }
    temp.second.day = readNumber(f, endLine, endFile, error);
    if (error) { exit(EXIT_FAILURE); }
    if ((!endFile)&&(!endLine)) { exit(EXIT_FAILURE); }
    people_alias.push_back(temp);
  }
}

template<typename T>
void printElementsScreen(const T& container) {
  typename T::const_iterator it = container.begin();
  while (it != container.end()) {
    std::cout << *it << "\n";
    ++it;
  }
}

template<typename R, typename S>
void sortElements(std::vector<R>& list, S& orderingOperator) {
  if (list.size() > 1) {
    R app;
    size_t minPos;
    for (size_t i = 0; i < list.size()-1; i++) {
      minPos = i;
      for (size_t j = i+1; j < list.size(); j++) {
	if (orderingOperator(list[j],list[minPos])) {
	  minPos = j;	  
	}
      }
      app = list[i];
      list[i] = list[minPos];
      list[minPos] = app;
    }
  }
}

template<typename T1, typename T2>
void flipPairs(const std::vector<std::pair<T1,T2> >& oldVector, std::vector<std::pair<T2,T1> >& newVector) {  
  typename std::vector<std::pair<T1,T2> >::const_iterator it = oldVector.begin();
  while (it != oldVector.end()) {
    std::pair<T2,T1> app;
    app.first = (*it).second;
    app.second = (*it).first;
    newVector.push_back(app);
    ++it;
  }
}

int main(void) {
  FILE * f = fopen("data.fil","r");
  if (f == NULL) { return EXIT_FAILURE; }
  std::vector<std::pair<FullName, BirthDate> > people;
  readElementsFile(f,people);
  if (fclose(f)!=0) {
    std::cerr << "Failed to close the file!";
    return EXIT_FAILURE;
  }
  std::cout << "\nOriginal elements:\n";
  printElementsScreen<std::vector<std::pair<FullName, BirthDate> > >(people);
  OrderPerson app1;
  sortElements<std::pair<FullName, BirthDate>,OrderPerson>(people, app1);
  std::cout << "\nSorted elements:\n";
  printElementsScreen<std::vector<std::pair<FullName, BirthDate> > >(people);
  std::vector<std::pair<BirthDate, FullName> > elpoep;
  flipPairs<FullName, BirthDate>(people, elpoep);
  std::cout << "\nSwapped elements:\n";
  printElementsScreen<std::vector<std::pair<BirthDate, FullName> > >(elpoep);
  OrderNosrep app2;
  sortElements<std::pair<BirthDate, FullName>,OrderNosrep>(elpoep, app2);
  std::cout << "\nSorted elements:\n";
  printElementsScreen<std::vector<std::pair<BirthDate, FullName> > >(elpoep);
  return EXIT_SUCCESS;
}

