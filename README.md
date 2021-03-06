
<!-- README.md is generated from README.Rmd. Please edit that file -->

# anrpackageusingc

<!-- badges: start -->
<!-- badges: end -->

The goal of anrpackageusingc is to demonstrate the structure of calling
a C function in a package. For a guide on actually writing C code using
the R API, see the [appropriate chapter of the R Packages
book](https://r-pkgs.org/src.html#clang), the [appropriate chapter of
Avanced R](http://adv-r.had.co.nz/C-interface.html) and the
[r-internals](https://github.com/hadley/r-internals) collection of
unofficial R API documentation.

## Installation

You can install the development version from GitHub with:

``` r
# install.packages("remotes")
remotes::install_github("paleolimbot/anrpackageusingc")
```

This package is designed so that you can fork, clone, and modify the C
code.

## Example

This package contains one function that calls a C function.

``` r
library(anrpackageusingc)
my_function("an input object")
#> NULL
```

The R function `my_function()` lives in `R/my-function.R`:

``` r
my_function <- function(input) {
  .Call(anrpackageusingc_c_my_function, input)
}
```

The C function `anrpackageusingc_c_my_function()` lives in
`src/my-function.c`. I use the prefix `anrpackageusingc_c_...()` when
I’m declaring a function that will get registered and called from R
because I have a tool that generates `src/init.c` using a regex and
because I read something a long time ago that suggested that exported C
functions might need unique names (I don’t know if this is still true).
You can call the functions anything you want but it’s helpful if you
have a naming convention for all the functions of this type in your
package.

``` c
SEXP anrpackageusingc_c_my_function(SEXP input_sexp) {
  return R_NilValue;
}
```

It’s registered in `src/init.c`. The `1` at the end of the registration
line is because the function accepts one argument; the `NULL, NULL, 0`
is to signify the end of the array (kind of like how `\0` signifies the
end of a null-terminated string).

``` c
SEXP anrpackageusingc_c_my_function(SEXP input_sexp);

static const R_CallMethodDef CallEntries[] = {
  {"anrpackageusingc_c_my_function", (DL_FUNC) &anrpackageusingc_c_my_function, 1},
  {NULL, NULL, 0}
};

void R_init_anrpackageusingc(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
```

If you want to add a function, you’ll have to copy the definition and a
line to `CallEntries`. The function can live in any `.c` file of your
choosing.

Finally, we need to add the `useDynLib()` line in the `NAMESPACE`. I use
the automatically populated roxygen line that happens when you call
`usethis::use_package_doc()` and `usethis::use_c("some-c-filename")` for
this.

``` r
#' @useDynLib anrpackageusingc, .registration = TRUE
```

There are some variations on these components but this should get you
started. From scratch, I created this package using a bunch of usethis
helpers:

``` r
create_package("anrpackageusingc")
# modify Title and Description in DESCRIPTION file
use_package_doc()
use_c("my-function")
# write skeleton of anrpackageusingc_c_my_function() that returns R_NilValue
use_c("init.c")
# copy boilerplate from a previous package using C like this one
use_r("my-function")
# write wrapper using .Call()
use_test("my-function")
# write a test that calls my_function()
use_git()
use_github()
```

## Exercises

1.  Modify the body of `anrpackageusingc_c_my_function()` to (1) print
    something using `Rprintf()` and (2) return an R object. The easiest
    R objects to create are strings (`Rf_mkString("some text")`),
    integers (`Rf_ScalarInteger(1234)`), and doubles
    (`Rf_ScalarReal(1234)`).

2.  Add a new C function called `anrpackageusingc_c_my_new_function()`
    that accepts two parameters (`SEXP item1, SEXP item2`) and returns
    the first one. Add the function to `init.c` and create an R wrapper
    called `my_new_function()`.

3.  Add a new C function in a new file that adds 2 to a numeric vector
    (you can use the example from the “Accessing vector data” section of
    the [appropriate chapter of Avanced
    R](http://adv-r.had.co.nz/C-interface.html)). Make sure you can call
    it from R!
