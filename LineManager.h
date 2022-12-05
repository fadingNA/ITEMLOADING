//
// Created by Nonthachai Plodthong on 19/11/2022 AD.
//

#ifndef STL_CONTAINER_LINEMANAGER_H
#define STL_CONTAINER_LINEMANAGER_H

#include <fstream>
#include "Workstation.h"
#include <algorithm>

namespace sdds {
	class LineManager : public Workstation {
		std::vector<Workstation *> m_activeLine{};
		size_t m_cntCustomerOrder{};
		Workstation *m_firstStation{};
	public:
		LineManager();

		~LineManager();

		LineManager(const std::string& file, const std::vector<Workstation *> &stations);

		void reorderStations();

		bool run(std::ostream &os);

		void display(std::ostream &os) const override;
	};
}

#endif //STL_CONTAINER_LINEMANAGER_H
