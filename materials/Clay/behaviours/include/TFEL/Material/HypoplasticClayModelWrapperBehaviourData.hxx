/*!
* \file   TFEL/Material/HypoplasticClayModelWrapperBehaviourData.hxx
* \brief  this file implements the HypoplasticClayModelWrapperBehaviourData class.
*         File generated by tfel version 4.1.0-dev
* \author Thomas Helfer
* \date   11 / 02 / 2021
 */

#ifndef LIB_TFELMATERIAL_HYPOPLASTICCLAYMODELWRAPPER_BEHAVIOUR_DATA_HXX
#define LIB_TFELMATERIAL_HYPOPLASTICCLAYMODELWRAPPER_BEHAVIOUR_DATA_HXX

#include<limits>
#include<string>
#include<sstream>
#include<iostream>
#include<stdexcept>
#include<algorithm>

#include"TFEL/Raise.hxx"
#include"TFEL/PhysicalConstants.hxx"
#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/Config/TFELTypes.hxx"
#include"TFEL/TypeTraits/IsFundamentalNumericType.hxx"
#include"TFEL/TypeTraits/IsReal.hxx"
#include"TFEL/Math/General/Abs.hxx"
#include"TFEL/Math/General/IEEE754.hxx"
#include"TFEL/Math/Array/ViewsArrayIO.hxx"
#include"TFEL/Math/Array/fsarrayIO.hxx"
#include"TFEL/Math/Array/runtime_arrayIO.hxx"
#include"TFEL/Math/fsarray.hxx"
#include"TFEL/Math/runtime_array.hxx"
#include"TFEL/Math/vector.hxx"
#include"TFEL/Math/tmatrix.hxx"
#include"TFEL/Math/Matrix/tmatrixIO.hxx"
#include"TFEL/Math/stensor.hxx"
#include"TFEL/Math/Stensor/StensorConceptIO.hxx"
#include"TFEL/Math/st2tost2.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2ConceptIO.hxx"
#include"TFEL/Material/ModellingHypothesis.hxx"

#line 17 "HypoplasticClayModelWrapper.mfront"
#include "MFrontUmatWrapper.hxx"

#include "MFront/GenericBehaviour/State.hxx"
#include "MFront/GenericBehaviour/BehaviourData.hxx"
namespace tfel::material{

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename,bool>
class HypoplasticClayModelWrapperBehaviourData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis, typename NumericType,bool use_qt>
class HypoplasticClayModelWrapperIntegrationData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename NumericType>
std::ostream&
 operator <<(std::ostream&,const HypoplasticClayModelWrapperBehaviourData<hypothesis, NumericType,false>&);

//! \brief forward declaration
template<typename NumericType>
std::ostream&
 operator <<(std::ostream&,const HypoplasticClayModelWrapperBehaviourData<ModellingHypothesis::TRIDIMENSIONAL, NumericType, false>&);

template<typename NumericType>
class HypoplasticClayModelWrapperBehaviourData<ModellingHypothesis::TRIDIMENSIONAL, NumericType, false>
{

static constexpr ModellingHypothesis::Hypothesis hypothesis = ModellingHypothesis::TRIDIMENSIONAL;
static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;
static_assert(N==1||N==2||N==3);
static_assert(tfel::typetraits::IsFundamentalNumericType<NumericType>::cond);
static_assert(tfel::typetraits::IsReal<NumericType>::cond);

friend std::ostream& operator<< <>(std::ostream&,const HypoplasticClayModelWrapperBehaviourData&);

/* integration data is declared friend to access   driving variables at the beginning of the time step */
friend class HypoplasticClayModelWrapperIntegrationData<hypothesis, NumericType, false>;

static constexpr unsigned short TVectorSize = N;
using StensorDimeToSize = tfel::math::StensorDimeToSize<N>;
static constexpr unsigned short StensorSize = StensorDimeToSize::value;
using TensorDimeToSize = tfel::math::TensorDimeToSize<N>;
static constexpr unsigned short TensorSize = TensorDimeToSize::value;

using ushort =  unsigned short;
using Types = tfel::config::Types<N, NumericType, false>;
using Type = NumericType;
using real = typename Types::real;
using time = typename Types::time;
using length = typename Types::length;
using frequency = typename Types::frequency;
using speed = typename Types::speed;
using stress = typename Types::stress;
using strain = typename Types::strain;
using strainrate = typename Types::strainrate;
using stressrate = typename Types::stressrate;
using temperature = typename Types::temperature;
using thermalexpansion = typename Types::thermalexpansion;
using thermalconductivity = typename Types::thermalconductivity;
using massdensity = typename Types::massdensity;
using energydensity = typename Types::energydensity;
using TVector = typename Types::TVector;
using DisplacementTVector = typename Types::DisplacementTVector;
using ForceTVector = typename Types::ForceTVector;
using HeatFlux = typename Types::HeatFlux;
using TemperatureGradient = typename Types::TemperatureGradient;
using Stensor = typename Types::Stensor;
using StressStensor = typename Types::StressStensor;
using StressRateStensor = typename Types::StressRateStensor;
using StrainStensor = typename Types::StrainStensor;
using StrainRateStensor = typename Types::StrainRateStensor;
using FrequencyStensor = typename Types::FrequencyStensor;
using Tensor = typename Types::Tensor;
using DeformationGradientTensor = typename Types::DeformationGradientTensor;
using DeformationGradientRateTensor = typename Types::DeformationGradientRateTensor;
using StressTensor = typename Types::StressTensor;
using StiffnessTensor = typename Types::StiffnessTensor;
using Stensor4 = typename Types::Stensor4;
using TangentOperator = StiffnessTensor;
using PhysicalConstants = tfel::PhysicalConstants<NumericType, false>;

protected:

StrainStensor eto;

StressStensor sig;

#line 13 "HypoplasticClayModelWrapper.mfront"
tfel::math::runtime_array<real > mps;

#line 14 "HypoplasticClayModelWrapper.mfront"
tfel::math::runtime_array<real > isvs;
temperature T;

public:

/*!
* \brief Default constructor
*/
HypoplasticClayModelWrapperBehaviourData()
{}

/*!
* \brief copy constructor
*/
HypoplasticClayModelWrapperBehaviourData(const HypoplasticClayModelWrapperBehaviourData& src)
: eto(src.eto),
sig(src.sig),
mps(src.mps),
isvs(src.isvs),
T(src.T)
{}

/*
 * \brief constructor for the Generic interface
 * \param[in] mgb_d: behaviour data
 */
HypoplasticClayModelWrapperBehaviourData(const mfront::gb::BehaviourData& mgb_d)
: T(mgb_d.s0.external_state_variables[0])
{
this-> sig = tfel::math::map<StressStensor>(mgb_d.s0.thermodynamic_forces);
this->mps.resize(22);
for(unsigned short idx=0; idx != 22; ++idx){
this->mps[idx] = mgb_d.s1.material_properties[0+idx];
}
this->isvs.resize(16);
for(unsigned short idx=0; idx != 16; ++idx){
this->isvs[idx] = mgb_d.s0.internal_state_variables[0+idx];
}
}


/*
* \brief Assignement operator
*/
HypoplasticClayModelWrapperBehaviourData&
operator=(const HypoplasticClayModelWrapperBehaviourData& src){
this->eto = src.eto;
this->sig = src.sig;
this->mps = src.mps;
this->isvs = src.isvs;
this->T = src.T;
return *this;
}

void exportStateData(mfront::gb::State& mbg_s1) const
{
using namespace tfel::math;
tfel::math::map<StressStensor>(mbg_s1.thermodynamic_forces) = this->sig;
mbg_s1.internal_state_variables[0] = this->isvs[0];
mbg_s1.internal_state_variables[1] = this->isvs[1];
mbg_s1.internal_state_variables[2] = this->isvs[2];
mbg_s1.internal_state_variables[3] = this->isvs[3];
mbg_s1.internal_state_variables[4] = this->isvs[4];
mbg_s1.internal_state_variables[5] = this->isvs[5];
mbg_s1.internal_state_variables[6] = this->isvs[6];
mbg_s1.internal_state_variables[7] = this->isvs[7];
mbg_s1.internal_state_variables[8] = this->isvs[8];
mbg_s1.internal_state_variables[9] = this->isvs[9];
mbg_s1.internal_state_variables[10] = this->isvs[10];
mbg_s1.internal_state_variables[11] = this->isvs[11];
mbg_s1.internal_state_variables[12] = this->isvs[12];
mbg_s1.internal_state_variables[13] = this->isvs[13];
mbg_s1.internal_state_variables[14] = this->isvs[14];
mbg_s1.internal_state_variables[15] = this->isvs[15];
} // end of exportStateData

}; // end of HypoplasticClayModelWrapperBehaviourDataclass

template<typename NumericType>
std::ostream&
operator <<(std::ostream& os,const HypoplasticClayModelWrapperBehaviourData<ModellingHypothesis::TRIDIMENSIONAL, NumericType, false>& b)
{
os << "εᵗᵒ : " << b.eto << '\n';
os << "σ : " << b.sig << '\n';
os << "mps : " << b.mps << '\n';
os << "isvs : " << b.isvs << '\n';
os << "T : " << b.T << '\n';
return os;
}

} // end of namespace tfel::material

#endif /* LIB_TFELMATERIAL_HYPOPLASTICCLAYMODELWRAPPER_BEHAVIOUR_DATA_HXX */
