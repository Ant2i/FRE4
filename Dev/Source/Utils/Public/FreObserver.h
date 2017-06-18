#pragma once

#include <vector>
#include <FreEvent.h>

namespace FRE
{
	namespace Utils
	{
		class UserData
		{

		};

		class Subject;

		class Observer
		{
		public:
			virtual void OnNotify(const Event& event, UserData* userData) = 0;
			virtual void OnDestroyed(const Subject& subject, UserData* userData) = 0;
		};

		class FREUTILS_EXPORT Subject
		{
		public:
			Subject();
			Subject(const Subject&) = delete;
			Subject& operator=(const Subject&) = delete;
			virtual ~Subject();

			void Attach(Observer* observer, UserData* userData = nullptr);
			void Detach(Observer* observer);
			bool IsAttached(Observer* observer) const;

		protected:
			void Notify(const Event& event);

		private:
			typedef std::pair<Observer*, UserData*> ObserverDataPair;
			typedef std::vector<ObserverDataPair> ObserverList;

			ObserverList _observers;
		};
	}
}
