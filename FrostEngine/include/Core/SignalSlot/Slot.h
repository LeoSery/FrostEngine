#pragma once

/*!
* \file Slot.h
* 
* \brief Header file for the Slot class.
* 
*/

#include <functional>

/*!
* \namespace frost::core
*
* \brief The namespace for FrostEngine's core functionalities.
*/
namespace frost::core
{	
    /*!
    * \class Slot
    * 
    * \brief Class for creating slots that can be connected to signals.
    */
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