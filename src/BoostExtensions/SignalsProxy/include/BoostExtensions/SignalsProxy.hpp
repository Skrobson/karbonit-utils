#pragma once
#include <boost/signals2.hpp>
#include <concepts>

namespace kit::be
{
    namespace bs2 = boost::signals2;

    template<typename Sig>
    requires std::derived_from<Sig, bs2::signal_base>
    class BoostSignalProxy
    {
    public:
        BoostSignalProxy(Sig &signal): signal(signal){}
        BoostSignalProxy() = delete;

        auto connect(const Sig::slot_type& slot, bs2::connect_position connect_position= bs2::at_back){
            return signal.connect(slot, connect_position);
        }

        auto connect(const Sig::group_type &group,
          const Sig::slot_type &slot, bs2::connect_position position = bs2::at_back){
          return signal.connect(group, slot, position);
        }

        auto connect_extended(const Sig::extended_slot_type &ext_slot, bs2::connect_position position = bs2::at_back){
            return signal.connect_extended(ext_slot, position);
        }

        auto connect_extended(const Sig::group_type &group,
            const Sig::extended_slot_type &ext_slot, bs2::connect_position position = bs2::at_back){
            return signal.connect_extended(group, ext_slot, position);
        }

        void disconnect(const Sig::group_type &group){
            signal.disconnect(group);
        }

        template <typename T>
        void disconnect(const T &slot){
            signal.disconnect(slot);
        }

    protected:
        Sig &signal;

    private:
        BoostSignalProxy(const BoostSignalProxy&) = delete;
        BoostSignalProxy& operator=(const BoostSignalProxy&) = delete;
        BoostSignalProxy(BoostSignalProxy&&) = delete;
        BoostSignalProxy& operator=(BoostSignalProxy&&) = delete;
    };
}
