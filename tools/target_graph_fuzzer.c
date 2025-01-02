/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/* Targeted fuzzer that targets the graphs.
  INSTRUCTIONS:

  * Get the very fresh clang, e.g. see http://libfuzzer.info#versions
  * Get and build libFuzzer:
     svn co http://llvm.org/svn/llvm-project/llvm/trunk/lib/Fuzzer
     ./Fuzzer/build.sh
  * build ffmpeg for fuzzing:
    FLAGS="-fsanitize=address -fsanitize-coverage=trace-pc-guard,trace-cmp -g" CC="clang $FLAGS" CXX="clang++ $FLAGS" ./configure  --disable-x86asm
    make clean && make -j
  * build the fuzz target.
    Choose the value of FFMPEG_CODEC (e.g. AV_CODEC_ID_DVD_SUBTITLE) and
    choose one of FUZZ_FFMPEG_VIDEO, FUZZ_FFMPEG_AUDIO, FUZZ_FFMPEG_SUBTITLE.
    clang -fsanitize=address -fsanitize-coverage=trace-pc-guard,trace-cmp tools/target_dec_fuzzer.c -o target_dec_fuzzer -I.   -DFFMPEG_CODEC=AV_CODEC_ID_MPEG1VIDEO -DFUZZ_FFMPEG_VIDEO ../../libfuzzer/libFuzzer.a   -Llibavcodec -Llibavdevice -Llibavfilter -Llibavformat -Llibavutil -Llibpostproc -Llibswscale -Llibswresample -Wl,--as-needed -Wl,-z,noexecstack -Wl,--warn-common -Wl,-rpath-link=:libpostproc:libswresample:libswscale:libavfilter:libavdevice:libavformat:libavcodec:libavutil -lavdevice -lavfilter -lavformat -lavcodec -lswresample -lswscale -lavutil -ldl -lxcb -lxcb-shm -lxcb -lxcb-xfixes  -lxcb -lxcb-shape -lxcb -lX11 -lasound -lm -lbz2 -lz -pthread
  * create a corpus directory and put some samples there (empty dir is ok too):
    mkdir CORPUS && cp some-files CORPUS

  * Run fuzzing:
    ./target_dec_fuzzer -max_len=100000 CORPUS

   More info:
   http://libfuzzer.info
   http://tutorial.libfuzzer.info
   https://github.com/google/oss-fuzz
   http://lcamtuf.coredump.cx/afl/
   https://security.googleblog.com/2016/08/guided-in-process-fuzzing-of-chrome.html
*/

// These next includes are taken from tools/uncoded_frame.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libavutil/avassert.h"
#include "libavutil/mem.h"
#include "libavdevice/avdevice.h"
#include "libavfilter/avfilter.h"
#include "libavfilter/buffersink.h"
#include "libavformat/avformat.h"
#include "libavcodec/codec_id.h"




// This loads all of the device shit:

int LLVMFuzzerInitialize(int *argc, char ***argv);

int LLVMFuzzerInitialize(int *argc, char ***argv) {
    avdevice_register_all(); // Register the device bullshit here...
    return 0;
}



int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // This fuzzer is based on the source found in tools/uncoded_frame.c
    int ret;
    // void *memset(void s[.n], int c, size_t n);
    uint8_t buf[10000];
    if (size < 3 || size > (sizeof(buf)-1)) { // Skip empty or nonsensical short inputs.
        return 0;
    }

    memset(buf, 0x00, 10000);

    // Now check for newline and space which are banned characters.
    //  Based on https://stackoverflow.com/a/9188556  thanks to stackoverflow user https://stackoverflow.com/users/65863/remy-lebeau

    //unsigned char buffer[1500];
    //bool allZeros = true;
    for (int i = 0; i < size; ++i)
    {
        if (data[i] == 0x0a || data[i] == 0x20) // For newline or space character
        {
            //allZeros = false;
            //break;
            return 0;
        }
    }
    // Now add a null byte at the end.
    // We can not do this because we get an error saying that the constant input data was changed: SUMMARY: libFuzzer: overwrites-const-input
    //data[size-1] = 0x00; // Add null byte at the end.
    // So we memcpy the data to a mutable buffer and add the thing.

    //        void *memcpy(void dest[restrict .n], const void src[restrict .n],
    //                size_t n);

    // buf
    // Check for abuffersink

    memcpy(buf, data, size);
    buf[size] = 0x00; // Add the null terminator

    // Check for "abuffersink"
    if (strstr(buf, "abuffersink")) { // This is to avoid the crash in the thing
        return 0;
    }

    if (strstr(buf, "mix=")) { // This is to avoid the timeout
        return 0;
    }
    

    AVFilterGraph *in_graph = NULL;
    if (!(in_graph = avfilter_graph_alloc())) { // If allocation fails, just bail out here early.
        return 0;
    }
    ret = avfilter_graph_parse_ptr(in_graph, buf, NULL, NULL, NULL);
    // Now free the graph object to avoid memory leaks...
    avfilter_graph_free(&in_graph); // This is a bit weird that this expects a pointer but idk....
    return 0;
}
