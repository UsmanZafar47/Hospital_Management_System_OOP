#pragma once
#include<iostream>
#include<fstream>
#include<cstring>
#include<random>
#include<ctime>
#include<iomanip>
#include<conio.h>
#include<string>

using namespace std;

void loggedin(int);
void mainscreen();

bool isinfile(ifstream& file, char str1[])
{
	string usertemp;
	bool found = false;
	while (getline(file, usertemp))
	{
		if (file.eof())
			break;
		if (usertemp.compare(str1) == 0) // entered username and the one in file are same
		{
			found = true;
			break;
		}
		else {
			found = false;
		}
	}

	return found;
}

int getlinenumber(ifstream& file, char str[30])
{
	const int strsize = 30;
	int lines = 0;
	char line[strsize];
	while (file >> line)
	{
		if (strcmp(line, str) == 0)
			return lines;
		++lines;
	}
	return lines;
}

int totallines(ifstream& file)
{
	const int strsize = 30;
	int lines = 0;
	char line[strsize];
	while (file >> line)
	{
		++lines;
	}
	file.close();
	return lines;
}


class name 
{
	char first_name[30];
	char last_name[30];
	
public:
	
	name(string f_name="", string l_name="")
	{
		strcpy_s(this->first_name, f_name.c_str());
		strcpy_s(this->last_name, l_name.c_str());
	}
	void input(int n)
	{
		cout << "\t\t-->Enter your details\n";
		const int strsize = 30;
		cout << "\t\t-->First Name: ";
		cin >> first_name;
		cout << "\t\t-->Last Name: ";
		cin >> last_name;

		if (n == 1) 
		{
			ofstream doc_out;//writing for doctor name
			doc_out.open("Doc_name.txt", ios::app);
			doc_out << first_name << last_name << endl;
			doc_out.close();
		}

		if (n == 2)
		{
			ofstream pat_out;//writing for patient name
			pat_out.open("Patient_name.txt", ios::app);
			pat_out << first_name << last_name << endl;
			pat_out.close();
		}




	}

	virtual void display()
	{
		cout << first_name << " " << last_name;
	}

	void setfname(string str)
	{
		strcpy_s(this->first_name, str.c_str());
	}
	void setlname(string str)
	{
		strcpy_s(this->last_name, str.c_str());
	}

	string getfname() 
	{
		return first_name;
	}

	string getlname()
	{
		return last_name;
	}

};

class User
{
protected:
	char password[30];
	char user_name[30];
	char cnic[30];
	char c[30];
	name Name;//composition of name class
	int age;
	char gender;

public:
	
	User(string user_name = "", string password = "",string cnic = "",string x="",char gender='\0',int age=0)
	{
		strcpy_s(this->user_name, user_name.c_str());
		strcpy_s(this->password, password.c_str());
		strcpy_s(this->cnic, cnic.c_str());
		strcpy_s(this-> c ,x.c_str());
		this->gender = gender;
		this->age = age;

	}

	char* get_username()
	{
		return user_name;
	}
	char* get_cnic()
	{
		return cnic;
	}

	string get_password()
	{
		return password;
	}
	string getchoice() 
	{
		return c;
	
	}


	void input_name(int n) 
	{
		Name.input(n);//input name of user
		cout << "\t\t-->Enter Age: ";
			cin >> age;
		cout << "\t\t-->Gender (M or F): ";
		cin >> gender;

	}


	string password_input() 
	{
		int length = 0;
		bool flag = false; char temp_pass[30];


		cout << "\t\t\tYour password must be at least 8 characters long." << endl;
		cout << "\t\tPlease enter a password that contains at least one uppercase letter, ";
		cout << "one\n\t\tlowercase letter, special character and at least one digit.\n\n" << endl;
		cout << "\t\tPassword: ";
		cin >> password;

		length = strlen(password);
		while (length < 8)
		{
			cout << "\t\tYour password is less then 8 characters.\n ";
			cout << "\t\tPlease re-enter your password." << endl;
			cout << "\t\tPassword: ";
			cin >> password;
			length = strlen(password);
		}

		if (passwordcheck(password))
		{
			cout << "\t\tYour password is valid." << endl;
			cout << "\t\t   Confirm Password: ";
			cin >> temp_pass;

			for (int i = 0; i < strnlen(temp_pass, 30); i++) {
				if (temp_pass[i] == password[i])
				{
					//cout << "Success: \n";
					flag = true;
				}
				else
				{
					cout << "Enter again: ";
					cin >> temp_pass;
				}
			}
			if (flag == true)
			{
				cout << "\t\t   Success...\n";
			}
		
		}
		else
		{

			while (!passwordcheck(password))
			{
				cout << "\t\tYour password is not valid. \n";
				cout << "\t\tPlease make sure you enter password with at least one special character\n\t\t, lowercase, uppercase and at least one digit" << endl;
				cout << "\t\tPlease re-enter your password." << endl;
				cin >> password;
			}

			cout << "\t\tyour password is valid\n\n";
		}

		return password;
	}

	bool passwordcheck(char pass[])//for requiremnt of password special, lower, uppercase letter and digit
	{
		bool capital = false, small = false, digit = false, special = false;

		for (int i = 0; pass[i]; ++i)
			if (pass[i] >= 65 && pass[i] <= 90)
				capital = true;
			else if (pass[i] >= 97 && pass[i] <= 122)
				small = true;
			else if (pass[i] >= 48 && pass[i] <= 57)
				digit = true;
			else if ((pass[i] >= 33 && pass[i] <= 47) || (pass[i] >= 58 && pass[i] <= 64) || (pass[i] >= 91 && pass[i] <= 96) || (pass[i] >= 123 && pass[i] <= 126))
				special = true;


		if (capital && small && digit && special)
			return true;

		else
			return false;
	}

	void Register(int n)
	{
		const int strsize = 30;
		char usertemp[strsize];
		bool usernamefound = false;
		bool usernamefound1 = false;
		ofstream passfile; // for writing into password
		ofstream userin; // userin for writing into user file
		ifstream userout; // userout for reading from user file
		ofstream cnic_in;// cnic_in for writing cnic file
		ifstream cnic_out;//cnic_out for reading from cnic file
		// step 1: check the file
		passfile.open("password.txt", ios::app);
		
		cout << "\t\t --For logging into this App--\n \t   \t--Press Any Key-- \n";
		cin.ignore();
		while (true)
		{
			

			userout.open("username.txt", ios::app | ios::in | ios::out);
			cout << "\t\t-->Enter username: ";
			cin.getline(user_name, strsize, '\n');
			usernamefound = isinfile(userout, user_name);
			userout.close();
			if (usernamefound)
			{
				cout << "\t\t	username Already taken!" << endl;
				continue;
			}
			else {
				userin.open("username.txt", ios::app);
				userin << user_name << '\n';
				userin.close();
				password_input();
				passfile << get_password() << '\n';
				passfile.close();


				
				int temp_count=0;
				cnic_out.open("cnic.txt", ios::app | ios::in | ios::out);
				cout << "\t\t(cnic must be of 13 numbers -->Enter in this format XXXXX-XXXXXXX-X)\n\t\tEnter Cnic: ";
				cin >> cnic;
					
					for (int i = 0; cnic[i] != '\0'; i++)
						temp_count++;


				if(temp_count>15 || temp_count<15)
				{
					//cout << "Enter cnic again: ";
					while (cnic[15] != '\0') 
					{
						cout << "\t\t-->Enter cnic again: ";
						cin.getline(cnic, strsize, '\n');
						
						

					}
				}
		
				usernamefound1 = isinfile(cnic_out, cnic);
				cnic_out.close();
				if (usernamefound1 == true)
				{
					cout << "\t\tAlready Registered with this cnic!" << endl;
					
					continue;
				}
				else
				{
					cnic_in.open("cnic.txt", ios::app);
					cnic_in << cnic << '\n';
					cnic_in.close();


				}

				cout << "\n\t\tYou are registered\n ";
				
				cout << "\n\t\t  Use this username and password to log in " << endl;
				
				if(n==1)
				Login(n);
				if (n == 2)
					Login(n);
				break;
				

				
			}

			

		}
		
	}

	

	void savecred(ofstream& fout)
	{
		fout.write(user_name, sizeof(user_name));
		fout.write(password, sizeof(password));
	}
	void loadcred(ifstream& fin)
	{
		fin.read(user_name, sizeof(user_name));
		fin.read(password, sizeof(password));
	}

	void Login(int x) 
	{
		const int strsize = 30;
		static char CurrentUser[strsize];
		char username[strsize];
		char password1[strsize];
		char temp_pass[30];
		ifstream users, pass;
		bool login = false,flag = false;

		int wrongattemps = 0;
		users.open("username.txt");
		pass.open("password.txt");
		int i = 0;
		cin.ignore();
		while (true)
		{
			if (login)
				break;
			system("cls");
			cout << "\t\t------LOGIN--------\n";
			cout << "\t\t    Username: ";
			cin.getline(username, strsize, '\n');
			strcpy_s(CurrentUser, username);
			int numberoflines = totallines(users);// we gotta open the file again after this
			users.open("username.txt");
			if (isinfile(users, username)) 
			{  
				int on_line = numberoflines - getlinenumber(users, username);
				while (true)
				{
					pass.seekg(std::ios::beg);
					string temp;
					cout << "\t\t    Enter password: ";
					cin.getline(password1, strsize, '\n');
					


					for (int i = 0; i < on_line; i++)
					{
						getline(pass, temp); // this is supposed to read from file
					}
					if (strcmp(temp.c_str(), password1) == 0)
					{
						loggedin(x);
						login = true;
						goto outside;
					}
					else {
						++wrongattemps;
						cout << "\t\t    Wrong password!" << endl;
						login = false;
						if (wrongattemps == 5)
						{
							
							cout << "\t\t    There have been " << wrongattemps << " attemps." << endl;
							cout << "\t\t    Exiting.." << endl;
						goto outside;
						}
					}
				}
			}
			else {
				cout << "\n\t\t    Username Not Found!\n" << endl;
				i++;
				if (i == 3)
				{
					
					cout << "\t\t\n-->Please Register first<--\n" << endl;
					
					system("pause");
					break;
				}
			}

		}
	outside:
		cout << " ";
	}


	

};



//Doctor

class Doctor : public User
{
protected:
	float charges;
	char availability[30];
	char specialization[30];
	char experience[30];
	char city[30];
	char hospital_name[30];
	
public:
	User login;

	Doctor(string user_name = "", string password = "", string specialization = "", string experience="", string city="", string hospital_name="")
	{
		User();
		strcpy_s(this->user_name, user_name.c_str());
		strcpy_s(this->password, password.c_str());
		strcpy_s(this->specialization, specialization.c_str());
		strcpy_s(this->experience, experience.c_str());
		strcpy_s(this->city, city.c_str());
		strcpy_s(this->hospital_name, hospital_name.c_str());
	
	}

	void set_specialization(string S)
	{
		strcpy_s(this->specialization, S.c_str());
	}

	void set_experience(string experience) 
	{
		strcpy_s(this->experience, experience.c_str());
	}

	string get_specialization() 
	{
		return specialization;
	}

	string get_experience() 
	{
		return experience;
	}

	string get_city() 
	{
		return city;
	}

	string get_hospital() 
	{
		return hospital_name;
	}


	void input_doctor()//regisster as a doctor 
	{
		login.Register(1);
	}

	void loaddoc(ifstream& fin)
	{
		login.loadcred(fin);
		fin.read(reinterpret_cast<char*>(&Name), sizeof(Name));
		fin.read((char*)&age, sizeof(age));
		fin.read((char*)&gender, sizeof(gender));
		fin.read(cnic, sizeof(cnic));
		
	}

	

	void display()
	{
		system("cls");
		cout << "\t\tName: "; Name.display();
		cout << "\t\t\nAge: " << age << endl;
		cout << "\t\tGender: " << gender << endl;
		cout << "\t\tCNIC: " << login.get_cnic() << endl;
		cout << "\t\tEmail: " << login.get_username();
		cout << "\n\t\tSpecialization: " << get_specialization();
		cout << "\n\t\tExperience: " << get_experience() << "years";
		cout << "\n\t\tCity: " << get_city();
		cout << "\n\t\tHospital: " << get_hospital();
		cout << endl;
		system("pause");

	}
	//specialization input function
	void special_input()
	{
		const int strsize = 30;
		int n=0;
		system("cls");
		//specialization input
		cout << "\t\t-->Now Enter your specilization: \n";
		cout << "\t\t-->Press 1 For Gynecologist\n";
		cout << "\t\t-->Press 2 For Dermatologist\n";
		cout << "\t\t-->Press 3 For Oncologist\n";
		cout << "\t\t-->Press 4 For Orthopedic\n";
		cin >> n;
		
		while (n > 4 || n < 1) 
		{
			cout << "\t\t-->Invalid input. Enter valid input: ";
			cin >> n;
		}

		switch(n)
		{
		case 1:
			set_specialization("Gynecologist");
			break;
		case 2:
			set_specialization("Dermatologist");
			break;
		case 3:
			set_specialization("Oncologist");
			break;
		case 4:
			set_specialization("Orthopedic");
			break;
		}

		

	
	}


	void input()
	{
		login.Register(1);
		User::input_name(1);
		cout << "you are registered successfully.\n";
		

		ofstream cityfile;//wrting city 
		ofstream years;//writing years of experience
		ofstream special_in;//for writing specialization
		ofstream hospitalfile;//writing hospital name
		ofstream app_rate;
		
		special_in.open("Specialization.txt", ios::app);
		special_input();

		special_in << specialization << '\n';
		special_in.close();

		years.open("YearsOfExperience.txt", ios::app);
		cout << "-->Enter Your Years of Experience: ";
		cin >> experience;
		years << experience << '\n';
		years.close();
		
		cityfile.open("city.txt", ios::app);
		cout << "-->Enter your city: ";
		cin >> city;
		cityfile << city << endl;
		cityfile.close();

		hospitalfile.open("hospital.txt", ios::app);
		cout << "-->Enter your hospital name: ";
		cin >> hospital_name;
		hospitalfile << hospital_name<< endl;
		hospitalfile.close();

		
		app_rate.open("Appointment_price.txt", ios::app);
		cout << "Enter Appointment Price: ";
		cin >> charges;
		app_rate << charges << endl;
		app_rate.close();



		display();
	}


	//void mainmenu_doc(Doctor& obj)
	//{
	//	int c = 0;
	//	int price;
	//	int app_hour = 0;
	//	int app_min = 0;
	//	
	////	do {
	//		system("cls");
	//		cout << "\t\t   WELCOME "; obj.get_username(); cout << endl;
	//		cout << "\t\t    1.Show My details\n";
	//		cout << "\t\t    2.Show Appointments\n";
	//		cout << "\t\t    3.Change information of Appointment\n";
	//		cout << "\t\t    4.Add Appointment details: ";
	//		cout << "\t\t    press 0 to log out\n";
	//		cout << "\t\t        select:";
	//		cin >> c;

	//		if (c == 2) 
	//		{
	//			Appointment data;
	//			data.book_appointment();
	//		}
	//		if (c == 0)
	//		{
	//			//break;
	//		}
	//		else {
	//			cout << "\t\t    Wrong input\n";
	//		//	continue;
	//		}
	//	//} while (true);
	//}




};


class Patient : public User
{
protected:
	User patient;
	int account;

public:
	Patient()
	{
		User();
		account = 0;
	}

	User getPatient() 
	{
		return patient;
	}

	void set_bal(int a) 
	{
		account = account - a;
	}


	void recharge(int a)
	{
		account += a;
	}

	int get_account() 
	{
		return account;
	}


	void input()
	{
		patient.Register(2);
		User::input_name(2);
		cout << "account Balance: ";
		ofstream read;
		read.open("patient_balance.txt");
		account = 3500;
		cout << account;
		read << account << endl;
		read.close();
		cout << endl;

	}


};





class Appointment:public Patient
{
protected:
	Patient pat;
	Doctor doc;
	char temp_user[30];
	char temp_city[30];
	char temp_hospital[30];
	bool flag = false;
public:
	Appointment(string c="",string u="", string h = "")
	{
		Patient();
		Doctor();
		strcpy_s(this->temp_city, c.c_str());
		strcpy_s(this->temp_user, u.c_str());
		strcpy_s(this->temp_hospital, h.c_str());
	}

	bool getflag() 
	{
		return flag;
	}

	void get_doctor()
	{

		int c;
		static char CurrentUser[30];
		char temp_city1[30],user1[30],hosp1[30];
		char username1[30];
		ifstream hosp_in;//reading hospital
		ifstream user_in;//reading doc
		ifstream city_in;//reading city
		ifstream read1;//doctor data whole showing;
		ifstream read_city;//read city
		ifstream read_cnic;
		ifstream read_hos,read_price;
		char temp1[20],temp2[20],temp3[20],temp4[20],temp5[20];

		
		system("cls");

		read1.open("Doc_name.txt");
		read_city.open("city.txt");
		read_cnic.open("cnic.txt");
		read_hos.open("hospital.txt");
		read_price.open("Appointment_price.txt");

		while (read1.eof() == 0) {

			read1 >> temp1;
			read_city >> temp2;
			read_cnic >> temp3;
			read_hos >> temp4;
			read_price >> temp5;

			cout << "\t\t   Available Doctors: " << temp1 << endl;
			cout << "\t\t   City: " << temp2 << endl;
			cout << "\t\t   Cnic: " << temp3 << endl;
			cout << "\t\t   Appointment Price: " << temp5 << endl;
			cout << "\t\t   Hospital: " << temp4 << "\n\n\n";
			
		}
		read1.close();
		read_city.close();
		read_cnic.close();
		read_hos.close();
		read_price.close();

		cout << "\t\tPress 1 to search by city. \n";
		cout << "\t\tPress 2 to search by name. \n";
		cout << "\t\tPress 3 to search by Hospital.\n";
		cout << "\t\t  Enter: ";
		cin >> c;
		
		if (c == 1)
		{
		
			while (true)
			{
				if (flag)
					break;
				cin.ignore();
				cout << "\t\t    Enter city: ";
				cin >> temp_city1;

				strcpy_s(CurrentUser, temp_city1);
				city_in.open("city.txt");
				user_in.open("username.txt");



				int numberoflines = totallines(city_in);// we gotta open the file again after this
				city_in.open("city.txt");
				if (isinfile(city_in, temp_city1))
				{
					int on_line = numberoflines - getlinenumber(city_in, temp_city1);
					flag = true;
					//while (true)
					//{
					//	user_in.seekg(std::ios::beg);
					//	string temp;
					//	cout << "\t\t  Enter name: ";
					//		cin >> username1;

					//	for (int i = 0; i < on_line; i++)
					//	{
					//		getline(user_in, temp); // this is supposed to read from file
					//	}
					//	if (strcmp(temp.c_str(), username1) == 0)
					//	{
					//		book_appointment();
					//		flag = true;
					//		goto outside;
					//	}
					//	else
					//	{
					//		cout << "\t\tErorr\n \t\tEnter again";
					//	}
					//	break;

					//}
					//book_appointment();
					goto outside;
				}
			}
		outside:
			cout << ":(())\n";
		}

			else if (c == 2)
			{
				while (true)
				{
					if (flag)
						break;
					cin.ignore();
					cout << "Enter name: ";
					cin >> user1;

					strcpy_s(CurrentUser, user1);
					user_in.open("Doc_name.txt");
					//user_in.open("username.txt");

					int numberoflines = totallines(user_in);// we gotta open the file again after this
					user_in.open("Doc_Name.txt");
					if (isinfile(user_in, user1))
					{
						int on_line = numberoflines - getlinenumber(user_in, user1);
						flag = true;
						//while (true)
						//{
						//	user_in.seekg(std::ios::beg);
						//	string temp;
						//	cout << "\t\t  Enter name: ";
						//		cin >> username1;

						//	for (int i = 0; i < on_line; i++)
						//	{
						//		getline(user_in, temp); // this is supposed to read from file
						//	}
						//	if (strcmp(temp.c_str(), username1) == 0)
						//	{
						//		book_appointment();
						//		flag = true;
						//		goto outside;
						//	}
						//	else
						//	{
						//		cout << "\t\tErorr\n \t\tEnter again";
						//	}
						//	break;

						//}
						//book_appointment();
						goto outside1;
					}
				}
			outside1:
				cout << ":(\n";
			}

			else if (c == 3)
			{
				while (true)
				{
					if (flag)
						break;
					cin.ignore();
					cout << "Enter Hospital: ";
					cin >> temp_hospital;


					strcpy_s(CurrentUser, temp_hospital);
					hosp_in.open("hospital.txt");
					//user_in.open("username.txt");

					int numberoflines = totallines(hosp_in);// we gotta open the file again after this
					hosp_in.open("hospital.txt");
					if (isinfile(hosp_in, temp_hospital))
					{
						int on_line = numberoflines - getlinenumber(hosp_in, temp_hospital);
						flag = true;
						//while (true)
						//{
						//	user_in.seekg(std::ios::beg);
						//	string temp;
						//	cout << "\t\t  Enter name: ";
						//		cin >> username1;

						//	for (int i = 0; i < on_line; i++)
						//	{
						//		getline(user_in, temp); // this is supposed to read from file
						//	}
						//	if (strcmp(temp.c_str(), username1) == 0)
						//	{
						//		book_appointment();
						//		flag = true;
						//		goto outside;
						//	}
						//	else
						//	{
						//		cout << "\t\tErorr\n \t\tEnter again";
						//	}
						//	break;

						//}
						//book_appointment();
						goto outside2;
					}
				}
			outside2:
				cout << ":(\n";
						}



		}
	
	void book_appointment() 
	{
		system("cls");
		ifstream read1;//read doc
		char temp[20];

		read1.open("Doc_name.txt");
		while (read1.eof() == 0) {
				
			read1 >> temp;
			cout << "\t\t   Doctor: " << temp;
			
			break;
		}
			read1.close();

		cout << "\n\t\t   Book your appointment for particular time slot \n";
		cout << "\n\t\t   Available slots of this doctor" << " are \n";
		ifstream read;
		read.open("Appointment.dat");
		int hours;

		int ary[13] = { 0 };
		int record_found = 0;

		if (read) 
		{
			string inp;
			char key = 'A';
			int i = 9;

			while(getline(read,inp))
			{
				char temp = inp[0];
				int dx = (temp - 65);// for index
				ary[dx] = 1;
				record_found = 1;
			}
			
			if (record_found==1)
			{
				cout << "\n\t\t   Appointment List by Hours: " << endl;
				char key = 'A';
				int hours = 9;
				for(int i=0;i<13;i++)
				{
					if(i==0)
					{
						if (ary[i] == 0)
							cout << "\t\t   Press " << key << " to select appointment of 0" << hours << " hour status: Available" << endl;
						else
							cout << "\t\t   Press " << key << " to select appointment of 0" << hours << " hour status:Booked" << endl;

					}
				
					else 
					{
						if (ary[i] == 0)
							cout << "\t\t   Press " << key << " to select appointment of " << hours << " hour status: Available" << endl;
						else
							cout << "\t\t   Press " << key << " to select appointment of " << hours << "hour status: Booked" << endl;
								
					}
					hours++;
					key++;
				}
			}
			read.close();
		}
		
		if(record_found == 0)
		{
			cout << "\n\t\t   Appointment Availble in following hours: ";
			char key = 'A';
			for(int i = 9;i<22;i++)
			{
				if (i == 9)
					cout << "\n\t\t   Press " << key << "to select appointment of" << " 0" << i << " hour status :Available " << endl;
				else 
					cout << "\n\t\t   Press " << key << "to select appointment of " << i << " hour status :Available " << endl;
				key++;
			}
		
		}
	
		char x; // for input of switch cases 

		cout << "\n\t\t   Enter Choice: ";
		cin >> x;

		if(!(x>='A' && x <='Z'))
		{
			cout << "\t\t   Invalid Input " << endl << "\t\t   Please Enter Valid input" << endl;
			cout << "\t\tPress Any key " << endl;
			getchar();
			system("cls");
			book_appointment();

		}

		//pat.getPatient();
		string username;
		cout << "Enter name: ";
		cin >> username;

		ofstream f_out;
		f_out.open("Appointment.dat", ios::app);
		if(f_out)
		{
			f_out << x << ":" << username.c_str() << endl; 
			f_out.close();

			cout << "\t\t   Appointment booked for Hour: " << (x - 65) + 9 << " successfully !" << endl;
			set_bal(1000);



		}

		else
		{
			cout << "\t\t   Error while saving booking. " << endl;
		}

		cout << "\n\t\t   Please any key to continue" << endl;
		getchar(); 
	}

	void Booked_appointment()//shows booked appointment
	{
		system("cls");
		cout << "\n\t\t   Appointments Summary" << endl;

		ifstream read;
		read.open("Appointment.dat");

		int hours_book = 8;
		int ary[10] = { 0 };
		int record_found = 0;

		if (read)
		{
			string inp;
			char key = 'A';
			int x = 9;

			while (getline(read, inp))
			{
				char temp = inp[0];
				int dx = (temp - 65);// for index
				ary[dx] = 1;
				record_found = 1;
			}

			if (record_found == 1)
			{
				cout << "\n\t\t   Booked Appointment Summary by Hours: " << endl;
				char key = 'A';
				int hours = 9;
				for (int i = 0; i < 13; i++)
				{
					if (ary[i] == 0)
						cout << "\t\t  " << key << " 0" << hours << " hour status : Available" << endl;
					else
						cout << "\t\t  " << key << " 0" << hours << " hour status : Booked" << endl;

					hours++;
					key++;
				}
			}
			read.close();

		}
		else
		{
			char key = 'A';
			for (int i = 9; i < 22; i++)
			{
				if (i == 9)
					cout << "\n\t\t   " << key << " 0" << i << " hour status : Available " << endl;
				else
					cout << "\n\t\t   " << key << " " << i << " hour status : Available " << endl;
				key++;
			}
		
		}

		cout << "\n\t\t   Press any key to continue." << endl;
		getchar();
		getchar();
	}


};

class admin : public User
{
protected:
	User login1;
public:
	admin()
	{
	}

	void Mainmenu()
	{
		int c;
		cout << "\t\t   Press 1 to Show Appointments.\n";
		cout << "\t\t   Press 2 to Show Doctor Data. \n";
		cout << "\t\t   Press 3 to show Patient data.\n ";
		cout << "\t\t   Enter: ";
		cin >> c;
		if (c == 1)
		{
			Appointment m;
			m.Booked_appointment();
		}

		if (c == 2)
		{
			ifstream read1;//doctor data whole showing;
			ifstream read_city;//read city
			ifstream read_cnic;
			ifstream read_hos, read_price;
			char temp1[20], temp2[20], temp3[20], temp4[20], temp5[20];
			char temp_use[30], inp[30];
			string extra;
			bool flag = false;


			read_cnic.open("cnic.txt");
			//user_in.open("username.txt");
			cout << "(format XXXXX-XXXXXXX-X write with -)\nEnter Cnic: ";
			cin >> inp;
			if (inp[15] != '\0')
			{
				cout << "enter again: ";
				cin >> inp;
			}
			strcpy_s(temp_use, inp);
			int numberoflines = totallines(read_cnic);// we gotta open the file again after this
			read_cnic.open("cnic.txt");
			if (isinfile(read_cnic, inp))
			{
				int on_line = numberoflines - getlinenumber(read_cnic, inp);
				flag = true;
			}
			read_cnic.close();


			read1.open("Doc_name.txt");
			read_city.open("city.txt");
			read_cnic.open("cnic.txt");
			read_hos.open("hospital.txt");
			read_price.open("Appointment_price.txt");

			while (read1.eof() == 0) {



				read1 >> temp1;
				read_city >> temp2;
				read_cnic >> temp3;
				read_hos >> temp4;
				read_price >> temp5;

				extra = temp3;
				//temp3 = temp3;

				if (extra == inp)
				{
					//system("cls");

					cout << "\t\t   Doctor: " << temp1 << endl;
					cout << "\t\t   City: " << temp2 << endl;
					cout << "\t\t   Cnic: " << temp3 << endl;
					cout << "\t\t   Appointment Price: " << temp5 << endl;
					cout << "\t\t   Hospital: " << temp4 << "\n\n\n";
					break;
				}

				else
					extra = '\0';
			}
			read1.close();
			read_city.close();
			read_cnic.close();
			read_hos.close();
			read_price.close();

			cout << "Press any key to continue: ";
			getchar();
			getchar();




		}


		if (c == 3)
		{
			ifstream read1;//doctor data whole showing;
			ifstream read_city;//read city
			ifstream read_cnic;
			ifstream read_hos, read_price;
			char temp1[20], temp2[20], temp3[20], temp4[20], temp5[20];
			char temp_use[30], inp[30];
			string extra;
			bool flag = false;


			read_cnic.open("cnic.txt");
			//user_in.open("username.txt");
			cout << "(format XXXXX-XXXXXXX-X write with -)\nEnter Cnic: ";
			cin >> inp;
			if (inp[15] != '\0')
			{
				cout << "enter again: ";
				cin >> inp;
			}
			strcpy_s(temp_use, inp);
			int numberoflines = totallines(read_cnic);// we gotta open the file again after this
			read_cnic.open("cnic.txt");
			if (isinfile(read_cnic, inp))
			{
				int on_line = numberoflines - getlinenumber(read_cnic, inp);
				flag = true;
			}
			read_cnic.close();


			read1.open("Patient_name.txt");
			read_cnic.open("cnic.txt");

			while (read1.eof() == 0) {



				read1 >> temp1;
				read_cnic >> temp3;

				extra = temp3;
				//temp3 = temp3;

				if (extra == inp)
				{
					//system("cls");

					cout << "\t\t   Doctor: " << temp1 << endl;
					cout << "\t\t   Cnic: " << temp3 << endl;
					break;
				}

				else
					extra = '\0';
			}
			read1.close();
			read_cnic.close();

			cout << "Press any key to continue: ";
			getchar();
			getchar();


		}


	}

};


void mainmenu_patient(Patient& obj)
{
	Appointment app;
	int c = 0;
	//do {
		system("cls");
		cout << "\t\t   WELCOME "; obj.get_username(); cout << endl;
		cout << "\t\t    1.Show Available Appointments\n";
		cout << "\t\t    2.Book Appointment\n";
		cout << "\t\t    3.Show my Balance\n";
		cout << "\t\t    4.payment menu\n";
		cout << "\t\t    press 0 to log out\n";
		cout << "\t\t        select:";
		cin >> c;

		if(c==1)
		{
			app.Booked_appointment();
			mainmenu_patient(obj);
		}

		if (c == 2)
		{
			app.get_doctor();
			if ((app.getflag()) == true)
				app.book_appointment();
			mainmenu_patient(obj);
		}

		if (c == 0)
		{
			mainscreen();
			//break;
		}

		if(c==3)
		{
			cout << "\t\t   Current Balance: " << obj.get_account() << endl;
		}
	/*	else {
			cout << "\t\t    Wrong input\n";
			continue;
		}
	*///} while (true);
}



void mainmenu_doc(Doctor& obj)
{
	int c = 0;
	int price;
	int app_hour = 0;
	int app_min = 0;
	ifstream read2; 
	char temp1[20];
	do{
	system("cls");
	cout << "\t\t   WELCOME "; obj.get_username(); cout << endl;
	cout << "\t\t    1.Show My details\n";
	cout << "\t\t    2.Show Appointments\n";
	cout << "\t\t    3.Change Appointment price\n";
	cout << "\t\t    press 0 to log out\n";
	cout << "\t\t        select:";
	cin >> c;

	if (c == 1)
	{
		ifstream read1;//doctor data whole showing;
		ifstream read_city;//read city
		ifstream read_cnic;
		ifstream read_hos, read_price;
		char temp1[20], temp2[20], temp3[20], temp4[20], temp5[20];
		char temp_use[30], inp[30];
		string extra;
		bool flag=false;

		
		read_cnic.open("cnic.txt");
		//user_in.open("username.txt");
		cout << "(format XXXXX-XXXXXXX-X write with -)\nEnter Cnic: ";
		cin >> inp;
		if (inp[15] != '\0')
		{
			cout << "enter again: ";
				cin >> inp;
		}
		strcpy_s(temp_use, inp);
		int numberoflines = totallines(read_cnic);// we gotta open the file again after this
		read_cnic.open("cnic.txt");
		if (isinfile(read_cnic, inp))
		{
			int on_line = numberoflines - getlinenumber(read_cnic, inp);
			flag = true;
		}
		read_cnic.close();

	
		read1.open("Doc_name.txt");
		read_city.open("city.txt");
		read_cnic.open("cnic.txt");
		read_hos.open("hospital.txt");
		read_price.open("Appointment_price.txt");

		while (read1.eof() == 0) {



			read1 >> temp1;
			read_city >> temp2;
			read_cnic >> temp3;
			read_hos >> temp4;
			read_price >> temp5;

			extra = temp3;
			//temp3 = temp3;

			if (extra == inp)
			{
				//system("cls");

				cout << "\t\t   Doctor: " << temp1 << endl;
				cout << "\t\t   City: " << temp2 << endl;
				cout << "\t\t   Cnic: " << temp3 << endl;
				cout << "\t\t   Appointment Price: " << temp5 << endl;
				cout << "\t\t   Hospital: " << temp4 << "\n\n\n";
				break;
			}

			else
				extra = '\0';
		}
		read1.close();
		read_city.close();
		read_cnic.close();
		read_hos.close();
		read_price.close();

		cout << "Press any key to continue: ";
		getchar();
		getchar();

		mainmenu_doc(obj);

	}

	if (c == 2)
	{
		Appointment book;
		book.Booked_appointment();
		read2.open("Patient_name.txt");
		while (read2.eof() == 0) {

			read2 >> temp1;
			cout << "\t\t   Booked Appointment patient name: " << temp1 << endl;
		}
		read2.close();

	}

	if(c==3)
	{
		fstream read3;
		char temp3[30];
		read3.open("Appointment_price.txt");
		read3 >> temp3;
		cout << "\t\t   Price:   " << temp3 << endl;
		read3.close();
	
		mainmenu_doc(obj);
			
	}

	else if (c == 0)
	{
		mainscreen();

	}
		else {
			cout << "\t\t    Wrong input\n";
			continue;
		}
	} while (true);
}


void loggedin(int n)
{
	const int strsize = 30;
	static char CurrentUser[30];
	Doctor temp;
	Patient p;
	ifstream fin;
	fin.open("records.dat", std::ios::in | ios::binary);
	while (!fin.eof()) // until end of file
	{
		temp.loaddoc(fin); // keep reading
		char x[strsize];
		if (n == 1)
			strcpy_s(x, temp.login.get_username());
		if (n == 2)
			strcpy_s(x, p.getPatient().get_username());

		cout << x << endl;
		if (strcmp(x, CurrentUser) == 0) // username say account nikalta hai
		{
			if (n == 1)
				mainmenu_doc(temp);
			if (n == 2)
				mainmenu_patient(p);
			break;
		}
	}
	fin.close();
}


void mainscreen() 
{
	int n, n1, n3;

	Doctor d;
	Patient p;
	admin a;
	system("cls");
	cout << "OlaDoc\n";
	cout << "-->Press 1 to Register\n-->Press 2 to Login: \n" << "-->Press 3 to use as a admin.\n ";
	cin >> n;

	while (n > 3 || n < 1)
	{
		cout << "Invalid input. \n-->Please Enter valid input: ";
		cin >> n;
	}

	switch (n)
	{
	case 1:
		cout << "-->Press 1 to Register as a Doctor. \n-->Press 2 to Register as a Patient: \n";
		cin >> n1;

		while (n1 > 2 || n1 < 1)
		{
			cout << "Invalid input. \n-->Please Enter valid input: ";
			cin >> n1;
		}

		switch (n1)
		{
		case 1:
			d.input();
			break;
		case 2:
			p.input();
			break;
		}
		break;
	case 2:

		cout << "-->Press 1 if you are doctor.\n-->Press 2 If you are a patient.\n";
		cin >> n3;
		system("cls");
		d.Login(n3);



		break;

	case 3:
		a.Mainmenu();
		break;

	}

}


int main()
{
	mainscreen();//all functianlity in it of main

	

}

