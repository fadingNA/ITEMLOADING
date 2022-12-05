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
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>
#include <sstream>

namespace sdds {
	class Utilities {

		[[maybe_unused]] static char m_delimiter;
		size_t m_widthField = 1;
		// instance variable
	public:
		void setFieldWIdth(size_t newWidth);

		size_t getFieldWidth() const;

		std::string extractToken(const std::string &str, size_t &next_pos, bool &more);

		static void setDelimiter(char newDelimiter);

		static char getDelimiter();
	};
}
#endif //SDDS_H
