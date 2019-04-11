#include<iostream>
#include<fstream>
using namespace std;

fstream file;
fstream file1;
void menu()
{
	system("cls");
	cout<<"Welcome to music manager:\n"<<endl;
	cout<<"Choose your option:\n "<<endl;
	cout<<"1->Add Record"<<endl;
	cout<<"2->Display all Records"<<endl;
	cout<<"3->Search Records"<<endl;
	cout<<"4->Show items that are in stock"<<endl;
	cout<<"5->Modify Record"<<endl;
	cout<<"6->Delete Record"<<endl;
}

class music
{
		int id, stock; 
		char name[30], category[25], type[25], artist[25];
		double price;
	public:
		void enter_data()
		{
			cout<<"Enter following data: "<<endl;
			cout<<"Enter track's ID: "; cin>>id;
			cout<<"Enter track's name: "; cin>>name;
			cout<<"Enter category(new/old): "; cin>>category;
			cout<<"Enter type(mp3/m4a/flac): "; cin>>type;
			cout<<"Enter Artist: "; cin>>artist;
			cout<<"Enter Price: "; cin>>price;
			cout<<"Enter Stock: "; cin>>stock;
		}
		void display()
		{
			cout<<"ID: "<<id<<endl;
			cout<<"Name: "<<name<<endl;
			cout<<"Category: "<<category<<endl;
			cout<<"Type: "<<type<<endl;
			cout<<"Artist: "<<artist<<endl;
			cout<<"Price: $"<<price<<endl;
			cout<<"Stock: "<<stock<<endl;
		}
		
		string getname()
		{
			return name;
		}
		
		string gettype()
		{
			return type;
		}
		string getcat()
		{
			return category;
		}
		string getart()
		{
			return artist;
		}
		int getstock()
		{
			return stock;
		}
		int getid()
		{
			return id;
		}
};
music m;

void write_data()
{
	system("cls");
	
	file.open("musicM.txt", ios::binary| ios::out| ios::app);
	m.enter_data();
	file.write((char*)&m, sizeof(m));
	file.close();
			
}
void read_all_data()
{
	system("cls");
	file1.open("musicM.txt", ios::binary| ios::in);
	while(file1.read((char*)&m, sizeof(m)) != NULL)
	{
		m.display();
		cout<<endl;
	}
	file1.close();		
}
void search_options()
{
	system("cls");
	cout<<"Enter a number to search by: "<<endl;
	cout<<"1-> Type(mp3/m4a/flac)"<<endl;
	cout<<"2-> Name"<<endl;
	cout<<"3-> Category"<<endl;
	cout<<"4-> Artist"<<endl;
}

void search_type()
{
	system("cls");
	char n[30];
	int state=0;
	cout<<"Enter type of the music(mp3/m4a/flac): "<<endl;
	cin>>n;
	file.open("musicM.txt", ios::binary| ios::in);
	while(file.read((char*)&m, sizeof(m)) != NULL)
	{
		if(m.gettype()==n)
		{
			m.display();
			state=1;
			cout<<endl;
		}
	} 
	file.close();
	if(state==0)
	{
		cout<<"Type not found!"<<endl;
	}
}
void search_name()
{
	system("cls");
	char n[30];
	int state=0;
	cout<<"Enter Name of the music: "<<endl;
	cin>>n;
	file.open("musicM.txt", ios::binary| ios::in);
	while(file.read((char*)&m, sizeof(m)) != NULL)
	{
		if(m.getname()==n)
		{
			m.display();
			state=1;
			cout<<endl;
		}
	} 
	file.close();
	if(state==0)
	{
		cout<<"Name not found!"<<endl;
	}
}
void search_category()
{
	system("cls");
	char n[30];
	int state=0;
	cout<<"Enter Category of the music(new/old): "<<endl;
	cin>>n;
	file.open("musicM.txt", ios::binary| ios::in);
	while(file.read((char*)&m, sizeof(m)) != NULL)
	{
		if(m.getcat()==n)
		{
			m.display();
			state=1;
			cout<<endl;
		}
	} 
	file.close();
	if(state==0)
	{
		cout<<"Category not found!"<<endl;
	}
}
void search_artist()
{
	system("cls");
	char n[30];
	int state=0;
	cout<<"Enter Artist of the music: "<<endl;
	cin>>n;
	file.open("musicM.txt", ios::binary| ios::in);
	while(file.read((char*)&m, sizeof(m)) != NULL)
	{
		if(m.getart()==n)
		{
			m.display();
			state=1;
			cout<<endl;
		}
	} 
	file.close();
	if(state==0)
	{
		cout<<"Artist not found!"<<endl;
	}
}
void search_rec()
{
	int n;
	search_options();
	cin>>n;
	switch(n)
	{
		case 1:
			search_type();
			break;
		case 2:
			search_name();
			break;
		case 3:
			search_category();
			break;
		case 4:
			search_artist();
			break;
		default:
			cout<<"Number not valid!"<<endl;
	}
}
void stock()
{
	system("cls");
	int state=0;
	file.open("musicM.txt", ios::in | ios::binary);
	while(file.read((char*)&m, sizeof(m)) != NULL)
	{
		if(m.getstock() > 0)
		{
			m.display();
			cout<<endl;
			state=1;
		}
	}
	if(state==0)
	{
		cout<<"Stock is Empty!"<<endl;
	}
	file.close();
}

void modify()
{
	system("cls");
	int n;
	int state=0;
	cout<<"Enter ID of the record that you want to edit: "; cin>>n;
	file.open("musicM.txt", ios::binary| ios::in| ios::out);
	while(file.read((char*)&m, sizeof(m))!= NULL)
	{
		if(m.getid()==n)
		{
			state=1;
			file.seekg(0,ios::cur);
			m.enter_data();
			file.seekp(file.tellg() - sizeof(m));
			file.write((char*)&m, sizeof(m));
			break;
		}
	}
	if(state==0)
	{
		cout<<"ID not found!"<<endl;
	}
	file.close();
}

void delete_rec()
{
	system("cls");
	int n;
	cout<<"Enter ID of the record that you want to delete: "; cin>>n;
	file.open("musicM.txt", ios::in| ios::binary);
	file1.open("temp.txt", ios::out| ios::binary);
	while(file.read((char*)&m, sizeof(m)) != NULL)
	{
		if(m.getid() != n)
		{
			file1.write((char*)&m, sizeof(m));
		}
	}
	file1.close();
	file.close();
	remove("musicM.txt");
	rename("temp.txt", "musicM.txt");
	cout<<"Record Deleted Successfully!"<<endl;
	
}

int main()
{
	int n;
	char a ='n';
	do
	{
		menu();
		cin>>n;
		switch(n)
		{
			case 1:
				write_data();
				break;
			case 2:
				read_all_data();
				break;
			case 3:
				search_rec();
				break;
			case 4:
				stock();
				break;
			case 5:
				modify();
				break;
			case 6:
				delete_rec();
				break;
			default:
				cout<<"Enter valid number: ";
		}
		cout<<"Go to Main Menu?(y/n)"; cin>>a;
	}
	while(a=='y'||a=='Y');
	return 0;
}
