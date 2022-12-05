/*
*****************************************************************************
                             MS2
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
#include <sstream>
#include "Utilities.h"

namespace sdds {
	static char m_delimiter = ' ';
	//static size_t m_widthField = 1;


	void Utilities::setFieldWIdth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more) {
		size_t begin = next_pos; // start point
		std::string source;
		source = str;
		more = false;
		next_pos = source.find_first_of(sdds::m_delimiter, begin); // 1st parameter หาอะไร ,, ต่อมา เริ่มจากตรงไหน
		//std::stringstream k(source);
		//std::cout << "k" << next_pos << std::endl;
		std::string::size_type pos = 0;
		if (source.at(begin) == sdds::m_delimiter) {
//
			throw "Found delimeter at starting point";
		}
		if (next_pos == std::string::npos) {
			source = source.substr(begin, next_pos - begin);
			if (m_widthField < source.length()) {
				m_widthField = source.length();
			}
			more = false;
			//throw "Found next post at the end";
		}
		if ((pos = source.find(sdds::m_delimiter, next_pos)) != std::string::npos) {
			source = source.substr(begin, next_pos - begin);
			if (m_widthField < source.length()) {
				m_widthField = source.length();
			}
			more = true;

		}
		next_pos++;
		return source;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		sdds::m_delimiter = newDelimiter;
	}

	//static can only be specified inside the class definition;
	char Utilities::getDelimiter() {
		return sdds::m_delimiter;
	}
}