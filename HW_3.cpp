#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <optional>
#include <vector>

using namespace std;

struct Person {

	string m_surname;
	string m_name;
	optional<string> m_lastname;

	Person(string name, string surname) :
		m_surname(surname), m_name(name) {}

	friend bool operator <(const Person& t1, const Person& t2);

	friend bool operator ==(const Person& t1, const Person& t2);

	friend ostream& operator<< (ostream& out, struct Person& person);
};

bool operator < (const Person& t1, const Person& t2) {

	return tie(t1.m_surname, t1.m_name, t1.m_lastname) <
		tie(t2.m_surname, t2.m_name, t2.m_lastname);
};

bool operator == (const Person& t1, const Person& t2) {

	return tie(t1.m_surname, t1.m_name, t1.m_lastname) ==
		tie(t2.m_surname, t2.m_name, t2.m_lastname);
};


ostream& operator<< (ostream& out, struct Person& person) {
	out << person.m_surname << " " << person.m_name << endl;
	return out;
};

struct PhoneNumber {
	int m_country_code;
	int m_city_code;
	string m_number;
	optional<int> m_extension;

	friend ostream& operator << (ostream& out, struct PhoneNumber& pn);
};

ostream& operator << (ostream& out, struct PhoneNumber& pn) {
	out << "+" << pn.m_country_code << "(" << pn.m_city_code << ")" << pn.m_number;
	if (pn.m_extension.has_value()) {
		out << " " << pn.m_extension.value();
	};
	return out;
};

int main() {
	PhoneNumber p_num;
	cout << p_num;
}

class PhoneBook {
	
public:
	vector< pair<Person, PhoneNumber> > m_phonebook;

	PhoneBook(ifstream& pb){
		if (pb.is_open()) {
			for (const auto& [person, phone_number] : m_phonebook) {

			};
		}
	};
};

int main() {

	ifstream file("D:\GB\C++\P3\HW_3\PhoneBook.txt"); // путь к файлу PhoneBook.txt
	PhoneBook book(file);
	cout << book;

	cout << "------SortByPhone-------" << endl;
	book.SortByPhone();
	cout << book;

	cout << "------SortByName--------" << endl;
	book.SortByName();
	cout << book;

	cout << "-----GetPhoneNumber-----" << endl;
	auto print_phone_number = // лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой

	// вызовы лямбды
		print_phone_number("Ivanov");
	print_phone_number("Petrov");

	cout << "----ChangePhoneNumber----" << endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", nullopt });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
	cout << book;
}
