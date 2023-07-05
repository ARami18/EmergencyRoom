#include "Queue.h"
#include "Patient.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

using namespace std;

void build_menu();
template <typename T> void display_queue(const Queue<T>& queue);
void add_patient(Queue<Patient>& queue);									
void process_patient(Queue<Patient>& waiting, Queue<Patient>& processed);
void process_input(Queue<Patient>& waiting, Queue<Patient>& processed, bool& flag);
bool validate_name(const char* name);



int main() {

	bool running = true;
	Queue<Patient> waiting;
	Queue<Patient> processed;

	do {
		build_menu();
		process_input(waiting, processed, running);
	} while (running);

	return EXIT_SUCCESS;
}

void build_menu() {
	cout << "============================================" << endl;
	cout << "Welcome to Fanshawe's College Medical Center" << endl;
	cout << "============================================\n" << endl;

	cout << "Please make a selection then press Enter:" << endl;
	cout << "1. Add a patient" << endl;
	cout << "2. Process Next Patient In Queue" << endl;
	cout << "3. Display Queue" << endl;
	cout << "4. View Processed Patients History" << endl;
	cout << "5. Load Queue From External 'csv' File" << endl;
	//cout << "6. Save Queue To An External 'csv' File" << endl;
	cout << "0. Exit" << endl;
}

void process_input(Queue<Patient>& waiting, Queue<Patient>& processed, bool& flag) {
	
	int input;
	cin >> input;

	switch (input)
	{
	case 1:
		add_patient(waiting);
		std::cout << "New patient has been added.\n" << std::endl;
		break;
	case 2:
		process_patient(waiting, processed);
		break;
	case 3:
		waiting.displayQueue();
		break;
	case 4:
		processed.displayQueue();
		break;
	case 5:
		//load_queue_from_file();
		break;
	case 6:
		//TODO
		break;
	case 0:
		cout << "Exiting Program!" << endl;
		flag = false;
		break;
	default:
		cout << "Invalid Input! Try again" << endl;
		break;
	}

}

bool validate_name(const char* name) {
	bool has_space = false;
	
	// iterate through each character of the name ensuring it is alphabetical and only has one space
	for (const char* c = name; *c != '\0'; c++) {
		if (*c >= 65 && *c <= 90) { // if the character is within the capital letter range of ascii this block of code will run
			continue;
		}
		else if (*c >= 97 && *c <= 122) { // if the character is within the lowercase letter range of ascii this block of code will run
			continue;
		}
		else if (*c == 32 && !has_space) { // if the character is a space and there is only one space in the string this code will run
			// if this code is reached we know the previous letter was a alphabetical character 
			has_space = true;
			char next = *(++c);
			if (isalpha(next)) { // ensures the characters on either side of the space are letters
				continue;
			}
			else { // the characters to the left and right of the string are not alphabetical characters and the string is invalid
				return false; 
			}
		}
		else {
			// if this block is reached it means the name is invalid and will immediately return false
			return false;
		}
	}
	
	if(has_space) // ensures names are only valid if they have at least one space because we need first and last name
		return true;
	else // if there is no space in the name we know it is only a first name so it is invalid
		return false;
}

void add_patient(Queue<Patient>& queue) {
	//TODO
	char name[31];
	char ailment[256];
	unsigned int severity = -1;
	unsigned int time_criticality = -1;
	unsigned int contagiousness = -1;

	//clear the input buffer
	cin.clear();
	cin.seekg(0, ios::beg);

	cout << "Please enter the patient's first and last name separated by a space (maximum 30 characters): ";
	// get the name
	cin.getline(name, 31);

	while (!validate_name(name)) {
		// print error message
		cout << "Invalid Name: Must contain first and last name in alphabetic characters" << endl;
		//clear the input buffer
		cin.clear();
		cin.seekg(0, ios::beg);
		// get input again for validation
		cin.getline(name, 31);
	}

	cout << "name: " << name << " is valid!" << endl;

	//clear the input buffer
	cin.clear();
	cin.seekg(0, ios::beg);

	cout << "Please enter the patient's ailment (maximum 255 characters): ";
	// get the patient's ailment
	cin.getline(ailment, 256); // since the ailment could be broken arm, pnemonia, "my chest has been hurting for 12 hours" I decided not to validate this since we don't have an idea of what it could be

	cout << "Please enter the ailment severity on a scale of 1 to 10: ";
	while ((!(cin >> severity)) || (severity < 1 || severity > 10)) { // while the stream returns a fail bit or a bad bit we will retry, or if the severity is out of range we will also retry
		cout << "Invalid amount entered for [severity] please try again." << endl;
		cout << "Please enter the ailment severity on a scale of 1 to 10: ";
		cin.clear();
		cin.seekg(0, ios::beg);
	}

	cout << "Please enter the ailment time criticality on a scale of 1 to 10: ";
	while ((!(cin >> time_criticality)) || (time_criticality < 1 || time_criticality > 10)) { // while the stream returns a fail bit or a bad bit we will retry, or if the time criticality is out of range we will also retry
		cout << "Invalid amount entered for [time criticality] please try again." << endl;
		cout << "Please enter the ailment time criticality on a scale of 1 to 10: ";
		cin.clear();
		cin.seekg(0, ios::beg);
	};

	cout << "Please enter the ailment contagiousness on a scale of 0 to 10: ";
	while ((!(cin >> contagiousness)) || (contagiousness < 0 || contagiousness > 10)) {// while the stream returns a fail bit or a bad bit we will retry, or if the contagiousness is out of range we will also retry
		cout << "Invalid amount entered for [contagiousness] please try again." << endl;
		cout << "Please enter the ailment contagiousness on a scale of 1 to 10: ";
		cin.clear();
		cin.seekg(0, ios::beg);
	};

	// creates a new patient to add to the queue with the values from the input stream
	Patient newPatient(name, ailment, severity, time_criticality, contagiousness);

	//TODO: Place the patient in the queue based on their priority!
	queue.insert_with_priority(newPatient);
}

void process_patient(Queue<Patient>& waiting, Queue<Patient>& processed) {
	processed.insert_to_front(waiting.pull_highest_priority());
	std::cout << "Patient " << processed.begin()->data.getName() << '\n' << std::endl;
}


