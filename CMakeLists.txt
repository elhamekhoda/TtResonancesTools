# Auto-generated on: 2017-03-08 14:47:39.905903

# Declare the name of this package:
atlas_subdir( TtResonancesTools None )

# This package depends on other packages:
atlas_depends_on_subdirs( PUBLIC
                          TopEventSelectionTools
                          TopEvent
                          TopConfiguration
                          TopEventReconstructionTools )

# This package uses ROOT:
find_package( ROOT REQUIRED COMPONENTS Core Gpad Tree Hist RIO MathCore Graf )

# Generate a CINT dictionary source file:
atlas_add_root_dictionary( TtResonancesTools _cintDictSource
                           ROOT_HEADERS Root/LinkDef.h
                           EXTERNAL_PACKAGES ROOT )

# Build a library that other components can link against:
atlas_add_library( TtResonancesTools Root/*.cxx Root/*.h Root/*.icc
                   TtResonancesTools/*.h TtResonancesTools/*.icc TtResonancesTools/*/*.h
                   TtResonancesTools/*/*.icc ${_cintDictSource} 
                   PUBLIC_HEADERS TtResonancesTools
                   LINK_LIBRARIES TopEventSelectionTools
                                  TopEvent
                                  TopConfiguration
                                  TopEventReconstructionTools
                                  ${ROOT_LIBRARIES}
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} )

# Install data files from the package:
atlas_install_data( DIRECTORY share )

