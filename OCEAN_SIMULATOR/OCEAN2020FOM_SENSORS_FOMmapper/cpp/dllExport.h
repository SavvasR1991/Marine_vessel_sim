/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**dllExport.tlt
*********************************************************************/
 
#pragma once
 
#ifdef WIN32
#  ifndef DT_OCEAN2020FOM_SENSORS_STATIC
#     ifdef OCEAN2020FOM_SENSORS_EXPORTS
#        define DT_DLL_OCEAN2020FOM_SENSORS __declspec ( dllexport )
#     else
#        define DT_DLL_OCEAN2020FOM_SENSORS __declspec ( dllimport )
#     endif
#  else
#     define DT_DLL_OCEAN2020FOM_SENSORS
#  endif
#else
#  define DT_DLL_OCEAN2020FOM_SENSORS
#endif