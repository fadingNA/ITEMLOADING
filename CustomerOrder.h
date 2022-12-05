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
#ifndef STL_CONTAINER_CUSTOMERORDER_H
#define STL_CONTAINER_CUSTOMERORDER_H

#include "Utilities.h"
#include "Station.h"
#include <regex>

namespace sdds {
	struct Item {
		std::string m_itemName{};
		size_t m_serialNumber{0};
		bool m_isFilled{false};

		Item(const std::string &src) : m_itemName(src) {};
	};

	class CustomerOrder {
		//instance
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItm{};
		Item **m_listItem{};// dynamically pointer to pointer
		//class variable static
		static size_t m_widthField; // non-const static cannot be initialized.
	public:

		CustomerOrder();

		~CustomerOrder();

		explicit CustomerOrder(const std::string &text);

		CustomerOrder(const CustomerOrder &);

		CustomerOrder(CustomerOrder &&) noexcept;

		CustomerOrder &operator=(const CustomerOrder &) = delete;

		CustomerOrder &operator=(CustomerOrder &&) noexcept;

		bool isOrderFilled() const;

		bool isItemFilled(const std::string &itemName);

		void fillItem(Station &station, std::ostream &os);

		void display(std::ostream &os) const;


	};


}

#endif //STL_CONTAINER_CUSTOMERORDER_H
