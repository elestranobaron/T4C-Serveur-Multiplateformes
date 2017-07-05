// Set of general definitions.

#ifndef DEFINE_GEN_REF
#define DEFINE_GEN_REF


#define PROHIBIT_ASSIGNMENT( classname ) enum{};classname( classname &sFoo ){};classname &operator = ( classname &sFoo ){ return sFoo; };


#endif
