# $FreeBSD$

.include <bsd.init.mk>

LIB=			i386

SRCS=	bio.c biosacpi.c biosdisk.c biosmem.c biospnp.c \
	biospci.c biossmap.c bootinfo.c bootinfo32.c bootinfo64.c \
	comconsole.c devicename.c elf32_freebsd.c \
	elf64_freebsd.c multiboot.c multiboot_tramp.S relocater_tramp.S \
	i386_copy.c i386_module.c nullconsole.c pxe.c pxetramp.s \
	time.c vidconsole.c amd64_tramp.S spinconsole.c
.PATH:	${ZFSSRC}
SRCS+=  devicename_stubs.c
CFLAGS+= -I${ZFSSRC}

BOOT_COMCONSOLE_PORT?= 0x3f8
CFLAGS+=	-DCOMPORT=${BOOT_COMCONSOLE_PORT}

BOOT_COMCONSOLE_SPEED?= 9600
CFLAGS+=	-DCOMSPEED=${BOOT_COMCONSOLE_SPEED}

.ifdef(BOOT_BIOSDISK_DEBUG)
# Make the disk code more talkative
CFLAGS+= -DDISK_DEBUG
.endif

# Include simple terminal emulation (cons25-compatible)
CFLAGS+= -DTERM_EMU

# XXX: make alloca() useable
CFLAGS+= -Dalloca=__builtin_alloca

CFLAGS+=	-I${BOOTSRC}/ficl -I${BOOTSRC}/ficl/i386 \
		-I${LDRSRC} -I${BOOTSRC}/i386/common \
		-I${SYSDIR}/cddl/boot/zfs \
		-I${SYSDIR}/cddl/contrib/opensolaris/uts/common \
		-I${SYSDIR}/contrib/dev/acpica/include

# Handle FreeBSD specific %b and %D printf format specifiers
CFLAGS+= ${FORMAT_EXTENSIONS}

.include <bsd.lib.mk>
