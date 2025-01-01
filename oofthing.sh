#!/bin/sh


#  FLAGS="-fsanitize=address,undefined -fsanitize-coverage=trace-pc-guard,trace-cmp -g" CC="clang $FLAGS" CXX="clang++ $FLAGS" ./configure  --disable-x86asm

#  make clean && make -j$(nproc) # Build


#  clang -fsanitize=address,undefined,fuzzer -fsanitize-coverage=trace-pc-guard,trace-cmp tools/target_graph_fuzzer.c -o target_graph_fuzzer -I.   -DFFMPEG_CODEC=AV_CODEC_ID_MPEG1VIDEO -DFUZZ_FFMPEG_VIDEO   -Llibavcodec -Llibavdevice -Llibavfilter -Llibavformat -Llibavutil -Llibpostproc -Llibswscale -Llibswresample -Wl,--as-needed -Wl,-z,noexecstack -Wl,--warn-common -Wl,-rpath-link=:libpostproc:libswresample:libswscale:libavfilter:libavdevice:libavformat:libavcodec:libavutil -lavdevice -lavfilter -lavformat -lavcodec -lswresample -lswscale -lavutil -ldl -lxcb -lxcb-shm -lxcb -lxcb-xfixes  -lxcb -lxcb-shape -lxcb -lX11 -lasound -lm -lbz2 -lz -pthread


FLAGS="-fsanitize=address,undefined -fsanitize-coverage=trace-pc-guard,trace-cmp -g" CC="clang $FLAGS" CXX="clang++ $FLAGS" ./configure \
        --ld="clang++  -fsanitize=address,undefined -fsanitize-coverage=trace-pc,trace-cmp -g -std=c++11" \
        --pkg-config-flags="--static" \
        --enable-ossfuzz \
        --optflags=-O3 \
        --enable-gpl \
        --enable-nonfree \
        --enable-libass \
        --enable-libfdk-aac \
        --enable-libfreetype \
        --enable-libopus \
        --enable-libtheora \
        --enable-libvorbis \
        --enable-libvpx \
        --enable-libxml2 \
        --enable-nonfree \
        --disable-libdrm \
        --disable-muxers \
        --disable-protocols \
        --disable-demuxer=rtp,rtsp,sdp \
        --disable-devices \
        --disable-shared \
        --disable-doc \
        --disable-programs

make tools/target_graph_fuzzer # Build the fuzzer

