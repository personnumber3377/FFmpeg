#!/bin/sh


# clang -I. -I./ -D_ISOC11_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_POSIX_C_SOURCE=200112 -D_XOPEN_SOURCE=600 -DPIC -DZLIB_CONST -fsanitize=address,undefined,fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping -fno-omit-frame-pointer -fsanitize=address   -std=c17 -fomit-frame-pointer -fPIC    -pthread  -I/usr/include/libdrm       -I/usr/include/libdrm    -g -Wdeclaration-after-statement -Wall -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -Wmissing-prototypes -Wstrict-prototypes -Wempty-body -Wno-parentheses -Wno-switch -Wno-format-zero-length -Wno-pointer-sign -Wno-unused-const-variable -Wno-bool-operation -Wno-char-subscripts -Wno-implicit-const-int-float-conversion -O3 -fno-math-errno -fno-signed-zeros -mstack-alignment=16 -Qunused-arguments -Werror=implicit-function-declaration -Werror=missing-prototypes -Werror=return-type -I/usr/include/SDL2 -D_REENTRANT   -MMD -MF tools/betterfuzzer.d -MT tools/betterfuzzer.o -c -o tools/betterfuzzer.o tools/betterfuzzer.c --warn-implicit-function-declaration -Wno-error=implicit-function-declaration -Wno-error=int-conversion

# clang -I. -I./ -D_ISOC11_SOURCE -D_FILE_OFFSET_BITS=64 -DPIC -DZLIB_CONST -fsanitize=address,undefined,fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping -fno-omit-frame-pointer -fsanitize=address   -std=c17 -fomit-frame-pointer -fPIC    -pthread  -I/usr/include/libdrm       -I/usr/include/libdrm    -g -Wdeclaration-after-statement -Wall -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -Wmissing-prototypes -Wstrict-prototypes -Wempty-body -Wno-parentheses -Wno-switch -Wno-format-zero-length -Wno-pointer-sign -Wno-unused-const-variable -Wno-bool-operation -Wno-char-subscripts -Wno-implicit-const-int-float-conversion -O3 -fno-math-errno -fno-signed-zeros -mstack-alignment=16 -Qunused-arguments -Werror=implicit-function-declaration -Werror=missing-prototypes -Werror=return-type -I/usr/include/SDL2 -D_REENTRANT   -MMD -MF tools/betterfuzzer.d -MT tools/betterfuzzer.o -c -o tools/betterfuzzer.o tools/betterfuzzer.c --warn-implicit-function-declaration -Wno-error=implicit-function-declaration -Wno-error=int-conversion



clang -I. -I./ -D_ISOC11_SOURCE -D_FILE_OFFSET_BITS=64 -DPIC -DZLIB_CONST -fsanitize=address,undefined,fuzzer -fno-omit-frame-pointer -fsanitize=address   -fomit-frame-pointer -fPIC    -pthread  -I/usr/include/libdrm       -I/usr/include/libdrm    -g -Wdeclaration-after-statement -Wall -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -Wmissing-prototypes -Wstrict-prototypes -Wempty-body -Wno-parentheses -Wno-switch -Wno-format-zero-length -Wno-pointer-sign -Wno-unused-const-variable -Wno-bool-operation -Wno-char-subscripts -Wno-implicit-const-int-float-conversion -O3 -fno-math-errno -fno-signed-zeros -mstack-alignment=16 -Qunused-arguments -Werror=implicit-function-declaration -Werror=missing-prototypes -Werror=return-type -I/usr/include/SDL2 -D_REENTRANT   -MMD -MF tools/betterfuzzer.d -MT tools/betterfuzzer.o -c -o tools/betterfuzzer.o tools/betterfuzzer.c --warn-implicit-function-declaration -Wno-error=implicit-function-declaration -Wno-error=int-conversion



# gcc -I. -I./ -D_ISOC11_SOURCE -D_FILE_OFFSET_BITS=64 -DPIC -DZLIB_CONST    -fomit-frame-pointer -fPIC    -pthread  -I/usr/include/libdrm       -I/usr/include/libdrm    -g -Wdeclaration-after-statement -Wall -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -Wmissing-prototypes -Wstrict-prototypes -Wempty-body -Wno-parentheses -Wno-switch -Wno-format-zero-length -Wno-pointer-sign -Wno-unused-const-variable -Wno-bool-operation -Wno-char-subscripts -O3 -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -Werror=format-security -Werror=implicit-function-declaration -Werror=missing-prototypes -Werror=return-type -Werror=vla -Wformat -fdiagnostics-color=auto -Wno-maybe-uninitialized -I/usr/include/SDL2 -D_REENTRANT   -MMD -MF tools/target_betterfuzzer.d -MT tools/target_betterfuzzer.o -c -o tools/target_betterfuzzer.o tools/target_betterfuzzer.c --warn-implicit-function-declaration -Wno-error=implicit-function-declaration




# clang -Llibavcodec -Llibavdevice -Llibavfilter -Llibavformat -Llibavutil -Llibpostproc -Llibswscale -Llibswresample -fsanitize=address,undefined,fuzzer -fprofile-instr-generate -fcoverage-mapping  -Wl,--as-needed -Wl,-z,noexecstack -Wl,-rpath-link=:libpostproc:libswresample:libswscale:libavfilter:libavdevice:libavformat:libavcodec:libavutil -Qunused-arguments -fsanitize=address,undefined,fuzzer-no-link  -o tools/betterfuzzer tools/betterfuzzer.o libavdevice/libavdevice.a libavfilter/libavfilter.a libavformat/libavformat.a libavcodec/libavcodec.a libswresample/libswresample.a libswscale/libswscale.a libavutil/libavutil.a  -lavdevice -lavfilter -lavformat -lavcodec -lswresample -lswscale -lavutil  -lm -latomic -ldrm -lxcb -lxcb-shm -lxcb-shape -lxcb-xfixes -lasound -lSDL2 -lsndio -lXv -lX11 -lXext -pthread -lm -latomic -lva -lm -latomic -lbz2 -lz -pthread -lm -latomic -llzma -lz -lva -lm -latomic -lm -latomic -lva-drm -lva -lva-x11 -lva -lvdpau -lX11 -lm -ldrm -lva -latomic -pthread -lX11

clang -Llibavcodec -Llibavdevice -Llibavfilter -Llibavformat -Llibavutil -Llibpostproc -Llibswscale -Llibswresample -fsanitize=address,undefined,fuzzer  -Wl,--as-needed -Wl,-z,noexecstack -Wl,-rpath-link=:libpostproc:libswresample:libswscale:libavfilter:libavdevice:libavformat:libavcodec:libavutil -Qunused-arguments -fsanitize=address,undefined,fuzzer-no-link  -o tools/betterfuzzer tools/betterfuzzer.o libavdevice/libavdevice.a libavfilter/libavfilter.a libavformat/libavformat.a libavcodec/libavcodec.a libswresample/libswresample.a libswscale/libswscale.a libavutil/libavutil.a  -lavdevice -lavfilter -lavformat -lavcodec -lswresample -lswscale -lavutil  -lm -latomic -ldrm -lxcb -lxcb-shm -lxcb-shape -lxcb-xfixes -lasound -lSDL2 -lsndio -lXv -lX11 -lXext -pthread -lm -latomic -lva -lm -latomic -lbz2 -lz -pthread -lm -latomic -llzma -lz -lva -lm -latomic -lm -latomic -lva-drm -lva -lva-x11 -lva -lvdpau -lX11 -lm -ldrm -lva -latomic -pthread -lX11

cp tools/betterfuzzer testing/

./testing/betterfuzzer ./testing/ourthing.txt

