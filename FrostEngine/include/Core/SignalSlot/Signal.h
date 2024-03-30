#pragma once

/*!
* \file Signal.h
* 
* \brief Header file for the Signal class.
*/

#include "Core/SignalSlot/Slot.h"

#include <vector>

/*!
* \namespace frost::core
*
* \brief The namespace for FrostEngine's core functionalities.
*/
namespace frost::core
{
    /*!
    * \class Signal
    * 
    * \brief Class for creating signals.
    * 
    * \details This class is used to create signals that can be connected to slots.
    * 
    * \tparam Args The types of the parameters that the signal will pass to the slots.
    */
    template <typename ...Args>
    class Signal
    {
    public:

        //Disabling default constructors
        Signal(const Signal&) = delete;
        Signal(Signal&&) = delete;
        Signal& operator=(const Signal&) = delete;

        //Constructor and Destructors
        Signal() = default;
        ~Signal() = default;

        //Methods
        void Connect(Slot<Args...>& _Slot);
        void Disconnect(Slot<Args...>& _Slot);
        void Disconnect();
        void Emit(Args&&... _Parameters);

        //Operators
        void operator()(Args&&... _Parameters);

    private:
        std::vector<Slot<Args...>*> m_connectedSlots;
    };
}

#include "Core/SignalSlot/Signal.hxx"