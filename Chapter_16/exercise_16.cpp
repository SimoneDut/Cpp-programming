#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>

class IntArray;

std::ostream & operator << (std::ostream & stream, const IntArray & data);
std::istream & operator >> (std::istream & stream, IntArray & data);

class IntArray {
friend std::ostream & operator << (std::ostream & stream, const IntArray & data);
friend std::istream & operator >> (std::istream & stream, IntArray & data);
private:
  size_t numElements;
  int * elements;
public:
  IntArray(): elements(NULL), numElements(0) {}
  IntArray(size_t n): elements(new int[n]), numElements(n) {}
  ~IntArray() {
    delete[] elements;
  }
  IntArray(const IntArray & rhs): elements(new int[rhs.numElements]), numElements(rhs.numElements) {
    for (size_t i = 0; i < numElements; i++) {
      elements[i] = rhs.elements[i];
    }
  }
  IntArray & operator = (const IntArray & rhs) {
    if (this != &rhs) {
      int * temp = new int[rhs.numElements];
      for (size_t i = 0; i < rhs.numElements; i++) {
	temp[i] = rhs.elements[i];
      }
      delete[] elements;
      numElements = rhs.numElements;
      elements = temp;
    }
    return *this;
  }
  IntArray & operator += (const int & rhs) {
    int * temp = new int[numElements + 1];
    for (size_t i = 0; i < numElements; i++) {
      temp[i] = elements[i];
    }
    temp[numElements] = rhs;
    delete[] elements;
    numElements++;
    elements = temp;
    return *this;
  }
  int & operator [] (size_t index) {
    return elements[index];
  }
  size_t size() const {
    return numElements;
  }
  void setSize(size_t n) {
    int * temp = new int[n];
    for (size_t i = 0; i < n; i++) {
      if (i < numElements) {
	temp[i] = elements[i];
      }
      else {
	temp[i] = 0;
      }
    }
    delete[] elements;
    numElements = n;
    elements = temp;
  }
};

std::ostream & operator << (std::ostream & stream, const IntArray & data) {
  std::stringstream str_stream;
  for (size_t i = 0; i < data.numElements - 1; i++) {
    str_stream << data.elements[i] << " ";
  }
  if (data.numElements > 0) { str_stream << data.elements[data.numElements -1]; }
  std::string str = str_stream.str();
  stream << str << "\n";
  return stream;
}


std::istream & operator >> (std::istream & stream, IntArray & data) {
  std::string str;
  std::getline(stream,str);
  std::stringstream str_stream;
  str_stream << str;
  int x;
  do {
    str_stream >> x;
    data += x;
  }
  while (str_stream.good());
  str_stream.clear();
  return stream;
}


void reverse(std::string & s) {
  size_t l = s.length();
  std::string ans(l,'\0');
  for (size_t i = 0; i < l; i++) {
    ans[i] = s[l-1-i];
  }
  s = ans;
}

int main(void) {
  std::string str1("Bar");
  std::cout << "str1 is \"" << str1 << "\" and has length " << str1.length() << "\n";
  std::string str2 = str1;
  std::cout << "str2 is \"" << str2 << "\" and has length " << str2.length() << "\n";
  str2[0] = 'C';
  std::cout << "Now str2 is \"" << str2 << "\" and has length " << str2.length() << "\n";
  str2.append(str1);
  std::cout << "Appending str1 it becomes \"" << str2 << "\" and has length " << str2.length() << "\n";
  str2 += str1;
  std::cout << "Doing it another times it becomes \"" << str2 << "\" and has length " << str2.length() << "\n";
  reverse(str2);
  std::cout << "Reversing: \"" << str2 << "\" with length " << str2.length() << "\n";
  reverse(str2);
  std::cout << "One more time: \"" << str2 << "\" with length " << str2.length() << "\n";
  char * c_str2 = new char[str2.length() + 1];
  std::strcpy(c_str2, str2.c_str());
  std::cout << "Same ctring in C format: \"" << c_str2 << "\"\n";
  std::string str3(c_str2);
  delete[] c_str2;
  std::cout << "Back to C++ format: \"" << str3 << "\" with length " << str3.length() << "\n";
  std::cout << "Default minimum width: " << std::cout.width() << "\n";
  std::cout << "Default fill character: '" << std::cout.fill() << "'\n";
  std::cout << "Test with minimum width = 5 and fill character = 'x': \"";
  std::cout.width(5);
  std::cout.fill('x');
  std::cout << 15 << "\"\n";
  std::cout << "Test left: \"";
  std::cout.width(5);
  std::cout.fill('x');
  std::cout << std::left << 15 << std::right << "\"\n";
  std::cout << "Test hex \"" << std::hex << 15 << std::dec << "\"\n";
  std::cout << "Test oct \"" << std::oct << 15 << std::dec << "\"\n";
  std::cout << "Default precision: " << std::cout.precision() << "\n";
  float f = 1/(float)3;
  std::cout << "1/3 is: \"" << f << "\"\n";
  std::cout.precision(10);
  std::cout << "now 1/3 is: \"" << f << "\"\n";
  std::cout.precision(6);
  std::cout << "Type an integer:\n";
  bool read_corr;
  int x;
  do {
    read_corr = true;
    std::cin >> x;
    if(!std::cin.good()) {
      read_corr = false;
      std::cin.clear();
      std::string badinput;
      std::cin >> badinput;
      if(!std::cin.good()) {
	std::cerr << "Cannot read anything!\n";
	return EXIT_FAILURE;
      }
      std::cout << "You typed: \"" << badinput << "\" instead of an integer, try again!\n";
    }
  }
  while (!read_corr);
  std::cout << "You typed: \"" << x << "\"\n";
  std::cout << "Now type a sentence:\n";
  std::string sentence;
  std::cin >> sentence;
  std::cout << "I read: \"" << sentence << "\"\n";
  std::getline(std::cin,sentence);
  std::cout << "Try again:\n";
  std::getline(std::cin,sentence);
  std::cout << "Now with getline I read: \"" << sentence << "\"\n";
  std::string str4("12 34 567");
  std::stringstream str_stream;
  str_stream << str4;
  do {
    str_stream >> x;
    std::cout << x << "\n";
  }
  while (str_stream.good());
  str_stream.clear();
  IntArray a;
  std::cout << "a has size: " << a.size() << "\n";
  IntArray b(4);
  std::cout << "b has size: " << b.size() << "\n";
  a += 0;
  a += 1;
  a += 2;
  a += 3;
  b[0] = 0;
  b[1] = 1;
  b[2] = 2;
  b[3] = 3;
  b += 4;
  std::cout << "now a has size: " << a.size() << "and its elements are:";
  for (size_t k = 0; k < a.size(); k++) {
    std::cout << " " << a[k];
  }
  std::cout << "\n";
  std::cout << "now b has size: " << b.size() << "and its elements are:";
  for (size_t k = 0; k < b.size(); k++) {
    std::cout << " " << b[k];
  }
  std::cout << "\n";
  IntArray c;
  std::cout << "Reading array c of size " << c.size() << " (enter integers separated by spaces, WITHOUT the final space)\n";
  std::cin >> c;
  std::cout << "Displaying array c of size " << c.size() << ":\n";
  std::cout << c;
  std::cout << "Now writing c to a file\n";
  std::ofstream ofs;
  ofs.open("record.out");
  ofs << c;
  ofs.close();
  IntArray d;
  std::cout << "Now reading d from the file\n";
  std::ifstream ifs;
  ifs.open("record.out");
  ifs >> d;
  ifs.close();
  std::cout << d;
  return EXIT_SUCCESS;
}
