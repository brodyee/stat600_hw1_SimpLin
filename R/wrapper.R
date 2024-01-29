# Author: Brody Erlandson
# Last Modified: 1/28/2024
#
# This file is a wrapper for the SimpLinCpp function. It error checks and 
# formats the output of SimpLinCpp. 



SimpLinR <- function(x, y) {
  ############ Error checking ############
  # Check that x and y are numeric vectors
  if (!is.numeric(x) | !is.numeric(y)) {
    stop("x and y must be numeric vectors")
  } else if (length(x) != length(y)) { # Check that x and y are the same length
    stop("x and y must be the same length")
  }
  
  ############ Data formatting ############
  X <- cbind(rep(1, length(x)), x) # Create the design matrix

  ############ Call SimpLinCpp ############
  output <- SimpLinCpp(X, y) # Call SimpLinCpp

  return(output)
}