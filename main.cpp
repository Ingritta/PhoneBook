#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <sstream>
#include <string>
#include <cstdio>
#include <vector>

//DZIALA//

using namespace std;

string loadText() {
    string text = "";
    cin.sync();
    getline(cin, text);
    return text;
}

char loadChar() {
    string text = "";
    char sign = {0};

    while (true) {
        cin.sync();
        getline(cin, text);
        if (text.length() == 1) {
            sign = text[0];
            break;
        }
        cout << "Prosze wpisac pojedynczy znak." << endl;
    }
    return sign;
}

int loadNumber() {
    string text = "";
    int number = 0;

    while(true) {
        cin.sync();
        getline(cin, text);
        stringstream myStream(text);
        if (myStream >> number)
            break;
        cout << "To nie jest liczba. Prosze wpisac liczbe." << endl;
    }
    return number;
}

int findSignPosition(string line) {
    size_t position = line.find('|');
    if (position != string::npos)
        return position;
    else {
        return 0;
    }
}

string findData(string line) {
    string data;
    fstream file;
    int position = findSignPosition(line);

    for (int k = 0; k < position; k++) {
        getline(file, data);
        data += line[k];
    }
    return data;
}

struct Person {
    int userId;
    string name, surname, eMail, address, phoneNo;
};

void printPerson(Person person) {
    cout << person.userId << "|" << person.name << "|" << person.surname << "|"  << person.phoneNo << "|" << person.eMail << "|" << person.address << "|" << endl;
}

int loadDataFromFile(vector<Person> &contacts) {
    string name, surname, eMail, address, phoneNumber, line, userId;
    Person data;
    int newUserId, lineNo = 1;
    fstream file;

    file.open("PhoneBook.txt", ios::in);
    if(!file.good()) {
        cout << "Brak ksiazki adresowej!";
        exit(0);

    } else {
        while (getline(file,line)) {
            userId = findData(line);
            data.userId = atoi(userId.c_str()); // konwersja string na int
            line = line.erase(0, userId.length() + 1);
            data.name = findData(line);
            line = line.erase(0, name.length() + 1);
            data.surname = findData(line);
            line = line.erase(0, surname.length() + 1);
            data.phoneNo = findData(line);
            line = line.erase(0, phoneNumber.length() + 1);
            data.eMail = findData(line);
            line = line.erase(0, eMail.length() + 1);
            data.address = findData(line);
            contacts.push_back(data);

            lineNo++;
        }
        file.close();
    }
    if (contacts.size() >= 1) {
        newUserId = contacts.at(contacts.size() - 1).userId + 1;

    } else
        newUserId = 1;

    return newUserId;
}

void addContact(vector<Person> &contacts, int lastUserId) {
    Person data;
    system("cls");

    data.userId = lastUserId;
    cout << "Podaj imie: ";
    data.name = loadText();
    cout << "Podaj nazwisko: ";
    data.surname = loadText();
    cout << "Podaj numer telefonu: ";
    data.phoneNo = loadText();
    cout << "Podaj e-mail: ";
    data.eMail = loadText();
    cout << "Podaj adres: ";
    data.address = loadText();

    contacts.push_back(data);

    fstream file;
    file.open("PhoneBook.txt", ios::out | ios::app);

    if (file.good()) {
        file << data.userId << "|" << data.name << "|"<< data.surname << "|" << data.phoneNo << "|" << data.eMail << "|" << data.address << "|" << endl;
        file.close();

    } else {
        cout << "Brak ksiazki adresowej!";
        file.close();
        exit(0);
    }
    cout << "Kontakt zostal pomyslnie dodany." << endl;
    system ("pause");
}

void searchContactByName(vector<Person> &contacts) {
    string data;
    system("cls");

    if(contacts.size() == 0) {
        cout << "****BRAK KONTAKTOW W KSIAZCE ADRESOWEJ****" << endl;
        system ("pause");

    } else if (contacts.size() > 0) {
        cout << "Wpisz imie: ";
        data = loadText();

        for (unsigned int i = 0; i < contacts.size(); i++) {
            if (contacts.at(i).name == data) {
                printPerson(contacts[i]);
                system ("pause");
                break;

            } else if (i == contacts.size() - 1 && contacts.at(i).name != data) {
                cout << endl;
                cout << "****NIE MA TAKIEGO KONTAKTU****" << endl;
                cout << endl;
                system ("pause");
                break;
            }
        }
    }
}

void searchContactBySurname(vector<Person> &contacts) {
    system("cls");
    string data;

    if(contacts.size() == 0) {
        cout << "****BRAK KONTAKTOW W KSIAZCE ADRESOWEJ****" << endl;
        system ("pause");

    } else if (contacts.size() > 0) {
        cout << "Wpisz nazwisko: ";
        data = loadText();

        for (unsigned int i = 0; i < contacts.size(); i++) {
            if (contacts.at(i).surname == data) {
                printPerson(contacts[i]);
                system ("pause");
                break;
            } else if (i == contacts.size() - 1 && contacts.at(i).name != data) {
                cout << endl;
                cout << "****NIE MA TAKIEGO KONTAKTU****" << endl;
                cout << endl;
                system ("pause");
                break;
            }
        }
    }
}

void readPhoneBook(vector<Person> &contacts) {
    system("cls");
    if (contacts.size() > 0) {
        cout << "****AKTUALNA LISTA KONTAKTOW****" << endl << endl;
        for (unsigned int i = 0; i < contacts.size(); i++) {
            printPerson(contacts[i]);
        }
    } else {
        cout << "*****BRAK KONTAKTOW W KSIAZCE ADRESOWEJ*****" << endl;
    }
    system ("pause");
}

void changeDetails(vector<Person> &contacts) {
    system("cls");
    int userId,  endOfchange;
    char choice;
    string newData;
    fstream file;
    vector <Person>::iterator itr;

    if(contacts.size() == 0) {
        cout << "****BRAK KONTAKTOW W KSIAZCE ADRESOWEJ****" << endl;
        system ("pause");

    } else if (contacts.size() > 0) {
        cout <<"Wpisz ID uzytkownika, ktorego dane chcesz edytowac: ";
        userId = loadNumber();

        for (unsigned int i = 0 ; i < contacts.size(); i++) {
            if (i == contacts.size() - 1 && contacts.at(i).userId != userId && endOfchange != 1) {
                cout << endl << "****NIE MA TAKIEGO KONTAKTU****" << endl << endl;
                system ("pause");
                break;

            } else if (contacts.at(i).userId == userId) {
                printPerson(contacts[i]);

                cout << endl << "Wybierz pole, ktore chcesz edytowac: " << endl;
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. Numer telefonu" << endl;
                cout << "4. Adres e-mail" << endl;
                cout << "5. Adres zamieszkania" << endl;
                cout << "6. Powrot do poprzedniego menu" << endl;

                choice = loadChar();

                switch (choice) {
                case '1':
                    cout << "Wpisz nowe imie: ";
                    newData = loadText();

                    if (newData.length() != 0) {
                        file.open("PhoneBook.txt", ios::out | ios::trunc);
                        if (file.good() == false) {
                            exit(0);
                        } else {
                            for (auto itr = contacts.begin(); itr != contacts.end(); ++itr) {
                                if (itr->userId == userId) {
                                    itr->name = newData;
                                    file << itr->userId << "|" << itr->name << "|"<< itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                } else {
                                    file << itr->userId << "|" << itr->name << "|"<< itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                }
                            }
                            cout << endl << "Dane zostaly pomyslnie zmienione!" << endl << endl;
                            cout << "Dane kontaktu po wprowadzeniu zmian: " << endl;
                            printPerson(contacts[i]);
                            cout << endl;
                            endOfchange = 1;
                            file.close();
                            system ("pause");
                        }

                    } else {
                        cout << endl << "Dane nie zostalo zmienione!" << endl;
                        system ("pause");
                        endOfchange = 1;
                    }
                    break;

                case '2':
                    cout << "Wpisz nowe nazwisko: ";
                    newData = loadText();

                    if (newData.length() != 0) {
                        file.open("PhoneBook.txt", ios::out | ios::trunc);
                        if (file.good() == false) {
                            exit(0);
                        } else {
                            for (auto itr = contacts.begin(); itr != contacts.end(); ++itr) {
                                if (itr->userId == userId) {
                                    itr->surname = newData;
                                    file << itr->userId << "|" << itr->name << "|"<< itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                } else {
                                    file << itr->userId << "|" << itr->name << "|"<< itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                }
                            }
                            cout << endl << "Dane zostaly pomyslnie zmienione!" << endl << endl;
                            cout << "Dane kontaktu po wprowadzeniu zmian: " << endl;
                            printPerson(contacts[i]);
                            cout << endl;
                            endOfchange = 1;
                            file.close();
                            system ("pause");
                        }
                    } else {
                        cout << endl << "Dane nie zostalo zmienione!" << endl;
                        system ("pause");
                        endOfchange = 1;
                    }
                    break;

                case '3':
                    cout << "Wpisz nowy numer telefonu: ";
                    newData = loadText();

                    if (newData.length() != 0) {
                        file.open("PhoneBook.txt", ios::out | ios::trunc);
                        if (file.good() == false) {
                            exit(0);
                        } else {
                            for (auto itr = contacts.begin(); itr != contacts.end(); ++itr) {
                                if (itr->userId == userId) {
                                    itr->phoneNo = newData;
                                    file << itr->userId << "|" << itr->name << "|"<< itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                } else {
                                    file << itr->userId << "|" << itr->name << "|"<< itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                }
                            }
                            cout << endl << "Dane zostaly pomyslnie zmienione!" << endl << endl;
                            cout << "Dane kontaktu po wprowadzeniu zmian: "<< endl;
                            printPerson(contacts[i]);
                            cout << endl;
                            endOfchange = 1;
                            file.close();
                            system ("pause");
                        }
                    } else {
                        cout << endl << "Dane nie zostalo zmienione!" << endl;
                        system ("pause");
                        endOfchange = 1;
                    }
                    break;

                case '4':
                    cout << "Wpisz nowy adres e-mail: ";
                    newData = loadText();

                    if (newData.length() != 0) {
                        file.open("PhoneBook.txt", ios::out | ios::trunc);
                        if (file.good() == false) {
                            exit(0);
                        } else {
                            for (auto itr = contacts.begin(); itr != contacts.end(); ++itr) {
                                if (itr->userId == userId) {
                                    itr->eMail = newData;
                                    file << itr->userId << "|" << itr->name << "|"<< itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                } else {
                                    file << itr->userId << "|" << itr->name << "|"<< itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                }
                            }
                            cout << endl << "Dane zostaly pomyslnie zmienione!" << endl << endl;
                            cout << "Dane kontaktu po wprowadzeniu zmian: " << endl;
                            printPerson(contacts[i]);
                            cout << endl;
                            endOfchange = 1;
                            file.close();
                            system ("pause");
                        }

                    } else {
                        cout << endl << "Dane nie zostalo zmienione!" << endl;
                        system ("pause");
                        endOfchange = 1;
                    }
                    break;

                case '5':
                    cout << "Wpisz nowy adres zamieszkania: ";
                    newData = loadText();

                    if (newData.length() != 0) {
                        file.open("PhoneBook.txt", ios::out | ios::trunc);
                        if (file.good() == false) {
                            exit(0);
                        } else {
                            for (auto itr = contacts.begin(); itr != contacts.end(); ++itr) {
                                if (itr->userId == userId) {
                                    itr->address = newData;
                                    file << itr->userId << "|" << itr->name << "|" << itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                } else {
                                    file << itr->userId << "|" << itr->name << "|"<< itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                }
                            }
                            cout << endl << "Dane zostaly pomyslnie zmienione!" << endl << endl;
                            cout << "Dane kontaktu po wprowadzeniu zmian: " << endl;
                            printPerson(contacts[i]);
                            cout << endl;
                            endOfchange = 1;
                            file.close();
                            system ("pause");
                        }

                    } else {
                        cout << endl << "Dane nie zostalo zmienione!" << endl;
                        system ("pause");
                        endOfchange = 1;
                    }
                    break;

                case '6':
                    break;
                }
            }
        }
    }
}

int removeContact(vector<Person> &contacts) {
    system("cls");
    int userId, endOfchange, newUserId;
    char choice;
    fstream file;
    vector <Person>::iterator itr;

    if(contacts.size() == 0) {
        cout << "****BRAK KONTAKTOW W KSIAZCE ADRESOWEJ****" << endl;
        system ("pause");

    } else if (contacts.size() > 0) {
        cout <<"Wpisz ID uzytkownika, ktorego chcesz usunac: ";
        userId = loadNumber();

        for (unsigned int i = 0; i < contacts.size(); i++) {
            if (i == contacts.size() - 1 && contacts.at(i).userId != userId && endOfchange != 1) {
                cout << endl;
                cout << "****NIE MA TAKIEGO KONTAKTU****" << endl;
                cout << endl;
                system ("pause");
                break;

            } else if (contacts.at(i).userId == userId) {
                printPerson(contacts[i]);
                cout << endl;
                cout << "Czy na pewno chcesz usunac kontakt [t/n]?" << endl;

                choice = loadChar();

                switch (choice) {
                case 't':
                    file.open("PhoneBook.txt", ios::out | ios::trunc);
                    if (file.good() == false) {
                        exit(0);

                    } else
                        for (auto itr = contacts.begin(); itr != contacts.end();) {
                            if (itr->userId == userId) {
                                itr = contacts.erase(itr);
                            } else {
                                file << itr->userId << "|" << itr->name << "|"<< itr->surname << "|" << itr->phoneNo << "|" << itr->eMail << "|" << itr->address << "|" << endl;
                                ++itr;
                            }
                        }
                    cout <<"Kontakt zostal pomyslnie usuniety!" << endl << endl;
                    Sleep(1000);
                    endOfchange = 1;
                    readPhoneBook(contacts);
                    file.close();
                    break;

                case 'n':
                    break;
                }
            }
        }
    }
    if (contacts.size() >= 1) {
        newUserId = contacts.at(contacts.size() - 1).userId + 1;

    } else
        newUserId = 1;

    return newUserId;
}

int main() {
    vector<Person> contacts;
    char choise;
    int lastUserId;
    fstream file;

    file.open("PhoneBook.txt", ios::app);
    file.close();

    lastUserId = loadDataFromFile(contacts);

    while (true) {
        system("cls");
        cout << "@@@@ KSIAZKA TELEFONICZNA @@@@" << endl << endl;
        cout << "1. Dodaj kontakt" << endl;
        cout << "2. Wyszukiwanie po imieniu" << endl;
        cout << "3. Wyszukiwanie po nazwisku" << endl;
        cout << "4. Wyswietl kontakty" << endl;
        cout << "5. Edytuj kontakt" << endl;
        cout << "6. Usun kontakt" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Wybierz opcje z menu: ";

        choise = loadChar();

        switch (choise) {
        case '1':
            addContact(contacts, lastUserId);
            lastUserId++;
            break;

        case '2':
            searchContactByName(contacts);
            break;

        case '3':
            searchContactBySurname(contacts);
            break;

        case '4':
            readPhoneBook(contacts);
            break;

        case '5':
            changeDetails(contacts);
            break;

        case '6':
            lastUserId = removeContact(contacts);
            break;

        case '9':
            exit(0);
        }
    }
    return 0;
}
