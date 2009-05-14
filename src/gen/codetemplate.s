	.data
	.align 5
_codeTempList:
	.long	_jc0_HALT
	.space 20
	.long	_jc0_MOVA
	.long	_jc1_MOVA
	.long	_jc2_MOVA
	.space 12
	.long	_jc0_MOVN
	.long	_jc1_MOVN
	.long	_jc2_MOVN
	.space 12
	.long	_jc0_MOVO
	.long	_jc1_MOVO
	.long	_jc2_MOVO
	.space 12
	.long	_jc0_MOVX
	.long	_jc1_MOVX
	.long	_jc2_MOVX
	.long	_jc3_MOVX
	.space 8
	.long	_jc0_MOVDEF
	.long	_jc1_MOVDEF
	.long	_jc2_MOVDEF
	.space 12
	.long	_jc0_MOVSYS
	.long	_jc1_MOVSYS
	.long	_jc2_MOVSYS
	.space 12
	.long	_jc0_XMOVS
	.long	_jc1_XMOVS
	.long	_jc2_XMOVS
	.long	_jc3_XMOVS
	.space 8
	.long	_jc0_XMOVO
	.long	_jc1_XMOVO
	.long	_jc2_XMOVO
	.long	_jc3_XMOVO
	.space 8
	.long	_jc0_XMOVX
	.long	_jc1_XMOVX
	.long	_jc2_XMOVX
	.long	_jc3_XMOVX
	.long	_jc4_XMOVX
	.space 4
	.long	_jc0_XMOVDEF
	.long	_jc1_XMOVDEF
	.long	_jc2_XMOVDEF
	.long	_jc3_XMOVDEF
	.space 8
	.long	_jc0_XMOVSYS
	.long	_jc1_XMOVSYS
	.long	_jc2_XMOVSYS
	.long	_jc3_XMOVSYS
	.space 8
	.long	_jc0_SWAP
	.long	_jc1_SWAP
	.long	_jc2_SWAP
	.space 12
	.long	_jc0_PINIO
	.long	_jc1_PINIO
	.long	_jc2_PINIO
	.space 12
	.long	_jc0_SETESP
	.long	_jc1_SETESP
	.space 16
	.long	_jc0_CHECKESP
	.long	_jc1_CHECKESP
	.space 16
	.long	_jc0_RET
	.space 20
	.long	_jc0_RETN
	.long	_jc1_RETN
	.long	_jc2_RETN
	.space 12
	.long	_jc0_RETA
	.long	_jc1_RETA
	.long	_jc2_RETA
	.space 12
	.long	_jc0_RETO
	.long	_jc1_RETO
	.long	_jc2_RETO
	.space 12
	.long	_jc0_RETX
	.long	_jc1_RETX
	.long	_jc2_RETX
	.long	_jc3_RETX
	.space 8
	.long	_jc0_BOX
	.long	_jc1_BOX
	.long	_jc2_BOX
	.space 12
	.long	_jc0_BOXNC
	.long	_jc1_BOXNC
	.long	_jc2_BOXNC
	.space 12
	.long	_jc0_NNBOX
	.long	_jc1_NNBOX
	.long	_jc2_NNBOX
	.space 12
	.long	_jc0_NNBOXNC
	.long	_jc1_NNBOXNC
	.long	_jc2_NNBOXNC
	.space 12
	.long	_jc0_UNBOX
	.long	_jc1_UNBOX
	.space 16
	.long	_jc0_ISNULL
	.long	_jc1_ISNULL
	.space 16
	.long	_jc0_ISNULLX
	.long	_jc1_ISNULLX
	.long	_jc2_ISNULLX
	.space 12
	.long	_jc0_ISTYPE
	.long	_jc1_ISTYPE
	.long	_jc2_ISTYPE
	.space 12
	.long	_jc0_ISNNTYPE
	.long	_jc1_ISNNTYPE
	.long	_jc2_ISNNTYPE
	.space 12
	.long	_jc0_FCALL
	.long	_jc1_FCALL
	.long	_jc2_FCALL
	.long	_jc3_FCALL
	.long	_jc4_FCALL
	.space 4
	.long	_jc0_SCALL
	.long	_jc1_SCALL
	.long	_jc2_SCALL
	.long	_jc3_SCALL
	.space 8
	.long	_jc0_AINVOKE
	.long	_jc1_AINVOKE
	.long	_jc2_AINVOKE
	.long	_jc3_AINVOKE
	.space 8
	.long	_jc0_CALL
	.long	_jc1_CALL
	.long	_jc2_CALL
	.long	_jc3_CALL
	.space 8
	.long	_jc0_ACALL
	.long	_jc1_ACALL
	.long	_jc2_ACALL
	.long	_jc3_ACALL
	.space 8
	.long	_jc0_NEW
	.long	_jc1_NEW
	.long	_jc2_NEW
	.long	_jc3_NEW
	.long	_jc4_NEW
	.long	_jc5_NEW
	.long	_jc0_TOSTR
	.long	_jc1_TOSTR
	.long	_jc2_TOSTR
	.space 12
	.long	_jc0_TOSTRF
	.long	_jc1_TOSTRF
	.long	_jc2_TOSTRF
	.long	_jc3_TOSTRF
	.space 8
	.long	_jc0_SMAP
	.long	_jc1_SMAP
	.long	_jc2_SMAP
	.space 12
	.long	_jc0_SMAPNC
	.long	_jc1_SMAPNC
	.long	_jc2_SMAPNC
	.space 12
	.long	_jc0_MAP
	.long	_jc1_MAP
	.long	_jc2_MAP
	.space 12
	.long	_jc0_MAPNC
	.long	_jc1_MAPNC
	.long	_jc2_MAPNC
	.space 12
	.long	_jc0_AMAP
	.long	_jc1_AMAP
	.long	_jc2_AMAP
	.space 12
	.long	_jc0_NNMAP
	.long	_jc1_NNMAP
	.long	_jc2_NNMAP
	.space 12
	.long	_jc0_JMP
	.long	_jc1_JMP
	.space 16
	.long	_jc0_BJIFT
	.long	_jc1_BJIFT
	.long	_jc2_BJIFT
	.space 12
	.long	_jc0_BJIFF
	.long	_jc1_BJIFF
	.long	_jc2_BJIFF
	.space 12
	.long	_jc0_BJIFF_LOOP
	.long	_jc1_BJIFF_LOOP
	.long	_jc2_BJIFF_LOOP
	.space 12
	.long	_jc0_JIFNUL
	.long	_jc1_JIFNUL
	.long	_jc2_JIFNUL
	.space 12
	.long	_jc0_JIFNN
	.long	_jc1_JIFNN
	.long	_jc2_JIFNN
	.space 12
	.long	_jc0_NEXT
	.long	_jc1_NEXT
	.long	_jc2_NEXT
	.long	_jc3_NEXT
	.long	_jc4_NEXT
	.space 4
	.long	_jc0_INEXT
	.long	_jc1_INEXT
	.long	_jc2_INEXT
	.long	_jc3_INEXT
	.long	_jc4_INEXT
	.long	_jc5_INEXT
	.long	_jc0_MAPNEXT
	.long	_jc1_MAPNEXT
	.long	_jc2_MAPNEXT
	.long	_jc3_MAPNEXT
	.long	_jc4_MAPNEXT
	.long	_jc5_MAPNEXT
	.long	_jc0_SMAPNEXT
	.long	_jc1_SMAPNEXT
	.long	_jc2_SMAPNEXT
	.long	_jc3_SMAPNEXT
	.long	_jc4_SMAPNEXT
	.long	_jc5_SMAPNEXT
	.long	_jc0_TRY
	.long	_jc1_TRY
	.long	_jc2_TRY
	.space 12
	.long	_jc0_TRYEND
	.long	_jc1_TRYEND
	.space 16
	.long	_jc0_CATCH
	.long	_jc1_CATCH
	.long	_jc2_CATCH
	.long	_jc3_CATCH
	.long	_jc4_CATCH
	.space 4
	.long	_jc0_THROW
	.long	_jc1_THROW
	.space 16
	.long	_jc0_THROWS
	.long	_jc1_THROWS
	.space 16
	.long	_jc0_THROW_AGAIN
	.long	_jc1_THROW_AGAIN
	.space 16
	.long	_jc0_P
	.long	_jc1_P
	.long	_jc2_P
	.long	_jc3_P
	.space 8
	.long	_jc0_PMSG
	.long	_jc1_PMSG
	.long	_jc2_PMSG
	.space 12
	.long	_jc0_ICAST
	.long	_jc1_ICAST
	.space 16
	.long	_jc0_INCAST
	.long	_jc1_INCAST
	.space 16
	.long	_jc0_FCAST
	.long	_jc1_FCAST
	.space 16
	.long	_jc0_FNCAST
	.long	_jc1_FNCAST
	.space 16
	.long	_jc0_BNOT
	.long	_jc1_BNOT
	.long	_jc2_BNOT
	.space 12
	.long	_jc0_INEG
	.long	_jc1_INEG
	.long	_jc2_INEG
	.space 12
	.long	_jc0_IADD
	.long	_jc1_IADD
	.long	_jc2_IADD
	.long	_jc3_IADD
	.space 8
	.long	_jc0_IADDN
	.long	_jc1_IADDN
	.long	_jc2_IADDN
	.long	_jc3_IADDN
	.space 8
	.long	_jc0_ISUB
	.long	_jc1_ISUB
	.long	_jc2_ISUB
	.long	_jc3_ISUB
	.space 8
	.long	_jc0_ISUBN
	.long	_jc1_ISUBN
	.long	_jc2_ISUBN
	.long	_jc3_ISUBN
	.space 8
	.long	_jc0_IMUL
	.long	_jc1_IMUL
	.long	_jc2_IMUL
	.long	_jc3_IMUL
	.space 8
	.long	_jc0_IMULN
	.long	_jc1_IMULN
	.long	_jc2_IMULN
	.long	_jc3_IMULN
	.space 8
	.long	_jc0_IDIV
	.long	_jc1_IDIV
	.long	_jc2_IDIV
	.long	_jc3_IDIV
	.space 8
	.long	_jc0_IDIVN
	.long	_jc1_IDIVN
	.long	_jc2_IDIVN
	.long	_jc3_IDIVN
	.space 8
	.long	_jc0_IMOD
	.long	_jc1_IMOD
	.long	_jc2_IMOD
	.long	_jc3_IMOD
	.space 8
	.long	_jc0_IMODN
	.long	_jc1_IMODN
	.long	_jc2_IMODN
	.long	_jc3_IMODN
	.space 8
	.long	_jc0_IEQ
	.long	_jc1_IEQ
	.long	_jc2_IEQ
	.long	_jc3_IEQ
	.space 8
	.long	_jc0_IEQN
	.long	_jc1_IEQN
	.long	_jc2_IEQN
	.long	_jc3_IEQN
	.space 8
	.long	_jc0_INEQ
	.long	_jc1_INEQ
	.long	_jc2_INEQ
	.long	_jc3_INEQ
	.space 8
	.long	_jc0_INEQN
	.long	_jc1_INEQN
	.long	_jc2_INEQN
	.long	_jc3_INEQN
	.space 8
	.long	_jc0_ILT
	.long	_jc1_ILT
	.long	_jc2_ILT
	.long	_jc3_ILT
	.space 8
	.long	_jc0_ILTN
	.long	_jc1_ILTN
	.long	_jc2_ILTN
	.long	_jc3_ILTN
	.space 8
	.long	_jc0_ILTE
	.long	_jc1_ILTE
	.long	_jc2_ILTE
	.long	_jc3_ILTE
	.space 8
	.long	_jc0_ILTEN
	.long	_jc1_ILTEN
	.long	_jc2_ILTEN
	.long	_jc3_ILTEN
	.space 8
	.long	_jc0_IGT
	.long	_jc1_IGT
	.long	_jc2_IGT
	.long	_jc3_IGT
	.space 8
	.long	_jc0_IGTN
	.long	_jc1_IGTN
	.long	_jc2_IGTN
	.long	_jc3_IGTN
	.space 8
	.long	_jc0_IGTE
	.long	_jc1_IGTE
	.long	_jc2_IGTE
	.long	_jc3_IGTE
	.space 8
	.long	_jc0_IGTEN
	.long	_jc1_IGTEN
	.long	_jc2_IGTEN
	.long	_jc3_IGTEN
	.space 8
	.long	_jc0_FNEG
	.long	_jc1_FNEG
	.long	_jc2_FNEG
	.space 12
	.long	_jc0_FADD
	.long	_jc1_FADD
	.long	_jc2_FADD
	.long	_jc3_FADD
	.space 8
	.long	_jc0_FADDN
	.long	_jc1_FADDN
	.long	_jc2_FADDN
	.long	_jc3_FADDN
	.space 8
	.long	_jc0_FSUB
	.long	_jc1_FSUB
	.long	_jc2_FSUB
	.long	_jc3_FSUB
	.space 8
	.long	_jc0_FSUBN
	.long	_jc1_FSUBN
	.long	_jc2_FSUBN
	.long	_jc3_FSUBN
	.space 8
	.long	_jc0_FMUL
	.long	_jc1_FMUL
	.long	_jc2_FMUL
	.long	_jc3_FMUL
	.space 8
	.long	_jc0_FMULN
	.long	_jc1_FMULN
	.long	_jc2_FMULN
	.long	_jc3_FMULN
	.space 8
	.long	_jc0_FDIV
	.long	_jc1_FDIV
	.long	_jc2_FDIV
	.long	_jc3_FDIV
	.space 8
	.long	_jc0_FDIVN
	.long	_jc1_FDIVN
	.long	_jc2_FDIVN
	.long	_jc3_FDIVN
	.space 8
	.long	_jc0_FEQ
	.long	_jc1_FEQ
	.long	_jc2_FEQ
	.long	_jc3_FEQ
	.space 8
	.long	_jc0_FEQN
	.long	_jc1_FEQN
	.long	_jc2_FEQN
	.long	_jc3_FEQN
	.space 8
	.long	_jc0_FNEQ
	.long	_jc1_FNEQ
	.long	_jc2_FNEQ
	.long	_jc3_FNEQ
	.space 8
	.long	_jc0_FNEQN
	.long	_jc1_FNEQN
	.long	_jc2_FNEQN
	.long	_jc3_FNEQN
	.space 8
	.long	_jc0_FLT
	.long	_jc1_FLT
	.long	_jc2_FLT
	.long	_jc3_FLT
	.space 8
	.long	_jc0_FLTN
	.long	_jc1_FLTN
	.long	_jc2_FLTN
	.long	_jc3_FLTN
	.space 8
	.long	_jc0_FLTE
	.long	_jc1_FLTE
	.long	_jc2_FLTE
	.long	_jc3_FLTE
	.space 8
	.long	_jc0_FLTEN
	.long	_jc1_FLTEN
	.long	_jc2_FLTEN
	.long	_jc3_FLTEN
	.space 8
	.long	_jc0_FGT
	.long	_jc1_FGT
	.long	_jc2_FGT
	.long	_jc3_FGT
	.space 8
	.long	_jc0_FGTN
	.long	_jc1_FGTN
	.long	_jc2_FGTN
	.long	_jc3_FGTN
	.space 8
	.long	_jc0_FGTE
	.long	_jc1_FGTE
	.long	_jc2_FGTE
	.long	_jc3_FGTE
	.space 8
	.long	_jc0_FGTEN
	.long	_jc1_FGTEN
	.long	_jc2_FGTEN
	.long	_jc3_FGTEN
	.space 8
	.cstring
LC0:
	.ascii "Halt!!\0"
	.text
	.align 4,0x90
_jc0_HALT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	call	L3
"L00000000001$pb":
L3:
	popl	%ebx
	int3
	leal	LC0-"L00000000001$pb"(%ebx), %eax
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_throw__s$stub
	int3
	addl	$20, %esp
	popl	%ebx
	leave
	ret
	.align 4,0x90
_jc0_MOVA:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	int3
	movl	-12(%edx), %esi
	incl	8(%esi)
	movl	-12(%edx), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	*64(%ecx)
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_MOVA:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -16(%ebp)
	movl	-12(%edx), %edi
	leal	12(%edx), %eax
	incl	8(%edi)
	movl	%eax, -12(%ebp)
	movl	12(%edx), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	*64(%ecx)
	movl	-16(%ebp), %ecx
	movl	%edi, 12(%esi)
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_MOVA:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	int3
	leal	24(%edx), %eax
	movl	%eax, -16(%ebp)
	movl	24(%edx), %edi
	leal	-12(%edx), %eax
	incl	8(%edi)
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	*64(%ecx)
	movl	-16(%ebp), %ecx
	movl	%edi, -12(%esi)
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_MOVN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	int3
	leave
	ret
	.align 4,0x90
_jc1_MOVN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-8(%edx), %esi
	movl	-4(%edx), %edi
	movl	%esi, 16(%edx)
	movl	%edi, 20(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_MOVN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %esi
	movl	32(%edx), %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_MOVO:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	int3
	incl	7
	movl	-12(%edx), %eax
	leal	-12(%edx), %edi
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L17
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L17:
	movl	$-1, -12(%esi)
	movl	11, %eax
	movl	15, %edx
	movl	%eax, 4(%edi)
	movl	%edx, 8(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_MOVO:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	int3
	incl	7
	movl	12(%edx), %eax
	leal	12(%edx), %edi
	decl	8(%eax)
	movl	12(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L22
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L22:
	movl	$-1, 12(%esi)
	movl	11, %eax
	movl	15, %edx
	movl	%eax, 4(%edi)
	movl	%edx, 8(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_MOVO:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	int3
	incl	10
	movl	-12(%edx), %eax
	leal	-12(%edx), %edi
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L26
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L26:
	movl	$2, -12(%esi)
	movl	14, %eax
	movl	18, %edx
	movl	%eax, 4(%edi)
	movl	%edx, 8(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_MOVX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %esi
	incl	8(%esi)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L30
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L30:
	movl	%esi, -12(%edi)
	movl	-12(%ebp), %ecx
	movl	12(%esi), %eax
	movl	16(%esi), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_MOVX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %esi
	leal	12(%edx), %eax
	incl	8(%esi)
	movl	%eax, -12(%ebp)
	movl	12(%edx), %eax
	decl	8(%eax)
	movl	12(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L34
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L34:
	movl	%esi, 12(%edi)
	movl	-12(%ebp), %ecx
	movl	12(%esi), %eax
	movl	16(%esi), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_MOVX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	int3
	movl	24(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %esi
	leal	-12(%edx), %eax
	incl	8(%esi)
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L38
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L38:
	movl	%esi, -12(%edi)
	movl	-12(%ebp), %ecx
	movl	12(%esi), %eax
	movl	16(%esi), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc3_MOVX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	12(%eax), %esi
	incl	8(%esi)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L42
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L42:
	movl	%esi, -12(%edi)
	movl	-12(%ebp), %ecx
	movl	12(%esi), %eax
	movl	16(%esi), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_MOVDEF:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -16(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$65535, 4(%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	leal	-12(%edi), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L46
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L46:
	movl	%esi, -12(%edi)
	movl	-12(%ebp), %ecx
	movl	12(%esi), %eax
	movl	16(%esi), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_MOVDEF:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -16(%ebp)
	int3
	movl	$65535, 4(%esp)
	movl	%ecx, (%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	leal	12(%edi), %eax
	movl	%eax, -12(%ebp)
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L50
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L50:
	movl	%esi, 12(%edi)
	movl	-12(%ebp), %ecx
	movl	12(%esi), %eax
	movl	16(%esi), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_MOVDEF:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -16(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$2, 4(%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	leal	-12(%edi), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L54
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L54:
	movl	%esi, -12(%edi)
	movl	-12(%ebp), %ecx
	movl	12(%esi), %eax
	movl	16(%esi), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_MOVSYS:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	$-1, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_tConst_systemValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L58
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L58:
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_MOVSYS:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$-1, 4(%esp)
	call	L_knh_tConst_systemValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L62
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L62:
	movl	%esi, 12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_MOVSYS:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	$2, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_tConst_systemValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L66
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L66:
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_XMOVS:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	int3
	movl	-12(%edx), %edi
	incl	8(%edi)
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edx), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L70
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%esi), %edx
L70:
	movl	12(%edx), %eax
	movl	%edi, -4(%eax)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_XMOVS:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	int3
	movl	-12(%edx), %edi
	incl	8(%edi)
	movl	12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	12(%edx), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L74
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	12(%esi), %edx
L74:
	movl	12(%edx), %eax
	movl	%edi, -4(%eax)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_XMOVS:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	int3
	movl	-12(%edx), %edi
	incl	8(%edi)
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	8(%eax), %eax
	decl	8(%eax)
	movl	-12(%edx), %edx
	movl	12(%edx), %eax
	movl	8(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L78
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%esi), %edx
L78:
	movl	12(%edx), %eax
	movl	%edi, 8(%eax)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc3_XMOVS:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	int3
	movl	36(%edx), %edi
	incl	8(%edi)
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edx), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L82
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%esi), %edx
L82:
	movl	12(%edx), %eax
	movl	%edi, -4(%eax)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_XMOVO:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%edx, %esi
	subl	$20, %esp
	int3
	incl	7
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edx), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L86
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%esi), %edx
L86:
	movl	12(%edx), %eax
	movl	$-1, -4(%eax)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc1_XMOVO:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%edx, %esi
	subl	$20, %esp
	int3
	incl	7
	movl	12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	12(%edx), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L90
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	12(%esi), %edx
L90:
	movl	12(%edx), %eax
	movl	$-1, -4(%eax)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc2_XMOVO:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%edx, %esi
	subl	$20, %esp
	int3
	incl	7
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	8(%eax), %eax
	decl	8(%eax)
	movl	-12(%edx), %edx
	movl	12(%edx), %eax
	movl	8(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L94
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%esi), %edx
L94:
	movl	12(%edx), %eax
	movl	$-1, 8(%eax)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc3_XMOVO:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%edx, %esi
	subl	$20, %esp
	int3
	incl	11
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edx), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L98
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%esi), %edx
L98:
	movl	12(%edx), %eax
	movl	$3, -4(%eax)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc0_XMOVX:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$16, %esp
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %esi
	incl	8(%esi)
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edx), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L102
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%edi), %edx
L102:
	movl	12(%edx), %eax
	movl	%esi, -4(%eax)
	int3
	addl	$16, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc1_XMOVX:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$16, %esp
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %esi
	incl	8(%esi)
	movl	12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	12(%edx), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L106
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	12(%edi), %edx
L106:
	movl	12(%edx), %eax
	movl	%esi, -4(%eax)
	int3
	addl	$16, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc2_XMOVX:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$16, %esp
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %esi
	incl	8(%esi)
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	8(%eax), %eax
	decl	8(%eax)
	movl	-12(%edx), %edx
	movl	12(%edx), %eax
	movl	8(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L110
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%edi), %edx
L110:
	movl	12(%edx), %eax
	movl	%esi, 8(%eax)
	int3
	addl	$16, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc3_XMOVX:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$16, %esp
	int3
	movl	36(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %esi
	incl	8(%esi)
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edx), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L114
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%edi), %edx
L114:
	movl	12(%edx), %eax
	movl	%esi, -4(%eax)
	int3
	addl	$16, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc4_XMOVX:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$16, %esp
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	16(%eax), %esi
	incl	8(%esi)
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edx), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	cmpl	$0, 8(%eax)
	jne	L118
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%edi), %edx
L118:
	movl	12(%edx), %eax
	movl	%esi, -4(%eax)
	int3
	addl	$16, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc0_XMOVDEF:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$65535, 4(%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edi), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L122
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%edi), %edx
L122:
	movl	12(%edx), %eax
	movl	%esi, -4(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc1_XMOVDEF:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$65535, 4(%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	12(%edi), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L126
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	12(%edi), %edx
L126:
	movl	12(%edx), %eax
	movl	%esi, -4(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc2_XMOVDEF:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$65535, 4(%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	movl	12(%eax), %eax
	movl	8(%eax), %eax
	decl	8(%eax)
	movl	-12(%edi), %edx
	movl	12(%edx), %eax
	movl	8(%eax), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L130
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%edi), %edx
L130:
	movl	12(%edx), %eax
	movl	%esi, 8(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc3_XMOVDEF:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$3, 4(%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edi), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L134
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%edi), %edx
L134:
	movl	12(%edx), %eax
	movl	%esi, -4(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc0_XMOVSYS:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$-1, 4(%esp)
	call	L_knh_tConst_systemValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edi), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L138
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%edi), %edx
L138:
	movl	12(%edx), %eax
	movl	%esi, -4(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc1_XMOVSYS:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$-1, 4(%esp)
	call	L_knh_tConst_systemValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	12(%edi), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L142
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	12(%edi), %edx
L142:
	movl	12(%edx), %eax
	movl	%esi, -4(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc2_XMOVSYS:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$-1, 4(%esp)
	call	L_knh_tConst_systemValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	movl	12(%eax), %eax
	movl	8(%eax), %eax
	decl	8(%eax)
	movl	-12(%edi), %edx
	movl	12(%edx), %eax
	movl	8(%eax), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L146
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%edi), %edx
L146:
	movl	12(%edx), %eax
	movl	%esi, 8(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc3_XMOVSYS:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$3, 4(%esp)
	call	L_knh_tConst_systemValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	decl	8(%eax)
	movl	-12(%edi), %edx
	movl	12(%edx), %eax
	movl	-4(%eax), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L150
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-12(%edi), %edx
L150:
	movl	12(%edx), %eax
	movl	%esi, -4(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc0_SWAP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	int3
	movl	-12(%edx), %edi
	leal	-12(%edx), %eax
	movl	%edi, -20(%ebp)
	movl	4(%eax), %esi
	movl	%esi, -16(%ebp)
	movl	8(%eax), %ecx
	movl	%edi, -12(%edx)
	movl	%ecx, -12(%ebp)
	movl	%esi, 4(%eax)
	movl	%ecx, 8(%eax)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_SWAP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$32, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	int3
	movl	12(%edx), %eax
	leal	12(%edx), %esi
	leal	-12(%edx), %ecx
	movl	%eax, -28(%ebp)
	movl	%eax, -20(%ebp)
	movl	4(%esi), %eax
	movl	%eax, -32(%ebp)
	movl	%eax, -16(%ebp)
	movl	-12(%edx), %eax
	movl	8(%esi), %edi
	movl	%eax, 12(%edx)
	movl	%edi, -12(%ebp)
	movl	4(%ecx), %eax
	movl	%eax, 4(%esi)
	movl	8(%ecx), %eax
	movl	%eax, 8(%esi)
	movl	-28(%ebp), %eax
	movl	%eax, -12(%edx)
	movl	-32(%ebp), %eax
	movl	%edi, 8(%ecx)
	movl	%eax, 4(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_SWAP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$32, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	int3
	movl	-12(%edx), %eax
	leal	-12(%edx), %esi
	leal	24(%edx), %ecx
	movl	%eax, -28(%ebp)
	movl	%eax, -20(%ebp)
	movl	4(%esi), %eax
	movl	%eax, -32(%ebp)
	movl	%eax, -16(%ebp)
	movl	24(%edx), %eax
	movl	8(%esi), %edi
	movl	%eax, -12(%edx)
	movl	%edi, -12(%ebp)
	movl	4(%ecx), %eax
	movl	%eax, 4(%esi)
	movl	8(%ecx), %eax
	movl	%eax, 8(%esi)
	movl	-28(%ebp), %eax
	movl	%eax, 24(%edx)
	movl	-32(%ebp), %eax
	movl	%edi, 8(%ecx)
	movl	%eax, 4(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_PINIO:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, %edi
	int3
	movl	-12(%edx), %eax
	leal	-12(%edx), %ecx
	cmpw	$2, 6(%eax)
	je	L165
L160:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L165:
	movl	11, %eax
	movl	15, %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	incl	7
	movl	-12(%esi), %eax
	decl	8(%eax)
	movl	-12(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L166
L162:
	movl	$-1, -12(%esi)
	jmp	L160
	.align 4,0x90
L166:
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_Object_free$stub
	jmp	L162
	.align 4,0x90
_jc1_PINIO:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, %edi
	int3
	movl	12(%edx), %eax
	leal	12(%edx), %ecx
	cmpw	$2, 6(%eax)
	je	L173
L168:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L173:
	movl	11, %eax
	movl	15, %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	incl	7
	movl	12(%esi), %eax
	decl	8(%eax)
	movl	12(%esi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L174
L170:
	movl	$-1, 12(%esi)
	jmp	L168
	.align 4,0x90
L174:
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_Object_free$stub
	jmp	L170
	.align 4,0x90
_jc2_PINIO:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, %edi
	int3
	movl	-12(%edx), %eax
	leal	-12(%edx), %ecx
	cmpw	$2, 6(%eax)
	je	L181
L176:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L181:
	movl	14, %eax
	movl	18, %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	incl	10
	movl	-12(%esi), %eax
	decl	8(%eax)
	movl	-12(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L182
L178:
	movl	$2, -12(%esi)
	jmp	L176
	.align 4,0x90
L182:
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_Object_free$stub
	jmp	L178
	.cstring
LC1:
	.ascii "codetemplate.c\0"
LC2:
	.ascii "StackOverflow!!\0"
	.text
	.align 4,0x90
_jc0_SETESP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%edi, -4(%ebp)
	movl	%ecx, %edi
	movl	%esi, -8(%ebp)
	call	L187
"L00000000002$pb":
L187:
	popl	%ebx
	int3
	subl	$12, %edx
	movl	36(%ecx), %eax
	movl	%edx, 32(%ecx)
	subl	28(%ecx), %edx
	sarl	$2, %edx
	imull	$-1431655765, %edx, %edx
	subl	%edx, %eax
	cmpl	$63, %eax
	ja	L184
	leal	LC1-"L00000000002$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_KNH_SAFEFILE$stub
	movl	%eax, %esi
	leal	LC2-"L00000000002$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_new_bytes$stub
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	movl	%edx, 8(%esp)
	call	L_new_Exception__b$stub
	movl	$477, 12(%esp)
	movl	%esi, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
L184:
	int3
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_SETESP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%edi, -4(%ebp)
	movl	%ecx, %edi
	movl	%esi, -8(%ebp)
	call	L192
"L00000000003$pb":
L192:
	popl	%ebx
	int3
	addl	$12, %edx
	movl	36(%ecx), %eax
	movl	%edx, 32(%ecx)
	subl	28(%ecx), %edx
	sarl	$2, %edx
	imull	$-1431655765, %edx, %edx
	subl	%edx, %eax
	cmpl	$63, %eax
	ja	L189
	leal	LC1-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_KNH_SAFEFILE$stub
	movl	%eax, %esi
	leal	LC2-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_new_bytes$stub
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	movl	%edx, 8(%esp)
	call	L_new_Exception__b$stub
	movl	$486, 12(%esp)
	movl	%esi, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
L189:
	int3
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_CHECKESP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%edi, -4(%ebp)
	movl	%ecx, %edi
	movl	%esi, -8(%ebp)
	call	L197
"L00000000004$pb":
L197:
	popl	%ebx
	int3
	subl	28(%ecx), %edx
	movl	36(%ecx), %eax
	subl	$12, %edx
	sarl	$2, %edx
	imull	$-1431655765, %edx, %edx
	subl	%edx, %eax
	cmpl	$63, %eax
	ja	L194
	leal	LC1-"L00000000004$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_KNH_SAFEFILE$stub
	movl	%eax, %esi
	leal	LC2-"L00000000004$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_new_bytes$stub
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	movl	%edx, 8(%esp)
	call	L_new_Exception__b$stub
	movl	$495, 12(%esp)
	movl	%esi, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
L194:
	int3
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_CHECKESP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%edi, -4(%ebp)
	movl	%ecx, %edi
	movl	%esi, -8(%ebp)
	call	L202
"L00000000005$pb":
L202:
	popl	%ebx
	int3
	subl	28(%ecx), %edx
	movl	36(%ecx), %eax
	addl	$12, %edx
	sarl	$2, %edx
	imull	$-1431655765, %edx, %edx
	subl	%edx, %eax
	cmpl	$63, %eax
	ja	L199
	leal	LC1-"L00000000005$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_KNH_SAFEFILE$stub
	movl	%eax, %esi
	leal	LC2-"L00000000005$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_new_bytes$stub
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	movl	%edx, 8(%esp)
	call	L_new_Exception__b$stub
	movl	$504, 12(%esp)
	movl	%esi, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
L199:
	int3
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_RET:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leave
	ret
	.align 4,0x90
_jc0_RETN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leave
	ret
	.align 4,0x90
_jc1_RETN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leave
	ret
	.align 4,0x90
_jc2_RETN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %esi
	movl	32(%edx), %edi
	movl	%esi, -8(%edx)
	movl	(%esp), %esi
	movl	%edi, -4(%edx)
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_RETA:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-12(%edx), %ecx
	incl	8(%ecx)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	%ecx, -12(%edx)
	leave
	ret
	.align 4,0x90
_jc1_RETA:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-12(%edx), %ecx
	incl	8(%ecx)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	%ecx, -12(%edx)
	leave
	ret
	.align 4,0x90
_jc2_RETA:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %esi
	movl	32(%edx), %edi
	movl	24(%edx), %ecx
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	incl	8(%ecx)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	(%esp), %esi
	movl	%ecx, -12(%edx)
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_RETO:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	11, %esi
	movl	15, %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	incl	7
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	(%esp), %esi
	movl	$-1, -12(%edx)
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc1_RETO:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	11, %esi
	movl	15, %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	incl	7
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	(%esp), %esi
	movl	$-1, -12(%edx)
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_RETO:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	14, %esi
	movl	18, %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	incl	10
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	(%esp), %esi
	movl	$2, -12(%edx)
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_RETX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %ecx
	movl	12(%ecx), %esi
	movl	16(%ecx), %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	incl	8(%ecx)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	(%esp), %esi
	movl	%ecx, -12(%edx)
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc1_RETX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %ecx
	movl	12(%ecx), %esi
	movl	16(%ecx), %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	incl	8(%ecx)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	(%esp), %esi
	movl	%ecx, -12(%edx)
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_RETX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	24(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %ecx
	movl	12(%ecx), %esi
	movl	16(%ecx), %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	incl	8(%ecx)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	(%esp), %esi
	movl	%ecx, -12(%edx)
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc3_RETX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	12(%eax), %ecx
	movl	12(%ecx), %esi
	movl	16(%ecx), %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	incl	8(%ecx)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	(%esp), %esi
	movl	%ecx, -12(%edx)
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_BOX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	leal	-12(%edx), %edx
	movl	$65535, (%esp)
	call	L_knh_boxing$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	subl	$4, %esp
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L232
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L232:
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_BOX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	leal	12(%edx), %edx
	movl	$65535, (%esp)
	call	L_knh_boxing$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	subl	$4, %esp
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L236
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L236:
	movl	%esi, 12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_BOX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	leal	-12(%edx), %edx
	movl	$2, (%esp)
	call	L_knh_boxing$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	subl	$4, %esp
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L240
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L240:
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_BOXNC:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edi), %eax
	leal	-12(%edx), %edx
	cmpw	$2, 6(%eax)
	je	L244
	movl	$65535, (%esp)
	call	L_knh_boxing$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	subl	$4, %esp
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L249
L246:
	movl	%esi, -12(%edi)
L244:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L249:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L246
	.align 4,0x90
_jc1_BOXNC:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	12(%edi), %eax
	leal	12(%edx), %edx
	cmpw	$2, 6(%eax)
	je	L251
	movl	$65535, (%esp)
	call	L_knh_boxing$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	subl	$4, %esp
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L256
L253:
	movl	%esi, 12(%edi)
L251:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L256:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L253
	.align 4,0x90
_jc2_BOXNC:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edi), %eax
	leal	-12(%edx), %edx
	cmpw	$2, 6(%eax)
	je	L258
	movl	$2, (%esp)
	call	L_knh_boxing$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	subl	$4, %esp
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L263
L260:
	movl	%esi, -12(%edi)
L258:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L263:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L260
	.align 4,0x90
_jc0_NNBOX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$65535, 4(%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L265
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L265:
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_NNBOX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	$65535, 4(%esp)
	movl	%ecx, (%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L269
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L269:
	movl	%esi, 12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_NNBOX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	%ecx, (%esp)
	movl	$2, 4(%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L273
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L273:
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_NNBOXNC:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edx), %eax
	cmpw	$-1, 6(%eax)
	je	L277
	movl	$65535, 4(%esp)
	movl	%ecx, (%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L282
L279:
	movl	%esi, -12(%edi)
L277:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L282:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L279
	.align 4,0x90
_jc1_NNBOXNC:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	12(%edx), %eax
	cmpw	$-1, 6(%eax)
	je	L284
	movl	%ecx, (%esp)
	movl	$65535, 4(%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L289
L286:
	movl	%esi, 12(%edi)
L284:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L289:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L286
	.align 4,0x90
_jc2_NNBOXNC:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L291
	movl	$2, 4(%esp)
	movl	%ecx, (%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L296
L293:
	movl	%esi, -12(%edi)
L291:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L296:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L293
	.align 4,0x90
_jc0_UNBOX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %esi
	movl	16(%eax), %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc1_UNBOX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	12(%edx), %eax
	movl	12(%eax), %esi
	movl	16(%eax), %edi
	movl	%esi, 16(%edx)
	movl	%edi, 20(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_ISNULL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%ecx, %esi
	subl	$20, %esp
	int3
	movl	-12(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L305
L302:
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
L305:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_new_Exception__Nue$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	jmp	L302
	.align 4,0x90
_jc1_ISNULL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%ecx, %esi
	subl	$20, %esp
	int3
	movl	12(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L310
L307:
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
L310:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_new_Exception__Nue$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	jmp	L307
	.align 4,0x90
_jc0_ISNULLX:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%ecx, %esi
	subl	$20, %esp
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	cmpw	$2, 6(%eax)
	je	L315
L312:
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
L315:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_new_Exception__Nue$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	jmp	L312
	.align 4,0x90
_jc1_ISNULLX:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%ecx, %esi
	subl	$20, %esp
	int3
	movl	12(%edx), %eax
	movl	12(%eax), %eax
	movl	-4(%eax), %eax
	cmpw	$2, 6(%eax)
	je	L320
L317:
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
L320:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_new_Exception__Nue$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	jmp	L317
	.align 4,0x90
_jc2_ISNULLX:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%ecx, %esi
	subl	$20, %esp
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	8(%eax), %eax
	cmpw	$2, 6(%eax)
	je	L325
L322:
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
L325:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_new_Exception__Nue$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	jmp	L322
	.align 4,0x90
_jc0_ISTYPE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%ecx, %esi
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	int3
	movl	$65535, 8(%esp)
	movl	-12(%edx), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Object_opTypeOf$stub
	testl	%eax, %eax
	jne	L327
	movl	-12(%edi), %eax
	movl	$65535, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_new_Exception__type$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
L327:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_ISTYPE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%ecx, %esi
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	int3
	movl	$65535, 8(%esp)
	movl	12(%edx), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Object_opTypeOf$stub
	testl	%eax, %eax
	jne	L331
	movl	12(%edi), %eax
	movl	$65535, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_new_Exception__type$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
L331:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_ISTYPE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%ecx, %esi
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	int3
	movl	$2, 8(%esp)
	movl	-12(%edx), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Object_opTypeOf$stub
	testl	%eax, %eax
	jne	L335
	movl	-12(%edi), %eax
	movl	$2, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_new_Exception__type$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
L335:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_ISNNTYPE:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%ecx, %edi
	pushl	%esi
	movl	%edx, %esi
	subl	$16, %esp
	int3
	movl	$65535, 8(%esp)
	movl	-12(%edx), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Object_opTypeOf$stub
	testl	%eax, %eax
	je	L344
	movl	-12(%esi), %eax
	cmpw	$2, 6(%eax)
	je	L345
L341:
	int3
	addl	$16, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L344:
	movl	-12(%esi), %eax
	movl	$65535, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_new_Exception__type$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	movl	-12(%esi), %eax
	cmpw	$2, 6(%eax)
	jne	L341
	.align 4,0x90
L345:
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_new_Exception__Nue$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	jmp	L341
	.align 4,0x90
_jc1_ISNNTYPE:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%ecx, %edi
	pushl	%esi
	movl	%edx, %esi
	subl	$16, %esp
	int3
	movl	$65535, 8(%esp)
	movl	12(%edx), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Object_opTypeOf$stub
	testl	%eax, %eax
	je	L352
	movl	12(%esi), %eax
	cmpw	$2, 6(%eax)
	je	L353
L349:
	int3
	addl	$16, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L352:
	movl	12(%esi), %eax
	movl	$65535, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_new_Exception__type$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	movl	12(%esi), %eax
	cmpw	$2, 6(%eax)
	jne	L349
	.align 4,0x90
L353:
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_new_Exception__Nue$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	jmp	L349
	.align 4,0x90
_jc2_ISNNTYPE:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%ecx, %edi
	pushl	%esi
	movl	%edx, %esi
	subl	$16, %esp
	int3
	movl	$2, 8(%esp)
	movl	-12(%edx), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Object_opTypeOf$stub
	testl	%eax, %eax
	je	L360
	movl	-12(%esi), %eax
	cmpw	$2, 6(%eax)
	je	L361
L357:
	int3
	addl	$16, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L360:
	movl	-12(%esi), %eax
	movl	$2, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_new_Exception__type$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	movl	-12(%esi), %eax
	cmpw	$2, 6(%eax)
	jne	L357
	.align 4,0x90
L361:
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_new_Exception__Nue$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%edi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	jmp	L357
	.align 4,0x90
_jc0_FCALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %esi
	incl	8(%esi)
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L368
L363:
	movl	-12(%ebp), %ecx
	movl	%esi, (%edi)
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	%eax, 4(%edi)
	movl	%edx, 8(%edi)
	incl	7
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L365
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L365:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	$-1, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	%edi, %edx
	movl	-12(%ebp), %ecx
	movl	20(%esi), %eax
	movl	%eax, 4(%ecx)
	movl	-16(%ebp), %ecx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L368:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L363
	.align 4,0x90
_jc1_FCALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -16(%ebp)
	movl	-12(%edx), %edi
	leal	24(%edx), %ecx
	incl	8(%edi)
	movl	%ecx, -12(%ebp)
	movl	24(%edx), %eax
	decl	8(%eax)
	movl	24(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L375
L370:
	movl	%edi, 24(%esi)
	movl	-16(%ebp), %ecx
	leal	12(%esi), %edi
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	incl	7
	movl	12(%esi), %eax
	decl	8(%eax)
	movl	12(%esi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L372
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L372:
	movl	$-1, 12(%esi)
	movl	-20(%ebp), %ecx
	movl	%esi, 32(%ecx)
	movl	12(%esi), %esi
	movl	20(%esi), %eax
	movl	%eax, 4(%edi)
	movl	-12(%ebp), %edx
	movl	-20(%ebp), %ecx
	call	*16(%esi)
	movl	-20(%ebp), %eax
	movl	%edi, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L375:
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L370
	.align 4,0x90
_jc2_FCALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %esi
	incl	8(%esi)
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L382
L377:
	movl	-12(%ebp), %ecx
	movl	%esi, (%edi)
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	%eax, 4(%edi)
	movl	%edx, 8(%edi)
	incl	7
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L379
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L379:
	movl	-16(%ebp), %edx
	leal	12(%edi), %eax
	movl	$-1, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	%edi, %edx
	movl	-12(%ebp), %ecx
	movl	20(%esi), %eax
	movl	%eax, 4(%ecx)
	movl	-16(%ebp), %ecx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L382:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L377
	.align 4,0x90
_jc3_FCALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	leal	36(%edx), %eax
	movl	%eax, -16(%ebp)
	movl	36(%edx), %esi
	incl	8(%esi)
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L389
L384:
	movl	-16(%ebp), %ecx
	movl	%esi, (%edi)
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	%eax, 4(%edi)
	leal	-12(%edi), %eax
	movl	%edx, 8(%edi)
	incl	7
	movl	%eax, -12(%ebp)
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L386
	movl	-20(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L386:
	movl	-20(%ebp), %ecx
	leal	-24(%edi), %eax
	movl	$-1, -12(%edi)
	movl	%eax, 32(%ecx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-20(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %eax
	movl	-20(%ebp), %ecx
	movl	%eax, 32(%ecx)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L389:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L384
	.align 4,0x90
_jc4_FCALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %esi
	incl	8(%esi)
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L396
L391:
	movl	-12(%ebp), %ecx
	movl	%esi, (%edi)
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	%eax, 4(%edi)
	movl	%edx, 8(%edi)
	incl	12
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L393
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L393:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	$4, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	%edi, %edx
	movl	-12(%ebp), %ecx
	movl	20(%esi), %eax
	movl	%eax, 4(%ecx)
	movl	-16(%ebp), %ecx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L396:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L391
	.align 4,0x90
_jc0_SCALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	7
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L398
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L398:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	$-1, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc1_SCALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%ecx, %edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	int3
	incl	7
	leal	12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	12(%edx), %eax
	decl	8(%eax)
	movl	12(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L402
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L402:
	movl	$-1, 12(%esi)
	movl	-12(%ebp), %ecx
	movl	%esi, 32(%edi)
	movl	12(%esi), %eax
	movl	20(%eax), %edx
	movl	%edx, 4(%ecx)
	leal	24(%esi), %edx
	movl	%edi, %ecx
	call	*16(%eax)
	movl	-12(%ebp), %eax
	movl	%eax, 32(%edi)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc2_SCALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	7
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L406
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L406:
	movl	-16(%ebp), %edx
	leal	12(%edi), %eax
	movl	$-1, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc3_SCALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	11
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %esi
	testl	%esi, %esi
	jne	L410
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L410:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	$3, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc0_AINVOKE:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	7
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L414
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L414:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	$-1, -12(%edi)
	movl	%eax, 32(%edx)
	movl	(%edi), %eax
	movl	$0, 12(%esp)
	movl	12(%eax), %eax
	movl	4(%eax), %eax
	movl	%edx, (%esp)
	movl	%edi, 4(%esp)
	movl	%eax, 8(%esp)
	call	L_knh_sfp_typecheck$stub
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc1_AINVOKE:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	7
	leal	12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	12(%edx), %eax
	decl	8(%eax)
	movl	12(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L418
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L418:
	movl	$-1, 12(%esi)
	movl	-16(%ebp), %eax
	leal	24(%esi), %edi
	movl	%esi, 32(%eax)
	movl	-16(%ebp), %edx
	movl	$0, 12(%esp)
	movl	24(%esi), %eax
	movl	12(%eax), %eax
	movl	4(%eax), %eax
	movl	%edx, (%esp)
	movl	%edi, 4(%esp)
	movl	%eax, 8(%esp)
	call	L_knh_sfp_typecheck$stub
	movl	12(%esi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc2_AINVOKE:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	7
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %esi
	testl	%esi, %esi
	jne	L422
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L422:
	movl	-16(%ebp), %edx
	leal	12(%edi), %eax
	movl	$-1, -12(%edi)
	movl	%eax, 32(%edx)
	movl	(%edi), %eax
	movl	$0, 12(%esp)
	movl	12(%eax), %eax
	movl	4(%eax), %eax
	movl	%edx, (%esp)
	movl	%edi, 4(%esp)
	movl	%eax, 8(%esp)
	call	L_knh_sfp_typecheck$stub
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc3_AINVOKE:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	11
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L426
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L426:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	$3, -12(%edi)
	movl	%eax, 32(%edx)
	movl	(%edi), %eax
	movl	$0, 12(%esp)
	movl	12(%eax), %eax
	movl	4(%eax), %eax
	movl	%edx, (%esp)
	movl	%edi, 4(%esp)
	movl	%eax, 8(%esp)
	call	L_knh_sfp_typecheck$stub
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc0_CALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	movl	$65535, 8(%esp)
	movl	(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Method_ufind$stub
	leal	-12(%edi), %edx
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	movl	%edx, -12(%ebp)
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L430
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L430:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	%esi, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc1_CALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	leal	24(%edx), %eax
	movl	%eax, -16(%ebp)
	movl	$65535, 8(%esp)
	movl	24(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Method_ufind$stub
	incl	8(%eax)
	movl	%eax, %edi
	leal	12(%esi), %eax
	movl	%eax, -12(%ebp)
	movl	12(%esi), %eax
	decl	8(%eax)
	movl	12(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L434
	movl	-20(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L434:
	movl	%edi, 12(%esi)
	movl	-20(%ebp), %eax
	movl	%esi, 32(%eax)
	movl	12(%esi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %edx
	movl	-20(%ebp), %ecx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc2_CALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	movl	$65535, 8(%esp)
	movl	(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Method_ufind$stub
	leal	-12(%edi), %edx
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	movl	%edx, -12(%ebp)
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L438
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L438:
	movl	-16(%ebp), %edx
	leal	12(%edi), %eax
	movl	%esi, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc3_CALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	movl	$3, 8(%esp)
	movl	(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Method_ufind$stub
	leal	-12(%edi), %edx
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	movl	%edx, -12(%ebp)
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L442
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L442:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	%esi, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc0_ACALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	movl	$65535, 8(%esp)
	movl	(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Method_ufind$stub
	leal	-12(%esi), %edx
	incl	8(%eax)
	movl	%eax, %edi
	movl	-12(%esi), %eax
	movl	%edx, -12(%ebp)
	decl	8(%eax)
	movl	-12(%esi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L446
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L446:
	movl	-16(%ebp), %edx
	leal	-24(%esi), %eax
	movl	%edi, -12(%esi)
	movl	%eax, 32(%edx)
	movl	%edx, (%esp)
	movl	$0, 12(%esp)
	movl	%edi, 8(%esp)
	movl	%esi, 4(%esp)
	call	L_knh_sfp_typecheck$stub
	movl	-12(%esi), %eax
	movl	-12(%ebp), %edx
	movl	20(%eax), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%esi, %edx
	call	*16(%edi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc1_ACALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	leal	24(%edx), %eax
	movl	%eax, -16(%ebp)
	movl	$65535, 8(%esp)
	movl	24(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Method_ufind$stub
	incl	8(%eax)
	movl	%eax, %edi
	leal	12(%esi), %eax
	movl	%eax, -12(%ebp)
	movl	12(%esi), %eax
	decl	8(%eax)
	movl	12(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L450
	movl	-20(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L450:
	movl	-20(%ebp), %eax
	movl	%edi, 12(%esi)
	movl	%esi, 32(%eax)
	movl	-16(%ebp), %edx
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	%edi, 8(%esp)
	movl	%edx, 4(%esp)
	call	L_knh_sfp_typecheck$stub
	movl	12(%esi), %eax
	movl	-12(%ebp), %edx
	movl	20(%eax), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %edx
	movl	-20(%ebp), %ecx
	call	*16(%edi)
	movl	-12(%ebp), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc2_ACALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	movl	$65535, 8(%esp)
	movl	(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Method_ufind$stub
	leal	-12(%esi), %edx
	incl	8(%eax)
	movl	%eax, %edi
	movl	-12(%esi), %eax
	movl	%edx, -12(%ebp)
	decl	8(%eax)
	movl	-12(%esi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L454
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L454:
	movl	-16(%ebp), %edx
	leal	12(%esi), %eax
	movl	%edi, -12(%esi)
	movl	%eax, 32(%edx)
	movl	%edx, (%esp)
	movl	$0, 12(%esp)
	movl	%edi, 8(%esp)
	movl	%esi, 4(%esp)
	call	L_knh_sfp_typecheck$stub
	movl	-12(%esi), %eax
	movl	-12(%ebp), %edx
	movl	20(%eax), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%esi, %edx
	call	*16(%edi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc3_ACALL:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	movl	$3, 8(%esp)
	movl	(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_Method_ufind$stub
	leal	-12(%esi), %edx
	incl	8(%eax)
	movl	%eax, %edi
	movl	-12(%esi), %eax
	movl	%edx, -12(%ebp)
	decl	8(%eax)
	movl	-12(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L458
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L458:
	movl	-16(%ebp), %edx
	leal	-24(%esi), %eax
	movl	%edi, -12(%esi)
	movl	%eax, 32(%edx)
	movl	%edx, (%esp)
	movl	$0, 12(%esp)
	movl	%edi, 8(%esp)
	movl	%esi, 4(%esp)
	call	L_knh_sfp_typecheck$stub
	movl	-12(%esi), %eax
	movl	-12(%ebp), %edx
	movl	20(%eax), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%esi, %edx
	call	*16(%edi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc0_NEW:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	7
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %esi
	testl	%esi, %esi
	je	L467
L462:
	movl	-16(%ebp), %eax
	movl	$-1, -12(%edi)
	movl	$0, 12(%esp)
	movl	$65535, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_Object_init$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L464
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L464:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	%esi, (%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L467:
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L462
	.align 4,0x90
_jc1_NEW:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	incl	7
	leal	12(%edx), %eax
	movl	%eax, -16(%ebp)
	movl	12(%edx), %eax
	decl	8(%eax)
	movl	12(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L474
L469:
	movl	$-1, 12(%esi)
	movl	-20(%ebp), %eax
	movl	$0, 12(%esp)
	movl	$65535, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_Object_init$stub
	leal	24(%esi), %edx
	incl	8(%eax)
	movl	%eax, %edi
	movl	%edx, -12(%ebp)
	movl	24(%esi), %eax
	decl	8(%eax)
	movl	24(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L471
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L471:
	movl	%edi, 24(%esi)
	movl	-20(%ebp), %edx
	movl	%esi, 32(%edx)
	movl	12(%esi), %esi
	movl	-16(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-12(%ebp), %edx
	movl	-20(%ebp), %ecx
	call	*16(%esi)
	movl	-16(%ebp), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L474:
	movl	-20(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L469
	.align 4,0x90
_jc2_NEW:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	7
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L481
L476:
	movl	-16(%ebp), %eax
	movl	$-1, -12(%edi)
	movl	$0, 12(%esp)
	movl	$65535, 8(%esp)
	movl	$2, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_Object_init$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L478
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L478:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	%esi, (%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L481:
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L476
	.align 4,0x90
_jc3_NEW:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	7
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L488
L483:
	movl	-16(%ebp), %eax
	movl	$-1, -12(%edi)
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_Object_init$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L485
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L485:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	%esi, (%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L488:
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L483
	.align 4,0x90
_jc4_NEW:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	7
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L495
L490:
	movl	-16(%ebp), %eax
	movl	$-1, -12(%edi)
	movl	$0, 12(%esp)
	movl	$65535, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_Object_init$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L492
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L492:
	movl	-16(%ebp), %edx
	leal	36(%edi), %eax
	movl	%esi, (%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L495:
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L490
	.align 4,0x90
_jc5_NEW:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	incl	13
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	decl	8(%eax)
	movl	-12(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L502
L497:
	movl	-16(%ebp), %eax
	movl	$5, -12(%edi)
	movl	$0, 12(%esp)
	movl	$65535, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_Object_init$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L499
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L499:
	movl	-16(%ebp), %edx
	leal	-24(%edi), %eax
	movl	%esi, (%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-12(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 32(%eax)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L502:
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L497
	.align 4,0x90
_jc0_TOSTR:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$96, %esp
	movl	%ecx, -64(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -60(%ebp)
	movl	-12(%edx), %esi
	movl	%esi, -32(%ebp)
	movl	4(%eax), %ecx
	movl	%ecx, -28(%ebp)
	movl	8(%eax), %edx
	movl	(%edi), %eax
	movl	%edx, -76(%ebp)
	movl	%edx, -24(%ebp)
	movl	4(%edi), %edx
	movl	%eax, -12(%edi)
	movl	-60(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	8(%edi), %edx
	movl	%edx, 8(%eax)
	movl	-76(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%esi, (%edi)
	movl	%ecx, 4(%edi)
	movl	%eax, 8(%edi)
	leal	-56(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_cwb$stub
	movl	-56(%ebp), %eax
	movl	-48(%ebp), %esi
	movl	%eax, -20(%ebp)
	movl	-52(%ebp), %eax
	movl	%esi, -12(%ebp)
	subl	$4, %esp
	movl	%eax, -16(%ebp)
	incl	8(%esi)
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L513
L504:
	movl	-64(%ebp), %edx
	movl	%esi, 12(%edi)
	movl	72(%edx), %esi
	incl	8(%esi)
	movl	24(%edi), %eax
	decl	8(%eax)
	movl	24(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L514
L506:
	movl	(%edi), %eax
	movl	%esi, 24(%edi)
	movl	$65535, 8(%esp)
	movzwl	6(%eax), %eax
	movl	%eax, 4(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_tMethod_findMT$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L515
L508:
	movl	-64(%ebp), %edx
	leal	36(%edi), %eax
	movl	%esi, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-60(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-64(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-60(%ebp), %edx
	movl	-64(%ebp), %eax
	movl	%edx, 32(%eax)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_new_String__cwb$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L510
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L510:
	movl	%esi, -12(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L515:
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L508
	.align 4,0x90
L514:
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L506
	.align 4,0x90
L513:
	movl	%eax, 4(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L504
	.align 4,0x90
_jc1_TOSTR:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$112, %esp
	movl	%ecx, -68(%ebp)
	int3
	leal	12(%edx), %eax
	movl	%eax, -64(%ebp)
	movl	12(%edx), %esi
	movl	%esi, -32(%ebp)
	movl	4(%eax), %ecx
	movl	%ecx, -28(%ebp)
	movl	8(%eax), %edx
	leal	24(%edi), %eax
	movl	%eax, -60(%ebp)
	movl	24(%edi), %eax
	movl	%edx, -92(%ebp)
	movl	%edx, -24(%ebp)
	movl	-60(%ebp), %edx
	movl	%eax, 12(%edi)
	movl	-64(%ebp), %eax
	movl	4(%edx), %edx
	movl	%edx, 4(%eax)
	movl	-60(%ebp), %edx
	movl	8(%edx), %edx
	movl	%edx, 8(%eax)
	movl	-60(%ebp), %eax
	movl	%esi, 24(%edi)
	movl	%ecx, 4(%eax)
	movl	-92(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-68(%ebp), %edx
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L_new_cwb$stub
	movl	-56(%ebp), %eax
	movl	-48(%ebp), %esi
	movl	%eax, -20(%ebp)
	movl	-52(%ebp), %eax
	movl	%esi, -12(%ebp)
	subl	$4, %esp
	movl	%eax, -16(%ebp)
	incl	8(%esi)
	movl	36(%edi), %eax
	decl	8(%eax)
	movl	36(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L526
L517:
	movl	-68(%ebp), %edx
	movl	%esi, 36(%edi)
	movl	72(%edx), %esi
	incl	8(%esi)
	movl	48(%edi), %eax
	decl	8(%eax)
	movl	48(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L527
L519:
	movl	24(%edi), %eax
	movl	%esi, 48(%edi)
	movl	$65535, 8(%esp)
	movzwl	6(%eax), %eax
	movl	%eax, 4(%esp)
	movl	-68(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_tMethod_findMT$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L528
L521:
	movl	-68(%ebp), %edx
	leal	60(%edi), %eax
	movl	%esi, 12(%edi)
	movl	%eax, 32(%edx)
	movl	12(%edi), %esi
	movl	-64(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-68(%ebp), %ecx
	movl	-60(%ebp), %edx
	call	*16(%esi)
	movl	-68(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%edx, 32(%eax)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-68(%ebp), %eax
	movl	%eax, (%esp)
	call	L_new_String__cwb$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L523
	movl	-68(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L523:
	movl	%esi, 12(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L528:
	movl	-68(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L521
	.align 4,0x90
L527:
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L519
	.align 4,0x90
L526:
	movl	%eax, 4(%esp)
	movl	-68(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L517
	.align 4,0x90
_jc2_TOSTR:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$96, %esp
	movl	%ecx, -64(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -60(%ebp)
	movl	-12(%edx), %esi
	movl	%esi, -32(%ebp)
	movl	4(%eax), %ecx
	movl	%ecx, -28(%ebp)
	movl	8(%eax), %edx
	movl	(%edi), %eax
	movl	%edx, -76(%ebp)
	movl	%edx, -24(%ebp)
	movl	4(%edi), %edx
	movl	%eax, -12(%edi)
	movl	-60(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	8(%edi), %edx
	movl	%edx, 8(%eax)
	movl	-76(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%esi, (%edi)
	movl	%ecx, 4(%edi)
	movl	%eax, 8(%edi)
	leal	-56(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_cwb$stub
	movl	-56(%ebp), %eax
	movl	-48(%ebp), %esi
	movl	%eax, -20(%ebp)
	movl	-52(%ebp), %eax
	movl	%esi, -12(%ebp)
	subl	$4, %esp
	movl	%eax, -16(%ebp)
	incl	8(%esi)
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L539
L530:
	movl	-64(%ebp), %edx
	movl	%esi, 12(%edi)
	movl	72(%edx), %esi
	incl	8(%esi)
	movl	24(%edi), %eax
	decl	8(%eax)
	movl	24(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L540
L532:
	movl	(%edi), %eax
	movl	%esi, 24(%edi)
	movl	$2, 8(%esp)
	movzwl	6(%eax), %eax
	movl	%eax, 4(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_tMethod_findMT$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L541
L534:
	movl	-64(%ebp), %edx
	leal	36(%edi), %eax
	movl	%esi, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-60(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-64(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-64(%ebp), %eax
	movl	-60(%ebp), %edx
	movl	%edx, 32(%eax)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_new_String__cwb$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L536
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L536:
	movl	%esi, -12(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L541:
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L534
	.align 4,0x90
L540:
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L532
	.align 4,0x90
L539:
	movl	%eax, 4(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L530
	.align 4,0x90
_jc0_TOSTRF:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$96, %esp
	movl	%ecx, -64(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -60(%ebp)
	movl	-12(%edx), %esi
	movl	%esi, -32(%ebp)
	movl	4(%eax), %ecx
	movl	%ecx, -28(%ebp)
	movl	8(%eax), %edx
	movl	(%edi), %eax
	movl	%edx, -76(%ebp)
	movl	%edx, -24(%ebp)
	movl	4(%edi), %edx
	movl	%eax, -12(%edi)
	movl	-60(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	8(%edi), %edx
	movl	%edx, 8(%eax)
	movl	-76(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%esi, (%edi)
	movl	%ecx, 4(%edi)
	movl	%eax, 8(%edi)
	leal	-56(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_cwb$stub
	movl	-56(%ebp), %eax
	movl	-48(%ebp), %esi
	movl	%eax, -20(%ebp)
	movl	-52(%ebp), %eax
	movl	%esi, -12(%ebp)
	subl	$4, %esp
	movl	%eax, -16(%ebp)
	incl	8(%esi)
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L552
L543:
	movl	%esi, 12(%edi)
	incl	7
	movl	24(%edi), %eax
	decl	8(%eax)
	movl	24(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L553
L545:
	movl	(%edi), %eax
	movl	$-1, 24(%edi)
	movl	$65535, 8(%esp)
	movzwl	6(%eax), %eax
	movl	%eax, 4(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_tMethod_findMT$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L554
L547:
	movl	-64(%ebp), %edx
	leal	36(%edi), %eax
	movl	%esi, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-60(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-64(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-64(%ebp), %eax
	movl	-60(%ebp), %edx
	movl	%edx, 32(%eax)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_new_String__cwb$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L549
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L549:
	movl	%esi, -12(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L554:
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L547
	.align 4,0x90
L553:
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L545
	.align 4,0x90
L552:
	movl	%eax, 4(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L543
	.align 4,0x90
_jc1_TOSTRF:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$112, %esp
	movl	%ecx, -68(%ebp)
	int3
	leal	12(%edx), %eax
	movl	%eax, -64(%ebp)
	movl	12(%edx), %esi
	movl	%esi, -32(%ebp)
	movl	4(%eax), %ecx
	movl	%ecx, -28(%ebp)
	movl	8(%eax), %edx
	leal	24(%edi), %eax
	movl	%eax, -60(%ebp)
	movl	24(%edi), %eax
	movl	%edx, -92(%ebp)
	movl	%edx, -24(%ebp)
	movl	-60(%ebp), %edx
	movl	%eax, 12(%edi)
	movl	-64(%ebp), %eax
	movl	4(%edx), %edx
	movl	%edx, 4(%eax)
	movl	-60(%ebp), %edx
	movl	8(%edx), %edx
	movl	%edx, 8(%eax)
	movl	-60(%ebp), %eax
	movl	%esi, 24(%edi)
	movl	%ecx, 4(%eax)
	movl	-92(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-68(%ebp), %edx
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L_new_cwb$stub
	movl	-56(%ebp), %eax
	movl	-48(%ebp), %esi
	movl	%eax, -20(%ebp)
	movl	-52(%ebp), %eax
	movl	%esi, -12(%ebp)
	subl	$4, %esp
	movl	%eax, -16(%ebp)
	incl	8(%esi)
	movl	36(%edi), %eax
	decl	8(%eax)
	movl	36(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L565
L556:
	movl	%esi, 36(%edi)
	incl	7
	movl	48(%edi), %eax
	decl	8(%eax)
	movl	48(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L566
L558:
	movl	24(%edi), %eax
	movl	$-1, 48(%edi)
	movl	$65535, 8(%esp)
	movzwl	6(%eax), %eax
	movl	%eax, 4(%esp)
	movl	-68(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_tMethod_findMT$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L567
L560:
	movl	-68(%ebp), %edx
	leal	60(%edi), %eax
	movl	%esi, 12(%edi)
	movl	%eax, 32(%edx)
	movl	12(%edi), %esi
	movl	-64(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-68(%ebp), %ecx
	movl	-60(%ebp), %edx
	call	*16(%esi)
	movl	-68(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%edx, 32(%eax)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-68(%ebp), %eax
	movl	%eax, (%esp)
	call	L_new_String__cwb$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L562
	movl	-68(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L562:
	movl	%esi, 12(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L567:
	movl	-68(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L560
	.align 4,0x90
L566:
	movl	-68(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L558
	.align 4,0x90
L565:
	movl	%eax, 4(%esp)
	movl	-68(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L556
	.align 4,0x90
_jc2_TOSTRF:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$96, %esp
	movl	%ecx, -64(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -60(%ebp)
	movl	-12(%edx), %esi
	movl	%esi, -32(%ebp)
	movl	4(%eax), %ecx
	movl	%ecx, -28(%ebp)
	movl	8(%eax), %edx
	movl	(%edi), %eax
	movl	%edx, -76(%ebp)
	movl	%edx, -24(%ebp)
	movl	4(%edi), %edx
	movl	%eax, -12(%edi)
	movl	-60(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	8(%edi), %edx
	movl	%edx, 8(%eax)
	movl	-76(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%esi, (%edi)
	movl	%ecx, 4(%edi)
	movl	%eax, 8(%edi)
	leal	-56(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_cwb$stub
	movl	-56(%ebp), %eax
	movl	-48(%ebp), %esi
	movl	%eax, -20(%ebp)
	movl	-52(%ebp), %eax
	movl	%esi, -12(%ebp)
	subl	$4, %esp
	movl	%eax, -16(%ebp)
	incl	8(%esi)
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L578
L569:
	movl	%esi, 12(%edi)
	incl	7
	movl	24(%edi), %eax
	decl	8(%eax)
	movl	24(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L579
L571:
	movl	(%edi), %eax
	movl	$-1, 24(%edi)
	movl	$2, 8(%esp)
	movzwl	6(%eax), %eax
	movl	%eax, 4(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_tMethod_findMT$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L580
L573:
	movl	-64(%ebp), %edx
	leal	36(%edi), %eax
	movl	%esi, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-60(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-64(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-64(%ebp), %eax
	movl	-60(%ebp), %edx
	movl	%edx, 32(%eax)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_new_String__cwb$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L575
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L575:
	movl	%esi, -12(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L580:
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L573
	.align 4,0x90
L579:
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L571
	.align 4,0x90
L578:
	movl	%eax, 4(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L569
	.align 4,0x90
_jc3_TOSTRF:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$96, %esp
	movl	%ecx, -64(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -60(%ebp)
	movl	-12(%edx), %esi
	movl	%esi, -32(%ebp)
	movl	4(%eax), %ecx
	movl	%ecx, -28(%ebp)
	movl	8(%eax), %edx
	movl	(%edi), %eax
	movl	%edx, -76(%ebp)
	movl	%edx, -24(%ebp)
	movl	4(%edi), %edx
	movl	%eax, -12(%edi)
	movl	-60(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	8(%edi), %edx
	movl	%edx, 8(%eax)
	movl	-76(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%esi, (%edi)
	movl	%ecx, 4(%edi)
	movl	%eax, 8(%edi)
	leal	-56(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	L_new_cwb$stub
	movl	-56(%ebp), %eax
	movl	-48(%ebp), %esi
	movl	%eax, -20(%ebp)
	movl	-52(%ebp), %eax
	movl	%esi, -12(%ebp)
	subl	$4, %esp
	movl	%eax, -16(%ebp)
	incl	8(%esi)
	movl	12(%edi), %eax
	decl	8(%eax)
	movl	12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L591
L582:
	movl	%esi, 12(%edi)
	incl	11
	movl	24(%edi), %eax
	decl	8(%eax)
	movl	24(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L592
L584:
	movl	(%edi), %eax
	movl	$3, 24(%edi)
	movl	$65535, 8(%esp)
	movzwl	6(%eax), %eax
	movl	%eax, 4(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_tMethod_findMT$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L593
L586:
	movl	-64(%ebp), %edx
	leal	36(%edi), %eax
	movl	%esi, -12(%edi)
	movl	%eax, 32(%edx)
	movl	-12(%edi), %esi
	movl	-60(%ebp), %edx
	movl	20(%esi), %eax
	movl	%eax, 4(%edx)
	movl	-64(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	-64(%ebp), %eax
	movl	-60(%ebp), %edx
	movl	%edx, 32(%eax)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_new_String__cwb$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L588
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
L588:
	movl	%esi, -12(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L593:
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L586
	.align 4,0x90
L592:
	movl	-64(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L584
	.align 4,0x90
L591:
	movl	%eax, 4(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L582
	.align 4,0x90
_jc0_SMAP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, %edi
	int3
	incl	7
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L595
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_Object_free$stub
L595:
	movl	$-1, (%esi)
	leal	-12(%esi), %edx
	movl	%edi, %ecx
	call	*15
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_SMAP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, %edi
	int3
	incl	7
	movl	24(%edx), %eax
	decl	8(%eax)
	movl	24(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L599
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
L599:
	movl	$-1, 24(%esi)
	leal	12(%esi), %edx
	movl	%edi, %ecx
	call	*15
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_SMAP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, %edi
	int3
	incl	10
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L603
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_Object_free$stub
L603:
	movl	$2, (%esi)
	leal	-12(%esi), %edx
	movl	%edi, %ecx
	call	*18
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_SMAPNC:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edx), %eax
	leal	-12(%edx), %edi
	cmpw	$2, 6(%eax)
	je	L607
	incl	7
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L612
L609:
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	movl	$-1, (%esi)
	call	*15
L607:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L612:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L609
	.align 4,0x90
_jc1_SMAPNC:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	12(%edx), %eax
	leal	12(%edx), %edi
	cmpw	$2, 6(%eax)
	je	L614
	incl	7
	movl	24(%edx), %eax
	decl	8(%eax)
	movl	24(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L619
L616:
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	movl	$-1, 24(%esi)
	call	*15
L614:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L619:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L616
	.align 4,0x90
_jc2_SMAPNC:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edx), %eax
	leal	-12(%edx), %edi
	cmpw	$2, 6(%eax)
	je	L621
	incl	10
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L626
L623:
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	movl	$2, (%esi)
	call	*18
L621:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L626:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L623
	.align 4,0x90
_jc0_MAP:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	-12(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L628
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L628:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	%esi, (%edi)
	call	*16(%esi)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc1_MAP:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	leal	12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	12(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	24(%edi), %eax
	decl	8(%eax)
	movl	24(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L632
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L632:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	%esi, 24(%edi)
	call	*16(%esi)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc2_MAP:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	$1, 12(%esp)
	movl	$2, 8(%esp)
	movl	-12(%edx), %eax
	movzwl	6(%eax), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L636
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
L636:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	%esi, (%edi)
	call	*16(%esi)
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc0_MAPNC:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	movzwl	6(%eax), %eax
	cmpw	$2, %ax
	je	L640
	movzwl	%ax, %eax
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L645
L642:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	%esi, (%edi)
	call	*16(%esi)
L640:
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L645:
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L642
	.align 4,0x90
_jc1_MAPNC:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	leal	12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	12(%edx), %eax
	movzwl	6(%eax), %eax
	cmpw	$2, %ax
	je	L647
	movzwl	%ax, %eax
	movl	%ecx, (%esp)
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%eax, 4(%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	24(%edi), %eax
	decl	8(%eax)
	movl	24(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L652
L649:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	%esi, 24(%edi)
	call	*16(%esi)
L647:
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L652:
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L649
	.align 4,0x90
_jc2_MAPNC:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	movzwl	6(%eax), %eax
	cmpw	$2, %ax
	je	L654
	movzwl	%ax, %eax
	movl	$1, 12(%esp)
	movl	$2, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L659
L656:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	%esi, (%edi)
	call	*16(%esi)
L654:
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L659:
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L656
	.align 4,0x90
_jc0_AMAP:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -16(%ebp)
	movl	-12(%edx), %eax
	movzwl	6(%eax), %esi
	cmpw	$-1, %si
	je	L661
	movzwl	%si, %eax
	movl	%eax, -12(%ebp)
	movl	$65535, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	jne	L661
	cmpw	$2, %si
	je	L661
	movl	-12(%ebp), %eax
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L668
L665:
	movl	-16(%ebp), %edx
	movl	-20(%ebp), %ecx
	movl	%esi, (%edi)
	call	*16(%esi)
	.align 4,0x90
L661:
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
L668:
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L665
	.align 4,0x90
_jc1_AMAP:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	leal	12(%edx), %eax
	movl	%eax, -16(%ebp)
	movl	12(%edx), %eax
	movzwl	6(%eax), %esi
	cmpw	$-1, %si
	je	L670
	movzwl	%si, %eax
	movl	%eax, -12(%ebp)
	movl	$65535, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	jne	L670
	cmpw	$2, %si
	je	L670
	movl	-12(%ebp), %eax
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	24(%edi), %eax
	decl	8(%eax)
	movl	24(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L677
L674:
	movl	-16(%ebp), %edx
	movl	-20(%ebp), %ecx
	movl	%esi, 24(%edi)
	call	*16(%esi)
	.align 4,0x90
L670:
	int3
	addl	$32, %esp
	popl	%esi
	popl	%edi
	leave
	ret
L677:
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L674
	.align 4,0x90
_jc2_AMAP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	movzwl	6(%eax), %eax
	cmpw	$2, %ax
	je	L679
	movzwl	%ax, %edi
	movl	$2, 8(%esp)
	movl	%edi, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	je	L685
L679:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L685:
	movl	-16(%ebp), %eax
	movl	%edi, 4(%esp)
	movl	$1, 12(%esp)
	movl	$2, 8(%esp)
	movl	%eax, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %edi
	movl	(%esi), %eax
	decl	8(%eax)
	movl	(%esi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L686
L682:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	%edi, (%esi)
	call	*16(%edi)
	jmp	L679
L686:
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L682
	.align 4,0x90
_jc0_NNMAP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L693
L688:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L693:
	movl	$65535, 4(%esp)
	movl	%ecx, (%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %edi
	movl	-12(%esi), %eax
	decl	8(%eax)
	movl	-12(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L694
L690:
	movl	%edi, -12(%esi)
	movl	-12(%ebp), %ecx
	movl	12(%edi), %eax
	movl	16(%edi), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	jmp	L688
L694:
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L690
	.align 4,0x90
_jc1_NNMAP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, -16(%ebp)
	int3
	leal	12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	12(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L701
L696:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L701:
	movl	%ecx, (%esp)
	movl	$65535, 4(%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %edi
	movl	12(%esi), %eax
	decl	8(%eax)
	movl	12(%esi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L702
L698:
	movl	%edi, 12(%esi)
	movl	-12(%ebp), %ecx
	movl	12(%edi), %eax
	movl	16(%edi), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	jmp	L696
L702:
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L698
	.align 4,0x90
_jc2_NNMAP:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edx, %esi
	movl	%edi, -4(%ebp)
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L709
L704:
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L709:
	movl	$2, 4(%esp)
	movl	%ecx, (%esp)
	call	L_konoha_getClassDefaultValue$stub
	incl	8(%eax)
	movl	%eax, %edi
	movl	-12(%esi), %eax
	decl	8(%eax)
	movl	-12(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L710
L706:
	movl	%edi, -12(%esi)
	movl	-12(%ebp), %ecx
	movl	12(%edi), %eax
	movl	16(%edi), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	jmp	L704
L710:
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L706
	.align 4,0x90
_jc0_JMP:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc1_JMP:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$1, %eax
	jmp	*%eax
	.align 4,0x90
_jc0_BJIFT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-8(%edx), %ecx
	testl	%ecx, %ecx
	je	L716
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L716:
	int3
	leave
	ret
	.align 4,0x90
_jc1_BJIFT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-8(%edx), %eax
	testl	%eax, %eax
	je	L720
	movl	$1, %eax
	jmp	*%eax
	.align 4,0x90
L720:
	int3
	leave
	ret
	.align 4,0x90
_jc2_BJIFT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	28(%edx), %eax
	testl	%eax, %eax
	je	L724
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L724:
	int3
	leave
	ret
	.align 4,0x90
_jc0_BJIFF:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-8(%edx), %eax
	testl	%eax, %eax
	jne	L728
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L728:
	int3
	leave
	ret
	.align 4,0x90
_jc1_BJIFF:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-8(%edx), %eax
	testl	%eax, %eax
	jne	L732
	movl	$1, %eax
	jmp	*%eax
	.align 4,0x90
L732:
	int3
	leave
	ret
	.align 4,0x90
_jc2_BJIFF:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	28(%edx), %eax
	testl	%eax, %eax
	jne	L736
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L736:
	int3
	leave
	ret
	.align 4,0x90
_jc0_BJIFF_LOOP:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-8(%edx), %eax
	testl	%eax, %eax
	jne	L740
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L740:
	int3
	leave
	ret
	.align 4,0x90
_jc1_BJIFF_LOOP:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-8(%edx), %edx
	testl	%edx, %edx
	jne	L744
	movl	$1, %eax
	jmp	*%eax
	.align 4,0x90
L744:
	int3
	leave
	ret
	.align 4,0x90
_jc2_BJIFF_LOOP:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	28(%edx), %ecx
	testl	%ecx, %ecx
	jne	L748
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L748:
	int3
	leave
	ret
	.align 4,0x90
_jc0_JIFNUL:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-12(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L755
	int3
	leave
	ret
	.align 4,0x90
L755:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc1_JIFNUL:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-12(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L760
	int3
	leave
	ret
	.align 4,0x90
L760:
	movl	$1, %eax
	jmp	*%eax
	.align 4,0x90
_jc2_JIFNUL:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	24(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L765
	int3
	leave
	ret
	.align 4,0x90
L765:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc0_JIFNN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-12(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L767
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L767:
	int3
	leave
	ret
	.align 4,0x90
_jc1_JIFNN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-12(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L771
	movl	$1, %eax
	jmp	*%eax
	.align 4,0x90
L771:
	int3
	leave
	ret
	.align 4,0x90
_jc2_JIFNN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	24(%edx), %eax
	cmpw	$2, 6(%eax)
	je	L775
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L775:
	int3
	leave
	ret
	.align 4,0x90
_jc0_NEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edi), %eax
	leal	-12(%edx), %edx
	movl	$0, (%esp)
	call	*16(%eax)
	movl	-12(%edi), %esi
	subl	$4, %esp
	cmpw	$2, 6(%esi)
	je	L784
	incl	8(%esi)
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L785
L781:
	movl	%esi, -12(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L785:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L781
	.align 4,0x90
L784:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc1_NEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edi), %eax
	leal	-12(%edx), %edx
	movl	$0, (%esp)
	call	*16(%eax)
	movl	-12(%edi), %esi
	subl	$4, %esp
	cmpw	$2, 6(%esi)
	je	L792
	incl	8(%esi)
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L793
L789:
	movl	%esi, -12(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L793:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L789
	.align 4,0x90
L792:
	movl	$1, %eax
	jmp	*%eax
	.align 4,0x90
_jc2_NEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	movl	-12(%ebp), %edx
	movl	$0, (%esp)
	call	*16(%eax)
	movl	-12(%esi), %edi
	subl	$4, %esp
	cmpw	$2, 6(%edi)
	je	L800
	incl	8(%edi)
	movl	24(%esi), %eax
	leal	24(%esi), %ecx
	movl	%ecx, -16(%ebp)
	decl	8(%eax)
	movl	24(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L801
L797:
	movl	-12(%ebp), %ecx
	movl	%edi, 24(%esi)
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L801:
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L797
	.align 4,0x90
L800:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc3_NEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	movl	36(%edi), %eax
	leal	36(%edx), %edx
	movl	$-4, (%esp)
	call	*16(%eax)
	movl	-12(%edi), %esi
	subl	$4, %esp
	cmpw	$2, 6(%esi)
	je	L808
	incl	8(%esi)
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L809
L805:
	movl	%esi, -12(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L809:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L805
	.align 4,0x90
L808:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc4_NEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %eax
	movl	-12(%ebp), %edx
	movl	$5, (%esp)
	call	*16(%eax)
	movl	48(%esi), %edi
	leal	48(%esi), %ecx
	movl	%ecx, -16(%ebp)
	subl	$4, %esp
	cmpw	$2, 6(%edi)
	je	L816
	incl	8(%edi)
	movl	-12(%esi), %eax
	decl	8(%eax)
	movl	-12(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L817
L813:
	movl	-16(%ebp), %ecx
	movl	%edi, -12(%esi)
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
	.align 4,0x90
L817:
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L813
	.align 4,0x90
L816:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc0_INEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	leal	-12(%edx), %esi
	jmp	L819
	.align 4,0x90
L830:
	movl	-12(%ebp), %ecx
L819:
	movl	(%esi), %eax
	movl	%esi, %edx
	movl	$0, (%esp)
	call	*16(%eax)
	movl	(%esi), %edi
	movzwl	6(%edi), %eax
	subl	$4, %esp
	cmpw	$2, %ax
	je	L831
	cmpw	$-1, %ax
	je	L822
	movzwl	%ax, %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	je	L830
	movl	(%esi), %edi
L822:
	incl	8(%edi)
	movl	(%esi), %eax
	decl	8(%eax)
	movl	(%esi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L832
L825:
	movl	%edi, (%esi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L832:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L825
L831:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc1_INEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	int3
	leal	-12(%edx), %esi
	jmp	L834
	.align 4,0x90
L845:
	movl	-12(%ebp), %ecx
L834:
	movl	(%esi), %eax
	movl	%esi, %edx
	movl	$0, (%esp)
	call	*16(%eax)
	movl	(%esi), %edi
	movzwl	6(%edi), %eax
	subl	$4, %esp
	cmpw	$2, %ax
	je	L846
	cmpw	$-1, %ax
	je	L837
	movzwl	%ax, %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	je	L845
	movl	(%esi), %edi
L837:
	incl	8(%edi)
	movl	(%esi), %eax
	decl	8(%eax)
	movl	(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L847
L840:
	movl	%edi, (%esi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L847:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L840
L846:
	movl	$1, %eax
	jmp	*%eax
	.align 4,0x90
_jc2_INEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%ecx, %edi
	pushl	%esi
	subl	$32, %esp
	int3
	leal	-12(%edx), %esi
	.align 4,0x90
L849:
	movl	(%esi), %eax
	movl	%esi, %edx
	movl	%edi, %ecx
	movl	$0, (%esp)
	call	*16(%eax)
	movl	(%esi), %eax
	movzwl	6(%eax), %eax
	subl	$4, %esp
	cmpw	$2, %ax
	je	L859
	movzwl	%ax, %eax
	movl	%eax, 8(%esp)
	movl	$2, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	je	L849
	movl	(%esi), %eax
	movl	%eax, -12(%ebp)
	incl	8(%eax)
	movl	(%esi), %eax
	decl	8(%eax)
	movl	(%esi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L860
L854:
	movl	-12(%ebp), %eax
	movl	%eax, (%esi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L860:
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_Object_free$stub
	jmp	L854
L859:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc3_INEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	movl	%edx, -20(%ebp)
	int3
	movl	%edx, %edi
	subl	$12, %edi
	jmp	L862
	.align 4,0x90
L873:
	movl	-16(%ebp), %ecx
L862:
	movl	(%edi), %eax
	movl	%edi, %edx
	movl	$0, (%esp)
	call	*16(%eax)
	movl	(%edi), %esi
	movzwl	6(%esi), %eax
	subl	$4, %esp
	cmpw	$2, %ax
	je	L874
	cmpw	$-1, %ax
	je	L865
	movzwl	%ax, %eax
	movl	%eax, 8(%esp)
	movl	-16(%ebp), %eax
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	je	L873
	movl	(%edi), %esi
L865:
	incl	8(%esi)
	movl	-20(%ebp), %edx
	movl	-20(%ebp), %ecx
	addl	$36, %edx
	movl	%edx, -12(%ebp)
	movl	36(%ecx), %eax
	decl	8(%eax)
	movl	36(%ecx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L875
L868:
	movl	-20(%ebp), %edx
	movl	4(%edi), %eax
	movl	%esi, 36(%edx)
	movl	8(%edi), %edx
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L875:
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L868
L874:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc4_INEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%ecx, %edi
	pushl	%esi
	subl	$32, %esp
	int3
	leal	48(%edx), %eax
	subl	$12, %edx
	movl	%edx, -12(%ebp)
	movl	%eax, %edx
	movl	%eax, -16(%ebp)
	jmp	L877
	.align 4,0x90
L888:
	movl	-16(%ebp), %edx
L877:
	movl	(%edx), %eax
	movl	%edi, %ecx
	movl	$-5, (%esp)
	call	*16(%eax)
	movl	-12(%ebp), %eax
	movl	(%eax), %esi
	subl	$4, %esp
	movzwl	6(%esi), %eax
	cmpw	$2, %ax
	je	L889
	cmpw	$-1, %ax
	je	L880
	movzwl	%ax, %eax
	movl	%eax, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	je	L888
	movl	-12(%ebp), %edx
	movl	(%edx), %esi
L880:
	incl	8(%esi)
	movl	-12(%ebp), %edx
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L890
L883:
	movl	-12(%ebp), %eax
	movl	%esi, (%eax)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L890:
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_Object_free$stub
	jmp	L883
L889:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc5_INEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	int3
	leal	-12(%edx), %edi
	addl	$60, %edx
	movl	%edx, -12(%ebp)
	jmp	L892
	.align 4,0x90
L903:
	movl	-16(%ebp), %ecx
L892:
	movl	(%edi), %eax
	movl	%edi, %edx
	movl	$6, (%esp)
	call	*16(%eax)
	movl	-12(%ebp), %eax
	movl	(%eax), %esi
	subl	$4, %esp
	movzwl	6(%esi), %eax
	cmpw	$2, %ax
	je	L904
	cmpw	$-1, %ax
	je	L895
	movl	-16(%ebp), %ecx
	movzwl	%ax, %eax
	movl	%eax, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	je	L903
	movl	-12(%ebp), %eax
	movl	(%eax), %esi
L895:
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L905
L898:
	movl	%esi, (%edi)
	movl	-12(%ebp), %ecx
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	%eax, 4(%edi)
	movl	%edx, 8(%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L905:
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L898
L904:
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
_jc0_MAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	movl	%edx, -16(%ebp)
	int3
	movl	-12(%edx), %esi
	movl	%edx, %edi
	subl	$12, %edi
	jmp	L907
	.align 4,0x90
L913:
	movl	-16(%ebp), %edx
	movl	%esi, (%edx)
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	je	L910
L922:
	movl	-12(%ebp), %ecx
L907:
	movl	$0, (%esp)
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %esi
	movzwl	6(%esi), %eax
	subl	$4, %esp
	cmpw	$2, %ax
	je	L921
	cmpw	$-1, %ax
	je	L910
	movzwl	%ax, %esi
	movl	-12(%ebp), %eax
	movl	%esi, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	jne	L919
	movl	-12(%ebp), %edx
	movl	%esi, 4(%esp)
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%edx, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-16(%ebp), %edx
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L913
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-16(%ebp), %edx
	movl	%esi, (%edx)
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	jne	L922
	.align 4,0x90
L910:
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L923
L916:
	movl	%esi, (%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L923:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L916
L921:
	movl	$-1, %eax
	jmp	*%eax
L919:
	movl	(%edi), %esi
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L916
	jmp	L923
	.align 4,0x90
_jc1_MAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	movl	%edx, -16(%ebp)
	int3
	movl	-12(%edx), %esi
	movl	%edx, %edi
	subl	$12, %edi
	jmp	L925
	.align 4,0x90
L931:
	movl	-16(%ebp), %edx
	movl	%esi, (%edx)
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	je	L928
L940:
	movl	-12(%ebp), %ecx
L925:
	movl	$0, (%esp)
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %esi
	movzwl	6(%esi), %eax
	subl	$4, %esp
	cmpw	$2, %ax
	je	L939
	cmpw	$-1, %ax
	je	L928
	movzwl	%ax, %esi
	movl	-12(%ebp), %eax
	movl	%esi, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	jne	L937
	movl	-12(%ebp), %edx
	movl	%esi, 4(%esp)
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%edx, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-16(%ebp), %edx
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L931
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-16(%ebp), %edx
	movl	%esi, (%edx)
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	jne	L940
	.align 4,0x90
L928:
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L941
L934:
	movl	%esi, (%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L941:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L934
L939:
	movl	$1, %eax
	jmp	*%eax
L937:
	movl	(%edi), %esi
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L934
	jmp	L941
	.align 4,0x90
_jc2_MAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	movl	%edx, -16(%ebp)
	int3
	movl	-12(%edx), %esi
	movl	%edx, %edi
	subl	$12, %edi
	jmp	L943
	.align 4,0x90
L948:
	movl	-16(%ebp), %edx
	movl	%esi, (%edx)
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	je	L946
L957:
	movl	-12(%ebp), %ecx
L943:
	movl	$0, (%esp)
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %eax
	movzwl	6(%eax), %eax
	subl	$4, %esp
	cmpw	$2, %ax
	je	L956
	movzwl	%ax, %esi
	movl	-12(%ebp), %eax
	movl	%esi, 8(%esp)
	movl	$2, 4(%esp)
	movl	%eax, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	jne	L954
	movl	-12(%ebp), %edx
	movl	%esi, 4(%esp)
	movl	$1, 12(%esp)
	movl	$2, 8(%esp)
	movl	%edx, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-16(%ebp), %edx
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L948
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-16(%ebp), %edx
	movl	%esi, (%edx)
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	jne	L957
	.align 4,0x90
L946:
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L958
L951:
	movl	%esi, (%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L958:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L951
L956:
	movl	$-1, %eax
	jmp	*%eax
L954:
	movl	(%edi), %esi
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L951
	jmp	L958
	.align 4,0x90
_jc3_MAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%edx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%edx), %esi
	movl	%eax, %edx
	jmp	L960
	.align 4,0x90
L966:
	movl	-20(%ebp), %ecx
	movl	-12(%ebp), %edx
	movl	%esi, (%edi)
	call	*16(%esi)
	movl	-12(%ebp), %ecx
	movl	(%ecx), %esi
	cmpw	$2, 6(%esi)
	je	L963
L975:
	movl	-12(%ebp), %edx
	movl	-20(%ebp), %ecx
L960:
	movl	$0, (%esp)
	call	*16(%esi)
	movl	-12(%ebp), %ecx
	movl	(%ecx), %esi
	subl	$4, %esp
	movzwl	6(%esi), %eax
	cmpw	$2, %ax
	je	L974
	cmpw	$-1, %ax
	je	L963
	movzwl	%ax, %esi
	movl	-20(%ebp), %eax
	movl	%esi, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	jne	L972
	movl	-20(%ebp), %ecx
	movl	%esi, 4(%esp)
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%ecx, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L966
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-20(%ebp), %ecx
	movl	-12(%ebp), %edx
	movl	%esi, (%edi)
	call	*16(%esi)
	movl	-12(%ebp), %ecx
	movl	(%ecx), %esi
	cmpw	$2, 6(%esi)
	jne	L975
	.align 4,0x90
L963:
	incl	8(%esi)
	movl	36(%edi), %eax
	leal	36(%edi), %ecx
	movl	%ecx, -16(%ebp)
	decl	8(%eax)
	movl	36(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L976
L969:
	movl	-12(%ebp), %ecx
	movl	%esi, 36(%edi)
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L976:
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L969
L974:
	movl	$-1, %eax
	jmp	*%eax
L972:
	movl	-12(%ebp), %eax
	leal	36(%edi), %ecx
	movl	(%eax), %esi
	incl	8(%esi)
	movl	36(%edi), %eax
	movl	%ecx, -16(%ebp)
	decl	8(%eax)
	movl	36(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L969
	jmp	L976
	.align 4,0x90
_jc4_MAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	movl	%edx, -20(%ebp)
	int3
	movl	-20(%ebp), %edi
	addl	$48, %edx
	movl	%edx, -12(%ebp)
	subl	$12, %edi
	jmp	L978
	.align 4,0x90
L984:
	movl	-20(%ebp), %edx
	movl	%esi, (%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	je	L981
L993:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %ecx
L978:
	movl	(%edx), %eax
	movl	$-5, (%esp)
	call	*16(%eax)
	movl	(%edi), %esi
	movzwl	6(%esi), %eax
	subl	$4, %esp
	cmpw	$2, %ax
	je	L992
	cmpw	$-1, %ax
	je	L981
	movzwl	%ax, %esi
	movl	-16(%ebp), %eax
	movl	%esi, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%eax, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	jne	L990
	movl	-16(%ebp), %edx
	movl	%esi, 4(%esp)
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%edx, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-20(%ebp), %edx
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L984
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	movl	-20(%ebp), %edx
	movl	%esi, (%edx)
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	call	*16(%esi)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	jne	L993
	.align 4,0x90
L981:
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L994
L987:
	movl	%esi, (%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L994:
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L987
L992:
	movl	$-1, %eax
	jmp	*%eax
L990:
	movl	(%edi), %esi
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L987
	jmp	L994
	.align 4,0x90
_jc5_MAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%ecx, %edi
	pushl	%esi
	subl	$32, %esp
	movl	%edx, -20(%ebp)
	int3
	movl	-20(%ebp), %eax
	subl	$12, %edx
	movl	%edx, -16(%ebp)
	addl	$60, %eax
	movl	%eax, -12(%ebp)
	jmp	L996
	.align 4,0x90
L1002:
	movl	-20(%ebp), %ecx
	movl	%esi, 72(%ecx)
	movl	-12(%ebp), %edx
	movl	%edi, %ecx
	call	*16(%esi)
	movl	-12(%ebp), %eax
	movl	(%eax), %esi
	cmpw	$2, 6(%esi)
	je	L999
L1011:
	movl	-16(%ebp), %edx
L996:
	movl	(%edx), %eax
	movl	%edi, %ecx
	movl	$6, (%esp)
	call	*16(%eax)
	movl	-12(%ebp), %ecx
	movl	(%ecx), %esi
	subl	$4, %esp
	movzwl	6(%esi), %eax
	cmpw	$2, %ax
	je	L1010
	cmpw	$-1, %ax
	je	L999
	movzwl	%ax, %esi
	movl	%esi, 8(%esp)
	movl	$65535, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_class_instanceof$stub
	testl	%eax, %eax
	jne	L1008
	movl	%esi, 4(%esp)
	movl	$1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%edi, (%esp)
	call	L_knh_tMapper_find_$stub
	incl	8(%eax)
	movl	%eax, %esi
	movl	-20(%ebp), %edx
	movl	72(%edx), %eax
	decl	8(%eax)
	movl	72(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	jne	L1002
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_Object_free$stub
	movl	-20(%ebp), %ecx
	movl	%esi, 72(%ecx)
	movl	-12(%ebp), %edx
	movl	%edi, %ecx
	call	*16(%esi)
	movl	-12(%ebp), %eax
	movl	(%eax), %esi
	cmpw	$2, 6(%esi)
	jne	L1011
	.align 4,0x90
L999:
	incl	8(%esi)
	movl	-16(%ebp), %ecx
	movl	(%ecx), %eax
	decl	8(%eax)
	movl	(%ecx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L1012
L1005:
	movl	-16(%ebp), %eax
	movl	%esi, (%eax)
	movl	-12(%ebp), %ecx
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L1012:
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1005
L1010:
	movl	$-1, %eax
	jmp	*%eax
L1008:
	movl	-12(%ebp), %edx
	movl	(%edx), %esi
	incl	8(%esi)
	movl	-16(%ebp), %ecx
	movl	(%ecx), %eax
	decl	8(%eax)
	movl	(%ecx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	jne	L1005
	jmp	L1012
	.align 4,0x90
_jc0_SMAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	movl	%edx, -16(%ebp)
	int3
	incl	7
	movl	%edx, %edi
	movl	(%edx), %eax
	subl	$12, %edi
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %esi
	testl	%esi, %esi
	je	L1026
L1014:
	movl	-16(%ebp), %edx
	movl	-12(%edx), %eax
	movl	$-1, (%edx)
	.align 4,0x90
L1016:
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	movl	$0, (%esp)
	call	*16(%eax)
	movl	(%edi), %eax
	subl	$4, %esp
	cmpw	$2, 6(%eax)
	je	L1027
	movl	-16(%ebp), %edx
	movl	-12(%ebp), %ecx
	movl	(%edx), %eax
	movl	%edi, %edx
	call	*16(%eax)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	movl	%esi, %eax
	jne	L1016
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L1028
L1021:
	movl	%esi, (%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L1028:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1021
L1027:
	movl	$-1, %eax
	jmp	*%eax
L1026:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1014
	.align 4,0x90
_jc1_SMAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	movl	%edx, -16(%ebp)
	int3
	incl	7
	movl	%edx, %edi
	movl	(%edx), %eax
	subl	$12, %edi
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L1042
L1030:
	movl	-16(%ebp), %edx
	movl	-12(%edx), %eax
	movl	$-1, (%edx)
	.align 4,0x90
L1032:
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	movl	$0, (%esp)
	call	*16(%eax)
	movl	(%edi), %eax
	subl	$4, %esp
	cmpw	$2, 6(%eax)
	je	L1043
	movl	-16(%ebp), %edx
	movl	-12(%ebp), %ecx
	movl	(%edx), %eax
	movl	%edi, %edx
	call	*16(%eax)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	movl	%esi, %eax
	jne	L1032
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L1044
L1037:
	movl	%esi, (%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L1044:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1037
L1043:
	movl	$1, %eax
	jmp	*%eax
L1042:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1030
	.align 4,0x90
_jc2_SMAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	movl	%edx, -20(%ebp)
	int3
	incl	7
	movl	%edx, %edi
	movl	(%edx), %eax
	subl	$12, %edi
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %esi
	testl	%esi, %esi
	je	L1058
L1046:
	movl	-20(%ebp), %eax
	movl	-12(%eax), %esi
	movl	$-1, (%eax)
	.align 4,0x90
L1048:
	movl	-16(%ebp), %ecx
	movl	%edi, %edx
	movl	$0, (%esp)
	call	*16(%esi)
	movl	(%edi), %eax
	subl	$4, %esp
	cmpw	$2, 6(%eax)
	je	L1059
	movl	-20(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	(%edx), %eax
	movl	%edi, %edx
	call	*16(%eax)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	jne	L1048
	incl	8(%esi)
	movl	-20(%ebp), %ecx
	movl	-20(%ebp), %edx
	addl	$24, %ecx
	movl	%ecx, -12(%ebp)
	movl	24(%edx), %eax
	decl	8(%eax)
	movl	24(%edx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L1060
L1053:
	movl	-20(%ebp), %eax
	movl	8(%edi), %edx
	movl	%esi, 24(%eax)
	movl	4(%edi), %eax
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L1060:
	movl	-16(%ebp), %ecx
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1053
L1059:
	movl	$-1, %eax
	jmp	*%eax
L1058:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1046
	.align 4,0x90
_jc3_SMAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -16(%ebp)
	movl	%edx, -20(%ebp)
	int3
	addl	$36, %edx
	movl	%edx, -12(%ebp)
	incl	7
	movl	-20(%ebp), %edx
	movl	(%edx), %eax
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L1074
L1062:
	movl	-20(%ebp), %edx
	movl	%edx, %edi
	movl	$-1, (%edx)
	subl	$12, %edi
	.align 4,0x90
L1064:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	(%edx), %eax
	movl	$-4, (%esp)
	call	*16(%eax)
	movl	(%edi), %eax
	subl	$4, %esp
	cmpw	$2, 6(%eax)
	je	L1075
	movl	-20(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	(%edx), %eax
	movl	%edi, %edx
	call	*16(%eax)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	jne	L1064
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L1076
L1069:
	movl	%esi, (%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L1076:
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1069
L1075:
	movl	$-1, %eax
	jmp	*%eax
L1074:
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1062
	.align 4,0x90
_jc4_SMAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	%edx, %esi
	subl	$32, %esp
	movl	%ecx, -20(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	leal	60(%edx), %edx
	incl	7
	movl	%edx, -16(%ebp)
	movl	60(%esi), %eax
	decl	8(%eax)
	movl	60(%esi), %eax
	movl	8(%eax), %edi
	testl	%edi, %edi
	je	L1090
L1078:
	movl	$-1, 60(%esi)
	leal	48(%esi), %edi
	.align 4,0x90
L1080:
	movl	-12(%ebp), %ecx
	movl	(%ecx), %eax
	movl	%ecx, %edx
	movl	-20(%ebp), %ecx
	movl	$5, (%esp)
	call	*16(%eax)
	movl	(%edi), %eax
	subl	$4, %esp
	cmpw	$2, 6(%eax)
	je	L1091
	movl	-16(%ebp), %edx
	movl	-20(%ebp), %ecx
	movl	(%edx), %eax
	movl	%edi, %edx
	call	*16(%eax)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	jne	L1080
	incl	8(%esi)
	movl	-12(%ebp), %ecx
	movl	(%ecx), %eax
	decl	8(%eax)
	movl	(%ecx), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L1092
L1085:
	movl	-12(%ebp), %edx
	movl	4(%edi), %eax
	movl	%esi, (%edx)
	movl	8(%edi), %edx
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L1092:
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1085
L1091:
	movl	$-1, %eax
	jmp	*%eax
L1090:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1078
	.align 4,0x90
_jc5_SMAPNEXT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	%ecx, -12(%ebp)
	movl	%edx, -16(%ebp)
	int3
	incl	13
	movl	%edx, %edi
	movl	(%edx), %eax
	subl	$12, %edi
	decl	8(%eax)
	movl	(%edx), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L1106
L1094:
	movl	-16(%ebp), %edx
	movl	-12(%edx), %eax
	movl	$5, (%edx)
	.align 4,0x90
L1096:
	movl	-12(%ebp), %ecx
	movl	%edi, %edx
	movl	$0, (%esp)
	call	*16(%eax)
	movl	(%edi), %eax
	subl	$4, %esp
	cmpw	$2, 6(%eax)
	je	L1107
	movl	-16(%ebp), %edx
	movl	-12(%ebp), %ecx
	movl	(%edx), %eax
	movl	%edi, %edx
	call	*16(%eax)
	movl	(%edi), %esi
	cmpw	$2, 6(%esi)
	movl	%esi, %eax
	jne	L1096
	incl	8(%esi)
	movl	(%edi), %eax
	decl	8(%eax)
	movl	(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L1108
L1101:
	movl	%esi, (%edi)
	int3
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
L1108:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1101
L1107:
	movl	$-1, %eax
	jmp	*%eax
L1106:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1094
	.align 4,0x90
_jc0_TRY:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%edx, %esi
	subl	$36, %esp
	movl	%ecx, -16(%ebp)
	int3
	movl	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	%eax, %edx
	cmpw	$38, 6(%eax)
	je	L1110
	movl	%ecx, (%esp)
	call	L_new_ExceptionHandler$stub
	movl	%eax, -12(%ebp)
	incl	8(%eax)
	movl	-12(%esi), %eax
	decl	8(%eax)
	movl	-12(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L1121
L1112:
	movl	-12(%ebp), %ecx
	movl	%ecx, -12(%esi)
	movl	%ecx, %edx
L1110:
	movzwl	2(%edx), %eax
	testb	$8, %ah
	je	L1122
	movl	%edx, %eax
L1114:
	orw	$1024, 2(%eax)
	int3
	addl	$36, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
L1122:
	orb	$8, %ah
	movw	%ax, 2(%edx)
	movl	12(%edx), %eax
	movl	%eax, (%esp)
	call	L_setjmp$stub
	testl	%eax, %eax
	je	L1116
	movl	-12(%ebp), %ecx
	movl	-16(%ebp), %edx
	movl	12(%ecx), %eax
	movl	72(%eax), %eax
	movl	%eax, 32(%edx)
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L1116:
	movl	-12(%ebp), %ecx
	movl	12(%ecx), %edx
	movl	-16(%ebp), %ecx
	movl	32(%ecx), %eax
	movl	%eax, 72(%edx)
	movl	-12(%ebp), %eax
	jmp	L1114
	.align 4,0x90
L1121:
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1112
	.align 4,0x90
_jc1_TRY:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%edx, %esi
	subl	$36, %esp
	movl	%ecx, -16(%ebp)
	int3
	movl	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	%eax, %edx
	cmpw	$38, 6(%eax)
	je	L1124
	movl	%ecx, (%esp)
	call	L_new_ExceptionHandler$stub
	movl	%eax, -12(%ebp)
	incl	8(%eax)
	movl	-12(%esi), %eax
	decl	8(%eax)
	movl	-12(%esi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L1135
L1126:
	movl	-12(%ebp), %ecx
	movl	%ecx, -12(%esi)
	movl	%ecx, %edx
L1124:
	movzwl	2(%edx), %eax
	testb	$8, %ah
	je	L1136
	movl	%edx, %eax
L1128:
	orw	$1024, 2(%eax)
	int3
	addl	$36, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
L1136:
	orb	$8, %ah
	movw	%ax, 2(%edx)
	movl	12(%edx), %eax
	movl	%eax, (%esp)
	call	L_setjmp$stub
	testl	%eax, %eax
	je	L1130
	movl	-12(%ebp), %ecx
	movl	-16(%ebp), %edx
	movl	12(%ecx), %eax
	movl	72(%eax), %eax
	movl	%eax, 32(%edx)
	movl	$1, %eax
	jmp	*%eax
	.align 4,0x90
L1130:
	movl	-12(%ebp), %ecx
	movl	12(%ecx), %edx
	movl	-16(%ebp), %ecx
	movl	32(%ecx), %eax
	movl	%eax, 72(%edx)
	movl	-12(%ebp), %eax
	jmp	L1128
	.align 4,0x90
L1135:
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1126
	.align 4,0x90
_jc2_TRY:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%edx, %esi
	subl	$36, %esp
	movl	%ecx, -16(%ebp)
	int3
	movl	24(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	%eax, %edx
	cmpw	$38, 6(%eax)
	je	L1138
	movl	%ecx, (%esp)
	call	L_new_ExceptionHandler$stub
	movl	%eax, -12(%ebp)
	incl	8(%eax)
	movl	24(%esi), %eax
	decl	8(%eax)
	movl	24(%esi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L1149
L1140:
	movl	-12(%ebp), %ecx
	movl	%ecx, 24(%esi)
	movl	%ecx, %edx
L1138:
	movzwl	2(%edx), %eax
	testb	$8, %ah
	je	L1150
	movl	%edx, %eax
L1142:
	orw	$1024, 2(%eax)
	int3
	addl	$36, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
L1150:
	orb	$8, %ah
	movw	%ax, 2(%edx)
	movl	12(%edx), %eax
	movl	%eax, (%esp)
	call	L_setjmp$stub
	testl	%eax, %eax
	je	L1144
	movl	-12(%ebp), %ecx
	movl	-16(%ebp), %edx
	movl	12(%ecx), %eax
	movl	72(%eax), %eax
	movl	%eax, 32(%edx)
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L1144:
	movl	-12(%ebp), %ecx
	movl	12(%ecx), %edx
	movl	-16(%ebp), %ecx
	movl	32(%ecx), %eax
	movl	%eax, 72(%edx)
	movl	-12(%ebp), %eax
	jmp	L1142
	.align 4,0x90
L1149:
	movl	-16(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1140
	.align 4,0x90
_jc0_TRYEND:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-12(%edx), %eax
	andw	$-1025, 2(%eax)
	int3
	leave
	ret
	.align 4,0x90
_jc1_TRYEND:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	12(%edx), %eax
	andw	$-1025, 2(%eax)
	int3
	leave
	ret
	.align 4,0x90
_jc0_CATCH:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	80(%eax), %esi
	movl	$-1, 8(%esp)
	movl	%ecx, (%esp)
	movl	%esi, 4(%esp)
	call	L_knh_Exception_isa$stub
	testl	%eax, %eax
	jne	L1156
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L1156:
	incl	8(%esi)
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L1161
L1158:
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L1161:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1158
	.align 4,0x90
_jc1_CATCH:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	80(%eax), %esi
	movl	$-1, 8(%esp)
	movl	%ecx, (%esp)
	movl	%esi, 4(%esp)
	call	L_knh_Exception_isa$stub
	testl	%eax, %eax
	jne	L1163
	movb	$1, %al
	jmp	*%eax
	.align 4,0x90
L1163:
	incl	8(%esi)
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L1168
L1165:
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L1168:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1165
	.align 4,0x90
_jc2_CATCH:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	24(%edx), %eax
	movl	12(%eax), %eax
	movl	80(%eax), %esi
	movl	$-1, 8(%esp)
	movl	%ecx, (%esp)
	movl	%esi, 4(%esp)
	call	L_knh_Exception_isa$stub
	testl	%eax, %eax
	jne	L1170
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L1170:
	incl	8(%esi)
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L1175
L1172:
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L1175:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1172
	.align 4,0x90
_jc3_CATCH:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	80(%eax), %esi
	movl	$-1, 8(%esp)
	movl	%ecx, (%esp)
	movl	%esi, 4(%esp)
	call	L_knh_Exception_isa$stub
	testl	%eax, %eax
	jne	L1177
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L1177:
	incl	8(%esi)
	movl	36(%edi), %eax
	decl	8(%eax)
	movl	36(%edi), %eax
	movl	8(%eax), %edx
	testl	%edx, %edx
	je	L1182
L1179:
	movl	%esi, 36(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L1182:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1179
	.align 4,0x90
_jc4_CATCH:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%edi, -4(%ebp)
	movl	%edx, %edi
	movl	%esi, -8(%ebp)
	movl	%ecx, -12(%ebp)
	int3
	movl	-12(%edx), %eax
	movl	12(%eax), %eax
	movl	80(%eax), %esi
	movl	$4, 8(%esp)
	movl	%ecx, (%esp)
	movl	%esi, 4(%esp)
	call	L_knh_Exception_isa$stub
	testl	%eax, %eax
	jne	L1184
	movl	$-1, %eax
	jmp	*%eax
	.align 4,0x90
L1184:
	incl	8(%esi)
	movl	-12(%edi), %eax
	decl	8(%eax)
	movl	-12(%edi), %eax
	movl	8(%eax), %ecx
	testl	%ecx, %ecx
	je	L1189
L1186:
	movl	%esi, -12(%edi)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
L1189:
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_knh_Object_free$stub
	jmp	L1186
	.cstring
___func__.11234:
	.ascii "jc0_THROW\0"
	.align 2
LC3:
	.ascii "((sfp[(-1)].e)->h.cid == ((knh_class_t)37))\0"
	.text
	.align 4,0x90
_jc0_THROW:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	%ecx, %esi
	call	L1199
"L00000000006$pb":
L1199:
	popl	%ebx
	int3
	movl	-12(%edx), %eax
	cmpw	$7, 4(%eax)
	je	L1197
	cmpw	$37, 6(%eax)
	jne	L1198
L1194:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	L_knh_throwException$stub
	int3
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	leave
	ret
	.align 4,0x90
L1197:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_new_Exception$stub
	jmp	L1194
L1198:
	leal	LC3-"L00000000006$pb"(%ebx), %eax
	movl	%eax, 12(%esp)
	leal	LC1-"L00000000006$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	___func__.11234-"L00000000006$pb"(%ebx), %eax
	movl	$1782, 8(%esp)
	movl	%eax, (%esp)
	call	L___assert_rtn$stub
	.cstring
___func__.11248:
	.ascii "jc1_THROW\0"
	.align 2
LC4:
	.ascii "((sfp[(1)].e)->h.cid == ((knh_class_t)37))\0"
	.text
	.align 4,0x90
_jc1_THROW:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	%ecx, %esi
	call	L1209
"L00000000007$pb":
L1209:
	popl	%ebx
	int3
	movl	12(%edx), %eax
	cmpw	$7, 4(%eax)
	je	L1207
	cmpw	$37, 6(%eax)
	jne	L1208
L1204:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	L_knh_throwException$stub
	int3
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	leave
	ret
	.align 4,0x90
L1207:
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_new_Exception$stub
	jmp	L1204
L1208:
	leal	LC4-"L00000000007$pb"(%ebx), %eax
	movl	%eax, 12(%esp)
	leal	LC1-"L00000000007$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	___func__.11248-"L00000000007$pb"(%ebx), %eax
	movl	$1791, 8(%esp)
	movl	%eax, (%esp)
	call	L___assert_rtn$stub
	.cstring
___func__.11262:
	.ascii "jc0_THROWS\0"
	.align 2
LC5:
	.ascii "(((knh_Object_t*)((knh_Object_t*)-1))->h.cid == ((knh_class_t)37))\0"
	.text
	.align 4,0x90
_jc0_THROWS:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	%ecx, %esi
	call	L1219
"L00000000008$pb":
L1219:
	popl	%ebx
	int3
	cmpw	$7, 3
	je	L1217
	cmpw	$37, 5
	jne	L1218
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$-1, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_throwException$stub
L1213:
	int3
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	leave
	ret
	.align 4,0x90
L1217:
	movl	$-1, 4(%esp)
	movl	%ecx, (%esp)
	call	L_new_Exception$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	jmp	L1213
L1218:
	leal	LC5-"L00000000008$pb"(%ebx), %eax
	movl	%eax, 12(%esp)
	leal	LC1-"L00000000008$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	___func__.11262-"L00000000008$pb"(%ebx), %eax
	movl	$1800, 8(%esp)
	movl	%eax, (%esp)
	call	L___assert_rtn$stub
	.cstring
___func__.11273:
	.ascii "jc1_THROWS\0"
	.align 2
LC6:
	.ascii "(((knh_Object_t*)((knh_Object_t*)1))->h.cid == ((knh_class_t)37))\0"
	.text
	.align 4,0x90
_jc1_THROWS:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -8(%ebp)
	movl	%esi, -4(%ebp)
	movl	%ecx, %esi
	call	L1229
"L00000000009$pb":
L1229:
	popl	%ebx
	int3
	cmpw	$7, 5
	je	L1227
	cmpw	$37, 7
	jne	L1228
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$1, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_throwException$stub
L1223:
	int3
	movl	-8(%ebp), %ebx
	movl	-4(%ebp), %esi
	leave
	ret
	.align 4,0x90
L1227:
	movl	$1, 4(%esp)
	movl	%ecx, (%esp)
	call	L_new_Exception$stub
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	L_knh_throwException$stub
	jmp	L1223
L1228:
	leal	LC6-"L00000000009$pb"(%ebx), %eax
	movl	%eax, 12(%esp)
	leal	LC1-"L00000000009$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	___func__.11273-"L00000000009$pb"(%ebx), %eax
	movl	$1809, 8(%esp)
	movl	%eax, (%esp)
	call	L___assert_rtn$stub
	.cstring
___func__.11284:
	.ascii "jc0_THROW_AGAIN\0"
	.align 2
LC7:
	.ascii "((sfp[(-1)].o)->h.cid == ((knh_class_t)38))\0"
	.text
	.align 4,0x90
_jc0_THROW_AGAIN:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	call	L1238
"L00000000010$pb":
L1238:
	popl	%ebx
	int3
	movl	-12(%edx), %eax
	cmpw	$38, 6(%eax)
	jne	L1236
	movl	12(%eax), %eax
	movl	80(%eax), %eax
	cmpw	$37, 6(%eax)
	je	L1237
L1233:
	int3
	addl	$20, %esp
	popl	%ebx
	leave
	ret
	.align 4,0x90
L1237:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_throwException$stub
	jmp	L1233
L1236:
	leal	LC7-"L00000000010$pb"(%ebx), %eax
	movl	%eax, 12(%esp)
	leal	LC1-"L00000000010$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	___func__.11284-"L00000000010$pb"(%ebx), %eax
	movl	$1818, 8(%esp)
	movl	%eax, (%esp)
	call	L___assert_rtn$stub
	.cstring
___func__.11298:
	.ascii "jc1_THROW_AGAIN\0"
	.align 2
LC8:
	.ascii "((sfp[(1)].o)->h.cid == ((knh_class_t)38))\0"
	.text
	.align 4,0x90
_jc1_THROW_AGAIN:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	call	L1247
"L00000000011$pb":
L1247:
	popl	%ebx
	int3
	movl	12(%edx), %eax
	cmpw	$38, 6(%eax)
	jne	L1245
	movl	12(%eax), %eax
	movl	80(%eax), %eax
	cmpw	$37, 6(%eax)
	je	L1246
L1242:
	int3
	addl	$20, %esp
	popl	%ebx
	leave
	ret
	.align 4,0x90
L1246:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_throwException$stub
	jmp	L1242
L1245:
	leal	LC8-"L00000000011$pb"(%ebx), %eax
	movl	%eax, 12(%esp)
	leal	LC1-"L00000000011$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	___func__.11298-"L00000000011$pb"(%ebx), %eax
	movl	$1827, 8(%esp)
	movl	%eax, (%esp)
	call	L___assert_rtn$stub
	.align 4,0x90
_jc0_P:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	int3
	movl	$-1, 16(%esp)
	movl	$65535, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_stack_p$stub
	int3
	leave
	ret
	.align 4,0x90
_jc1_P:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	int3
	movl	$-1, 16(%esp)
	movl	$65535, 12(%esp)
	movl	$1, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_stack_p$stub
	int3
	leave
	ret
	.align 4,0x90
_jc2_P:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	int3
	movl	$-1, 16(%esp)
	movl	$2, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_stack_p$stub
	int3
	leave
	ret
	.align 4,0x90
_jc3_P:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	int3
	movl	$3, 16(%esp)
	movl	$65535, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_stack_p$stub
	int3
	leave
	ret
	.align 4,0x90
_jc0_PMSG:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	int3
	movl	$-1, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_stack_pmsg$stub
	int3
	leave
	ret
	.align 4,0x90
_jc1_PMSG:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	int3
	movl	$-1, 12(%esp)
	movl	$1, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_stack_pmsg$stub
	int3
	leave
	ret
	.align 4,0x90
_jc2_PMSG:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	int3
	movl	$2, 12(%esp)
	movl	$65535, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%ecx, (%esp)
	call	L_knh_stack_pmsg$stub
	int3
	leave
	ret
	.align 4,0x90
_jc0_ICAST:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	int3
	fnstcw	-2(%ebp)
	fldl	-8(%edx)
	movzwl	-2(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -4(%ebp)
	fldcw	-4(%ebp)
	fistpll	-8(%edx)
	fldcw	-2(%ebp)
	int3
	leave
	ret
	.align 4,0x90
_jc1_ICAST:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	int3
	fnstcw	-2(%ebp)
	fldl	16(%edx)
	movzwl	-2(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -4(%ebp)
	fldcw	-4(%ebp)
	fistpll	16(%edx)
	fldcw	-2(%ebp)
	int3
	leave
	ret
	.align 4,0x90
_jc0_INCAST:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	int3
	movl	-12(%edx), %eax
	leal	-12(%edx), %ecx
	cmpw	$2, 6(%eax)
	je	L1271
	fldl	4(%ecx)
	fnstcw	-2(%ebp)
	movzwl	-2(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -4(%ebp)
	fldcw	-4(%ebp)
	fistpll	4(%ecx)
	fldcw	-2(%ebp)
L1269:
	int3
	leave
	ret
	.align 4,0x90
L1271:
	movl	$0, 4(%ecx)
	movl	$0, 8(%ecx)
	jmp	L1269
	.align 4,0x90
_jc1_INCAST:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	int3
	movl	12(%edx), %eax
	leal	12(%edx), %ecx
	cmpw	$2, 6(%eax)
	je	L1277
	fldl	4(%ecx)
	fnstcw	-2(%ebp)
	movzwl	-2(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -4(%ebp)
	fldcw	-4(%ebp)
	fistpll	4(%ecx)
	fldcw	-2(%ebp)
L1275:
	int3
	leave
	ret
	.align 4,0x90
L1277:
	movl	$0, 4(%ecx)
	movl	$0, 8(%ecx)
	jmp	L1275
	.const
	.align 4
LC9:
	.long	0
	.long	1106247680
	.long	0
	.long	0
	.align 4
LC10:
	.long	0
	.long	1105199104
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc0_FCAST:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	call	L1280
"L00000000012$pb":
L1280:
	popl	%ecx
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	int3
	subl	$12, %edx
	movl	4(%edx), %esi
	movl	8(%edx), %edi
	leal	-2147483648(%esi), %eax
	cvtsi2sd	%edi, %xmm1
	movd	%eax, %xmm0
	mulsd	LC9-"L00000000012$pb"(%ecx), %xmm1
	cvtdq2pd	%xmm0, %xmm0
	addsd	LC10-"L00000000012$pb"(%ecx), %xmm0
	addsd	%xmm1, %xmm0
	movapd	%xmm0, -24(%ebp)
	fldl	-24(%ebp)
	fstpl	4(%edx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.const
	.align 4
LC11:
	.long	0
	.long	1106247680
	.long	0
	.long	0
	.align 4
LC12:
	.long	0
	.long	1105199104
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc1_FCAST:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	call	L1283
"L00000000013$pb":
L1283:
	popl	%ecx
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	int3
	addl	$12, %edx
	movl	4(%edx), %esi
	movl	8(%edx), %edi
	leal	-2147483648(%esi), %eax
	cvtsi2sd	%edi, %xmm1
	movd	%eax, %xmm0
	mulsd	LC11-"L00000000013$pb"(%ecx), %xmm1
	cvtdq2pd	%xmm0, %xmm0
	addsd	LC12-"L00000000013$pb"(%ecx), %xmm0
	addsd	%xmm1, %xmm0
	movapd	%xmm0, -24(%ebp)
	fldl	-24(%ebp)
	fstpl	4(%edx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.const
	.align 4
LC14:
	.long	0
	.long	1106247680
	.long	0
	.long	0
	.align 4
LC15:
	.long	0
	.long	1105199104
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc0_FNCAST:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	call	L1290
"L00000000014$pb":
L1290:
	popl	%ebx
	int3
	movl	-12(%edx), %eax
	leal	-12(%edx), %ecx
	cmpw	$2, 6(%eax)
	je	L1289
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	subl	$2147483648, %eax
	cvtsi2sd	%edx, %xmm1
	movd	%eax, %xmm0
	mulsd	LC14-"L00000000014$pb"(%ebx), %xmm1
	cvtdq2pd	%xmm0, %xmm0
	addsd	LC15-"L00000000014$pb"(%ebx), %xmm0
	addsd	%xmm1, %xmm0
	movapd	%xmm0, -24(%ebp)
	fldl	-24(%ebp)
	fstpl	4(%ecx)
L1287:
	int3
	addl	$20, %esp
	popl	%ebx
	leave
	ret
	.align 4,0x90
L1289:
	movl	$0, 4(%ecx)
	movl	$0, 8(%ecx)
	jmp	L1287
	.const
	.align 4
LC17:
	.long	0
	.long	1106247680
	.long	0
	.long	0
	.align 4
LC18:
	.long	0
	.long	1105199104
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc1_FNCAST:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	call	L1297
"L00000000015$pb":
L1297:
	popl	%ebx
	int3
	movl	12(%edx), %eax
	leal	12(%edx), %ecx
	cmpw	$2, 6(%eax)
	je	L1296
	movl	4(%ecx), %eax
	movl	8(%ecx), %edx
	subl	$2147483648, %eax
	cvtsi2sd	%edx, %xmm1
	movd	%eax, %xmm0
	mulsd	LC17-"L00000000015$pb"(%ebx), %xmm1
	cvtdq2pd	%xmm0, %xmm0
	addsd	LC18-"L00000000015$pb"(%ebx), %xmm0
	addsd	%xmm1, %xmm0
	movapd	%xmm0, -24(%ebp)
	fldl	-24(%ebp)
	fstpl	4(%ecx)
L1294:
	int3
	addl	$20, %esp
	popl	%ebx
	leave
	ret
	.align 4,0x90
L1296:
	movl	$0, 4(%ecx)
	movl	$0, 8(%ecx)
	jmp	L1294
	.align 4,0x90
_jc0_BNOT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	subl	$12, %edx
	xorl	%eax, %eax
	cmpl	$0, 4(%edx)
	sete	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_BNOT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	cmpl	$0, -8(%edx)
	sete	%al
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_BNOT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	cmpl	$0, 28(%edx)
	sete	%al
	movl	%eax, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc0_INEG:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	negl	-8(%edx)
	adcl	$0, -4(%edx)
	negl	-4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_INEG:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-8(%edx), %esi
	movl	-4(%edx), %edi
	negl	%esi
	adcl	$0, %edi
	negl	%edi
	movl	%esi, 16(%edx)
	movl	%edi, 20(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_INEG:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %esi
	movl	32(%edx), %edi
	negl	%esi
	adcl	$0, %edi
	negl	%edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_IADD:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	subl	$12, %edx
	movl	4(%edx), %esi
	movl	8(%edx), %edi
	shldl	$1, %esi, %edi
	addl	%esi, %esi
	movl	%esi, 4(%edx)
	movl	%edi, 8(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc1_IADD:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-8(%edx), %esi
	movl	-4(%edx), %edi
	shldl	$1, %esi, %edi
	addl	%esi, %esi
	movl	%esi, 16(%edx)
	movl	%edi, 20(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_IADD:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %esi
	movl	32(%edx), %edi
	addl	%esi, -8(%edx)
	adcl	%edi, -4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc3_IADD:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	leal	-12(%edx), %eax
	movl	4(%eax), %esi
	movl	8(%eax), %edi
	addl	40(%edx), %esi
	adcl	44(%edx), %edi
	movl	%esi, 4(%eax)
	movl	%edi, 8(%eax)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_IADDN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	addl	$-1, -8(%edx)
	adcl	$-1, -4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_IADDN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-8(%edx), %esi
	movl	-4(%edx), %edi
	addl	$-1, %esi
	adcl	$-1, %edi
	movl	%esi, 16(%edx)
	movl	%edi, 20(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_IADDN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %esi
	movl	32(%edx), %edi
	addl	$-1, %esi
	adcl	$-1, %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc3_IADDN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	addl	$3, -8(%edx)
	adcl	$0, -4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc0_ISUB:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, -8(%edx)
	movl	$0, -4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_ISUB:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, 16(%edx)
	movl	$0, 20(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_ISUB:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %ecx
	movl	28(%edx), %eax
	movl	32(%edx), %edx
	subl	4(%ecx), %eax
	sbbl	8(%ecx), %edx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	leave
	ret
	.align 4,0x90
_jc3_ISUB:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	leal	-12(%edx), %eax
	movl	4(%eax), %esi
	movl	8(%eax), %edi
	subl	40(%edx), %esi
	sbbl	44(%edx), %edi
	movl	%esi, 4(%eax)
	movl	%edi, 8(%eax)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_ISUBN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	addl	$1, -8(%edx)
	adcl	$0, -4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_ISUBN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-8(%edx), %esi
	movl	-4(%edx), %edi
	addl	$1, %esi
	adcl	$0, %edi
	movl	%esi, 16(%edx)
	movl	%edi, 20(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_ISUBN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %esi
	movl	32(%edx), %edi
	addl	$1, %esi
	adcl	$0, %edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc3_ISUBN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	addl	$-3, -8(%edx)
	adcl	$-1, -4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc0_IMUL:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	int3
	subl	$12, %edx
	movl	%edx, -20(%ebp)
	movl	4(%edx), %esi
	movl	8(%edx), %edi
	movl	%esi, %eax
	movl	%esi, %ecx
	mull	%esi
	imull	%edi, %ecx
	movl	%eax, -16(%ebp)
	leal	(%ecx,%edx), %eax
	movl	-16(%ebp), %edx
	leal	(%eax,%ecx), %ecx
	movl	-20(%ebp), %eax
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %ecx
	movl	%edx, 4(%eax)
	movl	%ecx, 8(%eax)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc1_IMUL:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	%edx, -20(%ebp)
	int3
	movl	-8(%edx), %esi
	movl	-4(%edx), %edi
	movl	%esi, %eax
	movl	%esi, %ecx
	mull	%esi
	imull	%edi, %ecx
	movl	%eax, -16(%ebp)
	leal	(%ecx,%edx), %eax
	movl	-16(%ebp), %edx
	leal	(%eax,%ecx), %ecx
	movl	-20(%ebp), %eax
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %ecx
	movl	%edx, 16(%eax)
	movl	%ecx, 20(%eax)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc2_IMUL:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	%edx, -16(%ebp)
	int3
	subl	$12, %edx
	movl	-16(%ebp), %ecx
	movl	%edx, -12(%ebp)
	movl	4(%edx), %eax
	movl	%eax, -20(%ebp)
	mull	28(%ecx)
	movl	%edx, %edi
	movl	-12(%ebp), %edx
	movl	%eax, %esi
	movl	28(%ecx), %eax
	imull	8(%edx), %eax
	movl	-20(%ebp), %edx
	imull	32(%ecx), %edx
	movl	-12(%ebp), %ecx
	addl	%edi, %eax
	leal	(%eax,%edx), %edi
	movl	%esi, 4(%ecx)
	movl	%edi, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc3_IMUL:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	%edx, -16(%ebp)
	int3
	movl	-16(%ebp), %eax
	subl	$12, %edx
	movl	%edx, -12(%ebp)
	movl	%edx, %ecx
	movl	40(%eax), %eax
	movl	%eax, -20(%ebp)
	mull	4(%edx)
	movl	%edx, %edi
	movl	-16(%ebp), %edx
	movl	%eax, %esi
	movl	4(%ecx), %eax
	imull	44(%edx), %eax
	movl	-20(%ebp), %edx
	imull	8(%ecx), %edx
	movl	%esi, 4(%ecx)
	addl	%edi, %eax
	leal	(%eax,%edx), %edi
	movl	%edi, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_IMULN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	leal	-12(%edx), %ecx
	movl	$-1, %esi
	movl	4(%ecx), %eax
	mull	%esi
	movl	%eax, %esi
	movl	%edx, %eax
	subl	4(%ecx), %eax
	movl	%esi, 4(%ecx)
	movl	%eax, %edi
	subl	8(%ecx), %edi
	movl	%edi, 8(%ecx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc1_IMULN:
	pushl	%ebp
	movl	%edx, %ecx
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-8(%edx), %eax
	movl	$-1, %esi
	mull	%esi
	movl	%eax, %esi
	movl	%edx, %eax
	subl	-8(%ecx), %eax
	movl	%esi, 16(%ecx)
	movl	%eax, %edi
	subl	-4(%ecx), %edi
	movl	%edi, 20(%ecx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_IMULN:
	pushl	%ebp
	movl	%edx, %ecx
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %eax
	movl	$-1, %esi
	mull	%esi
	movl	%eax, %esi
	movl	%edx, %eax
	subl	28(%ecx), %eax
	movl	%esi, -8(%ecx)
	movl	%eax, %edi
	subl	32(%ecx), %edi
	movl	%edi, -4(%ecx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc3_IMULN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	subl	$12, %edx
	movl	4(%edx), %esi
	movl	8(%edx), %edi
	shldl	$1, %esi, %edi
	addl	%esi, %esi
	addl	4(%edx), %esi
	adcl	8(%edx), %edi
	movl	%esi, 4(%edx)
	movl	%edi, 8(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_IDIV:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$20, %esp
	int3
	leal	-12(%edx), %esi
	movl	4(%esi), %eax
	movl	8(%esi), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L___divdi3$stub
	movl	%eax, 4(%esi)
	movl	%edx, 8(%esi)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc1_IDIV:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%edx, %esi
	subl	$20, %esp
	int3
	movl	-8(%edx), %eax
	movl	-4(%edx), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L___divdi3$stub
	movl	%eax, 16(%esi)
	movl	%edx, 20(%esi)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc2_IDIV:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, -12(%ebp)
	movl	4(%eax), %esi
	movl	8(%eax), %edi
	movl	%esi, 8(%esp)
	movl	%edi, 12(%esp)
	movl	28(%edx), %eax
	movl	32(%edx), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L___divdi3$stub
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc3_IDIV:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$20, %esp
	int3
	movl	40(%edx), %eax
	leal	-12(%edx), %esi
	movl	44(%edx), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	4(%esi), %eax
	movl	8(%esi), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L___divdi3$stub
	movl	%eax, 4(%esi)
	movl	%edx, 8(%esi)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc0_IDIVN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	negl	-8(%edx)
	adcl	$0, -4(%edx)
	negl	-4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_IDIVN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-8(%edx), %esi
	movl	-4(%edx), %edi
	negl	%esi
	adcl	$0, %edi
	negl	%edi
	movl	%esi, 16(%edx)
	movl	%edi, 20(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_IDIVN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %esi
	movl	32(%edx), %edi
	negl	%esi
	adcl	$0, %edi
	negl	%edi
	movl	%esi, -8(%edx)
	movl	%edi, -4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc3_IDIVN:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$20, %esp
	int3
	leal	-12(%edx), %esi
	movl	4(%esi), %eax
	movl	8(%esi), %edx
	movl	$3, 8(%esp)
	movl	$0, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L___divdi3$stub
	movl	%eax, 4(%esi)
	movl	%edx, 8(%esi)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc0_IMOD:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$20, %esp
	int3
	leal	-12(%edx), %esi
	movl	4(%esi), %eax
	movl	8(%esi), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L___moddi3$stub
	movl	%eax, 4(%esi)
	movl	%edx, 8(%esi)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc1_IMOD:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	%edx, %esi
	subl	$20, %esp
	int3
	movl	-8(%edx), %eax
	movl	-4(%edx), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L___moddi3$stub
	movl	%eax, 16(%esi)
	movl	%edx, 20(%esi)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc2_IMOD:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, %ecx
	movl	%eax, -12(%ebp)
	movl	28(%edx), %esi
	movl	32(%edx), %edi
	movl	4(%eax), %eax
	movl	8(%ecx), %edx
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	call	L___moddi3$stub
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	%edx, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc3_IMOD:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	subl	$20, %esp
	int3
	movl	40(%edx), %eax
	leal	-12(%edx), %edi
	movl	44(%edx), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	4(%edi), %eax
	movl	8(%edi), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L___moddi3$stub
	movl	%eax, 4(%edi)
	movl	%edx, 8(%edi)
	int3
	addl	$20, %esp
	popl	%edi
	leave
	ret
	.align 4,0x90
_jc0_IMODN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, -8(%edx)
	movl	$0, -4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_IMODN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, 16(%edx)
	movl	$0, 20(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_IMODN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, -8(%edx)
	movl	$0, -4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc3_IMODN:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$20, %esp
	int3
	leal	-12(%edx), %esi
	movl	4(%esi), %eax
	movl	8(%esi), %edx
	movl	$3, 8(%esp)
	movl	$0, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	L___moddi3$stub
	movl	%eax, 4(%esi)
	movl	%edx, 8(%esi)
	int3
	addl	$20, %esp
	popl	%esi
	leave
	ret
	.align 4,0x90
_jc0_IEQ:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$1, -8(%edx)
	movl	$0, -4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_IEQ:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$1, 16(%edx)
	movl	$0, 20(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_IEQ:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %ecx
	leal	-12(%edx), %esi
	movl	32(%edx), %edi
	movl	%ecx, %eax
	movl	%edi, %edx
	xorl	4(%esi), %eax
	xorl	8(%esi), %edx
	movl	$0, 8(%esi)
	orl	%edx, %eax
	sete	%cl
	movzbl	%cl, %eax
	movl	%eax, 4(%esi)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc3_IEQ:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, %ecx
	movl	%eax, -12(%ebp)
	movl	4(%eax), %eax
	movl	8(%ecx), %ecx
	movl	%eax, %esi
	movl	%ecx, %edi
	xorl	40(%edx), %esi
	xorl	44(%edx), %edi
	orl	%edi, %esi
	sete	%cl
	movzbl	%cl, %eax
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	$0, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_IEQN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	subl	$12, %edx
	movl	4(%edx), %eax
	andl	8(%edx), %eax
	movl	$0, 8(%edx)
	incl	%eax
	sete	%al
	movzbl	%al, %esi
	movl	%esi, 4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc1_IEQN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-8(%edx), %eax
	andl	-4(%edx), %eax
	movl	$0, 20(%edx)
	incl	%eax
	sete	%al
	movzbl	%al, %esi
	movl	%esi, 16(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_IEQN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %eax
	andl	32(%edx), %eax
	movl	$0, -4(%edx)
	incl	%eax
	sete	%al
	movzbl	%al, %esi
	movl	%esi, -8(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc3_IEQN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	subl	$12, %edx
	movl	4(%edx), %esi
	movl	8(%edx), %edi
	movl	$0, 8(%edx)
	xorl	$3, %esi
	orl	%edi, %esi
	sete	%al
	movzbl	%al, %esi
	movl	%esi, 4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_INEQ:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, -8(%edx)
	movl	$0, -4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_INEQ:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, 16(%edx)
	movl	$0, 20(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_INEQ:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %ecx
	leal	-12(%edx), %esi
	movl	32(%edx), %edi
	movl	%ecx, %eax
	movl	%edi, %edx
	xorl	4(%esi), %eax
	xorl	8(%esi), %edx
	movl	$0, 8(%esi)
	orl	%edx, %eax
	setne	%cl
	movzbl	%cl, %eax
	movl	%eax, 4(%esi)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc3_INEQ:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	int3
	leal	-12(%edx), %eax
	movl	%eax, %ecx
	movl	%eax, -12(%ebp)
	movl	4(%eax), %eax
	movl	8(%ecx), %ecx
	movl	%eax, %esi
	movl	%ecx, %edi
	xorl	40(%edx), %esi
	xorl	44(%edx), %edi
	orl	%edi, %esi
	setne	%cl
	movzbl	%cl, %eax
	movl	-12(%ebp), %ecx
	movl	%eax, 4(%ecx)
	movl	$0, 8(%ecx)
	int3
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.align 4,0x90
_jc0_INEQN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	subl	$12, %edx
	movl	4(%edx), %eax
	andl	8(%edx), %eax
	movl	$0, 8(%edx)
	incl	%eax
	setne	%al
	movzbl	%al, %esi
	movl	%esi, 4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc1_INEQN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	-8(%edx), %eax
	andl	-4(%edx), %eax
	movl	$0, 20(%edx)
	incl	%eax
	setne	%al
	movzbl	%al, %esi
	movl	%esi, 16(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc2_INEQN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	movl	28(%edx), %eax
	andl	32(%edx), %eax
	movl	$0, -4(%edx)
	incl	%eax
	setne	%al
	movzbl	%al, %esi
	movl	%esi, -8(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc3_INEQN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	subl	$12, %edx
	movl	4(%edx), %esi
	movl	8(%edx), %edi
	movl	$0, 8(%edx)
	xorl	$3, %esi
	orl	%edi, %esi
	setne	%al
	movzbl	%al, %esi
	movl	%esi, 4(%edx)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
_jc0_ILT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_ILT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_ILT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	int3
	leal	-12(%edx), %ecx
	movl	28(%edx), %eax
	movl	$1, %esi
	movl	32(%edx), %edx
	cmpl	8(%ecx), %edx
	jl	L1427
	jle	L1430
L1428:
	xorl	%esi, %esi
L1427:
	movl	%esi, 4(%ecx)
	int3
	popl	%esi
	leave
	ret
	.align 4,0x90
L1430:
	cmpl	4(%ecx), %eax
	jb	L1427
	jmp	L1428
	.align 4,0x90
_jc3_ILT:
	pushl	%ebp
	movl	%edx, %ecx
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	leal	-12(%edx), %esi
	movl	$1, %edi
	movl	8(%esi), %edx
	cmpl	44(%ecx), %edx
	movl	4(%esi), %eax
	jl	L1432
	jle	L1435
L1433:
	xorl	%edi, %edi
L1432:
	movl	%edi, 4(%esi)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
L1435:
	cmpl	40(%ecx), %eax
	jb	L1432
	jmp	L1433
	.align 4,0x90
_jc0_ILTN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movl	$1, %edx
	cmpl	$-1, 8(%eax)
	jl	L1437
	jle	L1440
L1438:
	xorl	%edx, %edx
L1437:
	movl	%edx, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1440:
	cmpl	$-1, 4(%eax)
	jb	L1437
	jmp	L1438
	.align 4,0x90
_jc1_ILTN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	cmpl	$-1, -4(%edx)
	movl	$1, %eax
	jl	L1442
	jle	L1445
L1443:
	xorl	%eax, %eax
L1442:
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
L1445:
	cmpl	$-1, -8(%edx)
	jb	L1442
	jmp	L1443
	.align 4,0x90
_jc2_ILTN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	cmpl	$-1, 32(%edx)
	movl	$1, %eax
	jl	L1447
	jle	L1450
L1448:
	xorl	%eax, %eax
L1447:
	movl	%eax, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
L1450:
	cmpl	$-1, 28(%edx)
	jb	L1447
	jmp	L1448
	.align 4,0x90
_jc3_ILTN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movl	$1, %edx
	cmpl	$0, 8(%eax)
	jl	L1452
	jle	L1455
L1453:
	xorl	%edx, %edx
L1452:
	movl	%edx, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1455:
	cmpl	$2, 4(%eax)
	jbe	L1452
	jmp	L1453
	.align 4,0x90
_jc0_ILTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$1, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_ILTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$1, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_ILTE:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	int3
	leal	-12(%edx), %ecx
	movl	28(%edx), %eax
	movl	$1, %esi
	movl	32(%edx), %edx
	cmpl	8(%ecx), %edx
	jl	L1461
	jle	L1464
L1462:
	xorl	%esi, %esi
L1461:
	movl	%esi, 4(%ecx)
	int3
	popl	%esi
	leave
	ret
	.align 4,0x90
L1464:
	cmpl	4(%ecx), %eax
	jbe	L1461
	jmp	L1462
	.align 4,0x90
_jc3_ILTE:
	pushl	%ebp
	movl	%edx, %ecx
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	leal	-12(%edx), %esi
	movl	$1, %edi
	movl	8(%esi), %edx
	cmpl	44(%ecx), %edx
	movl	4(%esi), %eax
	jl	L1466
	jle	L1469
L1467:
	xorl	%edi, %edi
L1466:
	movl	%edi, 4(%esi)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
L1469:
	cmpl	40(%ecx), %eax
	jbe	L1466
	jmp	L1467
	.align 4,0x90
_jc0_ILTEN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	subl	$12, %edx
	movl	8(%edx), %eax
	shrl	$31, %eax
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_ILTEN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-4(%edx), %eax
	shrl	$31, %eax
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_ILTEN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	32(%edx), %eax
	shrl	$31, %eax
	movl	%eax, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc3_ILTEN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movl	$1, %edx
	cmpl	$0, 8(%eax)
	jl	L1477
	jle	L1480
L1478:
	xorl	%edx, %edx
L1477:
	movl	%edx, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1480:
	cmpl	$3, 4(%eax)
	jbe	L1477
	jmp	L1478
	.align 4,0x90
_jc0_IGT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_IGT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_IGT:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	int3
	leal	-12(%edx), %ecx
	movl	28(%edx), %eax
	movl	$1, %esi
	movl	32(%edx), %edx
	cmpl	8(%ecx), %edx
	jg	L1486
	jge	L1489
L1487:
	xorl	%esi, %esi
L1486:
	movl	%esi, 4(%ecx)
	int3
	popl	%esi
	leave
	ret
	.align 4,0x90
L1489:
	cmpl	4(%ecx), %eax
	ja	L1486
	jmp	L1487
	.align 4,0x90
_jc3_IGT:
	pushl	%ebp
	movl	%edx, %ecx
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	leal	-12(%edx), %esi
	movl	$1, %edi
	movl	8(%esi), %edx
	cmpl	44(%ecx), %edx
	movl	4(%esi), %eax
	jg	L1491
	jge	L1494
L1492:
	xorl	%edi, %edi
L1491:
	movl	%edi, 4(%esi)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
L1494:
	cmpl	40(%ecx), %eax
	ja	L1491
	jmp	L1492
	.align 4,0x90
_jc0_IGTN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	subl	$12, %edx
	movl	8(%edx), %eax
	notl	%eax
	shrl	$31, %eax
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_IGTN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	-4(%edx), %eax
	notl	%eax
	shrl	$31, %eax
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_IGTN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	32(%edx), %eax
	notl	%eax
	shrl	$31, %eax
	movl	%eax, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc3_IGTN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movl	$1, %edx
	cmpl	$0, 8(%eax)
	jle	L1505
L1502:
	movl	%edx, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1505:
	jl	L1503
	cmpl	$3, 4(%eax)
	ja	L1502
L1503:
	xorl	%edx, %edx
	jmp	L1502
	.align 4,0x90
_jc0_IGTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$1, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_IGTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$1, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_IGTE:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	int3
	leal	-12(%edx), %ecx
	movl	28(%edx), %eax
	movl	$1, %esi
	movl	32(%edx), %edx
	cmpl	8(%ecx), %edx
	jg	L1511
	jge	L1514
L1512:
	xorl	%esi, %esi
L1511:
	movl	%esi, 4(%ecx)
	int3
	popl	%esi
	leave
	ret
	.align 4,0x90
L1514:
	cmpl	4(%ecx), %eax
	jae	L1511
	jmp	L1512
	.align 4,0x90
_jc3_IGTE:
	pushl	%ebp
	movl	%edx, %ecx
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	int3
	leal	-12(%edx), %esi
	movl	$1, %edi
	movl	8(%esi), %edx
	cmpl	44(%ecx), %edx
	movl	4(%esi), %eax
	jg	L1516
	jge	L1519
L1517:
	xorl	%edi, %edi
L1516:
	movl	%edi, 4(%esi)
	int3
	movl	(%esp), %esi
	movl	4(%esp), %edi
	leave
	ret
	.align 4,0x90
L1519:
	cmpl	40(%ecx), %eax
	jae	L1516
	jmp	L1517
	.align 4,0x90
_jc0_IGTEN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movl	$1, %edx
	cmpl	$-1, 8(%eax)
	jle	L1524
L1521:
	movl	%edx, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1524:
	jl	L1522
	cmpl	$-1, 4(%eax)
	jae	L1521
L1522:
	xorl	%edx, %edx
	jmp	L1521
	.align 4,0x90
_jc1_IGTEN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	cmpl	$-1, -4(%edx)
	movl	$1, %eax
	jle	L1529
L1526:
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
L1529:
	jl	L1527
	cmpl	$-1, -8(%edx)
	jae	L1526
L1527:
	xorl	%eax, %eax
	jmp	L1526
	.align 4,0x90
_jc2_IGTEN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	cmpl	$-1, 32(%edx)
	movl	$1, %eax
	jle	L1534
L1531:
	movl	%eax, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
L1534:
	jl	L1532
	cmpl	$-1, 28(%edx)
	jae	L1531
L1532:
	xorl	%eax, %eax
	jmp	L1531
	.align 4,0x90
_jc3_IGTEN:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movl	$1, %edx
	cmpl	$0, 8(%eax)
	jle	L1539
L1536:
	movl	%edx, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1539:
	jl	L1537
	cmpl	$2, 4(%eax)
	ja	L1536
L1537:
	xorl	%edx, %edx
	jmp	L1536
	.const
	.align 4
LC19:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc0_FNEG:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	L1542
"L00000000016$pb":
L1542:
	popl	%ecx
	int3
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	xorpd	LC19-"L00000000016$pb"(%ecx), %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.const
	.align 4
LC20:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc1_FNEG:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	L1545
"L00000000017$pb":
L1545:
	popl	%ecx
	int3
	movsd	-8(%edx), %xmm0
	xorpd	LC20-"L00000000017$pb"(%ecx), %xmm0
	movsd	%xmm0, 16(%edx)
	int3
	leave
	ret
	.const
	.align 4
LC21:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc2_FNEG:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	L1548
"L00000000018$pb":
L1548:
	popl	%ecx
	int3
	movsd	28(%edx), %xmm0
	xorpd	LC21-"L00000000018$pb"(%ecx), %xmm0
	movsd	%xmm0, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc0_FADD:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	addsd	%xmm0, %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_FADD:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movsd	-8(%edx), %xmm0
	addsd	%xmm0, %xmm0
	movsd	%xmm0, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_FADD:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movsd	28(%edx), %xmm0
	addsd	4(%eax), %xmm0
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
_jc3_FADD:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movsd	4(%eax), %xmm0
	addsd	40(%edx), %xmm0
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.literal8
	.align 3
LC22:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc0_FADDN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1559
"L00000000019$pb":
L1559:
	popl	%ecx
	int3
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	subsd	LC22-"L00000000019$pb"(%ecx), %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC23:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc1_FADDN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1562
"L00000000020$pb":
L1562:
	popl	%ecx
	int3
	movsd	-8(%edx), %xmm0
	subsd	LC23-"L00000000020$pb"(%ecx), %xmm0
	movsd	%xmm0, 16(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC24:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc2_FADDN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1565
"L00000000021$pb":
L1565:
	popl	%ecx
	int3
	movsd	28(%edx), %xmm0
	subsd	LC24-"L00000000021$pb"(%ecx), %xmm0
	movsd	%xmm0, -8(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC25:
	.long	0
	.long	1074266112
	.text
	.align 4,0x90
_jc3_FADDN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1568
"L00000000022$pb":
L1568:
	popl	%ecx
	int3
	subl	$12, %edx
	movsd	LC25-"L00000000022$pb"(%ecx), %xmm0
	addsd	4(%edx), %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc0_FSUB:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	subsd	%xmm0, %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_FSUB:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movsd	-8(%edx), %xmm0
	subsd	%xmm0, %xmm0
	movsd	%xmm0, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_FSUB:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movsd	28(%edx), %xmm0
	subsd	4(%eax), %xmm0
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
_jc3_FSUB:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movsd	4(%eax), %xmm0
	subsd	40(%edx), %xmm0
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.literal8
	.align 3
LC26:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc0_FSUBN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1579
"L00000000023$pb":
L1579:
	popl	%ecx
	int3
	subl	$12, %edx
	movsd	LC26-"L00000000023$pb"(%ecx), %xmm0
	addsd	4(%edx), %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC27:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc1_FSUBN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1582
"L00000000024$pb":
L1582:
	popl	%ecx
	int3
	movsd	LC27-"L00000000024$pb"(%ecx), %xmm0
	addsd	-8(%edx), %xmm0
	movsd	%xmm0, 16(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC28:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc2_FSUBN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1585
"L00000000025$pb":
L1585:
	popl	%ecx
	int3
	movsd	LC28-"L00000000025$pb"(%ecx), %xmm0
	addsd	28(%edx), %xmm0
	movsd	%xmm0, -8(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC29:
	.long	0
	.long	1074266112
	.text
	.align 4,0x90
_jc3_FSUBN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1588
"L00000000026$pb":
L1588:
	popl	%ecx
	int3
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	subsd	LC29-"L00000000026$pb"(%ecx), %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc0_FMUL:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	mulsd	%xmm0, %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_FMUL:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movsd	-8(%edx), %xmm0
	mulsd	%xmm0, %xmm0
	movsd	%xmm0, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_FMUL:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movsd	28(%edx), %xmm0
	mulsd	4(%eax), %xmm0
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
_jc3_FMUL:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movsd	4(%eax), %xmm0
	mulsd	40(%edx), %xmm0
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.const
	.align 4
LC30:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc0_FMULN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	L1599
"L00000000027$pb":
L1599:
	popl	%ecx
	int3
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	xorpd	LC30-"L00000000027$pb"(%ecx), %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.const
	.align 4
LC31:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc1_FMULN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	L1602
"L00000000028$pb":
L1602:
	popl	%ecx
	int3
	movsd	-8(%edx), %xmm0
	xorpd	LC31-"L00000000028$pb"(%ecx), %xmm0
	movsd	%xmm0, 16(%edx)
	int3
	leave
	ret
	.const
	.align 4
LC32:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc2_FMULN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	L1605
"L00000000029$pb":
L1605:
	popl	%ecx
	int3
	movsd	28(%edx), %xmm0
	xorpd	LC32-"L00000000029$pb"(%ecx), %xmm0
	movsd	%xmm0, -8(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC33:
	.long	0
	.long	1074266112
	.text
	.align 4,0x90
_jc3_FMULN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1608
"L00000000030$pb":
L1608:
	popl	%ecx
	int3
	subl	$12, %edx
	movsd	LC33-"L00000000030$pb"(%ecx), %xmm0
	mulsd	4(%edx), %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc0_FDIV:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	divsd	%xmm0, %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_FDIV:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movsd	-8(%edx), %xmm0
	divsd	%xmm0, %xmm0
	movsd	%xmm0, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_FDIV:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movsd	28(%edx), %xmm0
	divsd	4(%eax), %xmm0
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
_jc3_FDIV:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	leal	-12(%edx), %eax
	movsd	4(%eax), %xmm0
	divsd	40(%edx), %xmm0
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.const
	.align 4
LC34:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc0_FDIVN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	L1619
"L00000000031$pb":
L1619:
	popl	%ecx
	int3
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	xorpd	LC34-"L00000000031$pb"(%ecx), %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.const
	.align 4
LC35:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc1_FDIVN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	L1622
"L00000000032$pb":
L1622:
	popl	%ecx
	int3
	movsd	-8(%edx), %xmm0
	xorpd	LC35-"L00000000032$pb"(%ecx), %xmm0
	movsd	%xmm0, 16(%edx)
	int3
	leave
	ret
	.const
	.align 4
LC36:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
	.align 4,0x90
_jc2_FDIVN:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	L1625
"L00000000033$pb":
L1625:
	popl	%ecx
	int3
	movsd	28(%edx), %xmm0
	xorpd	LC36-"L00000000033$pb"(%ecx), %xmm0
	movsd	%xmm0, -8(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC37:
	.long	0
	.long	1074266112
	.text
	.align 4,0x90
_jc3_FDIVN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1628
"L00000000034$pb":
L1628:
	popl	%ecx
	int3
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	divsd	LC37-"L00000000034$pb"(%ecx), %xmm0
	movsd	%xmm0, 4(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC38:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc0_FEQ:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1635
"L00000000035$pb":
L1635:
	popl	%ecx
	int3
	leal	-12(%edx), %eax
	movsd	4(%eax), %xmm0
	ucomisd	%xmm0, %xmm0
	jne	L1630
	jp	L1630
	movsd	LC38-"L00000000035$pb"(%ecx), %xmm0
L1633:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1630:
	xorpd	%xmm0, %xmm0
	jmp	L1633
	.literal8
	.align 3
LC40:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc1_FEQ:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1642
"L00000000036$pb":
L1642:
	popl	%ecx
	int3
	movsd	-8(%edx), %xmm0
	leal	12(%edx), %eax
	ucomisd	%xmm0, %xmm0
	jne	L1637
	jp	L1637
	movsd	LC40-"L00000000036$pb"(%ecx), %xmm0
L1640:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1637:
	xorpd	%xmm0, %xmm0
	jmp	L1640
	.literal8
	.align 3
LC42:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc2_FEQ:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1649
"L00000000037$pb":
L1649:
	popl	%ecx
	int3
	leal	-12(%edx), %eax
	movsd	28(%edx), %xmm0
	ucomisd	4(%eax), %xmm0
	jne	L1644
	jp	L1644
	movsd	LC42-"L00000000037$pb"(%ecx), %xmm0
L1647:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1644:
	xorpd	%xmm0, %xmm0
	jmp	L1647
	.literal8
	.align 3
LC44:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc3_FEQ:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1656
"L00000000038$pb":
L1656:
	popl	%ecx
	int3
	leal	-12(%edx), %eax
	movsd	4(%eax), %xmm0
	ucomisd	40(%edx), %xmm0
	jne	L1651
	jp	L1651
	movsd	LC44-"L00000000038$pb"(%ecx), %xmm0
L1654:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1651:
	xorpd	%xmm0, %xmm0
	jmp	L1654
	.literal8
	.align 3
LC46:
	.long	0
	.long	-1074790400
	.align 3
LC47:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc0_FEQN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1663
"L00000000039$pb":
L1663:
	popl	%ecx
	int3
	leal	-12(%edx), %eax
	movsd	LC46-"L00000000039$pb"(%ecx), %xmm0
	ucomisd	4(%eax), %xmm0
	jne	L1658
	jp	L1658
	movsd	LC47-"L00000000039$pb"(%ecx), %xmm0
L1661:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1658:
	xorpd	%xmm0, %xmm0
	jmp	L1661
	.literal8
	.align 3
LC49:
	.long	0
	.long	-1074790400
	.align 3
LC50:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc1_FEQN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1670
"L00000000040$pb":
L1670:
	popl	%ecx
	int3
	movsd	LC49-"L00000000040$pb"(%ecx), %xmm0
	leal	12(%edx), %eax
	ucomisd	-8(%edx), %xmm0
	jne	L1665
	jp	L1665
	movsd	LC50-"L00000000040$pb"(%ecx), %xmm0
L1668:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1665:
	xorpd	%xmm0, %xmm0
	jmp	L1668
	.literal8
	.align 3
LC52:
	.long	0
	.long	-1074790400
	.align 3
LC53:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc2_FEQN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1677
"L00000000041$pb":
L1677:
	popl	%ecx
	int3
	movsd	LC52-"L00000000041$pb"(%ecx), %xmm0
	leal	-12(%edx), %eax
	ucomisd	28(%edx), %xmm0
	jne	L1672
	jp	L1672
	movsd	LC53-"L00000000041$pb"(%ecx), %xmm0
L1675:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1672:
	xorpd	%xmm0, %xmm0
	jmp	L1675
	.literal8
	.align 3
LC55:
	.long	0
	.long	1074266112
	.align 3
LC56:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc3_FEQN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1684
"L00000000042$pb":
L1684:
	popl	%ecx
	int3
	leal	-12(%edx), %eax
	movsd	LC55-"L00000000042$pb"(%ecx), %xmm0
	ucomisd	4(%eax), %xmm0
	jne	L1679
	jp	L1679
	movsd	LC56-"L00000000042$pb"(%ecx), %xmm0
L1682:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1679:
	xorpd	%xmm0, %xmm0
	jmp	L1682
	.literal8
	.align 3
LC58:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc0_FNEQ:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1693
"L00000000043$pb":
L1693:
	popl	%ecx
	int3
	leal	-12(%edx), %eax
	movsd	4(%eax), %xmm0
	ucomisd	%xmm0, %xmm0
	jp	L1692
	je	L1686
L1692:
	movsd	LC58-"L00000000043$pb"(%ecx), %xmm0
L1689:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1686:
	xorpd	%xmm0, %xmm0
	jmp	L1689
	.literal8
	.align 3
LC60:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc1_FNEQ:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1702
"L00000000044$pb":
L1702:
	popl	%ecx
	int3
	movsd	-8(%edx), %xmm0
	leal	12(%edx), %eax
	ucomisd	%xmm0, %xmm0
	jp	L1701
	je	L1695
L1701:
	movsd	LC60-"L00000000044$pb"(%ecx), %xmm0
L1698:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1695:
	xorpd	%xmm0, %xmm0
	jmp	L1698
	.literal8
	.align 3
LC62:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc2_FNEQ:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1711
"L00000000045$pb":
L1711:
	popl	%ecx
	int3
	leal	-12(%edx), %eax
	movsd	28(%edx), %xmm0
	ucomisd	4(%eax), %xmm0
	jp	L1710
	je	L1704
L1710:
	movsd	LC62-"L00000000045$pb"(%ecx), %xmm0
L1707:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1704:
	xorpd	%xmm0, %xmm0
	jmp	L1707
	.literal8
	.align 3
LC64:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc3_FNEQ:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1720
"L00000000046$pb":
L1720:
	popl	%ecx
	int3
	leal	-12(%edx), %eax
	movsd	4(%eax), %xmm0
	ucomisd	40(%edx), %xmm0
	jp	L1719
	je	L1713
L1719:
	movsd	LC64-"L00000000046$pb"(%ecx), %xmm0
L1716:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1713:
	xorpd	%xmm0, %xmm0
	jmp	L1716
	.literal8
	.align 3
LC66:
	.long	0
	.long	-1074790400
	.align 3
LC67:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc0_FNEQN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1729
"L00000000047$pb":
L1729:
	popl	%ecx
	int3
	leal	-12(%edx), %eax
	movsd	LC66-"L00000000047$pb"(%ecx), %xmm0
	ucomisd	4(%eax), %xmm0
	jp	L1728
	je	L1722
L1728:
	movsd	LC67-"L00000000047$pb"(%ecx), %xmm0
L1725:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1722:
	xorpd	%xmm0, %xmm0
	jmp	L1725
	.literal8
	.align 3
LC69:
	.long	0
	.long	-1074790400
	.align 3
LC70:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc1_FNEQN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1738
"L00000000048$pb":
L1738:
	popl	%ecx
	int3
	movsd	LC69-"L00000000048$pb"(%ecx), %xmm0
	leal	12(%edx), %eax
	ucomisd	-8(%edx), %xmm0
	jp	L1737
	je	L1731
L1737:
	movsd	LC70-"L00000000048$pb"(%ecx), %xmm0
L1734:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1731:
	xorpd	%xmm0, %xmm0
	jmp	L1734
	.literal8
	.align 3
LC72:
	.long	0
	.long	-1074790400
	.align 3
LC73:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc2_FNEQN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1747
"L00000000049$pb":
L1747:
	popl	%ecx
	int3
	movsd	LC72-"L00000000049$pb"(%ecx), %xmm0
	leal	-12(%edx), %eax
	ucomisd	28(%edx), %xmm0
	jp	L1746
	je	L1740
L1746:
	movsd	LC73-"L00000000049$pb"(%ecx), %xmm0
L1743:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1740:
	xorpd	%xmm0, %xmm0
	jmp	L1743
	.literal8
	.align 3
LC75:
	.long	0
	.long	1074266112
	.align 3
LC76:
	.long	0
	.long	1072693248
	.text
	.align 4,0x90
_jc3_FNEQN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1756
"L00000000050$pb":
L1756:
	popl	%ecx
	int3
	leal	-12(%edx), %eax
	movsd	LC75-"L00000000050$pb"(%ecx), %xmm0
	ucomisd	4(%eax), %xmm0
	jp	L1755
	je	L1749
L1755:
	movsd	LC76-"L00000000050$pb"(%ecx), %xmm0
L1752:
	movsd	%xmm0, 4(%eax)
	int3
	leave
	ret
	.align 4,0x90
L1749:
	xorpd	%xmm0, %xmm0
	jmp	L1752
	.align 4,0x90
_jc0_FLT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_FLT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_FLT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	leal	-12(%edx), %ecx
	movsd	4(%ecx), %xmm0
	ucomisd	28(%edx), %xmm0
	seta	%al
	movl	%eax, 4(%ecx)
	int3
	leave
	ret
	.align 4,0x90
_jc3_FLT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	movsd	40(%edx), %xmm0
	leal	-12(%edx), %ecx
	ucomisd	4(%ecx), %xmm0
	seta	%al
	movl	%eax, 4(%ecx)
	int3
	leave
	ret
	.literal8
	.align 3
LC78:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc0_FLTN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1767
"L00000000051$pb":
L1767:
	popl	%ecx
	int3
	xorl	%eax, %eax
	subl	$12, %edx
	movsd	LC78-"L00000000051$pb"(%ecx), %xmm0
	ucomisd	4(%edx), %xmm0
	seta	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC79:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc1_FLTN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1770
"L00000000052$pb":
L1770:
	popl	%ecx
	int3
	xorl	%eax, %eax
	movsd	LC79-"L00000000052$pb"(%ecx), %xmm0
	ucomisd	-8(%edx), %xmm0
	seta	%al
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC80:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc2_FLTN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1773
"L00000000053$pb":
L1773:
	popl	%ecx
	int3
	xorl	%eax, %eax
	movsd	LC80-"L00000000053$pb"(%ecx), %xmm0
	ucomisd	28(%edx), %xmm0
	seta	%al
	movl	%eax, -8(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC81:
	.long	0
	.long	1074266112
	.text
	.align 4,0x90
_jc3_FLTN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1776
"L00000000054$pb":
L1776:
	popl	%ecx
	int3
	xorl	%eax, %eax
	subl	$12, %edx
	movsd	LC81-"L00000000054$pb"(%ecx), %xmm0
	ucomisd	4(%edx), %xmm0
	seta	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc0_FLTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	ucomisd	%xmm0, %xmm0
	setnp	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_FLTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	movsd	-8(%edx), %xmm0
	ucomisd	%xmm0, %xmm0
	setnp	%al
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_FLTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	leal	-12(%edx), %ecx
	movsd	4(%ecx), %xmm0
	ucomisd	28(%edx), %xmm0
	setae	%al
	movl	%eax, 4(%ecx)
	int3
	leave
	ret
	.align 4,0x90
_jc3_FLTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	movsd	40(%edx), %xmm0
	leal	-12(%edx), %ecx
	ucomisd	4(%ecx), %xmm0
	setae	%al
	movl	%eax, 4(%ecx)
	int3
	leave
	ret
	.literal8
	.align 3
LC82:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc0_FLTEN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1787
"L00000000055$pb":
L1787:
	popl	%ecx
	int3
	xorl	%eax, %eax
	subl	$12, %edx
	movsd	LC82-"L00000000055$pb"(%ecx), %xmm0
	ucomisd	4(%edx), %xmm0
	setae	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC83:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc1_FLTEN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1790
"L00000000056$pb":
L1790:
	popl	%ecx
	int3
	xorl	%eax, %eax
	movsd	LC83-"L00000000056$pb"(%ecx), %xmm0
	ucomisd	-8(%edx), %xmm0
	setae	%al
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC84:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc2_FLTEN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1793
"L00000000057$pb":
L1793:
	popl	%ecx
	int3
	xorl	%eax, %eax
	movsd	LC84-"L00000000057$pb"(%ecx), %xmm0
	ucomisd	28(%edx), %xmm0
	setae	%al
	movl	%eax, -8(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC85:
	.long	0
	.long	1074266112
	.text
	.align 4,0x90
_jc3_FLTEN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1796
"L00000000058$pb":
L1796:
	popl	%ecx
	int3
	xorl	%eax, %eax
	subl	$12, %edx
	movsd	LC85-"L00000000058$pb"(%ecx), %xmm0
	ucomisd	4(%edx), %xmm0
	setae	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc0_FGT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, -8(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_FGT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	movl	$0, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_FGT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	movsd	28(%edx), %xmm0
	leal	-12(%edx), %ecx
	ucomisd	4(%ecx), %xmm0
	seta	%al
	movl	%eax, 4(%ecx)
	int3
	leave
	ret
	.align 4,0x90
_jc3_FGT:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	leal	-12(%edx), %ecx
	movsd	4(%ecx), %xmm0
	ucomisd	40(%edx), %xmm0
	seta	%al
	movl	%eax, 4(%ecx)
	int3
	leave
	ret
	.literal8
	.align 3
LC86:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc0_FGTN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1807
"L00000000059$pb":
L1807:
	popl	%ecx
	int3
	xorl	%eax, %eax
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	ucomisd	LC86-"L00000000059$pb"(%ecx), %xmm0
	seta	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC87:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc1_FGTN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1810
"L00000000060$pb":
L1810:
	popl	%ecx
	int3
	xorl	%eax, %eax
	movsd	-8(%edx), %xmm0
	ucomisd	LC87-"L00000000060$pb"(%ecx), %xmm0
	seta	%al
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC88:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc2_FGTN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1813
"L00000000061$pb":
L1813:
	popl	%ecx
	int3
	xorl	%eax, %eax
	movsd	28(%edx), %xmm0
	ucomisd	LC88-"L00000000061$pb"(%ecx), %xmm0
	seta	%al
	movl	%eax, -8(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC89:
	.long	0
	.long	1074266112
	.text
	.align 4,0x90
_jc3_FGTN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1816
"L00000000062$pb":
L1816:
	popl	%ecx
	int3
	xorl	%eax, %eax
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	ucomisd	LC89-"L00000000062$pb"(%ecx), %xmm0
	seta	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc0_FGTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	ucomisd	%xmm0, %xmm0
	setnp	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc1_FGTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	movsd	-8(%edx), %xmm0
	ucomisd	%xmm0, %xmm0
	setnp	%al
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.align 4,0x90
_jc2_FGTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	movsd	28(%edx), %xmm0
	leal	-12(%edx), %ecx
	ucomisd	4(%ecx), %xmm0
	setae	%al
	movl	%eax, 4(%ecx)
	int3
	leave
	ret
	.align 4,0x90
_jc3_FGTE:
	pushl	%ebp
	movl	%esp, %ebp
	int3
	xorl	%eax, %eax
	leal	-12(%edx), %ecx
	movsd	4(%ecx), %xmm0
	ucomisd	40(%edx), %xmm0
	setae	%al
	movl	%eax, 4(%ecx)
	int3
	leave
	ret
	.literal8
	.align 3
LC90:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc0_FGTEN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1827
"L00000000063$pb":
L1827:
	popl	%ecx
	int3
	xorl	%eax, %eax
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	ucomisd	LC90-"L00000000063$pb"(%ecx), %xmm0
	setae	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC91:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc1_FGTEN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1830
"L00000000064$pb":
L1830:
	popl	%ecx
	int3
	xorl	%eax, %eax
	movsd	-8(%edx), %xmm0
	ucomisd	LC91-"L00000000064$pb"(%ecx), %xmm0
	setae	%al
	movl	%eax, 16(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC92:
	.long	0
	.long	-1074790400
	.text
	.align 4,0x90
_jc2_FGTEN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1833
"L00000000065$pb":
L1833:
	popl	%ecx
	int3
	xorl	%eax, %eax
	movsd	28(%edx), %xmm0
	ucomisd	LC92-"L00000000065$pb"(%ecx), %xmm0
	setae	%al
	movl	%eax, -8(%edx)
	int3
	leave
	ret
	.literal8
	.align 3
LC93:
	.long	0
	.long	1074266112
	.text
	.align 4,0x90
_jc3_FGTEN:
	pushl	%ebp
	movl	%esp, %ebp
	call	L1836
"L00000000066$pb":
L1836:
	popl	%ecx
	int3
	xorl	%eax, %eax
	subl	$12, %edx
	movsd	4(%edx), %xmm0
	ucomisd	LC93-"L00000000066$pb"(%ecx), %xmm0
	setae	%al
	movl	%eax, 4(%edx)
	int3
	leave
	ret
	.align 4,0x90
.globl _konoha_getCodeTemplate
_konoha_getCodeTemplate:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	call	L1839
"L00000000067$pb":
L1839:
	popl	%ecx
	leal	(%eax,%eax,2), %eax
	addl	%eax, %eax
	addl	12(%ebp), %eax
	movl	_codeTempList-"L00000000067$pb"(%ecx,%eax,4), %eax
	leave
	ret
	.section __IMPORT,__jump_table,symbol_stubs,self_modifying_code+pure_instructions,5
L_new_cwb$stub:
	.indirect_symbol _new_cwb
	hlt ; hlt ; hlt ; hlt ; hlt
L___moddi3$stub:
	.indirect_symbol ___moddi3
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_sfp_typecheck$stub:
	.indirect_symbol _knh_sfp_typecheck
	hlt ; hlt ; hlt ; hlt ; hlt
L_KNH_SAFEFILE$stub:
	.indirect_symbol _KNH_SAFEFILE
	hlt ; hlt ; hlt ; hlt ; hlt
L_new_Exception$stub:
	.indirect_symbol _new_Exception
	hlt ; hlt ; hlt ; hlt ; hlt
L___divdi3$stub:
	.indirect_symbol ___divdi3
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_throw__s$stub:
	.indirect_symbol _knh_throw__s
	hlt ; hlt ; hlt ; hlt ; hlt
L_new_Exception__Nue$stub:
	.indirect_symbol _new_Exception__Nue
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_boxing$stub:
	.indirect_symbol _knh_boxing
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_Object_free$stub:
	.indirect_symbol _knh_Object_free
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_Method_ufind$stub:
	.indirect_symbol _knh_Method_ufind
	hlt ; hlt ; hlt ; hlt ; hlt
L___assert_rtn$stub:
	.indirect_symbol ___assert_rtn
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_throwException$stub:
	.indirect_symbol _knh_throwException
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_tMethod_findMT$stub:
	.indirect_symbol _knh_tMethod_findMT
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_tConst_systemValue$stub:
	.indirect_symbol _knh_tConst_systemValue
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_Exception_isa$stub:
	.indirect_symbol _knh_Exception_isa
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_class_instanceof$stub:
	.indirect_symbol _knh_class_instanceof
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_stack_p$stub:
	.indirect_symbol _knh_stack_p
	hlt ; hlt ; hlt ; hlt ; hlt
L_konoha_getClassDefaultValue$stub:
	.indirect_symbol _konoha_getClassDefaultValue
	hlt ; hlt ; hlt ; hlt ; hlt
L_new_String__cwb$stub:
	.indirect_symbol _new_String__cwb
	hlt ; hlt ; hlt ; hlt ; hlt
L_new_Exception__type$stub:
	.indirect_symbol _new_Exception__type
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_Object_opTypeOf$stub:
	.indirect_symbol _knh_Object_opTypeOf
	hlt ; hlt ; hlt ; hlt ; hlt
L_new_Object_init$stub:
	.indirect_symbol _new_Object_init
	hlt ; hlt ; hlt ; hlt ; hlt
L_setjmp$stub:
	.indirect_symbol _setjmp
	hlt ; hlt ; hlt ; hlt ; hlt
L_new_bytes$stub:
	.indirect_symbol _new_bytes
	hlt ; hlt ; hlt ; hlt ; hlt
L_new_ExceptionHandler$stub:
	.indirect_symbol _new_ExceptionHandler
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_tMapper_find_$stub:
	.indirect_symbol _knh_tMapper_find_
	hlt ; hlt ; hlt ; hlt ; hlt
L_new_Exception__b$stub:
	.indirect_symbol _new_Exception__b
	hlt ; hlt ; hlt ; hlt ; hlt
L_knh_stack_pmsg$stub:
	.indirect_symbol _knh_stack_pmsg
	hlt ; hlt ; hlt ; hlt ; hlt
	.subsections_via_symbols
