# 1 "sparc/math/rem.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "sparc/math/rem.S"
# 45 "sparc/math/rem.S"


 .globl .rem
 .globl _Rem
.rem:
_Rem:
 ! compute sign of result; if neither is negative, no problem
 orcc %o1, %o0, %g0 ! either negative?
 bge 2f ! no, go do the divide
  mov %o0, %g2 ! compute sign in any case

 tst %o1
 bge 1f
  tst %o0
 ! %o1 is definitely negative; %o0 might also be negative
 bge 2f ! if %o0 not negative...
  sub %g0, %o1, %o1 ! in any case, make %o1 nonneg
1: ! %o0 is negative, %o1 is nonnegative
 sub %g0, %o0, %o0 ! make %o0 nonnegative
2:

 ! Ready to divide. Compute size of quotient; scale comparand.
 orcc %o1, %g0, %o5
 bne 1f
  mov %o0, %o3

  ! Divide by zero trap. If it returns, return 0 (about as
  ! wrong as possible, but that is what SunOS does...).
  ta ST_DIV0
  retl
   clr %o0

1:
 cmp %o3, %o5 ! if %o1 exceeds %o0, done
 blu Lgot_result ! (and algorithm fails otherwise)
  clr %o2

 sethi %hi(1 << (32 - 4 - 1)), %g1

 cmp %o3, %g1
 blu Lnot_really_big
  clr %o4

 ! Here the dividend is >= 2**(31-N) or so. We must be careful here,
 ! as our usual N-at-a-shot divide step will cause overflow and havoc.
 ! The number of bits in the result here is N*ITER+SC, where SC <= N.
 ! Compute ITER in an unorthodox manner: know we need to shift V into
 ! the top decade: so do not even bother to compare to R.
 1:
  cmp %o5, %g1
  bgeu 3f
   mov 1, %g7

  sll %o5, 4, %o5

  b 1b
   add %o4, 1, %o4

 ! Now compute %g7.
 2:
  addcc %o5, %o5, %o5

  bcc Lnot_too_big
   add %g7, 1, %g7

  ! We get here if the %o1 overflowed while shifting.
  ! This means that %o3 has the high-order bit set.
  ! Restore %o5 and subtract from %o3.
  sll %g1, 4, %g1 ! high order bit
  srl %o5, 1, %o5 ! rest of %o5
  add %o5, %g1, %o5

  b Ldo_single_div
   sub %g7, 1, %g7

 Lnot_too_big:
 3:
  cmp %o5, %o3
  blu 2b
   nop

  be Ldo_single_div
   nop


 ! %o5 > %o3: went too far: back up 1 step
 ! srl %o5, 1, %o5
 ! dec %g7
 ! do single-bit divide steps
 !
 ! We have to be careful here. We know that %o3 >= %o5, so we can do the
 ! first divide step without thinking. BUT, the others are conditional,
 ! and are only done if %o3 >= 0. Because both %o3 and %o5 may have the high-
 ! order bit set in the first step, just falling into the regular
 ! division loop will mess up the first time around.
 ! So we unroll slightly...
 Ldo_single_div:
  subcc %g7, 1, %g7
  bl Lend_regular_divide
   nop

  sub %o3, %o5, %o3
  mov 1, %o2

  b Lend_single_divloop
   nop
 Lsingle_divloop:
  sll %o2, 1, %o2

  bl 1f
   srl %o5, 1, %o5
  ! %o3 >= 0
  sub %o3, %o5, %o3

  b 2f
   add %o2, 1, %o2
 1: ! %o3 < 0
  add %o3, %o5, %o3
  sub %o2, 1, %o2
 2:
 Lend_single_divloop:
  subcc %g7, 1, %g7
  bge Lsingle_divloop
   tst %o3

  b,a Lend_regular_divide

Lnot_really_big:
1:
 sll %o5, 4, %o5
 cmp %o5, %o3
 bleu 1b
  addcc %o4, 1, %o4
 be Lgot_result
  sub %o4, 1, %o4

 tst %o3 ! set up for initial iteration
Ldivloop:
 sll %o2, 4, %o2
  ! depth 1, accumulated bits 0
 bl L.1.16
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
   ! depth 2, accumulated bits 1
 bl L.2.17
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
   ! depth 3, accumulated bits 3
 bl L.3.19
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
   ! depth 4, accumulated bits 7
 bl L.4.23
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3

 b 9f
  add %o2, (7*2+1), %o2

L.4.23:
 ! remainder is negative
 addcc %o3,%o5,%o3
 b 9f
  add %o2, (7*2-1), %o2

L.3.19:
 ! remainder is negative
 addcc %o3,%o5,%o3
   ! depth 4, accumulated bits 5
 bl L.4.21
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
 b 9f
  add %o2, (5*2+1), %o2

L.4.21:
 ! remainder is negative
 addcc %o3,%o5,%o3
 b 9f
  add %o2, (5*2-1), %o2

L.2.17:
 ! remainder is negative
 addcc %o3,%o5,%o3
   ! depth 3, accumulated bits 1
 bl L.3.17
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
   ! depth 4, accumulated bits 3
 bl L.4.19
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
 b 9f
  add %o2, (3*2+1), %o2

L.4.19:
 ! remainder is negative
 addcc %o3,%o5,%o3
 b 9f
  add %o2, (3*2-1), %o2

L.3.17:
 ! remainder is negative
 addcc %o3,%o5,%o3
   ! depth 4, accumulated bits 1
 bl L.4.17
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
 b 9f
  add %o2, (1*2+1), %o2

L.4.17:
 ! remainder is negative
 addcc %o3,%o5,%o3
 b 9f
  add %o2, (1*2-1), %o2

L.1.16:
 ! remainder is negative
 addcc %o3,%o5,%o3
   ! depth 2, accumulated bits -1
 bl L.2.15
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
   ! depth 3, accumulated bits -1
 bl L.3.15
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
   ! depth 4, accumulated bits -1
 bl L.4.15
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
 b 9f
  add %o2, (-1*2+1), %o2

L.4.15:
 ! remainder is negative
 addcc %o3,%o5,%o3
 b 9f
  add %o2, (-1*2-1), %o2

L.3.15:
 ! remainder is negative
 addcc %o3,%o5,%o3
   ! depth 4, accumulated bits -3
 bl L.4.13
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
 b 9f
  add %o2, (-3*2+1), %o2

L.4.13:
 ! remainder is negative
 addcc %o3,%o5,%o3
 b 9f
  add %o2, (-3*2-1), %o2

L.2.15:
 ! remainder is negative
 addcc %o3,%o5,%o3
   ! depth 3, accumulated bits -3
 bl L.3.13
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
   ! depth 4, accumulated bits -5
 bl L.4.11
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
 b 9f
  add %o2, (-5*2+1), %o2

L.4.11:
 ! remainder is negative
 addcc %o3,%o5,%o3
 b 9f
  add %o2, (-5*2-1), %o2


L.3.13:
 ! remainder is negative
 addcc %o3,%o5,%o3
   ! depth 4, accumulated bits -7
 bl L.4.9
  srl %o5,1,%o5
 ! remainder is positive
 subcc %o3,%o5,%o3
 b 9f
  add %o2, (-7*2+1), %o2

L.4.9:
 ! remainder is negative
 addcc %o3,%o5,%o3
 b 9f
  add %o2, (-7*2-1), %o2

 9:
Lend_regular_divide:
 subcc %o4, 1, %o4
 bge Ldivloop
  tst %o3

 bl,a Lgot_result
 ! non-restoring fixup here (one instruction only!)
 add %o3, %o1, %o3

Lgot_result:
 ! check to see if answer should be < 0
 tst %g2
 bl,a 1f
  sub %g0, %o3, %o3
1:
 retl
  mov %o3, %o0

 .globl .rem_patch
.rem_patch:
 sra %o0, 0x1f, %o4
 wr %o4, 0x0, %y
 nop
 nop
 nop
 sdivcc %o0, %o1, %o2
 bvs,a 1f
  xnor %o2, %g0, %o2
1: smul %o2, %o1, %o2
 retl
  sub %o0, %o2, %o0
 nop