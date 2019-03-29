#include <iostream>
#include <vector>
#include <string>
#include <sstream> 	// int to string
using namespace std;

// This function recieves a hex integer and returns a string
inline string int_to_string(unsigned int number) {
	stringstream ss;
	ss << hex << number;
	string result(ss.str());
	return result;
}

// This function recieves a string and returns a hex integer 
inline unsigned short string_to_int(string str) { return stoul(str, nullptr, 16); }

// This function receives a string packet and returns vector packet
inline vector<string> seperate(string packet) {

	vector <string> vec;
	string temp = ""; 	// to hold temporary words
	const int WORD = 4;	// 4 hex characters = 16 bit word

	// split packet into 16-bit words and put into vector 	
	for (int i = (packet.length() - 1) / WORD; i >= 0; i--) {

		// if we have packet string with atleast WORD in size
		if(packet.length() >= WORD) {

			// grab 16-bits at a time and put in vec vector
			temp = packet.substr(packet.length() - WORD, WORD);
			vec.push_back(temp);
			packet.erase(packet.length() - WORD, WORD);
		}

		// if our packet string is less than WORD in size
		else {

			// grab whatever bits is left	
			temp = packet.substr(0, packet.length());
			vec.push_back(temp);
		}
	}
	return vec;
}

// This function recieves a string packet returns the checksum
inline signed short int calculate_checksum(string packet) {

	int32_t sum = 0;					    // the max sum of our packet can be 4 bytes
	signed short int checksum = 0;	        // our resultant checksum
	vector<string> V = seperate(packet);    // convert string packet to vector seperated packet

	// calculate 16-bit 2's comp sum of packet
	for (int i = V.size() - 1; i >= 0; i--) {
		sum += string_to_int(V[i]);
	}

	vector<string> V2 = seperate(int_to_string(sum));

	// add the caries to get the 16-bit 1's complement sum
	for (int i = V2.size() - 1; i >= 0; i--) {
		checksum += string_to_int(V2[i]);
	}

	// return the 1's complement of the 1's complement sum
	return (~checksum);
}


int main(void) {

	string packet_string = "";		// our simulation packet
	signed short int checksum = 0;  // our checksum for our packet

	cout << "Enter a packet: ";
	cin >> packet_string;

	checksum = calculate_checksum(packet_string);
	cout << "Checksum(" << packet_string << "): " << hex << checksum << endl;

   return 0;
}
