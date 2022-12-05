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
#include <memory>
#include "CustomerOrder.h"

namespace sdds {
	size_t CustomerOrder::m_widthField = 0u;

	CustomerOrder::CustomerOrder() = default;

	CustomerOrder::CustomerOrder(const std::string &text) {
		Utilities local;
		size_t pos = 0;
		bool flag = false;
		try {
			this->m_name = local.extractToken(text, pos, flag);
			this->m_name = std::regex_replace(this->m_name, std::regex("^ +| +$|( ) +"), "$1");
			this->m_product = local.extractToken(text, pos, flag);
			this->m_product = std::regex_replace(this->m_product, std::regex("^ +| +$|( ) +"), "$1");
			m_cntItm = std::count(text.begin() + local.getFieldWidth(), text.end(), sdds::Utilities::getDelimiter());
			// move 13 position to avoid first delimiter
			if (m_cntItm > 0) {
				m_listItem = new Item *[m_cntItm];
			}
			for (size_t i = 0; i < m_cntItm && flag; ++i) {
				m_listItem[i] = new Item(local.extractToken(text, pos, flag));
				if (m_listItem[i]->m_itemName.find_first_not_of(' ')) {
					m_listItem[i]->m_itemName.erase(0, 1);
				}

			}
			if (CustomerOrder::m_widthField < local.getFieldWidth()) {
				CustomerOrder::m_widthField = local.getFieldWidth();
			}
		} catch (std::string &err) {
			std::cout << err;
		}

	}


	CustomerOrder::CustomerOrder(CustomerOrder &&object) noexcept {
		*this = std::move(object);
	}


	CustomerOrder &CustomerOrder::operator=(CustomerOrder &&object) noexcept {
		if (this != &object) {
			//clear
			for (size_t i = 0; i < m_cntItm; i++) {
				delete this->m_listItem[i];
			}
			delete[] m_listItem;

			this->m_cntItm = object.m_cntItm;
			this->m_name = object.m_name;
			this->m_product = object.m_product;
			this->m_listItem = object.m_listItem;

			object.m_cntItm = 0;
			object.m_name = "";
			object.m_product = "";
			object.m_listItem = nullptr;
		}
		return *this;
	}

	bool CustomerOrder::isOrderFilled() const {
		bool flag = true;
		for (auto i = 0u; i < m_cntItm; ++i) {
			if (!m_listItem[i]->m_isFilled) {
				flag = false;
			}
		}
		return flag;
	}

	bool CustomerOrder::isItemFilled(const std::string &itemName) {
		bool flag = false;
		size_t countDuplicate = 0;
		size_t select = 0;
		std::vector<Item *> tmp;
		for (size_t i = 0; i < m_cntItm; ++i) {
			tmp.push_back(m_listItem[i]);
		}
		for_each(tmp.begin(), tmp.end(), [&](Item *it) {
			if (it->m_itemName == itemName) {
				countDuplicate++;
			}
		});
		if (countDuplicate == 0) {
			return true;
		}
		for_each(tmp.begin(), tmp.end(), [&](Item *it2) {
			if (it2->m_isFilled) {
				if (it2->m_itemName == itemName) {
					select++;
				}
			}
		});
		if (countDuplicate == select) {
			flag = true;
		}
		return flag;
	}

	void CustomerOrder::fillItem(Station &station, std::ostream &os) {
		using namespace std;
		unsigned int counts = 0;
		unsigned int point = 0;
		for (size_t i = 0; i < m_cntItm; ++i) {
			if (m_listItem[i]->m_itemName == station.getItemName()) {
				counts++;
				if (!m_listItem[i]->m_isFilled) {// check if not filled additional from ms2 to make fill item properly.
					point = i;
					if (station.getQuantity() > 0) {
						station.updateQuantity();
						m_listItem[point]->m_isFilled = true;
						m_listItem[point]->m_serialNumber = station.getNextSerialNumber();
						os << setw(11) << right << "Filled " << m_name << ", " << m_product << " ["
						   << m_listItem[point]->m_itemName
						   << "]\n";
						break;
					} else {
						os  << "    Unable to fill " << m_name << ", " << m_product << " ["
						   << m_listItem[point]->m_itemName
						   << "]\n";
					}
				}
			}
		}
	}

	//std::shared_ptr<CustomerOrder> c;

	void CustomerOrder::display(std::ostream &os) const {
		using namespace std;

		os << m_name << " - " << m_product << endl;
		//	os << m_cntItm << endl;check how many item need to be filled
		for (auto i = 0u; i < m_cntItm; ++i) {
			os << "[" << right << setw(6) << setfill('0') << m_listItem[i]->m_serialNumber << "] ";
			os << left << setw(CustomerOrder::m_widthField) << setfill(' ') << m_listItem[i]->m_itemName;
			os << " - " << (m_listItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder &) {
		throw "error";
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItm; ++i) {
			delete m_listItem[i];
		}
		delete[] m_listItem;
	}

}
