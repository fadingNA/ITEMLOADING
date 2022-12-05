/*
*****************************************************************************
                             MS1
Full Name  : NONTHACHAI PLODTHONG
Student ID#: 152487211
Email      : nplodthong@myseneca.ca
Section    : NAA
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.

*****************************************************************************
*/
#include <regex>
#include "Station.h"

namespace sdds {
	size_t m_widthField = 0;
	size_t id_generator = 0;

	Station::Station() = default;

	Station::Station(const std::string &record) {
		std::string tmp;
		sdds::id_generator++;
		//std::cout << sdds::id_generator << std::endl;
		Utilities localUti;
		std::string::size_type pos = 0;
		bool flag = false;

		{
			this->station_id = sdds::id_generator;
			this->station_name = localUti.extractToken(record, pos, flag);
			//std::cout << "[" << station_name << "]\n";
			this->station_name = std::regex_replace(this->station_name, std::regex(" +$"), "");
			//Parameters
			//first, last	-	the input character sequence, represented as a pair of iterators
			//s	-	the input character sequence, represented as std::basic_string or character array
			//re	-	the std::basic_regex that will be matched against the input sequence
			//fmt	-	the regex replacement format string, exact syntax depends on the value of flags
			//flags	-	the match flags of type std::regex_constants::match_flag_type
			//out	-	output iterator to store the result of the replacement

		}
		{
			this->serial_number = std::stoi(localUti.extractToken(record, pos, flag));
			//std::cout << "[" << serial_number << "]\n";
		}
		{
			this->numOfstock = std::stoi(localUti.extractToken(record, pos, flag));
			//std::cout << "[" << numOfstock << "]\n";
		}
		{
			if (sdds::m_widthField < localUti.getFieldWidth()) {
				sdds::m_widthField = localUti.getFieldWidth();
			}
			this->station_description = localUti.extractToken(record, pos, flag);
			//std::cout << "[" << station_description << " ]\n";
			if (station_description.at(1) == ' ') {
				station_description.erase(0, 1);
			}
			/*if(station_description.find_first_of(' ')){
				station_description.erase(0,pos);
			}*/

		}
		//std::cout << sdds::m_widthField << "[" << station_description << "]\n";
	}

	void Station::display(std::ostream &os, bool full) const {
		//os << m_widthField << endl;
		using namespace std;
		{
			os << right << setfill('0') << setw(3) << this->station_id;
			os << " | ";
			os << left << setw(sdds::m_widthField) << setfill(' ') << station_name;
			os << " | ";
			os << right << setfill('0') << setw(6) << serial_number;
			os << " | ";
			if (full) {
				os << right << setfill(' ') << setw(4) << this->numOfstock << " |" << setfill('0') << setw(6)
				   << this->station_description;
			}
		}

		std::cout << endl;

	}

	const std::string &Station::getItemName() const {
		return this->station_name;
	}

	size_t Station::getNextSerialNumber() {
		this->serial_number++;
		return this->serial_number - 1;
	}

	size_t Station::getQuantity() const {
		return this->numOfstock;
	}

	void Station::updateQuantity() {
		if (this->numOfstock == 0) {
			numOfstock = 0;
		} else {
			--numOfstock;
		}
	}

	Station::~Station() = default;
}