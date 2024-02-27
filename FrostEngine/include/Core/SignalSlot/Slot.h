#pragma once

#include <functional>

namespace frost::core
{	
    template <typename ...Args>
    class Slot
    {
    public:

        //Disabling default constructors
        Slot(const Slot&) = delete;
        Slot(Slot&&) = delete;
        Slot& operator=(const Slot&) = delete;

        //Constructors and Destructors
        Slot();
        Slot(const std::function<void(Args...)>& _Callback);
        ~Slot() = default;

        //Operators
        void operator()(Args&&... _Parameters);

        //Methods
        void call(Args&&... _Parameters);
        void setSlotFunction(std::function<void(Args...)> _Callback);

    private:
        bool m_init;
        std::function<void(Args...)> m_callback;
    };
}

#include "Core/SignalSlot/Slot.hxx"