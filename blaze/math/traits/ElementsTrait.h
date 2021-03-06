//=================================================================================================
/*!
//  \file blaze/math/traits/ElementsTrait.h
//  \brief Header file for the elements trait
//
//  Copyright (C) 2012-2018 Klaus Iglberger - All Rights Reserved
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

#ifndef _BLAZE_MATH_TRAITS_ELEMENTSTRAIT_H_
#define _BLAZE_MATH_TRAITS_ELEMENTSTRAIT_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <utility>
#include <blaze/util/InvalidType.h>
#include <blaze/util/Types.h>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename, size_t... > struct ElementsTrait;
template< typename, size_t, typename = void > struct ElementsTraitEval1;
template< typename, size_t, typename = void > struct ElementsTraitEval2;
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< size_t... CEAs, typename T >
auto evalElementsTrait( T& )
   -> typename ElementsTraitEval1<T,sizeof...(CEAs)>::Type;

template< size_t... CEAs, typename T >
auto evalElementsTrait( const T& )
   -> typename ElementsTrait<T,CEAs...>::Type;

template< size_t... CEAs, typename T >
auto evalElementsTrait( const volatile T& )
   -> typename ElementsTrait<T,CEAs...>::Type;
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Base template for the ElementsTrait class.
// \ingroup math_traits
//
// \section elementstrait_general General
//
// The ElementsTrait class template offers the possibility to select the resulting data type
// when selecting elements from a dense or sparse vector. ElementsTrait defines the nested
// type \a Type, which represents the resulting data type of the elements operation. In case
// the given data type is not a dense or sparse vector type, the resulting data type \a Type
// is set to \a INVALID_TYPE. Note that \a const and \a volatile qualifiers and reference
// modifiers are generally ignored.
//
//
// \section elementstrait_specializations Creating custom specializations
//
// Per default, ElementsTrait supports all vector types of the Blaze library (including views and
// adaptors). For all other data types it is possible to specialize the ElementsTrait template.
// The following example shows the according specialization for the DynamicVector class template:

   \code
   template< typename T1, bool TF, size_t... CEAs >
   struct ElementsTrait< DynamicVector<T1,TF>, CEAs... >
   {
      using Type = DynamicVector<T1,TF>;
   };
   \endcode

// \n \section elementstrait_examples Examples
//
// The following example demonstrates the use of the ElementsTrait template, where depending
// on the given vector type the according result type is selected:

   \code
   using blaze::columnVector;
   using blaze::rowVector;

   // Definition of the result type of a dynamic column vector
   using VectorType1 = blaze::DynamicVector<int,columnVector>;
   using ResultType1 = typename blaze::ElementsTrait<VectorType1>::Type;

   // Definition of the result type for the two elements of a static row vector
   using VectorType2 = blaze::StaticVector<int,4UL,rowVector>;
   using ResultType2 = typename blaze::ElementsTrait<VectorType2,1UL,4UL>::Type;
   \endcode
*/
template< typename VT       // Type of the vector
        , size_t... CEAs >  // Compile time element arguments
struct ElementsTrait
{
 public:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   using Type = decltype( evalElementsTrait<CEAs...>( std::declval<VT&>() ) );
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Auxiliary alias declaration for the ElementsTrait type trait.
// \ingroup math_traits
//
// The ElementsTrait_t alias declaration provides a convenient shortcut to access the nested
// \a Type of the ElementsTrait class template. For instance, given the vector type \a VT the
// following two type definitions are identical:

   \code
   using Type1 = typename blaze::ElementsTrait<VT>::Type;
   using Type2 = blaze::ElementsTrait_t<VT>;
   \endcode
*/
template< typename VT       // Type of the vector
        , size_t... CEAs >  // Compile time element arguments
using ElementsTrait_t = typename ElementsTrait<VT,CEAs...>::Type;
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief First auxiliary helper struct for the ElementsTrait type trait.
// \ingroup math_traits
*/
template< typename VT  // Type of the vector
        , size_t N     // Number of elements
        , typename >   // Restricting condition
struct ElementsTraitEval1
{
 public:
   //**********************************************************************************************
   using Type = typename ElementsTraitEval2<VT,N>::Type;
   //**********************************************************************************************
};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Second auxiliary helper struct for the ElementsTrait type trait.
// \ingroup math_traits
*/
template< typename VT  // Type of the vector
        , size_t N     // Number of elements
        , typename >   // Restricting condition
struct ElementsTraitEval2
{
 public:
   //**********************************************************************************************
   using Type = INVALID_TYPE;
   //**********************************************************************************************
};
/*! \endcond */
//*************************************************************************************************

} // namespace blaze

#endif
