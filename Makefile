CC		= g++
CC_OBJ_FLAGS	= -c -fPIC
CC_Shared_FLAGS	= -shared -Wl,-soname,libtcs.so
ROOT_CFLAGS	= $(shell root-config --cflags)
ROOT_LIBS	= $(shell root-config --libs)

GenTCS:		tcs_lib GenTCS.cc
		$(CC) $(ROOT_CFLAGS) $(ROOT_LIBS) -L./ -ltcs GenTCS.cc -o GenTCS.exe

tcs_lib:	TTCS_kine.o kin_funcs.o TTCS_crs.o TGFlux.o TCLASChargedParticle.o cc_eff_funcs.o
		$(CC) $(CC_Shared_FLAGS) -o libtcs.so TTCS_kine.o kin_funcs.o TTCS_crs.o TGFlux.o TCLASChargedParticle.o cc_eff_funcs.o

TTCS_kine.o:	TTCS_kine.cc TTCS_kine.hh
		$(CC) $(CC_OBJ_FLAGS) $(ROOT_CFLAGS) $(ROOT_LIBS) TTCS_kine.cc -o TTCS_kine.o

kin_funcs.o:	kin_funcs.cc kin_funcs.h
		$(CC) $(CC_OBJ_FLAGS) kin_funcs.cc -o kin_funcs.o

TTCS_crs.o:	TTCS_crs.hh TTCS_crs.cc
		$(CC) $(CC_OBJ_FLAGS) $(ROOT_CFLAGS) $(ROOT_LIBS) TTCS_crs.cc -o TTCS_crs.o

TGFlux.o:	TGFlux.hh TGFlux.cc
		$(CC) $(CC_OBJ_FLAGS) $(ROOT_CFLAGS) $(ROOT_LIBS) TGFlux.cc -o TGFlux.o

TCLASChargedParticle.o:	 	TCLASChargedParticle.hh TCLASChargedParticle.cc
	$(CC) $(CC_OBJ_FLAGS) $(ROOT_CFLAGS) $(ROOT_LIBS) TCLASChargedParticle.cc -o TCLASChargedParticle.o

cc_eff_funcs.o:	cc_eff_funcs.f
		$(CC) $(CC_OBJ_FLAGS) cc_eff_funcs.f -o cc_eff_funcs.o
		
clean:		
		rm -f *.so* *.o *.exe
