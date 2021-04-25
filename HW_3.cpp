#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <optional>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Person {

	string m_surname;
	string m_name;
	optional<string> m_lastname;

	//Person() {}
	//
	//Person(string surname, string name, optional<string> lastname)
	//	:m_surname(surname), m_name(name), m_lastname(lastname) {}
};

ostream& operator<< (ostream& out, const Person& person) {
	out.width(10);
	out << person.m_surname << " ";
	out.width(10);
	out << person.m_name << " ";
	out.width(15); 
	out << person.m_lastname.value_or("");
	return out;
}

bool operator < (const Person& t1, const Person& t2) {

	return tie(t1.m_surname, t1.m_name, t1.m_lastname) <
		tie(t2.m_surname, t2.m_name, t2.m_lastname);
}

bool operator == (const Person& t1, const Person& t2) {

	return tie(t1.m_surname, t1.m_name, t1.m_lastname) ==
		tie(t2.m_surname, t2.m_name, t2.m_lastname);
}



struct PhoneNumber {
	int m_country_code;
	int m_city_code;
	string m_number;
	optional<int> m_extension;

	//PhoneNumber() {}
	//
	//PhoneNumber(int country, int city, string num, optional<int> ext)
	//	:m_country_code(country), m_city_code(city), m_number(num), m_extension(ext) {}
};

ostream& operator<< (ostream& out, const PhoneNumber& pn) {
	out.width(15);
	out << "+" << pn.m_country_code << "(" << pn.m_city_code << ")" << pn.m_number;
	if (pn.m_extension.has_value()) {
		out << " " << pn.m_extension.value();
	};
	return out;
}

class PhoneBook {

public:

	vector< pair <Person, PhoneNumber> > m_phonebook;
	PhoneBook(ifstream& f_source) {

		while (!f_source.eof()) {

			Person person;
			PhoneNumber phone;
			string opt_check;

			f_source >> person.m_surname >> person.m_name >> opt_check;
			if (opt_check == "-") person.m_lastname = nullopt;
			else person.m_lastname = opt_check;

			f_source >> phone.m_country_code >> phone.m_city_code >> phone.m_number >> opt_check;
			if (opt_check == "-") phone.m_extension = nullopt;
			else phone.m_extension = stoi(opt_check);

			m_phonebook.push_back({ person, phone });
		}
	}

	friend ostream& operator << (ostream& out, const PhoneBook& pb) {
		for (const auto& [person, number] : pb.m_phonebook) {
			out << person << number << endl;
		}
		return out;
	}

	void SortByName() {
		sort(m_phonebook.begin(), m_phonebook.end(), 
			[] (pair<Person, PhoneNumber> t1, pair<Person, PhoneNumber> t2) {
				return tie(t1.first.m_surname, t1.first.m_name, t1.first.m_surname) < tie(t2.first.m_surname, t2.first.m_name, t2.first.m_surname); 
			});
	};

	void SortByPhone() {
		sort(m_phonebook.begin(), m_phonebook.end(),
			[](pair<Person, PhoneNumber> t1, pair<Person, PhoneNumber> t2) {
				return tie(t1.second.m_country_code, t1.second.m_city_code, t1.second.m_number, t1.second.m_extension) < 
					   tie(t2.second.m_country_code, t2.second.m_city_code, t2.second.m_number, t2.second.m_extension) ;
			});
	};

	tuple <string, PhoneNumber> GetPhoneNumber(string surname) {
		PhoneNumber number;
		string result = "";
		int count = 0;
		for_each(m_phonebook.begin(), m_phonebook.end(),
			[&](const auto& pos) {
				if (pos.first.m_surname == surname) {
					number = pos.second;
					count++;
				}
			});
		if (count == 0) result = "not found";
		else if (count > 1) result  = "more than 1";
		return make_tuple(result, number);
	};

	void ChangePhoneNumber(const Person& person, const PhoneNumber& pn) {
		auto match_check = find_if(m_phonebook.begin(), m_phonebook.end(),
			[person](const auto& pos) {
				return pos.first == person;
			});
		if (match_check != m_phonebook.end()) match_check->second = pn;
	};


};



int main() {

	ifstream file("D:\\GB\\C++\\P3\\HW_3\\PhoneBook.txt"); // путь к файлу PhoneBook.txt
	PhoneBook book(file);
	cout << book;

	cout << "------SortByPhone-------" << endl;
	book.SortByPhone();
	cout << book;
	
	cout << "------SortByName--------" << endl;
	book.SortByName();
	cout << book;
	
	//cout << "-----GetPhoneNumber-----" << endl;
	//auto print_phone_number = 
	//};
	 //лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
	
	// вызовы лямбды
	//print_phone_number("Ivanov");
	//print_phone_number("Petrov");
	//
	cout << "----ChangePhoneNumber----" << endl;
	book.ChangePhoneNumber(Person{ "Zaitsev", "Zakhar", "Artemovic" }, PhoneNumber{ 7, 123, "15344458", nullopt });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
	cout << book;
}
