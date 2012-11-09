# 1 "sparc/math/umul.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "sparc/math/umul.S"
# 23 "sparc/math/umul.S"
 .globl .umul
 .globl _Umul
.umul:
_Umul:
 or %o0, %o1, %o4
 mov %o0, %y ! multiplier -> Y

 andncc %o4, 0xfff, %g0 ! test bits 12..31 of *both* args
 be Lmul_shortway ! if zero, can do it the short way
  andcc %g0, %g0, %o4 ! zero the partial product and clear N and V




 mulscc %o4, %o1, %o4 ! 1
 mulscc %o4, %o1, %o4 ! 2
 mulscc %o4, %o1, %o4 ! 3
 mulscc %o4, %o1, %o4 ! 4
 mulscc %o4, %o1, %o4 ! 5
 mulscc %o4, %o1, %o4 ! 6
 mulscc %o4, %o1, %o4 ! 7
 mulscc %o4, %o1, %o4 ! 8
 mulscc %o4, %o1, %o4 ! 9
 mulscc %o4, %o1, %o4 ! 10
 mulscc %o4, %o1, %o4 ! 11
 mulscc %o4, %o1, %o4 ! 12
 mulscc %o4, %o1, %o4 ! 13
 mulscc %o4, %o1, %o4 ! 14
 mulscc %o4, %o1, %o4 ! 15
 mulscc %o4, %o1, %o4 ! 16
 mulscc %o4, %o1, %o4 ! 17
 mulscc %o4, %o1, %o4 ! 18
 mulscc %o4, %o1, %o4 ! 19
 mulscc %o4, %o1, %o4 ! 20
 mulscc %o4, %o1, %o4 ! 21
 mulscc %o4, %o1, %o4 ! 22
 mulscc %o4, %o1, %o4 ! 23
 mulscc %o4, %o1, %o4 ! 24
 mulscc %o4, %o1, %o4 ! 25
 mulscc %o4, %o1, %o4 ! 26
 mulscc %o4, %o1, %o4 ! 27
 mulscc %o4, %o1, %o4 ! 28
 mulscc %o4, %o1, %o4 ! 29
 mulscc %o4, %o1, %o4 ! 30
 mulscc %o4, %o1, %o4 ! 31
 mulscc %o4, %o1, %o4 ! 32
 mulscc %o4, %g0, %o4 ! final shift
# 117 "sparc/math/umul.S"
 sra %o1, 31, %o2 ! make mask from sign bit
 and %o0, %o2, %o2 ! %o2 = 0 or %o0, depending on sign of %o1
 rd %y, %o0 ! get lower half of product
 retl
  addcc %o4, %o2, %o1 ! add compensation and put upper half in place


Lmul_shortway:






 mulscc %o4, %o1, %o4 ! 1
 mulscc %o4, %o1, %o4 ! 2
 mulscc %o4, %o1, %o4 ! 3
 mulscc %o4, %o1, %o4 ! 4
 mulscc %o4, %o1, %o4 ! 5
 mulscc %o4, %o1, %o4 ! 6
 mulscc %o4, %o1, %o4 ! 7
 mulscc %o4, %o1, %o4 ! 8
 mulscc %o4, %o1, %o4 ! 9
 mulscc %o4, %o1, %o4 ! 10
 mulscc %o4, %o1, %o4 ! 11
 mulscc %o4, %o1, %o4 ! 12
 mulscc %o4, %g0, %o4 ! final shift
# 159 "sparc/math/umul.S"
 rd %y, %o5
 sll %o4, 12, %o0 ! shift middle bits left 12
 srl %o5, 20, %o5 ! shift low bits right 20
 or %o5, %o0, %o0
 retl
  addcc %g0, %g0, %o1 ! %o1 = zero, and set Z

 .globl .umul_patch
.umul_patch:
 umul %o0, %o1, %o0
 retl
  rd %y, %o1
 nop
