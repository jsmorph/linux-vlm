/************************************************************************
 * WARNING: DO NOT EDIT THIS FILE.  THIS FILE WAS AUTOMATICALLY GENERATED
 * FROM ../alpha-emulator/ifunjosh.as. ANY CHANGES MADE TO THIS FILE WILL BE LOST
 ************************************************************************/

  /* 'AI' instructions. */
/* start DoDereference */

  /* Halfword operand from stack instruction - DoDereference */

dodereference:
  if (_trace) printf("dodereference:\n");
  /* arg2 has the preloaded 8 bit operand. */
#ifdef TRACING
#endif

DoDereferenceIM:
  if (_trace) printf("DoDereferenceIM:\n");
  /* This sequence only sucks a moderate amount */
  /* sign extend the byte argument. */
  arg2 = arg2 << 56;

g8930:
  if (_trace) printf("g8930:\n");
  /* Rest of sign extension */
  arg2 = (s64)arg2 >> 56;
  *(u32 *)&processor->immediate_arg = arg2;
  arg1 = *(u64 *)&(processor->immediate_arg);
  goto begindodereference;
#ifdef TRACING
#endif

DoDereferenceSP:
  if (_trace) printf("DoDereferenceSP:\n");
  /* Assume SP mode */
  arg1 = arg5;
  /* SP-pop mode */
  if (arg2 == 0)
    arg1 = iSP;
  /* Adjust SP if SP-pop mode */
  if (arg2 == 0)
    iSP = arg4;
#ifdef TRACING
  goto headdodereference;
#endif

DoDereferenceLP:
  if (_trace) printf("DoDereferenceLP:\n");
#ifdef TRACING
  goto headdodereference;
#endif

DoDereferenceFP:
  if (_trace) printf("DoDereferenceFP:\n");

headdodereference:
  if (_trace) printf("headdodereference:\n");
  /* Compute operand address */
  arg1 = (arg2 * 8) + arg1;
  /* Get the operand */
  arg1 = *(u64 *)arg1;

begindodereference:
  if (_trace) printf("begindodereference:\n");
  /* arg1 has the operand, sign extended if immediate. */
  arg2 = arg1 >> 32;
  arg1 = (u32)arg1;
  /* Strip off any CDR code bits. */
  t1 = arg2 & 63;
  t2 = (t1 == Type_OneQForward) ? 1 : 0;

g8925:
  if (_trace) printf("g8925:\n");
  if (t2 != 0)
    goto g8921;
  t2 = (t1 == Type_ElementForward) ? 1 : 0;

g8926:
  if (_trace) printf("g8926:\n");
  if (t2 != 0)
    goto g8921;
  t2 = (t1 == Type_HeaderForward) ? 1 : 0;

g8927:
  if (_trace) printf("g8927:\n");
  if (t2 != 0)
    goto g8921;
  t2 = (t1 == Type_ExternalValueCellPointer) ? 1 : 0;

g8928:
  if (_trace) printf("g8928:\n");
  if (t2 == 0)
    goto g8908;

g8921:
  if (_trace) printf("g8921:\n");
  /* Here if argument (TypeOneQForward TypeElementForward TypeHeaderForward TypeExternalValueCellPointer) */
  /* Memory Read Internal */

g8909:
  /* Base of stack cache */
  t5 = *(u64 *)&(processor->stackcachebasevma);
  t7 = arg1 + ivory;
  t6 = *(s32 *)&processor->scovlimit;
  t3 = (t7 * 4);
  t4 = LDQ_U(t7);
  /* Stack cache offset */
  t5 = arg1 - t5;
  t8 = *(u64 *)&(processor->dataread_mask);
  /* In range? */
  t6 = ((u64)t5 < (u64)t6) ? 1 : 0;
  t3 = *(s32 *)t3;
  t4 = (u8)(t4 >> ((t7&7)*8));
  if (t6 != 0)
    goto g8911;

g8910:
  t7 = zero + 240;
  t8 = t8 >> (t4 & 63);
  t7 = t7 >> (t4 & 63);
  if (t8 & 1)
    goto g8913;

g8920:
  /* set CDR-NEXT */
  t5 = t4 & 63;
  *(u32 *)(iSP + 8) = t3;
  /* write the stack cache */
  *(u32 *)(iSP + 12) = t5;
  iSP = iSP + 8;
  goto NEXTINSTRUCTION;

g8908:
  if (_trace) printf("g8908:\n");
  t2 = (t1 == Type_LogicVariable) ? 1 : 0;

g8929:
  if (_trace) printf("g8929:\n");
  if (t2 == 0)
    goto g8922;
  /* Here if argument TypeLogicVariable */
  t5 = Type_ExternalValueCellPointer;
  *(u32 *)(iSP + 8) = arg1;
  /* write the stack cache */
  *(u32 *)(iSP + 12) = t5;
  iSP = iSP + 8;
  goto NEXTINSTRUCTION;

g8922:
  if (_trace) printf("g8922:\n");
  /* Here for all other cases */
  /* set CDR-NEXT */
  t5 = arg2 & 63;
  *(u32 *)(iSP + 8) = arg1;
  /* write the stack cache */
  *(u32 *)(iSP + 12) = t5;
  iSP = iSP + 8;
  goto NEXTINSTRUCTION;

g8907:
  if (_trace) printf("g8907:\n");

g8911:
  if (_trace) printf("g8911:\n");
  t6 = *(u64 *)&(processor->stackcachedata);
  /* reconstruct SCA */
  t5 = (t5 * 8) + t6;
  t3 = *(s32 *)t5;
  /* Read from stack cache */
  t4 = *(s32 *)(t5 + 4);
  goto g8910;

g8913:
  if (_trace) printf("g8913:\n");
  if ((t7 & 1) == 0)
    goto g8912;
  /* Do the indirect thing */
  arg1 = (u32)t3;
  goto g8909;

g8912:
  if (_trace) printf("g8912:\n");
  /* Load the memory action table for cycle */
  t8 = *(u64 *)&(processor->dataread);
  /* TagType. */
  /* Discard the CDR code */
  t7 = t4 & 63;
  /* stash the VMA for the (likely) trap */
  *(u64 *)&processor->vma = arg1;
  /* Adjust for a longword load */
  t7 = (t7 * 4) + t8;
  /* Get the memory action */
  t8 = *(s32 *)t7;

g8917:
  if (_trace) printf("g8917:\n");
  t7 = t8 & MemoryActionTransform;
  if (t7 == 0)
    goto g8916;
  t4 = t4 & ~63L;
  t4 = t4 | Type_ExternalValueCellPointer;
  goto g8920;
#ifndef MINIMA

g8916:
#endif
#ifdef MINIMA

g8916:
  if (_trace) printf("g8916:\n");
  t7 = t8 & MemoryActionBinding;
  t6 = *(u64 *)&(processor->dbcmask);
  if (t7 == 0)
    goto g8915;
  t5 = arg1 << 1;
  t7 = *(u64 *)&(processor->dbcbase);
  /* Hash index */
  t5 = t5 & t6;
  t6 = 1;
  t6 = t6 << (ivorymemorydata & 63);
  t5 = (s32)t5 + (s32)t7;
  /* Clear sign-extension */
  t5 = (u32)t5;
  t6 = (t5 * 4) + t6;
  /* Fetch the key */
  t5 = *(s32 *)t6;
  /* Fetch value */
  t3 = *(s32 *)(t6 + 4);
  /* Compare */
  t7 = (s32)arg1 - (s32)t5;
  /* Trap on miss */
  if (t7 != 0)
    goto g8919;
  /* Extract the pointer, and indirect */
  arg1 = (u32)t3;
  goto g8909;

g8919:
  if (_trace) printf("g8919:\n");
  goto dbcachemisstrap;
#endif

g8915:
  /* Perform memory action */
  arg1 = t8;
  arg2 = 0;
  goto performmemoryaction;

/* end DoDereference */
  /* End of Halfword operand from stack instruction - DoDereference */
/* start DoUnify */

  /* Halfword operand from stack instruction - DoUnify */

dounify:
  if (_trace) printf("dounify:\n");
  /* arg2 has the preloaded 8 bit operand. */
#ifdef TRACING
#endif

DoUnifyIM:
  if (_trace) printf("DoUnifyIM:\n");
  /* This sequence only sucks a moderate amount */
  /* sign extend the byte argument. */
  arg2 = arg2 << 56;

g8931:
  if (_trace) printf("g8931:\n");
  /* Rest of sign extension */
  arg2 = (s64)arg2 >> 56;
  *(u32 *)&processor->immediate_arg = arg2;
  arg1 = *(u64 *)&(processor->immediate_arg);
  goto begindounify;
#ifdef TRACING
#endif

DoUnifySP:
  if (_trace) printf("DoUnifySP:\n");
  /* Assume SP mode */
  arg1 = arg5;
  /* SP-pop mode */
  if (arg2 == 0)
    arg1 = iSP;
  /* Adjust SP if SP-pop mode */
  if (arg2 == 0)
    iSP = arg4;
#ifdef TRACING
  goto headdounify;
#endif

DoUnifyLP:
  if (_trace) printf("DoUnifyLP:\n");
#ifdef TRACING
  goto headdounify;
#endif

DoUnifyFP:
  if (_trace) printf("DoUnifyFP:\n");

headdounify:
  if (_trace) printf("headdounify:\n");
  /* Compute operand address */
  arg1 = (arg2 * 8) + arg1;
  /* Get the operand */
  arg1 = *(u64 *)arg1;

begindounify:
  if (_trace) printf("begindounify:\n");
  /* arg1 has the operand, sign extended if immediate. */
  /* This instruction has not been written yet. */
  arg5 = 0;
  arg2 = 38;
  goto illegaloperand;
  goto NEXTINSTRUCTION;

/* end DoUnify */
  /* End of Halfword operand from stack instruction - DoUnify */
/* start DoPushLocalLogicVariables */

  /* Halfword operand from stack instruction - DoPushLocalLogicVariables */
  /* arg2 has the preloaded 8 bit operand. */

dopushlocallogicvariables:
  if (_trace) printf("dopushlocallogicvariables:\n");
#ifdef TRACING
#endif

DoPushLocalLogicVariablesIM:
  if (_trace) printf("DoPushLocalLogicVariablesIM:\n");
  /* This sequence is lukewarm */
  *(u32 *)&processor->immediate_arg = arg2;
  arg1 = *(u64 *)&(processor->immediate_arg);
  goto begindopushlocallogicvariables;
#ifdef TRACING
#endif

DoPushLocalLogicVariablesSP:
  if (_trace) printf("DoPushLocalLogicVariablesSP:\n");
  /* Assume SP mode */
  arg1 = arg5;
  /* SP-pop mode */
  if (arg2 == 0)
    arg1 = iSP;
  /* Adjust SP if SP-pop mode */
  if (arg2 == 0)
    iSP = arg4;
#ifdef TRACING
  goto headdopushlocallogicvariables;
#endif

DoPushLocalLogicVariablesLP:
  if (_trace) printf("DoPushLocalLogicVariablesLP:\n");
#ifdef TRACING
  goto headdopushlocallogicvariables;
#endif

DoPushLocalLogicVariablesFP:
  if (_trace) printf("DoPushLocalLogicVariablesFP:\n");

headdopushlocallogicvariables:
  if (_trace) printf("headdopushlocallogicvariables:\n");
  /* Compute operand address */
  arg1 = (arg2 * 8) + arg1;
  /* Get the operand */
  arg1 = *(u64 *)arg1;

begindopushlocallogicvariables:
  if (_trace) printf("begindopushlocallogicvariables:\n");
  /* arg1 has the operand, not sign extended if immediate. */
  arg6 = Type_LogicVariable;
  t1 = arg1 >> 32;
  arg2 = (u32)arg1;
  t2 = t1 - Type_Fixnum;
  /* Strip CDR code */
  t2 = t2 & 63;
  if (t2 != 0)
    goto pllvillop;
  /* Current stack cache limit (words) */
  t4 = *(s32 *)&processor->scovlimit;
  t1 = zero + 128;
  /* Alpha base of stack cache */
  t2 = *(u64 *)&(processor->stackcachedata);
  /* Account for what we're about to push */
  t1 = t1 + arg2;
  /* SCA of desired end of cache */
  t1 = (t1 * 8) + iSP;
  /* SCA of current end of cache */
  t2 = (t4 * 8) + t2;
  t4 = ((s64)t1 <= (s64)t2) ? 1 : 0;
  /* We're done if new SCA is within bounds */
  if (t4 == 0)
    goto stackcacheoverflowhandler;
  goto pllvloopend;

pllvlooptop:
  if (_trace) printf("pllvlooptop:\n");
  *(u32 *)(iSP + 8) = iSP;
  /* write the stack cache */
  *(u32 *)(iSP + 12) = arg6;
  iSP = iSP + 8;

pllvloopend:
  if (_trace) printf("pllvloopend:\n");
  arg2 = arg2 - 1;
  /* J. If iterations to go. */
  if ((s64)arg2 >= 0)
    goto pllvlooptop;
  goto NEXTINSTRUCTION;

pllvillop:
  if (_trace) printf("pllvillop:\n");
  arg5 = 0;
  arg2 = 63;
  goto illegaloperand;

/* end DoPushLocalLogicVariables */
  /* End of Halfword operand from stack instruction - DoPushLocalLogicVariables */
/* start DoPushGlobalLogicVariable */

  /* Halfword operand from stack instruction - DoPushGlobalLogicVariable */

dopushgloballogicvariable:
  if (_trace) printf("dopushgloballogicvariable:\n");
  /* arg2 has the preloaded 8 bit operand. */
#ifdef TRACING
#endif

DoPushGlobalLogicVariableIM:
  if (_trace) printf("DoPushGlobalLogicVariableIM:\n");
  /* This sequence only sucks a moderate amount */
  /* sign extend the byte argument. */
  arg2 = arg2 << 56;

g8948:
  if (_trace) printf("g8948:\n");
  /* Rest of sign extension */
  arg2 = (s64)arg2 >> 56;
  *(u32 *)&processor->immediate_arg = arg2;
  arg1 = *(u64 *)&(processor->immediate_arg);
  goto begindopushgloballogicvariable;
#ifdef TRACING
#endif

DoPushGlobalLogicVariableSP:
  if (_trace) printf("DoPushGlobalLogicVariableSP:\n");
  /* Assume SP mode */
  arg1 = arg5;
  /* SP-pop mode */
  if (arg2 == 0)
    arg1 = iSP;
  /* Adjust SP if SP-pop mode */
  if (arg2 == 0)
    iSP = arg4;
#ifdef TRACING
  goto headdopushgloballogicvariable;
#endif

DoPushGlobalLogicVariableLP:
  if (_trace) printf("DoPushGlobalLogicVariableLP:\n");
#ifdef TRACING
  goto headdopushgloballogicvariable;
#endif

DoPushGlobalLogicVariableFP:
  if (_trace) printf("DoPushGlobalLogicVariableFP:\n");

headdopushgloballogicvariable:
  if (_trace) printf("headdopushgloballogicvariable:\n");
  /* Compute operand address */
  arg1 = (arg2 * 8) + arg1;
  /* Get the operand */
  arg1 = *(u64 *)arg1;

begindopushgloballogicvariable:
  if (_trace) printf("begindopushgloballogicvariable:\n");
  /* arg1 has the operand, sign extended if immediate. */
  /* Get the structure stack pointer */
  t1 = *(s32 *)&processor->bar2;
  t3 = Type_ExternalValueCellPointer;
  *(u32 *)(iSP + 8) = t1;
  /* write the stack cache */
  *(u32 *)(iSP + 12) = t3;
  iSP = iSP + 8;
  /* Memory Read Internal */

g8933:
  /* Base of stack cache */
  t6 = *(u64 *)&(processor->stackcachebasevma);
  t8 = t1 + ivory;
  t7 = *(s32 *)&processor->scovlimit;
  t5 = (t8 * 4);
  t4 = LDQ_U(t8);
  /* Stack cache offset */
  t6 = t1 - t6;
  t9 = *(u64 *)&(processor->datawrite_mask);
  /* In range? */
  t7 = ((u64)t6 < (u64)t7) ? 1 : 0;
  t5 = *(s32 *)t5;
  t4 = (u8)(t4 >> ((t8&7)*8));
  if (t7 != 0)
    goto g8935;

g8934:
  t8 = zero + 240;
  t9 = t9 >> (t4 & 63);
  t8 = t8 >> (t4 & 63);
  if (t9 & 1)
    goto g8937;

g8943:
  /* Merge cdr-code */
  t5 = t3 & 63;
  t4 = t4 & 192;
  t4 = t4 | t5;
  t7 = *(u64 *)&(processor->stackcachebasevma);
  t6 = t1 + ivory;
  t9 = *(s32 *)&processor->scovlimit;
  t5 = (t6 * 4);
  t8 = LDQ_U(t6);
  /* Stack cache offset */
  t7 = t1 - t7;
  /* In range? */
  t9 = ((u64)t7 < (u64)t9) ? 1 : 0;
  t7 = (t4 & 0xff) << ((t6&7)*8);
  t8 = t8 & ~(0xffL << (t6&7)*8);

g8946:
  if (_trace) printf("g8946:\n");
  t8 = t8 | t7;
  STQ_U(t6, t8);
  *(u32 *)t5 = t1;
  /* J. if in cache */
  if (t9 != 0)
    goto g8945;

g8944:
  /* Increment the structure-stack-pointer */
  t2 = t1 + 1;
  /* Set the structure stack pointer */
  *(u32 *)&processor->bar2 = t2;
  goto NEXTINSTRUCTION;

g8945:
  if (_trace) printf("g8945:\n");
  t7 = *(u64 *)&(processor->stackcachebasevma);

g8947:
  if (_trace) printf("g8947:\n");
  t6 = *(u64 *)&(processor->stackcachedata);
  /* Stack cache offset */
  t7 = t1 - t7;
  /* reconstruct SCA */
  t6 = (t7 * 8) + t6;
  /* Store in stack */
  *(u32 *)t6 = t1;
  /* write the stack cache */
  *(u32 *)(t6 + 4) = t4;
  goto g8944;

g8935:
  if (_trace) printf("g8935:\n");
  t7 = *(u64 *)&(processor->stackcachedata);
  /* reconstruct SCA */
  t6 = (t6 * 8) + t7;
  t5 = *(s32 *)t6;
  /* Read from stack cache */
  t4 = *(s32 *)(t6 + 4);
  goto g8934;

g8937:
  if (_trace) printf("g8937:\n");
  if ((t8 & 1) == 0)
    goto g8936;
  /* Do the indirect thing */
  t1 = (u32)t5;
  goto g8933;

g8936:
  if (_trace) printf("g8936:\n");
  /* Load the memory action table for cycle */
  t9 = *(u64 *)&(processor->datawrite);
  /* TagType. */
  /* Discard the CDR code */
  t8 = t4 & 63;
  /* stash the VMA for the (likely) trap */
  *(u64 *)&processor->vma = t1;
  /* Adjust for a longword load */
  t8 = (t8 * 4) + t9;
  /* Get the memory action */
  t9 = *(s32 *)t8;
#ifndef MINIMA

g8940:
#endif
#ifdef MINIMA

g8940:
  if (_trace) printf("g8940:\n");
  t8 = t9 & MemoryActionBinding;
  t7 = *(u64 *)&(processor->dbcmask);
  if (t8 == 0)
    goto g8939;
  t6 = t1 << 1;
  t8 = *(u64 *)&(processor->dbcbase);
  /* Hash index */
  t6 = t6 & t7;
  t7 = 1;
  t7 = t7 << (ivorymemorydata & 63);
  t6 = (s32)t6 + (s32)t8;
  /* Clear sign-extension */
  t6 = (u32)t6;
  t7 = (t6 * 4) + t7;
  /* Fetch the key */
  t6 = *(s32 *)t7;
  /* Fetch value */
  t5 = *(s32 *)(t7 + 4);
  /* Compare */
  t8 = (s32)t1 - (s32)t6;
  /* Trap on miss */
  if (t8 != 0)
    goto g8942;
  /* Extract the pointer, and indirect */
  t1 = (u32)t5;
  goto g8933;

g8942:
  if (_trace) printf("g8942:\n");
  goto dbcachemisstrap;
#endif

g8939:
  /* Perform memory action */
  arg1 = t9;
  arg2 = 1;
  goto performmemoryaction;

/* end DoPushGlobalLogicVariable */
  /* End of Halfword operand from stack instruction - DoPushGlobalLogicVariable */
/* start DoLogicTailTest */

  /* Halfword operand from stack instruction - DoLogicTailTest */

dologictailtest:
  if (_trace) printf("dologictailtest:\n");
  /* arg2 has the preloaded 8 bit operand. */
#ifdef TRACING
#endif

DoLogicTailTestIM:
  if (_trace) printf("DoLogicTailTestIM:\n");
  /* This sequence only sucks a moderate amount */
  /* sign extend the byte argument. */
  arg2 = arg2 << 56;

g8958:
  if (_trace) printf("g8958:\n");
  /* Rest of sign extension */
  arg2 = (s64)arg2 >> 56;
  *(u32 *)&processor->immediate_arg = arg2;
  arg1 = *(u64 *)&(processor->immediate_arg);
  goto begindologictailtest;
#ifdef TRACING
#endif

DoLogicTailTestSP:
  if (_trace) printf("DoLogicTailTestSP:\n");
  /* Assume SP mode */
  arg1 = arg5;
  /* SP-pop mode */
  if (arg2 == 0)
    arg1 = iSP;
  /* Adjust SP if SP-pop mode */
  if (arg2 == 0)
    iSP = arg4;
#ifdef TRACING
  goto headdologictailtest;
#endif

DoLogicTailTestLP:
  if (_trace) printf("DoLogicTailTestLP:\n");
#ifdef TRACING
  goto headdologictailtest;
#endif

DoLogicTailTestFP:
  if (_trace) printf("DoLogicTailTestFP:\n");

headdologictailtest:
  if (_trace) printf("headdologictailtest:\n");
  /* Compute operand address */
  arg1 = (arg2 * 8) + arg1;
  /* Get the operand */
  arg1 = *(u64 *)arg1;

begindologictailtest:
  if (_trace) printf("begindologictailtest:\n");
  /* arg1 has the operand, sign extended if immediate. */
  arg2 = arg1 >> 32;
  /* Strip off any CDR code bits. */
  t1 = arg2 & 63;
  t2 = (t1 == Type_List) ? 1 : 0;

g8955:
  if (_trace) printf("g8955:\n");
  if (t2 == 0)
    goto g8950;
  /* Here if argument TypeList */
  t3 = *(u64 *)&(processor->niladdress);
  /* push the data */
  *(u64 *)(iSP + 8) = t3;
  iSP = iSP + 8;
  goto NEXTINSTRUCTION;

g8950:
  if (_trace) printf("g8950:\n");
  t2 = (t1 == Type_ExternalValueCellPointer) ? 1 : 0;

g8956:
  if (_trace) printf("g8956:\n");
  if (t2 == 0)
    goto g8951;
  /* Here if argument TypeExternalValueCellPointer */
  t3 = *(u64 *)&(processor->taddress);
  /* push the data */
  *(u64 *)(iSP + 8) = t3;
  iSP = iSP + 8;
  goto NEXTINSTRUCTION;

g8951:
  if (_trace) printf("g8951:\n");
  t2 = (t1 == Type_ListInstance) ? 1 : 0;

g8957:
  if (_trace) printf("g8957:\n");
  if (t2 == 0)
    goto g8952;
  /* Here if argument TypeListInstance */
  t3 = *(u64 *)&(processor->niladdress);
  /* push the data */
  *(u64 *)(iSP + 8) = t3;
  iSP = iSP + 8;
  goto NEXTINSTRUCTION;

g8952:
  if (_trace) printf("g8952:\n");
  /* Here for all other cases */
  /* arg6 = tag to dispatch on */
  arg6 = t2;
  /* arg3 = stackp */
  arg3 = 0;
  /* arg1 = instruction arity */
  arg1 = 1;
  /* arg4 = arithmeticp */
  arg4 = 0;
  goto exception;

g8949:
  if (_trace) printf("g8949:\n");

/* end DoLogicTailTest */
  /* End of Halfword operand from stack instruction - DoLogicTailTest */
  /* Fin. */



/* End of file automatically generated from ../alpha-emulator/ifunjosh.as */