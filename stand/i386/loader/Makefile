# $FreeBSD$

HAVE_ZFS=		${MK_LOADER_ZFS}

LOADER_NET_SUPPORT?=	yes
LOADER_NFS_SUPPORT?=	yes
LOADER_TFTP_SUPPORT?=	yes
LOADER_CD9660_SUPPORT?=	yes
LOADER_EXT2FS_SUPPORT?=	yes
LOADER_MSDOS_SUPPORT?=	yes
LOADER_UFS_SUPPORT?=	yes
LOADER_GZIP_SUPPORT?=	yes
LOADER_BZIP2_SUPPORT?=	yes

.include <bsd.init.mk>

LOADER?=	loader_${LOADER_INTERP}
PROG=		${LOADER}.sym
INTERNALPROG=
NEWVERSWHAT?=	"bootstrap loader" x86
VERSION_FILE=	${.CURDIR}/../loader/version

.PATH:		${BOOTSRC}/i386/loader

# architecture-specific loader code
SRCS=		main.c conf.c vers.c chain.c

# Include bcache code.
HAVE_BCACHE=	yes

# Enable PnP and ISA-PnP code.
HAVE_PNP=	yes
HAVE_ISABUS=	yes

.if ${MK_LOADER_FIREWIRE} == "yes"
CFLAGS+=	-DLOADER_FIREWIRE_SUPPORT
LIBFIREWIRE=	${BOOTOBJ}/i386/libfirewire/libfirewire.a
.endif

.if exists(${.CURDIR}/help.i386)
HELP_FILES=	${.CURDIR}/help.i386
.endif

# Always add MI sources
.include	"${BOOTSRC}/loader.mk"

CLEANFILES+=	${LOADER} ${LOADER}.bin

ORG=		0x0

CFLAGS+=	-Wall
LDFLAGS+=	-static ${LDFLAGS_ORG} -Wl,--gc-sections
.if ${LINKER_TYPE} == "lld" && ${LINKER_VERSION} >= 130000
# lld 13 and higher default to garbage collecting start/stop symbols,
# completely ruining our linker sets. For now, work around it by
# disabling this un-feature.
LDFLAGS+=	-Wl,-z,nostart-stop-gc
.endif

# i386 standalone support library
LIBI386=	${BOOTOBJ}/i386/libi386/libi386.a
CFLAGS+=	-I${BOOTSRC}/i386

# Debug me!
#CFLAGS+=	-g
#LDFLAGS+=	-g

${LOADER}: ${LOADER}.bin ${BTXLDR} ${BTXKERN}
	btxld -v -f aout -e ${LOADER_ADDRESS} -o ${.TARGET} -l ${BTXLDR} \
		-b ${BTXKERN} ${LOADER}.bin

${LOADER}.bin: ${LOADER}.sym
	strip -R .comment -R .note -o ${.TARGET} ${.ALLSRC}

.if ${MK_LOADER_ZFS} == "yes" && ${LOADER_INTERP} == ${LOADER_DEFAULT_INTERP}
LINKS+=		${BINDIR}/${LOADER} ${BINDIR}/zfsloader
.endif
.if ${LOADER_INTERP} == ${LOADER_DEFAULT_INTERP}
LINKS+=		${BINDIR}/${LOADER} ${BINDIR}/loader
.endif
FILES+=	${LOADER}
FILESMODE_${LOADER}= ${BINMODE} -b

# Note: crt0.o needs to be first for pxeboot(8) to work. It assumes that the
# startup code is located at the start of the loader and will jump
# there. Although btx is more flexible than this, the emulated boot2 environment
# that pxeloader provides has none of that flexibility because it lacks access
# to the a.out/elf headers and assumes an entry point of 0.
#
# We must add it to the LDFLAGS instead of the OBJS because the former won't try
# to clean it. When it is in OBJS, this cleaning can lead to races where
# btxcrt.o is rebuilt, but boot2 isn't, leading to errors at installation time.
# LDFLAGS does not have this baggage and will be included first in the list of
# files.
LDFLAGS+=	${BTXCRT}

DPADD=	${LDR_INTERP32} ${LIBFIREWIRE} ${LIBI386} ${LIBSA32}
LDADD=	${LDR_INTERP32} ${LIBFIREWIRE} ${LIBI386} ${LIBSA32}

.if ${MACHINE_CPUARCH} == "amd64"
CFLAGS+=	-DLOADER_PREFER_AMD64
.endif

.include <bsd.prog.mk>
