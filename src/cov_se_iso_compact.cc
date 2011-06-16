/**************************************************************
 libgp - Gaussian Process library for Machine Learning
 Copyright (C) 2011 Universität Freiburg
 Author: Manuel Blum
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 ***************************************************************/

#include "cov_se_iso_compact.h"
#include <cmath>

namespace libgp
{
  
  CovSEisoCompact::CovSEisoCompact() {}
  
  CovSEisoCompact::~CovSEisoCompact() {}
  
  bool CovSEisoCompact::init(int n)
  {
    input_dim = n;
    param_dim = 2;
    loghyper.resize(param_dim);
    loghyper.setZero();
    nu = input_dim - input_dim%2 + 1;
    threshold = 0.8;
    return true;
  }
  
  double CovSEisoCompact::get(const Eigen::VectorXd &x1, const Eigen::VectorXd &x2)
  {
    double q = std::max(0.0, pow(1 - (x1-x2).norm()/threshold, 3));
    double z = ((x1-x2)/ell).squaredNorm();
    return q*sf2*exp(-0.5*z);
  }
  
  void CovSEisoCompact::grad(const Eigen::VectorXd &x1, const Eigen::VectorXd &x2, Eigen::VectorXd &grad)
  {
    grad << 0.0, 0.0;
  }
  
  void CovSEisoCompact::set_loghyper(const Eigen::VectorXd &p)
  {
    CovarianceFunction::set_loghyper(p);
    ell = exp(loghyper(0));
    sf2 = exp(2*loghyper(1));
  }
  
  std::string CovSEisoCompact::to_string()
  {
    return "CovSEisoCompact";
  }
  
  double CovSEisoCompact::get_threshold()
  {
    return threshold;
  }
  
  void CovSEisoCompact::set_threshold(double threshold)
  {
    this->threshold = threshold;
  }
}