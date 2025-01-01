#!/bin/sh
# FLAGS="-fsanitize=address,undefined,fuzzer -fsanitize-coverage=trace-pc,trace-cmp -g" CC="clang $FLAGS -fno-omit-frame-pointer" CXX="clang++ $FLAGS -fno-omit-frame-pointer" LD="clang -fsanitize=address,undefined,fuzzer -fsanitize-coverage=trace-pc,trace-cmp" ./configure  --disable-x86asm --pkg-config-flags="--static" --toolchain=clang-asan --enable-ossfuzz --optflags=-O3 --enable-gpl --enable-nonfree --enable-libass --enable-libfdk-aac --enable-libfreetype --enable-libopus --enable-libtheora --enable-libvorbis --enable-libvpx --enable-libxml2 --enable-nonfree --disable-libdrm --disable-muxers --disable-protocols --disable-demuxer=rtp,rtsp,sdp --disable-devices --disable-shared --disable-doc --disable-programs

FLAGS="-fsanitize=address,undefined,fuzzer -g" CC="clang $FLAGS -fno-omit-frame-pointer" CXX="clang++ $FLAGS -fno-omit-frame-pointer" LD="clang -fsanitize=address,undefined,fuzzer" ./configure  --disable-x86asm --pkg-config-flags="--static" --toolchain=clang-asan --enable-ossfuzz --optflags=-O3 --enable-gpl --enable-nonfree --enable-libass --enable-libfdk-aac --enable-libfreetype --enable-libopus --enable-libtheora --enable-libvorbis --enable-libvpx --enable-libxml2 --enable-nonfree --disable-libdrm --disable-muxers --disable-protocols --disable-demuxer=rtp,rtsp,sdp --disable-devices --disable-shared --disable-doc --disable-programs


make clean && make -j$(nproc) # Build

FLAGS="-fsanitize=address,undefined,fuzzer -g" CC="clang $FLAGS -fno-omit-frame-pointer" CXX="clang++ $FLAGS -fno-omit-frame-pointer" LD="clang -fsanitize=address,undefined,fuzzer" make tools/target_graph_fuzzer



# clang -fsanitize=address,undefined,fuzzer -fsanitize-coverage=trace-pc-guard,trace-cmp tools/target_graph_fuzzer.c -o target_graph_fuzzer -I. -I libpostproc -I libswresample -I libswscale -I libavfilter -I libavdevice -I libavformat -I libavcodec -I libavutil   -DFFMPEG_CODEC=AV_CODEC_ID_MPEG1VIDEO -DFUZZ_FFMPEG_VIDEO   -Llibavcodec -Llibavdevice -Llibavfilter -Llibavformat -Llibavutil -Llibpostproc -Llibswscale -Llibswresample -Wl,--as-needed -Wl,-z,noexecstack -Wl,--warn-common -Wl,-rpath-link=:libpostproc:libswresample:libswscale:libavfilter:libavdevice:libavformat:libavcodec:libavutil -lavdevice -lavfilter -lavformat -lavcodec -lswresample -lswscale -lavutil -ldl -lxcb -lxcb-shm -lxcb -lxcb-xfixes  -lxcb -lxcb-shape -lxcb -lX11 -lasound -lm -lbz2 -lz -pthread
# ause --enable-libfdk_aac and --enable-nonfree are alread

# make tools/target_graph_fuzzer

