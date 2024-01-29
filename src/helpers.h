/*
Author: Brody Erlandson
Last Modified: 1/28/2024

This file contains the Rcpp functions for the simpLin Package.
*/

// [[Rcpp::plugins(cpp17)]]

#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;
using namespace arma;

arma::vec getPredictions(const arma::mat& X, const arma::vec& beta) {
  arma::vec yhat = X * beta;

  return yhat;
}

arma::vec getFit(const arma::mat& X, const arma::vec& y) {
  arma::vec beta = arma::inv(X.t() * X) * X.t() * y;

  return beta;
}

arma::mat getStdErr(const arma::vec& residuals, const arma::mat& X) {
  arma::mat sigHat = arma::var(residuals) * arma::inv(X.t() * X);

  return sigHat;
}

arma::mat getConfInt(const arma::vec& beta, const arma::mat& stdErr,
                     const double& alpha, const double& n) {
  const int NUM_COEF = beta.n_elem;
  arma::mat confInt = arma::zeros(NUM_COEF, 2);

  for (int i = 0; i < NUM_COEF; i++) {
    confInt(i, 0) = beta(i) 
                    - R::qt(1 - alpha / 2, n - beta.n_elem, true, false) 
                      * stdErr(i, i);
    confInt(i, 1) = beta(i) 
                    + R::qt(1 - alpha / 2, n - beta.n_elem, true, false) 
                      * stdErr(i, i);
  }

  return confInt;
}