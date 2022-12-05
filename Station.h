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

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include "Utilities.h"

#include <iomanip>

namespace sdds {
	class Station {
		unsigned int station_id{};
		std::string station_name{};
		std::string station_description{};
		size_t serial_number{};
		size_t numOfstock{};
		//Class varible
		size_t m_widthField{};
		static size_t id_generator;
		//Non-const static cannot be initialized.
		//Non Const statc data member must be initialized out of line;
	public:
		Station();

		Station(const std::string &record);

		void display(std::ostream &os, bool full) const;

		const std::string &getItemName() const;

		size_t getNextSerialNumber();

		size_t getQuantity() const;

		void updateQuantity();

		virtual ~Station();

	};
}
#endif //SDDS_STATION_H
