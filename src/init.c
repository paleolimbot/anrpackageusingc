#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

SEXP anrpackageusingc_c_my_function(SEXP input_sexp);

static const R_CallMethodDef CallEntries[] = {
  {"anrpackageusingc_c_my_function", (DL_FUNC) &anrpackageusingc_c_my_function, 1},
  {NULL, NULL, 0}
};

void R_init_anrpackageusingc(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
