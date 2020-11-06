#include <iostream>
#include <string.h>
#include <conio.h>
#include <fstream>
#define max 100
using namespace std;
// concepts of oops used
// inheritence,
// array of objects,
// exception handling,
// file handling

//Class Patient
class Patient
{
public:
	char name[100];
	char address[100];
	char phone[12];
	char from_date[20];
	char to_date[20];
	float payment_advance;
	int booking_id;
};

class Room
{
public:
	char type;
	char stype;
	char ac;
	int roomNumber;
	int rent;
	int status;
	char special;

	class Patient patient;
	class Room addRoom(int);
	void searchRoom(int);
	void deleteRoom(int);
	void displayRoom(Room);
};

//Global Declarations
// number of rooms in hospital
// and count of that room
Room rooms[max];
int count = 0;

Room Room::addRoom(int rno)
{
	class Room room;
	room.roomNumber = rno;
	ofstream outFile;//file handling
	outFile.open("room.dat",ios::binary|ios::app);
	
	
	cout << "\n Is this a room in COVID-19 ward ? (Y/N) : ";
	cin >> room.special;
	cout << "\nType AC/Non-AC (A/N) : ";
	cin >> room.ac;
	cout << "\nType Comfort (S/N) : ";
	cin >> room.type;
	cout << "\nType Bed Size (B/S) : ";
	cin >> room.stype;
	cout << "\nDaily Rent : ";
	cin >> room.rent;
	room.status = 0;
	
	outFile.write(reinterpret_cast<char *> (&room), sizeof(Room));
	cout << "\n Room Added Successfully!";
	getch();
	return room;
}

void Room::searchRoom(int rno)
{
	int i, found = 0;
	for (i = 0; i < count; i++)
	{
		if (rooms[i].roomNumber == rno)
		{
			found = 1;
			break;
		}
	}
	try//exception handling
	{
		if (found == 1)
		{
			cout << "Room Details\n";
			if (rooms[i].status == 1)
			{
				cout << "\nRoom is Reserved";
			}
			else
			{
				cout << "\nRoom is available";
			}
			displayRoom(rooms[i]);
			getch();
		}
		else
		{
			throw found;
		}
	}

	catch (int y)
	{
		//"Exception occured (" << y << "):
		cout << " Room not found!!" << endl;
		getch();
	}
}

void Room::displayRoom(Room tempRoom)
{

	cout << "\nRoom Number: \t" << tempRoom.roomNumber;
	cout << "\nCOVID-19 Room (Y/N) " << tempRoom.special;
	cout << "\nType AC/Non-AC (A/N) " << tempRoom.ac;
	cout << "\nType Comfort (S/N) " << tempRoom.type;
	cout << "\nType Size (B/S) " << tempRoom.stype;
	cout << "\nRent: " << tempRoom.rent;
}

//hospital management class
//inheritence
class HospitalMgnt : protected Room
{
public:
	void checkIn();
	void getAvailRoom();
	void searchPatient(char *);
	void checkOut(int);
	void totalPatientsSummary();
};

void HospitalMgnt::totalPatientsSummary()
{

	if (count == 0)
	{
		cout << "\n No patient in Hospital !!";
	}
	for (int i = 0; i < count; i++)
	{
		if (rooms[i].status == 1)
		{
			cout << "\n Person's First Name : " << rooms[i].patient.name;
			cout << "\n Room Number : " << rooms[i].roomNumber;
			if (rooms[i].special == 'Y')
				cout << "\n COVID-19 : "
					 << "Positive";
			else
				cout << "\n COVID-19 : "
					 << "Negative";
			cout << "\n Address (only city) : " << rooms[i].patient.address;
			cout << "\n Phone : " << rooms[i].patient.phone;
			cout << "\n---------------------------------------";
		}
	}

	getch();
}

//hospital management reservation of room
void HospitalMgnt::checkIn()
{
	int i, found = 0, rno;

	class Room room;
	cout << "\nEnter Room number : ";
	cin >> rno;
	for (i = 0; i < count; i++)
	{
		if (rooms[i].roomNumber == rno)
		{
			found = 1;
			break;
		}
	}
	try//exception handling
	{
		if (found == 1)
		{
			if (rooms[i].status == 1)
			{
				cout << "\nRoom is already Booked";
				getch();
				return;
			}

			cout << "\nEnter booking id: ";
			cin >> rooms[i].patient.booking_id;

			cout << "\nEnter Patient's Name (First Name): ";
			cin >> rooms[i].patient.name;

			cout << "\nEnter Address (only city): ";
			cin >> rooms[i].patient.address;

			cout << "\nEnter Phone: ";
			cin >> rooms[i].patient.phone;

			cout << "\nEnter Admit Date: ";
			cin >> rooms[i].patient.from_date;

			//cout<<"\nEnter to  Date: ";
			//cin>>rooms[i].patient.to_date;

			cout << "\nEnter Advance Payment: ";
			cin >> rooms[i].patient.payment_advance;

			rooms[i].status = 1;

			cout << "\n Patient Checked-in Successfully..";
			getch();
		}

		else
		{
			throw found;
		}
	}

	catch (int found)
	{
	//	cout << "Exception occured : "
			cout << "No room with " << rno << " room number!" << endl;
		getch();
	}
}

//hospital management shows available rooms
void HospitalMgnt::getAvailRoom()
{
	int i, found = 0;
	for (i = 0; i < count; i++)
	{
		if (rooms[i].status == 0)
		{
			displayRoom(rooms[i]);
			cout << "\n\nPress enter for next room";
			found = 1;
			getch();
		}
	}
	if (found == 0)
	{
		cout << "\nAll rooms are reserved right now";
		getch();
	}
}

//hospital management shows all patients that have booked room
void HospitalMgnt::searchPatient(char *pname)
{
	int i, found = 0;
	for (i = 0; i < count; i++)
	{
		if (rooms[i].status == 1 && stricmp(rooms[i].patient.name, pname) == 0)
		{
			cout << "\nPatient's Name: " << rooms[i].patient.name;
			cout << "\nRoom Number: " << rooms[i].roomNumber;
			if (rooms[i].special == 'Y')
				cout << "\nThis patient is COVID-19 positive";
			else
				cout << "\nThis patient is COVID-19 negative\n";
			cout << "\n\nPress enter for next record";
			found = 1;
			getch();
		}
	}
	if (found == 0)
	{
		cout << "\nPatient not found.";
		getch();
	}
}

//hospital management generates the bill of the expenses
void HospitalMgnt::checkOut(int roomNum)
{
	int i, found = 0, days, rno;
	float billAmount = 0;
	for (i = 0; i < count; i++)
	{
		if (rooms[i].status == 1 && rooms[i].roomNumber == roomNum)
		{
			//rno = rooms[i].roomNumber;
			found = 1;
			//getch();
			break;
		}
	}
	try
	{
		if (found == 1)
		{
			cout << "\nEnter Number of Days:\t";
			cin >> days;
			billAmount = days * rooms[i].rent;

			cout << "\n\t######## CheckOut Details ########\n";
			cout << "\nPatient's Name : " << rooms[i].patient.name;
			cout << "\nRoom Number : " << rooms[i].roomNumber;
			if (rooms[i].special == 'Y')
				cout << "\nCOVID-19 recovered Patient\n";

			cout << "\nAddress : " << rooms[i].patient.address;
			cout << "\nPhone : " << rooms[i].patient.phone;
			cout << "\nTotal Amount Due : " << billAmount << " /-";
			cout << "\nAdvance Paid: " << rooms[i].patient.payment_advance << " /-";
			cout << "\n*** Total Payable: " << billAmount - rooms[i].patient.payment_advance << "/- only";

			rooms[i].status = 0;
			getch();
		}
		else
		{
			throw found;
		}
	}

	catch (int found)
	{
		cout << "Error occured : NO such room no. is present!" << endl;
		getch();
	}
}

//managing rooms (adding and searching available rooms)
void manageRooms()
{
	class Room room;
	int opt, rno, i, flag = 0;
	char ch;
	do
	{
		system("cls");
		cout << "\n ### Manage Rooms ###";
		cout << "\n 1. Add Room";
		cout << "\n 2. Search Room";
		cout << "\n 3. Back to Main Menu";
		cout << "\n\n Enter Option: ";
		cin >> opt;

		//switch statement
		switch (opt)
		{
		case 1:
			cout << "\n Enter Room Number: ";
			cin >> rno;
			i = 0;
			for (i = 0; i < count; i++)
			{
				if (rooms[i].roomNumber == rno)
				{
					flag = 1;
				}
			}
			if (flag == 1)
			{
				cout << "\n Room Number is already present.\n Please enter unique Number";
				flag = 0;
				getch();
			}
			else
			{
				rooms[count] = room.addRoom(rno);
				count++;
			}
			break;
		case 2:
			cout << "\n Enter room number: ";
			cin >> rno;
			room.searchRoom(rno);
			break;
		case 3:
			//nothing to do
			break;
		default:
			cout << "\n Please Enter correct option";
			break;
		}
	} while (opt != 3);
}

int main()
{
	class HospitalMgnt hm;
	int i, j, opt, rno;
	char ch;
	char pname[100];

	system("cls");

	do
	{
		system("cls");
		cout << "######## Hospital Bed Management in COVID-19 period #########\n";
		cout << "\n 1. Manage Rooms";
		cout << "\n 2. Check-In Room";
		cout << "\n 3. Available Rooms";
		cout << "\n 4. Search Patient";
		cout << "\n 5. Check-Out Room";
		cout << "\n 6. All Patient's Summary";
		cout << "\n 7. Exit";
		cout << "\n\n Enter Option: ";
		cin >> opt;
		switch (opt)
		{
		case 1:
			manageRooms();
			break;
		case 2:
			if (count == 0)
			{
				cout << "\nRooms data is not available.\nPlease add the rooms first.";
				getch();
			}
			else
				hm.checkIn();
			break;
		case 3:
			if (count == 0)
			{
				cout << "\nRooms data is not available.\nPlease add the rooms first.";
				getch();
			}
			else
				hm.getAvailRoom();
			break;
		case 4:
			if (count == 0)
			{
				cout << "\nRooms are not available.\nPlease add the rooms first.";
				getch();
			}
			else
			{
				cout << "Enter Patient's Name: ";
				cin >> pname;
				hm.searchPatient(pname);
			}
			break;
		case 5:
			if (count == 0)
			{
				cout << "\nRooms are not available.\nPlease add the rooms first.";
				getch();
			}
			else
			{
				cout << "Enter Room Number : ";
				cin >> rno;
				hm.checkOut(rno);
			}
			break;
		case 6:
			hm.totalPatientsSummary();
			break;
		case 7:
			cout << "\nTHANK YOU! FOR USING OUR SOFTWARE. GREETINGS OF THE DAY..";
			break;
		default:
			cout << "\nPlease Enter correct option";
			break;
		}
	} while (opt != 7);

	getch();

	return 0;
}
