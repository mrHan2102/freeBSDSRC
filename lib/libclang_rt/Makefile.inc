# $FreeBSD$

.include <bsd.compiler.mk>

# armv[67] is a bit special since we allow a soft-floating version via
# CPUTYPE matching *soft*. This variant may not actually work though.
.if ${MACHINE_ARCH:Marmv[67]*} != "" && \
    (!defined(CPUTYPE) || ${CPUTYPE:M*soft*} == "")
CRTARCH?=	armhf
.else
CRTARCH?=	${MACHINE_ARCH:C/amd64/x86_64/}
.endif
CRTSRC=		${SRCTOP}/contrib/llvm-project/compiler-rt

.PATH:		${CRTSRC}/lib

CLANGDIR=	/usr/lib/clang/10.0.1
LIBDIR=		${CLANGDIR}/lib/freebsd
SHLIBDIR=	${LIBDIR}

NO_PIC=
MK_PROFILE=	no
MK_SSP=		no

WARNS?=		0

CFLAGS+=	-DNDEBUG
CFLAGS+=	-DHAVE_RPC_XDR_H=0
CFLAGS+=	-DSANITIZER_SUPPORTS_WEAK_HOOKS=0
CFLAGS+=	-DUBSAN_CAN_USE_CXXABI
CFLAGS+=	${PICFLAG}
CFLAGS+=	-fno-builtin
CFLAGS+=	-fno-exceptions
CXXFLAGS+=	-fno-rtti
.if ${COMPILER_TYPE} == clang && ${COMPILER_VERSION} >= 30700
CFLAGS+=	-fno-sanitize=safe-stack
.endif
CFLAGS+=	-fno-stack-protector
CFLAGS+=	-funwind-tables
CXXFLAGS+=	-fvisibility-inlines-hidden
CXXFLAGS+=	-fvisibility=hidden
CFLAGS+=	-I${CRTSRC}/include
CFLAGS+=	-I${CRTSRC}/lib
CXXSTD=		c++14
