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
        Slot(const std::function<void(Args...)>& callback);
        ~Slot() = default;

        //Operators
        void operator()(Args&&... parameters);

        //Methods
        void call(Args&&... parameters);
        void setSlotFunction(std::function<void(Args...)> callback);

    private:
        bool m_Init;
        std::function<void(Args...)> m_Callback;
    };
}

#include "Core/SignalSlot/Slot.hxx"