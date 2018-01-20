/*
 * NOTICE
 *
 * This work was produced at the Lawrence Livermore National Laboratory (LLNL)
 * under contract no. DE-AC-52-07NA27344 (Contract 44) between the U.S.
 * Department of Energy (DOE) and Lawrence Livermore National Security, LLC
 * (LLNS) for the operation of LLNL. The rights of the Federal Government are
 * reserved under Contract 44.
 *
 * DISCLAIMER
 *
 * This work was prepared as an account of work sponsored by an agency of the
 * United States Government. Neither the United States Government nor Lawrence
 * Livermore National Security, LLC nor any of their employees, makes any
 * warranty, express or implied, or assumes any liability or responsibility
 * for the accuracy, completeness, or usefulness of any information, apparatus,
 * product, or process disclosed, or represents that its use would not infringe
 * privately-owned rights. Reference herein to any specific commercial products,
 * process, or service by trade name, trademark, manufacturer or otherwise does
 * not necessarily constitute or imply its endorsement, recommendation, or
 * favoring by the United States Government or Lawrence Livermore National
 * Security, LLC. The views and opinions of authors expressed herein do not
 * necessarily state or reflect those of the United States Government or
 * Lawrence Livermore National Security, LLC, and shall not be used for
 * advertising or product endorsement purposes.
 *
 * NOTIFICATION OF COMMERCIAL USE
 *
 * Commercialization of this product is prohibited without notifying the
 * Department of Energy (DOE) or Lawrence Livermore National Security.
 */

#ifndef KRIPKE_ARCH_SOURCE
#define KRIPKE_ARCH_SOURCE

#include <Kripke.h>
#include <Kripke/VarTypes.h>

namespace Kripke {
namespace Arch {

  using Policy_Source_Seq =
    RAJA::nested::Policy<
      RAJA::nested::TypedFor<0, RAJA::loop_exec, Group>,
      RAJA::nested::TypedFor<1, RAJA::loop_exec, MixElem>
    >;

  using Policy_Source_Omp =
    RAJA::nested::Policy<
      RAJA::nested::TypedFor<0, RAJA::omp_parallel_for_exec, Group>,
      RAJA::nested::TypedFor<1, RAJA::loop_exec, MixElem>
    >;

  using Policy_Source_Omp2 =
    RAJA::nested::Policy<
      RAJA::nested::TypedFor<0, RAJA::loop_exec, Group>,
      RAJA::nested::TypedFor<1, RAJA::omp_parallel_for_exec, MixElem>
    >;

  template <typename BODY>
  void SourcePolicySwitcher(int choice, BODY body) {
    switch (choice) {
      case 1: body(Policy_Source_Omp{}); break;
      case 2: body(Policy_Source_Omp2{}); break;
      case 0: 
      default: body(Policy_Source_Seq{}); break;
    }
  }
}
}

#endif
