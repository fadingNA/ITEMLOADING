//
// Created by Nonthachai Plodthong on 19/11/2022 AD.
//



#include "LineManager.h"

namespace sdds {

	LineManager::LineManager() = default;

	LineManager::~LineManager() = default;

	LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations) {
		Utilities tmp;
		std::string getFile{}, workstation{}, nextWorkStation{};
		std::fstream fs(file);
		size_t pos = 0;
		bool flag = false;
		try {
			if (!fs) {
				throw "Unable to open file";
			} else {
				while (std::getline(fs, getFile)) {
					//load workstation
					workstation = tmp.extractToken(getFile, pos, flag);
					if (flag) {
						nextWorkStation = tmp.extractToken(getFile, pos, flag);
					} else {
						nextWorkStation = "";
					}
					//std::cout << "first station >[" << workstation << "]\n" << "second station[" << nextWorkStation << "]\n";

					// 1st check
					bool entry1 = std::any_of(stations.begin(), stations.end(), [&](Workstation *current) {
						if (current->getItemName() == workstation) {
							m_activeLine.push_back(current);
							return true;
						}
						return false;
					});
					if (entry1) {
						std::any_of(stations.begin(), stations.end(), [&](Workstation *next) {
							if (!nextWorkStation.empty()) {
								if (next->getItemName() == nextWorkStation) {
									m_activeLine.back()->setNextStation(next);
									return true;
								}
							}
							return false;
						});
					}
				}
			}
			fs.close();

			std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *sort) {
				bool run = std::any_of(stations.begin(), stations.end(), [&](Workstation *running) {
					if (sort == running->getNextStation()) {
						return true;
					}
					return false;
				});
				if (!run) {
					m_firstStation = sort;
				}
			});

			//std::cout << "[" << g_pending.size() << "]\n";
			m_cntCustomerOrder = g_pending.size();
		} catch (std::string &msg) {
			throw "Station error";
		} catch (...) {
			throw "Unexpected error";
		}

	}

	void LineManager::reorderStations() {
		// void reorderStations() - this modifier reorders the workstations present in the instance variable m_activeLine
		// (loaded by the constructor) and stores the reordered collection in the same instance variable.
		// The elements in the reordered collection start with the first station, proceeds to the next,
		// and so forth until the end of the line.
		Workstation *tmp = m_firstStation->getNextStation();
		Workstation *tmp2;
		std::vector<Workstation *> tmp3;
		tmp3.push_back(m_firstStation);
		while (tmp) {
			for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *sort) {
				if (tmp == sort) {
					tmp2 = sort;
				}
			});
			tmp3.push_back(tmp2);
			tmp = tmp2->getNextStation();
		}
		std::transform(tmp3.begin(), tmp3.end(), m_activeLine.begin(), [&](Workstation *check) {
			return check ? check : nullptr;
		});
//		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *k) {
//			k->display(std::cout);
//		});
	}


	bool LineManager::run(std::ostream &os) {
		//keeps track of the current iteration number (use a local variable)
		static size_t roudn = 1;

		os << "Line Manager Iteration: " << roudn++ << std::endl;
		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
		for (auto &first: m_activeLine) {
			first->fill(os);
		}
		for (auto &second: m_activeLine) {
			second->attemptToMoveOrder();
		}
//		std::cout << "[" << g_completed.size()<<"]\n";
//		std::cout << "[" << g_pending.size() <<"]\n";
//		std::cout << "[" << g_incomplete.size() <<"]\n";
//		std::cout << "[" << m_cntCustomerOrder<<"]\n";
		return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();

	}

	void LineManager::display(std::ostream &os) const {
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation *ws) {
			ws->display(std::cout);
		});
	}
}
