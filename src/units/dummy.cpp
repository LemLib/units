// this file exists to force the PROS build script to produce a .a file
// otherwise units does not compile reliably on all platforms
// and the pros conductor will not let you create a template if there is
// no .a file

// a global, volatile variable in an anonymous namespace
// its put in an anonymous namespace to guarantee that there won't be any
// linker errors
// 10/10 codebase (i don't feel like PRing a fix to PROS, make is scary)
namespace {
volatile char dummy_var;
}