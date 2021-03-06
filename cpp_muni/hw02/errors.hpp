#ifndef ERRORS_HPP
#define ERRORS_HPP
#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>

//=============================================================================
// DO NOT EDIT THIS FILE
//=============================================================================

/*
 * How to use the Complain class:
 *
 * 1. On syntax error in the world file
 *
 *      Complain::invalidWorld(lineno);
 *      Complain::invalidWorld(lineno, ...);
 *      Complain::invalidWorld(lineno, a, b, c, ...);
 *
 *    The first version will simply throw a general error on line
 *    lineno.
 *
 *    If more parameters are supplied, then these parameters will be
 *    concatenated and used as the description of the error.
 *
 * 2. On syntax error in the program source file
 *
 *      Complain::invalidSource(lineno);
 *      Complain::invalidSource(lineno, ...);
 *
 * 3. On undefined reference in the program source file
 *
 *      Complain::undefinedReference(from, to);
 *      Complain::undefinedReference(from, to, ...);
 *
 *  The from parameter is the name of the procedure that contains
 *  the offending instruction.
 *  The to parameter is the name of the procedure that was not defined.
 *
 * 4. On runtime error when interpreting the program
 *
 *      Complain::runtimeError(procedure, index);
 *      Complain::runtimeError(procedure, index, ...);
 *
 *  The procedure parameter specifies in which procedure the error occured.
 *  The index parameter tells which instruciton caused the error.
 *
 * 5. Custom error for your testing
 *
 *      Complain::error();
 *      Complain::error(...);
 *
 * ---------------------------------------------------------------------------
 *
 * You are discouraged to read any futher as mere attempt to comprehend
 * the contents of this file may cause seizures, headaches, uncontrollable
 * vomiting, severe diuresis, delusions and may crash your computer.
 *
 * You have been warned.
 *
 * ---------------------------------------------------------------------------
 */

//=============================================================================
// DO NOT EDIT THIS FILE
//=============================================================================

#ifndef COMPLAIN_EXCEPTIONS
#  define COMPLAIN_EXCEPTIONS 0
#endif

#define UNUSED(VAR) ((void) (VAR))

//=============================================================================
// DO NOT EVEN READ THIS FILE
//=============================================================================

class Complain
{
    // Writing const std::string& every time is too long and boring.
    using String = const std::string&;

    /**
     * Append arg to os and then append the rest of arguments recursively.
     */
    template<typename T, typename... Rest>
    static void _mkmsg(std::ostream& os, T&& arg, Rest&&... other)
    { _mkmsg<Rest...>(os << arg, std::forward<Rest>(other)...); }

    /**
     * Base case for the recursion.
     */
    template<typename...>
    static void _mkmsg(std::ostream&)
    { }

    /**
     * Used when called with no template parameters.
     */
    static void _mkmsg(std::ostream& os)
    { os << "unspecified error"; }

    /**
     * Throws an exception or calls std::exit based on the value of
     * COMPLAIN_EXCEPTIONS macro.
     *
     * Implemented in errors.cpp, do not edit that file either.
     */
    [[noreturn]]
    static
    void _croak(String what, String msg, String details);

//=============================================================================
// WHY ARE YOU STILL HERE?
//=============================================================================

public:
    // Disallow to create an instance of this class.
    Complain() = delete;

    template<typename... Args> [[noreturn]]
    static void invalidWorld(unsigned line, Args&& ...args)
    {
        std::stringstream msg;
        msg << "on line " << line;
        std::stringstream details;
        Complain::_mkmsg(details, std::forward<Args>(args)...);
        Complain::_croak("invalid world", msg.str(), details.str());
    }

    template<typename... Args> [[noreturn]]
    static void invalidSource(unsigned line, Args&& ...args)
    {
        std::stringstream msg;
        msg << "on line " << line;
        std::stringstream details;
        Complain::_mkmsg(details, std::forward<Args>(args)...);
        Complain::_croak("invalid source", msg.str(), details.str());
    }

    template<typename... Args> [[noreturn]]
    static void undefinedReference(String where, String& to, Args&& ...args)
    {
        std::stringstream msg;
        msg << where << " calls " << to;
        std::stringstream details;
        Complain::_mkmsg(details, std::forward<Args>(args)...);
        Complain::_croak("undefined reference", msg.str(), details.str());
    }

    template<typename... Args> [[noreturn]]
    static void runtimeError(String& procedure, unsigned index, Args&& ...args)
    {
        std::stringstream msg;
        msg << "in " << procedure << " on instruction " << index;
        std::stringstream details;
        Complain::_mkmsg(details, std::forward<Args>(args)...);
        Complain::_croak("runtime error", msg.str(), details.str());
    }

    template<typename... Args> [[noreturn]]
    static void error(Args&& ...args)
    {
        std::stringstream details;
        Complain::_mkmsg(details, std::forward<Args>(args)...);
        Complain::_croak("error", "details", details.str());
    }
};

//=============================================================================
// YOU SKIPPED THE CODE WITHOUT READING IT, DIDN'T YOU?
//=============================================================================

#endif // ERRORS_HPP
