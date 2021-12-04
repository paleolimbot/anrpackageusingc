
#' A Wrapper for a 'C' Function
#'
#' @param input An input value to the C function
#'
#' @return The result of the C function.
#' @export
#'
#' @examples
#' my_function("some input")
#'
my_function <- function(input) {
  .Call(anrpackageusingc_c_my_function, input)
}
