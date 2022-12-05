//
// Created by Nonthachai Plodthong on 16/11/2022 AD.
//

#include "Workstation.h"

namespace sdds {
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;
	Workstation::~Workstation() = default;
	Workstation::Workstation() = default;

	Workstation::Workstation(std::string &str) : Station(str) {
		m_pNextStation = nullptr;
	}

	void Workstation::fill(std::ostream &os) {
		if (!m_order.empty()) {
			m_order.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		bool flag = false;
		if (!m_order.empty()) {
			if (m_order.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				if (m_pNextStation) {
					*m_pNextStation += std::move(m_order.front());
				} else if (m_order.front().isOrderFilled()) {
					g_completed.push_back(std::move(m_order.front()));
				} else if (!m_order.front().isOrderFilled()) {
					g_incomplete.push_back(std::move(m_order.front()));
				}
				m_order.pop_front();
				flag = true;
			}
		}
		return flag;
	}

	void Workstation::setNextStation(Workstation *station) {
		m_pNextStation = station;
	}

	Workstation *Workstation::getNextStation() const {
		//std::cout <<"This is NextStation[" << m_pNextStation << "]\n";
		return m_pNextStation;
	}

	void Workstation::display(std::ostream &os) const {
		std::string endLine = "End of Line";
		os << getItemName() << " --> ";
		if (m_pNextStation) {
			os << m_pNextStation->getItemName() << '\n';
		} else {
			os << endLine << '\n';
		}


	}

	Workstation &Workstation::operator+=(CustomerOrder &&newOrder) noexcept {
		m_order.push_back(std::move(newOrder));
		return *this;
	}


}