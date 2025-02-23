#!/bin/sh
# FLAGS="-fsanitize=address,undefined -fsanitize-coverage=trace-pc-guard,trace-cmp -g -fprofile-instr-generate -fcoverage-mapping" CC="clang $FLAGS" CXX="clang++ $FLAGS" LD="$CC $FLAGS" ./configure  --disable-x86asm --toolchain=clang-asan

FLAGS="-fsanitize=address,undefined -fsanitize-coverage=trace-pc-guard,trace-cmp -g" CC="clang $FLAGS" CXX="clang++ $FLAGS" LD="$CC $FLAGS" ./configure  --disable-x86asm --toolchain=clang-asan

make clean && make -j$(nproc) # Build


# profile-instr-generate
# clang-asan
# -fprofile-instr-generate -fcoverage-mapping

# clang -fsanitize=address,undefined,fuzzer -fsanitize-coverage=trace-pc-guard,trace-cmp tools/target_graph_fuzzer.c -o target_graph_fuzzer -I.   -DFFMPEG_CODEC=AV_CODEC_ID_MPEG1VIDEO -DFUZZ_FFMPEG_VIDEO   -Llibavcodec -Llibavdevice -Llibavfilter -Llibavformat -Llibavutil -Llibpostproc -Llibswscale -Llibswresample -Wl,--as-needed -Wl,-z,noexecstack -Wl,--warn-common -Wl,-rpath-link=:libpostproc:libswresample:libswscale:libavfilter:libavdevice:libavformat:libavcodec:libavutil -lavdevice -lavfilter -lavformat -lavcodec -lswresample -lswscale -lavutil -ldl -lxcb -lxcb-shm -lxcb -lxcb-xfixes  -lxcb -lxcb-shape -lxcb -lX11 -lasound -lm -lbz2 -lz -pthread

