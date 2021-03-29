/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
#pragma once
 
#ifdef WIN32
#  ifndef DT_OCEAN2020FOM_STATIC
#     ifdef OCEAN2020FOM_EXPORTS
#        define DT_DLL_OCEAN2020FOM __declspec ( dllexport )
#     else
#        define DT_DLL_OCEAN2020FOM __declspec ( dllimport )
#     endif
#  else
#     define DT_DLL_OCEAN2020FOM
#  endif
#else
#  define DT_DLL_OCEAN2020FOM
#endif
