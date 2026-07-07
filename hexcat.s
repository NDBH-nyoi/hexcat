	.file	"hexcat.c"
	.text
	.section .rdata,"dr"
	.align 8
.LC0:
	.ascii "Usage: hexcat.exe [flags] <args>...\0"
.LC1:
	.ascii "-i <arg>: File input.\0"
	.align 8
.LC2:
	.ascii "-p --padding <arg>: Specify index padding. Also is padding for match positions. Default is 8.\0"
	.align 8
.LC3:
	.ascii "-caps: Capitalizes hex characters.\0"
	.align 8
.LC4:
	.ascii "--stats: At the end of cat-ting, returns a table with the frequency of each byte.\0"
.LC5:
	.ascii "flags that support --stats:\0"
	.align 8
.LC6:
	.ascii "    -st-p --stats-padding <arg_num>: Specify the frequency padding. Default is 4.\0"
	.align 8
.LC7:
	.ascii "    -st-sp --stats-space <arg_num>: Specify the whitespace padding between columns. Default is 4.\0"
	.align 8
.LC8:
	.ascii "    -st-c --stats-colnum <arg_num>: Specify the number of columns. Default is 8.\0"
	.align 8
.LC9:
	.ascii "    -st-v --stats-verbose: Will print hexs that have 0 occurence. Default hides this.\0"
	.align 8
.LC10:
	.ascii "    -fr --freq: Display stats table from highest to lowest frequency order.\0"
	.align 8
.LC11:
	.ascii "-m --match \"num1,num2,...\": Returns the starting position of sequences that matches the sequence given. Everything should be under quotes and also seperated by commas.\0"
.LC12:
	.ascii "flags that support --match:\0"
	.align 8
.LC13:
	.ascii "    -m-p --match-padding <arg_num>: Specify match index padding. Default is 2.\0"
	.align 8
.LC14:
	.ascii "-sil --silent: Silent mode. Do not print hexdump.\0"
	.align 8
.LC15:
	.ascii "-ref: Displays useful references for control characters.\0"
.LC16:
	.ascii "-h --help: Show this list.\0"
	.text
	.globl	PRINT_HELP
	.def	PRINT_HELP;	.scl	2;	.type	32;	.endef
	.seh_proc	PRINT_HELP
PRINT_HELP:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC5(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC6(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC7(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC8(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC9(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC10(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC11(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC12(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC13(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC14(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC15(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC16(%rip), %rax
	movq	%rax, %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	is_escape_char
	.def	is_escape_char;	.scl	2;	.type	32;	.endef
	.seh_proc	is_escape_char
is_escape_char:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, %eax
	movb	%al, 16(%rbp)
	cmpb	$0, 16(%rbp)
	js	.L3
	cmpb	$31, 16(%rbp)
	jle	.L4
.L3:
	cmpb	$127, 16(%rbp)
	jne	.L5
.L4:
	movl	$1, %eax
	jmp	.L6
.L5:
	movl	$0, %eax
.L6:
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC17:
	.ascii "Useful references: \0"
	.align 8
.LC18:
	.ascii "All characters from 00 to 1f and 7f are control characters.\0"
	.align 8
.LC19:
	.ascii "Especially important characters:\0"
.LC20:
	.ascii "0a: Line feed/ new line.\0"
.LC21:
	.ascii "0d: Carriage return.\0"
	.text
	.globl	PRINT_REFERENCE
	.def	PRINT_REFERENCE;	.scl	2;	.type	32;	.endef
	.seh_proc	PRINT_REFERENCE
PRINT_REFERENCE:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	$10, %ecx
	call	putchar
	leaq	.LC17(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC18(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC19(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC20(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC21(%rip), %rax
	movq	%rax, %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	inFileName
	.section .rdata,"dr"
.LC22:
	.ascii "\0"
	.data
	.align 8
inFileName:
	.quad	.LC22
	.globl	HELP_FLAG
	.bss
HELP_FLAG:
	.space 1
	.globl	CAPITAL_FLAG
CAPITAL_FLAG:
	.space 1
	.globl	PaddingSize
	.data
PaddingSize:
	.byte	8
	.globl	STATS_FLAG
	.bss
STATS_FLAG:
	.space 1
	.globl	STATS_FREQ_FLAG
STATS_FREQ_FLAG:
	.space 1
	.globl	STATS_VERBOSE_FLAG
STATS_VERBOSE_FLAG:
	.space 1
	.globl	STATS_PADDING
	.data
STATS_PADDING:
	.byte	4
	.globl	STATS_SPACEPADDING
STATS_SPACEPADDING:
	.byte	4
	.globl	COLUMN_NUMBER
COLUMN_NUMBER:
	.byte	8
	.globl	byteStats
	.bss
	.align 32
byteStats:
	.space 1024
	.globl	MATCH_STRING
	.data
	.align 8
MATCH_STRING:
	.quad	.LC22
	.globl	RETURN_MATCH_STR
	.bss
	.align 32
RETURN_MATCH_STR:
	.space 96
	.globl	MATCH_FLAG
MATCH_FLAG:
	.space 1
	.globl	MatchIndexPadding
	.data
MatchIndexPadding:
	.byte	2
	.globl	SILENT_FLAG
	.bss
SILENT_FLAG:
	.space 1
	.globl	REFERENCE_FLAG
REFERENCE_FLAG:
	.space 1
	.globl	ch
	.align 4
ch:
	.space 4
	.globl	HexPerLine
	.data
	.align 4
HexPerLine:
	.long	16
	.globl	Buf_forChars16
	.bss
	.align 32
Buf_forChars16:
	.space 64
	.globl	Hex_Counter
	.data
	.align 4
Hex_Counter:
	.long	16
	.globl	LineNum
	.bss
	.align 8
LineNum:
	.space 8
	.globl	ConversionBuf
	.align 32
ConversionBuf:
	.space 32
	.globl	ConverBufCounter
ConverBufCounter:
	.space 1
	.globl	ComparisonBuf
	.align 32
ComparisonBuf:
	.space 32
	.globl	CompareCounter
CompareCounter:
	.space 1
	.globl	matchesPosition
	.align 32
matchesPosition:
	.space 1024
	.globl	PositionCounter
PositionCounter:
	.space 1
	.globl	EqualCounter
EqualCounter:
	.space 1
	.section .rdata,"dr"
.LC23:
	.ascii "-i\0"
	.align 8
.LC24:
	.ascii "Error: -i requires an argument.\0"
.LC25:
	.ascii "-h\0"
.LC26:
	.ascii "--help\0"
.LC27:
	.ascii "-caps\0"
.LC28:
	.ascii "--stats\0"
.LC29:
	.ascii "--padding\0"
.LC30:
	.ascii "-p\0"
	.align 8
.LC31:
	.ascii "Error: -p requires an argument.\0"
.LC32:
	.ascii "--stats-colnum\0"
.LC33:
	.ascii "-st-c\0"
	.align 8
.LC34:
	.ascii "Error: -st-c requires an argument.\0"
.LC35:
	.ascii "--stats-padding\0"
.LC36:
	.ascii "-st-p\0"
	.align 8
.LC37:
	.ascii "Error: -st-p requires an argument.\0"
.LC38:
	.ascii "--stats-space\0"
.LC39:
	.ascii "-st-sp\0"
	.align 8
.LC40:
	.ascii "Error: -st-sp requires an argument.\0"
.LC41:
	.ascii "--freq\0"
.LC42:
	.ascii "--stats-verbose\0"
.LC43:
	.ascii "-st-v\0"
.LC44:
	.ascii "--match\0"
.LC45:
	.ascii "-m\0"
	.align 8
.LC46:
	.ascii "Error: -m requires an argument.\0"
.LC47:
	.ascii "--match-padding\0"
.LC48:
	.ascii "-m-p\0"
	.align 8
.LC49:
	.ascii "Error: -m-p requires an argument.\0"
.LC50:
	.ascii "--silent\0"
.LC51:
	.ascii "-sil\0"
.LC52:
	.ascii "-ref\0"
	.align 8
.LC53:
	.ascii "Unknown command or missing arguments: %s.\12\0"
	.align 8
.LC54:
	.ascii "Type -h or --help for usage help.\0"
	.align 8
.LC55:
	.ascii "Padding size is invalid or too large: %d.\0"
.LC56:
	.ascii "%0*x  \0"
.LC57:
	.ascii "%.2x \0"
.LC58:
	.ascii "%0*X  \0"
.LC59:
	.ascii "%.2X \0"
.LC60:
	.ascii ",\0"
	.align 8
.LC61:
	.ascii "Exceed matching string's buffer.\0"
.LC62:
	.ascii "rb\0"
.LC63:
	.ascii "   \0"
	.align 8
.LC64:
	.ascii "End of file reached. Total file size: %llu B.\12\0"
	.align 8
.LC65:
	.ascii "Input was likely incorrect: %s\12\0"
.LC66:
	.ascii "Matches to %s (length +%d): \12\0"
.LC67:
	.ascii "%0*d  \0"
.LC68:
	.ascii "Start position %0*x.\12\0"
.LC69:
	.ascii "No matches founded.\0"
.LC70:
	.ascii "\12Total match count: %d.\12\0"
	.align 8
.LC71:
	.ascii "Frequency flag --freq has to be used with --stats.\0"
	.align 8
.LC72:
	.ascii "Stats padding size is invalid or too large: %d.\0"
	.align 8
.LC73:
	.ascii "Stats space padding size is invalid or too large: %d.\0"
	.align 8
.LC74:
	.ascii "Column number is invalid or too large: %d.\0"
.LC75:
	.ascii "Byte frequency: \0"
.LC76:
	.ascii "%.2x: %.*u\0"
.LC77:
	.ascii "%*s\0"
	.align 8
.LC78:
	.ascii "Hex with 0 occurences are hidden.\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$112, %rsp
	.seh_stackalloc	112
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	call	__main
	movl	$1, -4(%rbp)
	cmpl	$1, 16(%rbp)
	jne	.L10
	movb	$1, HELP_FLAG(%rip)
	jmp	.L10
.L42:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC23(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L11
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, 16(%rbp)
	jg	.L12
	leaq	.LC24(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %eax
	jmp	.L13
.L12:
	movl	-4(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, inFileName(%rip)
	addl	$2, -4(%rbp)
	jmp	.L10
.L11:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC25(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	je	.L14
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC26(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L15
.L14:
	movb	$1, HELP_FLAG(%rip)
	addl	$1, -4(%rbp)
	jmp	.L10
.L15:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC27(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L16
	movb	$1, CAPITAL_FLAG(%rip)
	addl	$1, -4(%rbp)
	jmp	.L10
.L16:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC28(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L17
	movb	$1, STATS_FLAG(%rip)
	addl	$1, -4(%rbp)
	jmp	.L10
.L17:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC29(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	je	.L18
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC30(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L19
.L18:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, 16(%rbp)
	jg	.L20
	leaq	.LC31(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %eax
	jmp	.L13
.L20:
	movl	-4(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	call	atoi
	movb	%al, PaddingSize(%rip)
	addl	$2, -4(%rbp)
	jmp	.L10
.L19:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC32(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	je	.L21
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC33(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L22
.L21:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, 16(%rbp)
	jg	.L23
	leaq	.LC34(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %eax
	jmp	.L13
.L23:
	movl	-4(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	call	atoi
	movb	%al, COLUMN_NUMBER(%rip)
	addl	$2, -4(%rbp)
	jmp	.L10
.L22:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC35(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	je	.L24
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC36(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L25
.L24:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, 16(%rbp)
	jg	.L26
	leaq	.LC37(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %eax
	jmp	.L13
.L26:
	movl	-4(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	call	atoi
	movb	%al, STATS_PADDING(%rip)
	addl	$2, -4(%rbp)
	jmp	.L10
.L25:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC38(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	je	.L27
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC39(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L28
.L27:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, 16(%rbp)
	jg	.L29
	leaq	.LC40(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %eax
	jmp	.L13
.L29:
	movl	-4(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	call	atoi
	movb	%al, STATS_SPACEPADDING(%rip)
	addl	$2, -4(%rbp)
	jmp	.L10
.L28:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC41(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L30
	movb	$1, STATS_FREQ_FLAG(%rip)
	addl	$1, -4(%rbp)
	jmp	.L10
.L30:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC42(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	je	.L31
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC43(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L32
.L31:
	movb	$1, STATS_VERBOSE_FLAG(%rip)
	addl	$1, -4(%rbp)
	jmp	.L10
.L32:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC44(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	je	.L33
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC45(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L34
.L33:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, 16(%rbp)
	jg	.L35
	leaq	.LC46(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %eax
	jmp	.L13
.L35:
	movl	-4(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, MATCH_STRING(%rip)
	addl	$2, -4(%rbp)
	movb	$1, MATCH_FLAG(%rip)
	jmp	.L10
.L34:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC47(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	je	.L36
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC48(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L37
.L36:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, 16(%rbp)
	jg	.L38
	leaq	.LC49(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %eax
	jmp	.L13
.L38:
	movl	-4(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	call	atoi
	movb	%al, MatchIndexPadding(%rip)
	addl	$2, -4(%rbp)
	jmp	.L10
.L37:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC50(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	je	.L39
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC51(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L40
.L39:
	movb	$1, SILENT_FLAG(%rip)
	addl	$1, -4(%rbp)
	jmp	.L10
.L40:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC52(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L41
	movb	$1, REFERENCE_FLAG(%rip)
	addl	$1, -4(%rbp)
	jmp	.L10
.L41:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC53(%rip), %rcx
	movq	%rax, %rdx
	call	printf
	leaq	.LC54(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %eax
	jmp	.L13
.L10:
	movl	-4(%rbp), %eax
	cmpl	16(%rbp), %eax
	jl	.L42
	movzbl	PaddingSize(%rip), %eax
	cmpb	$16, %al
	ja	.L43
	movzbl	PaddingSize(%rip), %eax
	testb	%al, %al
	je	.L43
	movzbl	PaddingSize(%rip), %eax
	cmpb	$1, %al
	jne	.L44
.L43:
	movzbl	PaddingSize(%rip), %eax
	movzbl	%al, %eax
	leaq	.LC55(%rip), %rcx
	movl	%eax, %edx
	call	printf
	movl	$1, %eax
	jmp	.L13
.L44:
	leaq	.LC56(%rip), %rax
	movq	%rax, -16(%rbp)
	leaq	.LC57(%rip), %rax
	movq	%rax, -24(%rbp)
	movzbl	CAPITAL_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L45
	leaq	.LC58(%rip), %rax
	movq	%rax, -16(%rbp)
	leaq	.LC59(%rip), %rax
	movq	%rax, -24(%rbp)
.L45:
	movzbl	HELP_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L46
	call	PRINT_HELP
	movq	inFileName(%rip), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	testl	%eax, %eax
	jne	.L46
	movl	$1, %eax
	jmp	.L13
.L46:
	movq	MATCH_STRING(%rip), %rax
	leaq	RETURN_MATCH_STR(%rip), %rcx
	movq	%rax, %rdx
	call	strcpy
	movzbl	MATCH_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L47
	movq	MATCH_STRING(%rip), %rax
	leaq	.LC60(%rip), %rdx
	movq	%rax, %rcx
	call	strtok
	movq	%rax, -32(%rbp)
	jmp	.L48
.L49:
	movq	-32(%rbp), %rax
	movl	$16, %r8d
	movl	$0, %edx
	movq	%rax, %rcx
	call	strtol
	movl	%eax, %edx
	movzbl	ConverBufCounter(%rip), %eax
	movzbl	%al, %eax
	movl	%edx, %ecx
	cltq
	leaq	ConversionBuf(%rip), %rdx
	movb	%cl, (%rax,%rdx)
	movzbl	ConverBufCounter(%rip), %eax
	addl	$1, %eax
	movb	%al, ConverBufCounter(%rip)
	leaq	.LC60(%rip), %rax
	movq	%rax, %rdx
	movl	$0, %ecx
	call	strtok
	movq	%rax, -32(%rbp)
.L48:
	cmpq	$0, -32(%rbp)
	jne	.L49
.L47:
	movzbl	ConverBufCounter(%rip), %eax
	cmpb	$32, %al
	jbe	.L50
	movzbl	MATCH_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L50
	leaq	.LC61(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %eax
	jmp	.L13
.L50:
	movq	inFileName(%rip), %rax
	leaq	.LC62(%rip), %rdx
	movq	%rax, %rcx
	call	fopen
	movq	%rax, -72(%rbp)
	jmp	.L51
.L67:
	movl	Hex_Counter(%rip), %edx
	movl	HexPerLine(%rip), %eax
	cmpl	%eax, %edx
	jne	.L52
	movl	$0, Hex_Counter(%rip)
	movzbl	SILENT_FLAG(%rip), %eax
	cmpb	$1, %al
	je	.L53
	movl	$10, %ecx
	call	putchar
	movq	LineNum(%rip), %rcx
	movzbl	PaddingSize(%rip), %eax
	movzbl	%al, %edx
	movq	-16(%rbp), %rax
	movq	%rcx, %r8
	movq	%rax, %rcx
	call	printf
.L53:
	movl	HexPerLine(%rip), %eax
	movslq	%eax, %rdx
	movq	LineNum(%rip), %rax
	addq	%rdx, %rax
	movq	%rax, LineNum(%rip)
.L52:
	movzbl	SILENT_FLAG(%rip), %eax
	cmpb	$1, %al
	je	.L54
	movl	ch(%rip), %edx
	movq	-24(%rbp), %rax
	movq	%rax, %rcx
	call	printf
.L54:
	movzbl	MATCH_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L55
	movzbl	CompareCounter(%rip), %edx
	movzbl	ConverBufCounter(%rip), %eax
	cmpb	%al, %dl
	je	.L56
	movl	ch(%rip), %edx
	movzbl	CompareCounter(%rip), %eax
	movzbl	%al, %eax
	movl	%edx, %ecx
	cltq
	leaq	ComparisonBuf(%rip), %rdx
	movb	%cl, (%rax,%rdx)
	movzbl	CompareCounter(%rip), %eax
	addl	$1, %eax
	movb	%al, CompareCounter(%rip)
	jmp	.L57
.L56:
	movzbl	CompareCounter(%rip), %eax
	movzbl	%al, %eax
	subl	$1, %eax
	movslq	%eax, %rcx
	leaq	1+ComparisonBuf(%rip), %rdx
	leaq	ComparisonBuf(%rip), %rax
	movq	%rcx, %r8
	movq	%rax, %rcx
	call	memmove
	movl	ch(%rip), %edx
	movzbl	CompareCounter(%rip), %eax
	movzbl	%al, %eax
	subl	$1, %eax
	movl	%edx, %ecx
	cltq
	leaq	ComparisonBuf(%rip), %rdx
	movb	%cl, (%rax,%rdx)
.L57:
	movl	$0, -36(%rbp)
	jmp	.L58
.L61:
	movl	-36(%rbp), %eax
	cltq
	leaq	ComparisonBuf(%rip), %rdx
	movzbl	(%rax,%rdx), %edx
	movl	-36(%rbp), %eax
	cltq
	leaq	ConversionBuf(%rip), %rcx
	movzbl	(%rax,%rcx), %eax
	cmpb	%al, %dl
	je	.L59
	movb	$0, EqualCounter(%rip)
	jmp	.L60
.L59:
	movzbl	EqualCounter(%rip), %eax
	addl	$1, %eax
	movb	%al, EqualCounter(%rip)
	addl	$1, -36(%rbp)
.L58:
	movzbl	ConverBufCounter(%rip), %eax
	movzbl	%al, %eax
	cmpl	%eax, -36(%rbp)
	jl	.L61
.L60:
	movzbl	EqualCounter(%rip), %edx
	movzbl	ConverBufCounter(%rip), %eax
	cmpb	%al, %dl
	jne	.L55
	movl	Hex_Counter(%rip), %eax
	movslq	%eax, %rdx
	movq	LineNum(%rip), %rax
	addq	%rax, %rdx
	movzbl	ConverBufCounter(%rip), %eax
	movzbl	%al, %eax
	subq	%rax, %rdx
	subq	$15, %rdx
	movzbl	PositionCounter(%rip), %eax
	movzbl	%al, %eax
	movq	%rdx, %rcx
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	matchesPosition(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movzbl	PositionCounter(%rip), %eax
	addl	$1, %eax
	movb	%al, PositionCounter(%rip)
	movb	$0, EqualCounter(%rip)
.L55:
	movzbl	STATS_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L62
	movl	ch(%rip), %eax
	movslq	%eax, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	byteStats(%rip), %rdx
	movl	(%rcx,%rdx), %edx
	leal	1(%rdx), %ecx
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	byteStats(%rip), %rax
	movl	%ecx, (%rdx,%rax)
.L62:
	movl	Hex_Counter(%rip), %edx
	movl	ch(%rip), %eax
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	Buf_forChars16(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	Hex_Counter(%rip), %eax
	addl	$1, %eax
	movl	%eax, Hex_Counter(%rip)
	movl	Hex_Counter(%rip), %edx
	movl	HexPerLine(%rip), %eax
	cmpl	%eax, %edx
	jne	.L51
	movzbl	SILENT_FLAG(%rip), %eax
	cmpb	$1, %al
	je	.L51
	movl	$0, -40(%rbp)
	jmp	.L63
.L66:
	movl	-40(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Buf_forChars16(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %ecx
	call	is_escape_char
	cmpl	$1, %eax
	jne	.L64
	movl	$46, %ecx
	call	putchar
	jmp	.L65
.L64:
	movl	-40(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Buf_forChars16(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putchar
.L65:
	addl	$1, -40(%rbp)
.L63:
	cmpl	$15, -40(%rbp)
	jle	.L66
.L51:
	movq	-72(%rbp), %rax
	movq	%rax, %rcx
	call	fgetc
	movl	%eax, ch(%rip)
	movl	ch(%rip), %eax
	cmpl	$-1, %eax
	jne	.L67
	movzbl	SILENT_FLAG(%rip), %eax
	cmpb	$1, %al
	je	.L68
	movl	$0, -44(%rbp)
	jmp	.L69
.L70:
	leaq	.LC63(%rip), %rax
	movq	%rax, %rcx
	call	printf
	addl	$1, -44(%rbp)
.L69:
	movl	HexPerLine(%rip), %edx
	movl	Hex_Counter(%rip), %eax
	subl	%eax, %edx
	cmpl	%edx, -44(%rbp)
	jl	.L70
	movl	$0, -48(%rbp)
	jmp	.L71
.L74:
	movl	-48(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Buf_forChars16(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %ecx
	call	is_escape_char
	cmpl	$1, %eax
	jne	.L72
	movl	$46, %ecx
	call	putchar
	jmp	.L73
.L72:
	movl	-48(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Buf_forChars16(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putchar
.L73:
	addl	$1, -48(%rbp)
.L71:
	movl	Hex_Counter(%rip), %eax
	cmpl	%eax, -48(%rbp)
	jl	.L74
.L68:
	movl	$10, %ecx
	call	putchar
	movq	LineNum(%rip), %rdx
	movl	HexPerLine(%rip), %ecx
	movl	Hex_Counter(%rip), %eax
	subl	%eax, %ecx
	movslq	%ecx, %rax
	subq	%rax, %rdx
	leaq	.LC64(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	HexPerLine(%rip), %edx
	movl	Hex_Counter(%rip), %eax
	subl	%eax, %edx
	movslq	%edx, %rdx
	movq	LineNum(%rip), %rax
	cmpq	%rax, %rdx
	jne	.L75
	movq	inFileName(%rip), %rax
	leaq	.LC65(%rip), %rcx
	movq	%rax, %rdx
	call	printf
.L75:
	movzbl	REFERENCE_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L76
	call	PRINT_REFERENCE
.L76:
	movzbl	MATCH_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L77
	movl	$10, %ecx
	call	putchar
	movzbl	ConverBufCounter(%rip), %eax
	movzbl	%al, %ecx
	leaq	RETURN_MATCH_STR(%rip), %rdx
	leaq	.LC66(%rip), %rax
	movl	%ecx, %r8d
	movq	%rax, %rcx
	call	printf
	movl	$0, -52(%rbp)
	jmp	.L78
.L79:
	movl	-52(%rbp), %eax
	leal	1(%rax), %edx
	movzbl	MatchIndexPadding(%rip), %eax
	movzbl	%al, %eax
	leaq	.LC67(%rip), %rcx
	movl	%edx, %r8d
	movl	%eax, %edx
	call	printf
	movl	-52(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	matchesPosition(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movzbl	PaddingSize(%rip), %eax
	movzbl	%al, %eax
	leaq	.LC68(%rip), %rcx
	movq	%rdx, %r8
	movl	%eax, %edx
	call	printf
	addl	$1, -52(%rbp)
.L78:
	movzbl	PositionCounter(%rip), %eax
	movzbl	%al, %eax
	cmpl	%eax, -52(%rbp)
	jl	.L79
	movzbl	PositionCounter(%rip), %eax
	testb	%al, %al
	jne	.L80
	leaq	.LC69(%rip), %rax
	movq	%rax, %rcx
	call	puts
.L80:
	movzbl	PositionCounter(%rip), %eax
	movzbl	%al, %eax
	leaq	.LC70(%rip), %rcx
	movl	%eax, %edx
	call	printf
.L77:
	movzbl	STATS_FREQ_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L81
	movzbl	STATS_FLAG(%rip), %eax
	testb	%al, %al
	jne	.L81
	leaq	.LC71(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %eax
	jmp	.L13
.L81:
	movzbl	STATS_PADDING(%rip), %eax
	cmpb	$16, %al
	ja	.L82
	movzbl	STATS_PADDING(%rip), %eax
	testb	%al, %al
	jne	.L83
.L82:
	movzbl	STATS_PADDING(%rip), %eax
	movzbl	%al, %eax
	leaq	.LC72(%rip), %rcx
	movl	%eax, %edx
	call	printf
	movl	$1, %eax
	jmp	.L13
.L83:
	movzbl	STATS_SPACEPADDING(%rip), %eax
	cmpb	$16, %al
	ja	.L84
	movzbl	STATS_SPACEPADDING(%rip), %eax
	testb	%al, %al
	jne	.L85
.L84:
	movzbl	STATS_SPACEPADDING(%rip), %eax
	movzbl	%al, %eax
	leaq	.LC73(%rip), %rcx
	movl	%eax, %edx
	call	printf
	movl	$1, %eax
	jmp	.L13
.L85:
	movzbl	COLUMN_NUMBER(%rip), %eax
	cmpb	$16, %al
	ja	.L86
	movzbl	COLUMN_NUMBER(%rip), %eax
	testb	%al, %al
	jne	.L87
.L86:
	movzbl	COLUMN_NUMBER(%rip), %eax
	movzbl	%al, %eax
	leaq	.LC74(%rip), %rcx
	movl	%eax, %edx
	call	printf
	movl	$1, %eax
	jmp	.L13
.L87:
	movzbl	STATS_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L88
	movl	$10, %ecx
	call	putchar
	leaq	.LC75(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movzbl	STATS_VERBOSE_FLAG(%rip), %eax
	cmpb	$1, %al
	jne	.L89
	movl	$0, -56(%rbp)
	jmp	.L90
.L92:
	movzbl	COLUMN_NUMBER(%rip), %eax
	movzbl	%al, %ecx
	movl	-56(%rbp), %eax
	cltd
	idivl	%ecx
	movl	%edx, %ecx
	movl	%ecx, %eax
	testl	%eax, %eax
	jne	.L91
	movl	$10, %ecx
	call	putchar
.L91:
	movl	-56(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	byteStats(%rip), %rax
	movl	(%rdx,%rax), %r8d
	movzbl	STATS_PADDING(%rip), %eax
	movzbl	%al, %edx
	movl	-56(%rbp), %eax
	leaq	.LC76(%rip), %rcx
	movl	%r8d, %r9d
	movl	%edx, %r8d
	movl	%eax, %edx
	call	printf
	movzbl	STATS_SPACEPADDING(%rip), %eax
	movzbl	%al, %eax
	leaq	.LC22(%rip), %rdx
	leaq	.LC77(%rip), %rcx
	movq	%rdx, %r8
	movl	%eax, %edx
	call	printf
	addl	$1, -56(%rbp)
.L90:
	cmpl	$255, -56(%rbp)
	jle	.L92
	jmp	.L88
.L89:
	leaq	.LC78(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$0, -60(%rbp)
	movl	$0, -64(%rbp)
	jmp	.L93
.L96:
	movzbl	COLUMN_NUMBER(%rip), %eax
	movzbl	%al, %eax
	leal	1(%rax), %ecx
	movl	-60(%rbp), %eax
	cltd
	idivl	%ecx
	movl	%edx, %ecx
	movl	%ecx, %eax
	testl	%eax, %eax
	jne	.L94
	movl	$10, %ecx
	call	putchar
	addl	$1, -60(%rbp)
.L94:
	movl	-64(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	byteStats(%rip), %rax
	movl	(%rdx,%rax), %eax
	testl	%eax, %eax
	je	.L95
	movl	-64(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	byteStats(%rip), %rax
	movl	(%rdx,%rax), %r8d
	movzbl	STATS_PADDING(%rip), %eax
	movzbl	%al, %edx
	movl	-64(%rbp), %eax
	leaq	.LC76(%rip), %rcx
	movl	%r8d, %r9d
	movl	%edx, %r8d
	movl	%eax, %edx
	call	printf
	movzbl	STATS_SPACEPADDING(%rip), %eax
	movzbl	%al, %eax
	leaq	.LC22(%rip), %rdx
	leaq	.LC77(%rip), %rcx
	movq	%rdx, %r8
	movl	%eax, %edx
	call	printf
	addl	$1, -60(%rbp)
.L95:
	addl	$1, -64(%rbp)
.L93:
	cmpl	$255, -64(%rbp)
	jle	.L96
.L88:
	movl	$10, %ecx
	call	putchar
	movq	-72(%rbp), %rax
	movq	%rax, %rcx
	call	fclose
	movl	$0, %eax
.L13:
	addq	$112, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev8, Built by MSYS2 project) 15.2.0"
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	putchar;	.scl	2;	.type	32;	.endef
	.def	strcmp;	.scl	2;	.type	32;	.endef
	.def	atoi;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	strcpy;	.scl	2;	.type	32;	.endef
	.def	strtok;	.scl	2;	.type	32;	.endef
	.def	strtol;	.scl	2;	.type	32;	.endef
	.def	fopen;	.scl	2;	.type	32;	.endef
	.def	memmove;	.scl	2;	.type	32;	.endef
	.def	fgetc;	.scl	2;	.type	32;	.endef
	.def	fclose;	.scl	2;	.type	32;	.endef
