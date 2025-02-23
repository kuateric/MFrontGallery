/*!
* \file   TFEL/Material/HypoplasticClayModelWrapper.hxx
* \brief  this file implements the HypoplasticClayModelWrapper Behaviour.
*         File generated by tfel version 4.1.0-dev
* \author Thomas Helfer
* \date   11 / 02 / 2021
 */

#ifndef LIB_TFELMATERIAL_HYPOPLASTICCLAYMODELWRAPPER_HXX
#define LIB_TFELMATERIAL_HYPOPLASTICCLAYMODELWRAPPER_HXX

#include<string>
#include<iostream>
#include<limits>
#include<stdexcept>
#include<algorithm>

#include"TFEL/Raise.hxx"
#include"TFEL/PhysicalConstants.hxx"
#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/Config/TFELTypes.hxx"
#include"TFEL/TypeTraits/IsFundamentalNumericType.hxx"
#include"TFEL/TypeTraits/IsReal.hxx"
#include"TFEL/Math/General/IEEE754.hxx"
#include"TFEL/Material/MaterialException.hxx"
#include"TFEL/Material/MechanicalBehaviour.hxx"
#include"TFEL/Material/MechanicalBehaviourTraits.hxx"
#include"TFEL/Material/OutOfBoundsPolicy.hxx"
#include"TFEL/Material/BoundsCheck.hxx"
#include"TFEL/Material/IsotropicPlasticity.hxx"
#include"TFEL/Material/Lame.hxx"
#include"TFEL/Material/Hosford1972YieldCriterion.hxx"
#include"TFEL/Material/HypoplasticClayModelWrapperBehaviourData.hxx"
#include"TFEL/Material/HypoplasticClayModelWrapperIntegrationData.hxx"

#line 17 "HypoplasticClayModelWrapper.mfront"
#include "MFrontUmatWrapper.hxx"

#include "MFront/GenericBehaviour/State.hxx"
#include "MFront/GenericBehaviour/BehaviourData.hxx"
namespace tfel::material{

struct HypoplasticClayModelWrapperTridimensionalParametersInitializer
{
static HypoplasticClayModelWrapperTridimensionalParametersInitializer&
get();


void set(const char* const,const double);

private :

HypoplasticClayModelWrapperTridimensionalParametersInitializer();

HypoplasticClayModelWrapperTridimensionalParametersInitializer(const HypoplasticClayModelWrapperTridimensionalParametersInitializer&);

HypoplasticClayModelWrapperTridimensionalParametersInitializer&
operator=(const HypoplasticClayModelWrapperTridimensionalParametersInitializer&);
/*!
 * \brief read the parameters from the given file
 * \param[out] pi : parameters initializer
 * \param[in]  fn : file name
 */
static void readParameters(HypoplasticClayModelWrapperTridimensionalParametersInitializer&,const char* const);
};

struct HypoplasticClayModelWrapperParametersInitializer
{
static HypoplasticClayModelWrapperParametersInitializer&
get();

double minimal_time_step_scaling_factor;
double maximal_time_step_scaling_factor;

void set(const char* const,const double);

/*!
 * \brief convert a string to double
 * \param[in] p : parameter
 * \param[in] v : value
 */
static double getDouble(const std::string&,const std::string&);
private :

HypoplasticClayModelWrapperParametersInitializer();

HypoplasticClayModelWrapperParametersInitializer(const HypoplasticClayModelWrapperParametersInitializer&);

HypoplasticClayModelWrapperParametersInitializer&
operator=(const HypoplasticClayModelWrapperParametersInitializer&);
/*!
 * \brief read the parameters from the given file
 * \param[out] pi : parameters initializer
 * \param[in]  fn : file name
 */
static void readParameters(HypoplasticClayModelWrapperParametersInitializer&,const char* const);
};

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis, typename NumericType, bool use_qt>
struct HypoplasticClayModelWrapper;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis, typename NumericType>
std::ostream&
 operator <<(std::ostream&,const HypoplasticClayModelWrapper<hypothesis, NumericType, false>&);

//! \brief forward declaration
template<typename NumericType>
std::ostream&
 operator <<(std::ostream&,const HypoplasticClayModelWrapper<ModellingHypothesis::TRIDIMENSIONAL, NumericType, false>&);

/*!
* \class HypoplasticClayModelWrapper
* \brief This class implements the HypoplasticClayModelWrapper behaviour.
* \tparam hypothesis: modelling hypothesis.
* \tparam NumericType: numerical type.
* \author Thomas Helfer
* \date   11 / 02 / 2021
*/
template<typename NumericType>
struct HypoplasticClayModelWrapper<ModellingHypothesis::TRIDIMENSIONAL, NumericType, false> final
: public MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,ModellingHypothesis::TRIDIMENSIONAL, NumericType, false>,
public HypoplasticClayModelWrapperBehaviourData<ModellingHypothesis::TRIDIMENSIONAL, NumericType, false>,
public HypoplasticClayModelWrapperIntegrationData<ModellingHypothesis::TRIDIMENSIONAL, NumericType, false>
{

static constexpr ModellingHypothesis::Hypothesis hypothesis = ModellingHypothesis::TRIDIMENSIONAL;
static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;

static_assert(N==1||N==2||N==3);
static_assert(tfel::typetraits::IsFundamentalNumericType<NumericType>::cond);
static_assert(tfel::typetraits::IsReal<NumericType>::cond);

friend std::ostream& operator<< <>(std::ostream&,const HypoplasticClayModelWrapper&);

static constexpr unsigned short TVectorSize = N;
typedef tfel::math::StensorDimeToSize<N> StensorDimeToSize;
static constexpr unsigned short StensorSize = StensorDimeToSize::value;
typedef tfel::math::TensorDimeToSize<N> TensorDimeToSize;
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

public :

typedef HypoplasticClayModelWrapperBehaviourData<hypothesis, NumericType, false> BehaviourData;
typedef HypoplasticClayModelWrapperIntegrationData<hypothesis, NumericType, false> IntegrationData;
typedef typename MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::SMFlag SMFlag;
typedef typename MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::SMType SMType;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::ELASTIC;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::SECANTOPERATOR;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::TANGENTOPERATOR;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::CONSISTENTTANGENTOPERATOR;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::NOSTIFFNESSREQUESTED;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::STANDARDTANGENTOPERATOR;
using IntegrationResult = typename MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::IntegrationResult;

using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::SUCCESS;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::FAILURE;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::UNRELIABLE_RESULTS;

using StressFreeExpansionType = StrainStensor;

private :

#line 9 "HypoplasticClayModelWrapper.mfront"
static constexpr auto nmps = int{22};
#line 11 "HypoplasticClayModelWrapper.mfront"
static constexpr auto nisvs = int{16};


#line 14 "HypoplasticClayModelWrapper.mfront"
tfel::math::runtime_array<real > disvs;

#line 20 "HypoplasticClayModelWrapper.mfront"
StiffnessTensor K;

time minimal_time_step_scaling_factor;
time maximal_time_step_scaling_factor;

//! Tangent operator;
TangentOperator Dt;
//! alias to the tangent operator;
TangentOperator& dsig_ddeto;
/*!
* \brief Update internal variables at end of integration
*/
void updateIntegrationVariables(){
}

/*!
* \brief Update internal variables at end of integration
*/
void updateStateVariables(){
this->isvs += this->disvs;
}

/*!
* \brief Update auxiliary state variables at end of integration
*/
void updateAuxiliaryStateVariables()
{}

//! \brief Default constructor (disabled)
HypoplasticClayModelWrapper() =delete ;
//! \brief Copy constructor (disabled)
HypoplasticClayModelWrapper(const HypoplasticClayModelWrapper&) = delete;
//! \brief Assignement operator (disabled)
HypoplasticClayModelWrapper& operator = (const HypoplasticClayModelWrapper&) = delete;

public:

/*!
* \brief Constructor
*/
HypoplasticClayModelWrapper(const HypoplasticClayModelWrapperBehaviourData<hypothesis, NumericType, false>& src1,
const HypoplasticClayModelWrapperIntegrationData<hypothesis, NumericType, false>& src2)
: HypoplasticClayModelWrapperBehaviourData<hypothesis, NumericType, false>(src1),
HypoplasticClayModelWrapperIntegrationData<hypothesis, NumericType, false>(src2),
disvs(16,real(0)),
dsig_ddeto(Dt)
{
using namespace std;
using namespace tfel::math;
using std::vector;
this->minimal_time_step_scaling_factor = HypoplasticClayModelWrapperParametersInitializer::get().minimal_time_step_scaling_factor;
this->maximal_time_step_scaling_factor = HypoplasticClayModelWrapperParametersInitializer::get().maximal_time_step_scaling_factor;
}

/*
 * \brief constructor for the Generic interface
 * \param[in] mgb_d: behaviour data
 */
HypoplasticClayModelWrapper(const mfront::gb::BehaviourData& mgb_d)
: HypoplasticClayModelWrapperBehaviourData<hypothesis, NumericType, false>(mgb_d),
HypoplasticClayModelWrapperIntegrationData<hypothesis, NumericType, false>(mgb_d),
disvs(16,real(0)),
dsig_ddeto(Dt)
{
using namespace std;
using namespace tfel::math;
using std::vector;
this->minimal_time_step_scaling_factor = HypoplasticClayModelWrapperParametersInitializer::get().minimal_time_step_scaling_factor;
this->maximal_time_step_scaling_factor = HypoplasticClayModelWrapperParametersInitializer::get().maximal_time_step_scaling_factor;
this-> eto = tfel::math::map<StrainStensor>(mgb_d.s0.gradients);
tfel::fsalgo::transform<StensorSize>::exe(mgb_d.s1.gradients,mgb_d.s0.gradients,this->deto.begin(),std::minus<real>());
}

/*!
 * \ brief initialize the behaviour with user code
 */
void initialize(){
using namespace std;
using namespace tfel::math;
using std::vector;
}

/*!
 * \brief set the policy for "out of bounds" conditions
 */
void
setOutOfBoundsPolicy(const OutOfBoundsPolicy policy_value){
  this->policy = policy_value;
} // end of setOutOfBoundsPolicy

/*!
* \return the modelling hypothesis
*/
constexpr ModellingHypothesis::Hypothesis
getModellingHypothesis() const{
return hypothesis;
} // end of getModellingHypothesis

//! \brief check physical bounds and standard bounds
void checkBounds() const{
} // end of checkBounds

IntegrationResult computePredictionOperator(const SMFlag,const SMType) override{
tfel::raise("HypoplasticClayModelWrapper::computePredictionOperator: "
"unsupported prediction operator flag");
}

time getMinimalTimeStepScalingFactor() const noexcept override{
  return this->minimal_time_step_scaling_factor;
}

std::pair<bool, time>
computeAPrioriTimeStepScalingFactor(const time current_time_step_scaling_factor) const override{
const auto time_scaling_factor = this->computeAPrioriTimeStepScalingFactorII();
return {time_scaling_factor.first,
        std::min(std::min(std::max(time_scaling_factor.second,
                                   this->minimal_time_step_scaling_factor),
                          this->maximal_time_step_scaling_factor),
                  current_time_step_scaling_factor)};
}

/*!
* \brief Integrate behaviour  over the time step
*/
IntegrationResult
integrate(const SMFlag smflag, const SMType smt) override{
using namespace std;
using namespace tfel::math;
raise_if(smflag!=MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::STANDARDTANGENTOPERATOR,
"invalid tangent operator flag");
bool computeTangentOperator_ = smt!=NOSTIFFNESSREQUESTED;
#line 24 "HypoplasticClayModelWrapper.mfront"
const AbaqusRealType drot[9] = {1, 0, 0,
#line 25 "HypoplasticClayModelWrapper.mfront"
0, 1, 0,
#line 26 "HypoplasticClayModelWrapper.mfront"
0, 0, 1};
#line 27 "HypoplasticClayModelWrapper.mfront"
const AbaqusIntegerType KSTEP[3u] = {0, 0, 0};
#line 29 "HypoplasticClayModelWrapper.mfront"
AbaqusIntegerType KINC = 1;
#line 31 "HypoplasticClayModelWrapper.mfront"
const char name[81] =
#line 32 "HypoplasticClayModelWrapper.mfront"
"Elasticity                              "
#line 33 "HypoplasticClayModelWrapper.mfront"
"                                        ";
#line 35 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType e[6];
#line 36 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType de[6];
#line 37 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType s[6];
#line 38 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType rdt = 1;
#line 40 "HypoplasticClayModelWrapper.mfront"
mfront_umat_wrapper::convertStrainToAbaqus<hypothesis>(e, &this->eto[0]);
#line 41 "HypoplasticClayModelWrapper.mfront"
mfront_umat_wrapper::convertStrainToAbaqus<hypothesis>(de, &this->deto[0]);
#line 42 "HypoplasticClayModelWrapper.mfront"
mfront_umat_wrapper::convertStressToAbaqus<hypothesis>(s, &this->sig[0]);
#line 43 "HypoplasticClayModelWrapper.mfront"
for (ushort i = 0; i != 6; ++i) {
#line 45 "HypoplasticClayModelWrapper.mfront"
s[i] *= 1e-3;
#line 46 "HypoplasticClayModelWrapper.mfront"
}
#line 48 "HypoplasticClayModelWrapper.mfront"
const auto nprops = static_cast<AbaqusIntegerType>(HypoplasticClayModelWrapper::nmps);
#line 49 "HypoplasticClayModelWrapper.mfront"
const auto nstatv = static_cast<AbaqusIntegerType>(HypoplasticClayModelWrapper::nisvs);
#line 50 "HypoplasticClayModelWrapper.mfront"
const auto ntens = static_cast<AbaqusIntegerType>(6);
#line 51 "HypoplasticClayModelWrapper.mfront"
const auto ndi = static_cast<AbaqusIntegerType>(3);
#line 52 "HypoplasticClayModelWrapper.mfront"
const auto nshr = static_cast<AbaqusIntegerType>(3);
#line 53 "HypoplasticClayModelWrapper.mfront"
const auto noel = static_cast<AbaqusIntegerType>(0);
#line 54 "HypoplasticClayModelWrapper.mfront"
const auto npt = static_cast<AbaqusIntegerType>(0);
#line 58 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType sse, spd, scd, rpl;
#line 59 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType ddsddt[6];
#line 60 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType drplde[6];
#line 61 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType drpldt;
#line 62 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType time[2];
#line 63 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType pred[1] = {0};
#line 64 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType dpred[1] = {0};
#line 65 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType coords[3] = {0, 0, 0};
#line 66 "HypoplasticClayModelWrapper.mfront"
const AbaqusRealType dfgrd0[9] = {1, 0, 0,
#line 67 "HypoplasticClayModelWrapper.mfront"
0, 1, 0,
#line 68 "HypoplasticClayModelWrapper.mfront"
0, 0, 1};
#line 69 "HypoplasticClayModelWrapper.mfront"
const AbaqusRealType dfgrd1[9] = {1, 0, 0,
#line 70 "HypoplasticClayModelWrapper.mfront"
0, 1, 0,
#line 71 "HypoplasticClayModelWrapper.mfront"
0, 0, 1};
#line 72 "HypoplasticClayModelWrapper.mfront"
AbaqusRealType celent;
#line 73 "HypoplasticClayModelWrapper.mfront"
AbaqusIntegerType layer;
#line 74 "HypoplasticClayModelWrapper.mfront"
AbaqusIntegerType kspt;
#line 76 "HypoplasticClayModelWrapper.mfront"
umat_hcea_(
#line 77 "HypoplasticClayModelWrapper.mfront"
s,
#line 78 "HypoplasticClayModelWrapper.mfront"
&this->isvs[0],
#line 79 "HypoplasticClayModelWrapper.mfront"
&this->K(0, 0),
#line 80 "HypoplasticClayModelWrapper.mfront"
&sse, &spd, &scd, &rpl, ddsddt, drplde, &drpldt, e,
#line 81 "HypoplasticClayModelWrapper.mfront"
de,
#line 82 "HypoplasticClayModelWrapper.mfront"
time,
#line 83 "HypoplasticClayModelWrapper.mfront"
&this->dt,
#line 84 "HypoplasticClayModelWrapper.mfront"
&this->T,
#line 85 "HypoplasticClayModelWrapper.mfront"
&this->dT,
#line 86 "HypoplasticClayModelWrapper.mfront"
pred,
#line 87 "HypoplasticClayModelWrapper.mfront"
dpred,
#line 88 "HypoplasticClayModelWrapper.mfront"
name, &ndi, &nshr, &ntens,
#line 89 "HypoplasticClayModelWrapper.mfront"
&nstatv,
#line 90 "HypoplasticClayModelWrapper.mfront"
&this->mps[0],
#line 91 "HypoplasticClayModelWrapper.mfront"
&nprops,
#line 92 "HypoplasticClayModelWrapper.mfront"
coords, drot,
#line 93 "HypoplasticClayModelWrapper.mfront"
&rdt,
#line 94 "HypoplasticClayModelWrapper.mfront"
&celent, dfgrd0, dfgrd1, &noel, &npt, &layer, &kspt, KSTEP, &KINC, 80);
#line 96 "HypoplasticClayModelWrapper.mfront"
mfront_umat_wrapper::convertStressFromAbaqus<hypothesis>(&this->sig[0], s);
#line 98 "HypoplasticClayModelWrapper.mfront"
this->sig *= 1e3;
#line 100 "HypoplasticClayModelWrapper.mfront"
if (rdt < 1) {
#line 101 "HypoplasticClayModelWrapper.mfront"
return FAILURE;
#line 102 "HypoplasticClayModelWrapper.mfront"
}
this->updateIntegrationVariables();
this->updateStateVariables();
this->updateAuxiliaryStateVariables();
if(computeTangentOperator_){
if(!this->computeConsistentTangentOperator(smt)){
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::FAILURE;
}
}
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis, NumericType, false>::SUCCESS;
}

std::pair<bool, time>
computeAPosterioriTimeStepScalingFactor(const time current_time_step_scaling_factor) const override{
const auto time_scaling_factor = this->computeAPosterioriTimeStepScalingFactorII();
return {time_scaling_factor.first,
        std::min(std::min(std::max(time_scaling_factor.second,
                                   this->minimal_time_step_scaling_factor),
                          this->maximal_time_step_scaling_factor),
                 current_time_step_scaling_factor)};
}

/*!
* \brief Update the internal energy at end of the time step
* \param[in] Psi_s: internal energy at end of the time step
*/
void computeInternalEnergy(stress& Psi_s) const
{
Psi_s=stress{0};
}

/*!
* \brief Update the dissipated energy at end of the time step
* \param[in] Psi_d: dissipated energy at end of the time step
*/
void computeDissipatedEnergy(stress& Psi_d) const
{
Psi_d=stress{0};
}

bool computeConsistentTangentOperator(const SMType smt){
using namespace std;
using namespace tfel::math;
using std::vector;
auto mfront_success = true;
#line 106 "HypoplasticClayModelWrapper.mfront"
static_cast<void>(smt);
#line 107 "HypoplasticClayModelWrapper.mfront"
mfront_umat_wrapper::convertStiffnessMatrixFromAbaqus<hypothesis>(&this->Dt(0, 0),
#line 108 "HypoplasticClayModelWrapper.mfront"
&this->K(0, 0));
#line 110 "HypoplasticClayModelWrapper.mfront"
this->Dt *= 1e3;
return mfront_success;
}

/*!
* \brief compute the sound velocity
* \param[in] rho_m0: mass density in the reference configuration
*/
speed computeSpeedOfSound(const massdensity&) const {
return speed(0);

}

const TangentOperator& getTangentOperator() const{
return this->Dt;
}

void updateExternalStateVariables(){
this->eto  += this->deto;
this->T += this->dT;
}

//!
~HypoplasticClayModelWrapper()
 override = default;

private:

std::pair<bool, time> computeAPrioriTimeStepScalingFactorII() const{
return {true, this->maximal_time_step_scaling_factor};
}

std::pair<bool, time> computeAPosterioriTimeStepScalingFactorII() const{
return {true,this->maximal_time_step_scaling_factor};
}

//! policy for treating out of bounds conditions
OutOfBoundsPolicy policy = tfel::material::None;

}; // end of HypoplasticClayModelWrapper class

template<typename NumericType>
std::ostream&
operator <<(std::ostream& os,const HypoplasticClayModelWrapper<ModellingHypothesis::TRIDIMENSIONAL, NumericType, false>& b)
{
os << "εᵗᵒ : " << b.eto << '\n';
os << "Δεᵗᵒ : " << b.deto << '\n';
os << "σ : " << b.sig << '\n';
os << "Δt : " << b.dt << '\n';
os << "mps : " << b.mps << '\n';
os << "isvs : " << b.isvs << '\n';
os << "Δisvs : " << b.disvs << '\n';
os << "T : " << b.T << '\n';
os << "ΔT : " << b.dT << '\n';
os << "K : " << b.K << '\n';
os << "minimal_time_step_scaling_factor : " << b.minimal_time_step_scaling_factor << '\n';
os << "maximal_time_step_scaling_factor : " << b.maximal_time_step_scaling_factor << '\n';
return os;
}

/*!
* Partial specialisation for HypoplasticClayModelWrapper.
*/
template<ModellingHypothesis::Hypothesis hypothesis, typename NumericType>
class MechanicalBehaviourTraits<HypoplasticClayModelWrapper<hypothesis, NumericType, false> >
{
using size_type = unsigned short;
public:
static constexpr bool is_defined = false;
static constexpr bool use_quantities = false;
static constexpr bool hasStressFreeExpansion = false;
static constexpr bool handlesThermalExpansion = false;
static constexpr unsigned short dimension = 0u;
static constexpr size_type material_properties_nb = 0;
static constexpr size_type internal_variables_nb  = 0;
static constexpr size_type external_variables_nb  = 0;
static constexpr size_type external_variables_nb2 = 0;
static constexpr bool hasConsistentTangentOperator = false;
static constexpr bool isConsistentTangentOperatorSymmetric = false;
static constexpr bool hasPredictionOperator = false;
static constexpr bool hasAPrioriTimeStepScalingFactor = false;
static constexpr bool hasComputeInternalEnergy = false;
static constexpr bool hasComputeDissipatedEnergy = false;
/*!
* \return the name of the class.
*/
static const char* getName(){
return "HypoplasticClayModelWrapper";
}

};

/*!
* Partial specialisation for HypoplasticClayModelWrapper.
*/
template<typename NumericType>
class MechanicalBehaviourTraits<HypoplasticClayModelWrapper<ModellingHypothesis::TRIDIMENSIONAL, NumericType, false> >
{
using size_type = unsigned short;
static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<ModellingHypothesis::TRIDIMENSIONAL>::value;
static constexpr unsigned short TVectorSize = N;
typedef tfel::math::StensorDimeToSize<N> StensorDimeToSize;
static constexpr unsigned short StensorSize = StensorDimeToSize::value;
typedef tfel::math::TensorDimeToSize<N> TensorDimeToSize;
static constexpr unsigned short TensorSize = TensorDimeToSize::value;
public:
static constexpr bool is_defined = true;
static constexpr bool use_quantities = false;
static constexpr bool hasStressFreeExpansion = false;
static constexpr bool handlesThermalExpansion = false;
static constexpr unsigned short dimension = N;
static constexpr size_type material_properties_nb = 22;
static constexpr size_type internal_variables_nb  = 16;
static constexpr size_type external_variables_nb  = 1;
static constexpr size_type external_variables_nb2 = 0;
static constexpr bool hasConsistentTangentOperator = true;
static constexpr bool isConsistentTangentOperatorSymmetric = false;
static constexpr bool hasPredictionOperator = false;
static constexpr bool hasAPrioriTimeStepScalingFactor = false;
static constexpr bool hasComputeInternalEnergy = false;
static constexpr bool hasComputeDissipatedEnergy = false;
/*!
* \return the name of the class.
*/
static const char* getName(){
return "HypoplasticClayModelWrapper";
}

};

} // end of namespace tfel::material

#endif /* LIB_TFELMATERIAL_HYPOPLASTICCLAYMODELWRAPPER_HXX */
