#pragma once

    class Subject
    {
    public:
      // Do not copy the list of observers during copy/assignment.
      // The observers won't know about the 'new' attachment and thus
      // it cannot detach itself;
      Subject() : m_inNotify(false) {}
      Subject( Subject const& ) : m_inNotify(false) {}
      Subject& operator=( const Subject& /* rhs */ ) { return *this; }

      DP_UTIL_API virtual ~Subject();

      DP_UTIL_API void attach( Observer* observer, Payload * payload = nullptr );
      DP_UTIL_API void detach( Observer* observer, Payload * payload = nullptr  );
      DP_UTIL_API bool isAttached( Observer * observer, Payload * payload = nullptr ) const;

    protected:
      DP_UTIL_API void notify( const Event &event );

    private:
      typedef std::pair<Observer*, Payload*> ObserverEntry;
      typedef std::vector<ObserverEntry> Observers;

    private:
      Observers m_observers;
      bool      m_inNotify;
    };

    class Observer
    {
    public:
      DP_UTIL_API virtual void onNotify( dp::util::Event const & event, dp::util::Payload * payload ) = 0;
      DP_UTIL_API virtual void onDestroyed( dp::util::Subject const & subject, dp::util::Payload * payload ) = 0;
    };
