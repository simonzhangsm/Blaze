//=================================================================================================
/*!
//  \file blaze/util/mpl/Or.h
//  \brief Header file for the Or class template
//
//  Copyright (C) 2013 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_UTIL_MPL_OR_H_
#define _BLAZE_UTIL_MPL_OR_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/util/mpl/Bool.h>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*! Auxiliary helper struct for the Or class template.
// \ingroup mpl
*/
template< typename T        // Type of the mandatory argument
        , typename... Ts >  // Types of the optional operands
struct OrHelper
   : public Bool< T::value || OrHelper<Ts...>::value >
{};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*! Specialization of the OrHelper class template for a single template argument.
// \ingroup mpl
*/
template< typename T >  // Type of the mandatory argument
struct OrHelper<T>
   : public Bool< T::value >
{};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Compile time logical or evaluation.
// \ingroup mpl
//
// The Or class template performs at compile time a logical or ('&&') evaluation of at least
// two compile time conditions:

   \code
   using namespace blaze;

   typedef int  Type;

   Or< IsIntegral<Type>, IsSigned<Type>        >::value  // Evaluates to 1
   Or< IsIntegral<Type>, IsFloatingPoint<Type> >::value  // Evaluates to 1
   Or< IsFloat<Type>   , IsDouble<Type>        >::value  // Evaluates to 0
   \endcode
*/
template< typename T1       // Type of the first mandatory operand
        , typename T2       // Type of the second mandatory operand
        , typename... Ts >  // Types of the optional operands
struct Or
   : public Bool< OrHelper<T1,T2,Ts...>::value >
{};
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Auxiliary alias declaration for the Or class template.
// \ingroup mpl
//
// The Or_ alias declaration provides a convenient shortcut to access the nested \a value of
// the Or class template. For instance, given the types \a T1, \a T2 and \a T3 the following
// two statements are identical:

   \code
   constexpr bool value1 = Or<T1,T2,T3>::value;
   constexpr bool value2 = Or_<T1,T2,T3>;
   \endcode
*/
template< typename T1       // Type of the first mandatory operand
        , typename T2       // Type of the second mandatory operand
        , typename... Ts >  // Types of the optional operands
constexpr bool Or_ = Or<T1,T2,Ts...>::value;
//*************************************************************************************************

} // namespace blaze

#endif
