/*=========================================================================

Library:   TubeTK

Copyright 2010 Kitware Inc. 28 Corporate Drive,
Clifton Park, NY, 12065, USA.

All rights reserved. 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

=========================================================================*/
#ifndef __itkAnisotropicEdgeEnhancementDiffusionImageFilter_h
#define __itkAnisotropicEdgeEnhancementDiffusionImageFilter_h

#include "itkAnisotropicDiffusionTensorImageFilter.h"
#include "itkAnisotropicDiffusionTensorFunction.h"
#include "itkMultiThreader.h"
#include "itkDiffusionTensor3D.h"
#include "itkHessianRecursiveGaussianImageFilter.h"
#include "itkStructureTensorRecursiveGaussianImageFilter.h"
#include "itkSymmetricEigenAnalysisImageFilter.h"
#include "itkSymmetricEigenVectorAnalysisImageFilter.h"

namespace itk {
/** \class AnisotropicEdgeEnhancementDiffusionImageFilter
 *  This class is an implementation of Edge-enhancing diffusion
 *   INSERT reference here
 * 
 * \sa itkAnisotropicDiffusionTensorImageFilter 
 * \sa itkAnisotropicCoherenceEnhancingDiffusionImageFilter
 *
 * \ingroup FiniteDifferenceFunctions
 * \ingroup Functions
 */


template <class TInputImage, class TOutputImage>
class ITK_EXPORT AnisotropicEdgeEnhancementDiffusionImageFilter  
  : public AnisotropicDiffusionTensorImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard class typedefs */
  typedef AnisotropicEdgeEnhancementDiffusionImageFilter Self;

  typedef AnisotropicDiffusionTensorImageFilter<TInputImage, TOutputImage> 
                                                           Superclass;

  typedef SmartPointer<Self>                               Pointer;
  typedef SmartPointer<const Self>                         ConstPointer;
 

  /** Method for creation through the object factory */
  itkNewMacro( Self );

  /** Run-time type information (and related methods) */
  itkTypeMacro(AnisotropicEdgeEnhancementDiffusionImageFilter,
                                                ImageToImageFilter );
  
  /** Convenient typedefs */
  typedef typename Superclass::InputImageType  InputImageType;
  typedef typename Superclass::OutputImageType OutputImageType;
  typedef typename Superclass::PixelType       PixelType;

  typedef typename Superclass::DiffusionTensorImageType 
                                                DiffusionTensorImageType;

  // Structure tensor type 
  typedef StructureTensorRecursiveGaussianImageFilter < InputImageType >
                                                StructureTensorFilterType;
  
  /** Dimensionality of input and output data is assumed to be the same.
   * It is inherited from the superclass. */
  itkStaticConstMacro(ImageDimension, unsigned int,Superclass::ImageDimension);

  typedef itk::Matrix<double, ImageDimension, ImageDimension> MatrixType;

  // Define image of matrix pixel type 
  typedef itk::Image< MatrixType, ImageDimension>  OutputMatrixImageType;

  // Define the symmetric tensor pixel type
  typedef itk::SymmetricSecondRankTensor< double, ImageDimension> 
                                                         TensorPixelType;
  typedef itk::Image< TensorPixelType, ImageDimension>  
                                                         TensorImageType;

   // Define the type for storing the eigen-value
  typedef itk::FixedArray< double, ImageDimension >      EigenValueArrayType;
  
  // Declare the types of the output images
  typedef itk::Image< EigenValueArrayType, ImageDimension >  
                                                  EigenAnalysisOutputImageType;
  
  /** The container type for the update buffer. */
  typedef OutputImageType UpdateBufferType;

  /** Define diffusion image nbd type */
  typedef typename Superclass::DiffusionTensorNeighborhoodType
                                               DiffusionTensorNeighborhoodType;

  /** Set the contrast parameter */
  void SetContrastParameterLambdaE( double value ); 

  /** Set threshold parameter C */
  void SetThresholdParameterC( double value );

  /** Set the sigma value for structure tensor computation */
  void SetSigma( double sigma );


protected:
  AnisotropicEdgeEnhancementDiffusionImageFilter();
 ~AnisotropicEdgeEnhancementDiffusionImageFilter() {}
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** Update diffusion tensor image */
  void virtual UpdateDiffusionTensorImage();
 
private:
  //purposely not implemented
  AnisotropicEdgeEnhancementDiffusionImageFilter(const Self&); 
  void operator=(const Self&); //purposely not implemented

  double    m_ContrastParameterLambdaE;
  double    m_ThresholdParameterC;
  double    m_Sigma;
};
  

}// end namespace itk

#if ITK_TEMPLATE_TXX
# include "itkAnisotropicEdgeEnhancementDiffusionImageFilter.txx"
#endif

#endif
