#Change PROJECT_NAME to the name of your project
PROJECT(StructureTensor)

# Require CMake 2.8 for the superbuild functionality
cmake_minimum_required( VERSION 2.8)

#include some macros from another file...
INCLUDE(IJMacros.txt)

#The following lines are required to use Dart
ENABLE_TESTING()
INCLUDE(Dart)

#Declare any external dependencies that your project may have here.
#examples include: ITK, VTK, JPEG, PNG, OpenGL, ZLIB, Perl, Java
#If you're not sure what name to use, look in the Modules directory of your
#cmake install and check that a file named Find(Package).cmake exists
SET(Required_Packages
  ITK
)

#this foreach loads all of the packages that you specified as required.
#It shouldn't need to be modified.
FOREACH(Package ${Required_Packages})
  LOADPACKAGE(${Package})
ENDFOREACH(Package)

# install devel files
OPTION(INSTALL_DEVEL_FILES "Install C++ headers" ON)
IF(INSTALL_DEVEL_FILES)
FILE(GLOB develFiles *.h *.txx) 
FOREACH(f ${develFiles})
  INSTALL_FILES(/include/InsightToolkit/BasicFilters FILES ${f})
ENDFOREACH(f)
ENDIF(INSTALL_DEVEL_FILES)


# option for wrapping
OPTION(BUILD_WRAPPERS "Wrap library" OFF)
IF(BUILD_WRAPPERS)
   SUBDIRS(Wrapping)
ENDIF(BUILD_WRAPPERS)
   
   

#the following block of code is an example of how to build an executable in
#cmake.  Unmodified, it will add an executable called "MyExe" to the project.
#MyExe will be built using the files MyClass.h and MyClass.cxx, and it will
#be linked to all the libraries you specified above. 
#You can build more than one executable per project

SET(TEST_SRCS
itkStructureTensorRecursiveGaussianImageFilterTest
itkAnisotropicEdgeEnhancementDiffusionImageFilterTest
itkAnisotropicCoherenceEnhancingDiffusionImageFilterTest
itkAnisotropicHybridDiffusionImageFilterTest
)

FOREACH(test ${TEST_SRCS})
  ADD_EXECUTABLE( ${test} ${test}.cxx)
  TARGET_LINK_LIBRARIES( ${test} ITKIO ITKCommon ITKBasicFilters)
ENDFOREACH(test)
  
IF(BUILD_TESTING)

  ADD_TEST( StructureTensorRecursiveGaussianImageFilterTest 
            itkStructureTensorRecursiveGaussianImageFilterTest
            ${CMAKE_SOURCE_DIR}/PrimitiveObjects.mha
            ${CMAKE_BINARY_DIR}/PrimaryEigenVectorImage.mha
            ${CMAKE_BINARY_DIR}/PrimaryEigenValueImage.mha )

  ADD_TEST( AnisotropicHybridDiffusionImageFilterTest 
            itkAnisotropicHybridDiffusionImageFilterTest
               ${CMAKE_SOURCE_DIR}/CroppedWholeLungCTScan.mhd
               ${CMAKE_BINARY_DIR}/itkAnisotropicHybridDiffusionImageFilterTest.mha )

  ADD_TEST( AnisotropicCoherenceEnhancingDiffusionImageFilterTest
            itkAnisotropicCoherenceEnhancingDiffusionImageFilterTest
               ${CMAKE_SOURCE_DIR}/CroppedWholeLungCTScan.mhd
               ${CMAKE_BINARY_DIR}/itkAnisotropicCoherenceEnhancingDiffusionImageFilterTest.mha )

  ADD_TEST( AnisotropicEdgeEnhancementDiffusionImageFilterTest 
            itkAnisotropicEdgeEnhancementDiffusionImageFilterTest
               ${CMAKE_SOURCE_DIR}/CroppedWholeLungCTScan.mhd
               ${CMAKE_BINARY_DIR}/itkAnisotropicEdgeEnhancementDiffusionImageFilterTest.mha )

ENDIF(BUILD_TESTING)

