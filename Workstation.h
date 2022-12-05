//
// Created by Nonthachai Plodthong on 16/11/2022 AD.
//

#ifndef STL_CONTAINER_WORKSTATION_H
#define STL_CONTAINER_WORKSTATION_H

#include "CustomerOrder.h"
#include "Station.h"
#include <deque>
#include <memory>

namespace sdds {
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station {
		//std::deque<Station> w_station{};
		std::deque<CustomerOrder> m_order{};
		Workstation *m_pNextStation{};
		//std::unique_ptr<Item> w_item;
	public:
		~Workstation();

		Workstation();

		explicit Workstation(std::string &);

		void fill(std::ostream &os);

		bool attemptToMoveOrder();

		Workstation(const Workstation &) = delete;

		Workstation &operator=(const Workstation &) = delete;

		Workstation(Workstation &&) = delete;

		Workstation &operator=(Workstation &&) = delete;

		void setNextStation(Workstation *station);

		Workstation *getNextStation() const;

		virtual void display(std::ostream &os) const;

		Workstation &operator+=(CustomerOrder &&newOrder) noexcept;
		//Workstation &operator+=(CustomerOrder &newOrder) noexcept;




	};
}

#endif //STL_CONTAINER_WORKSTATION_H
