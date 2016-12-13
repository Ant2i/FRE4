#include "FreObserver.h"
#include <algorithm>

namespace FRE
{
	namespace Utils
	{
		Subject::Subject()
		{
		}

		Subject::~Subject()
		{

		}

		void Subject::Attach(Observer* observer, UserData* userData)
		{
			_observers.emplace_back(observer, userData);
		}

		void Subject::Detach(Observer* observer)
		{
			auto it = std::find_if(_observers.begin(), _observers.end(), [observer](const ObserverDataPair& pair)
			{
				return pair.first == observer;
			});

			if (it != _observers.end())
			{
				*it = _observers.back();
				_observers.pop_back();
			}
		}

		bool Subject::IsAttached(Observer* observer) const
		{
			auto it = std::find_if(_observers.begin(), _observers.end(), [observer](const ObserverDataPair& pair)
			{
				return pair.first == observer;
			});

			return it != _observers.end();
		}

		void Subject::Notify(const Event& event)
		{
			for (const auto & pair : _observers)
			{
				pair.first->OnNotify(event, pair.second);
			}
		}
	}
}