/*
Author: Brody Erlandson
Last Modified: 1/28/2024

This file contains the Rcpp functions for the simpLin Package.
*/

// [[Rcpp::plugins(cpp17)]]

#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
#include <helpers.h>

using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]]
Rcpp::List SimpLinCpp(arma::mat X, arma::vec y) {
  arma::vec beta = getFit(X, y);
  arma::vec yhat = getPredictions(X, beta);
  arma::vec residuals = y - yhat;
  arma::mat stdErr = getStdErr(residuals, X);
  arma::mat confInt = getConfInt(beta, stdErr, 0.05, X.n_rows);
  
  return List::create(Named("beta") = beta,
                      Named("stdErr") = stdErr,
                      Named("confInt") = confInt,
                      Named("residuals") = residuals,
                      Named("yhat") = yhat);
}