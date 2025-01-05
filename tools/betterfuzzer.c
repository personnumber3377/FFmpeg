

#include <unistd.h>

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libavutil/channel_layout.h"
#include "libavutil/mem.h"
#include "libavutil/opt.h"
#include <stdio.h>
#include <stdint.h>


// This here is unused because reasons..

volatile static uint8_t STATIC_MP3_INPUT[] = { 0x00 };

// Here is the video which only has one frame (see oldfiles.txt in the root for the old files stuff)

volatile static uint8_t STATIC_FLV_INPUT[] = { 0x46, 0x4c, 0x56, 0x1, 0x5, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x0, 0x12, 0x0, 0x1, 0x74, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0xa, 0x6f, 0x6e, 0x4d, 0x65, 0x74, 0x61, 0x44, 0x61, 0x74, 0x61, 0x8, 0x0, 0x0, 0x0, 0x10, 0x0, 0x8, 0x64, 0x75, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x0, 0x3f, 0xac, 0xac, 0x8, 0x31, 0x26, 0xe9, 0x79, 0x0, 0x5, 0x77, 0x69, 0x64, 0x74, 0x68, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x68, 0x65, 0x69, 0x67, 0x68, 0x74, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd, 0x76, 0x69, 0x64, 0x65, 0x6f, 0x64, 0x61, 0x74, 0x61, 0x72, 0x61, 0x74, 0x65, 0x0, 0x40, 0x68, 0x6a, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0x66, 0x72, 0x61, 0x6d, 0x65, 0x72, 0x61, 0x74, 0x65, 0x0, 0x40, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x76, 0x69, 0x64, 0x65, 0x6f, 0x63, 0x6f, 0x64, 0x65, 0x63, 0x69, 0x64, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd, 0x61, 0x75, 0x64, 0x69, 0x6f, 0x64, 0x61, 0x74, 0x61, 0x72, 0x61, 0x74, 0x65, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x61, 0x75, 0x64, 0x69, 0x6f, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x61, 0x74, 0x65, 0x0, 0x40, 0xe7, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x61, 0x75, 0x64, 0x69, 0x6f, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x73, 0x69, 0x7a, 0x65, 0x0, 0x40, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x73, 0x74, 0x65, 0x72, 0x65, 0x6f, 0x1, 0x1, 0x0, 0xc, 0x61, 0x75, 0x64, 0x69, 0x6f, 0x63, 0x6f, 0x64, 0x65, 0x63, 0x69, 0x64, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xb, 0x6d, 0x61, 0x6a, 0x6f, 0x72, 0x5f, 0x62, 0x72, 0x61, 0x6e, 0x64, 0x2, 0x0, 0x4, 0x69, 0x73, 0x6f, 0x6d, 0x0, 0xd, 0x6d, 0x69, 0x6e, 0x6f, 0x72, 0x5f, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x2, 0x0, 0x3, 0x35, 0x31, 0x32, 0x0, 0x11, 0x63, 0x6f, 0x6d, 0x70, 0x61, 0x74, 0x69, 0x62, 0x6c, 0x65, 0x5f, 0x62, 0x72, 0x61, 0x6e, 0x64, 0x73, 0x2, 0x0, 0x10, 0x69, 0x73, 0x6f, 0x6d, 0x69, 0x73, 0x6f, 0x32, 0x61, 0x76, 0x63, 0x31, 0x6d, 0x70, 0x34, 0x31, 0x0, 0x7, 0x65, 0x6e, 0x63, 0x6f, 0x64, 0x65, 0x72, 0x2, 0x0, 0xd, 0x4c, 0x61, 0x76, 0x66, 0x36, 0x30, 0x2e, 0x31, 0x36, 0x2e, 0x31, 0x30, 0x30, 0x0, 0x8, 0x66, 0x69, 0x6c, 0x65, 0x73, 0x69, 0x7a, 0x65, 0x0, 0x40, 0x93, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x1, 0x7f, 0x8, 0x0, 0x1, 0x81, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xff, 0xfb, 0x94, 0x64, 0x0, 0xf, 0xf0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0xd, 0x20, 0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0xa4, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x34, 0x80, 0x0, 0x0, 0x4, 0x4c, 0x41, 0x4d, 0x45, 0x33, 0x2e, 0x31, 0x30, 0x30, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4c, 0x41, 0x4d, 0x45, 0x33, 0x2e, 0x31, 0x30, 0x30, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x0, 0x0, 0x1, 0x8c, 0x9, 0x0, 0x0, 0xf, 0x0, 0x0, 0x17, 0x0, 0x0, 0x0, 0x0, 0x12, 0x0, 0x0, 0x84, 0x0, 0x1, 0x1, 0x11, 0x26, 0x20, 0x20, 0x20, 0x21, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x1a, 0x8, 0x0, 0x1, 0x81, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xff, 0xfb, 0x94, 0x64, 0x51, 0x8f, 0xf0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0xd, 0x20, 0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0xa4, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x34, 0x80, 0x0, 0x0, 0x4, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x0, 0x0, 0x1, 0x8c };


// This here is basically the buffer which we want to fuzz with this program.

// static const char *filter_descr = "aresample=8000,aformat=sample_fmts=s16:channel_layouts=mono";

// asegment=timestamps="60|150"

// static const char *filter_descr = "aresample=8000,ebur128=audio=1:meter=18,aformat=sample_fmts=s16:channel_layouts=mono";

char* fuzzbuf[300]; // Our fuzzer thing...


// static const char *player       = "ffplay -f s16le -ar 8000 -ac 1 -"; // Not needed...

static AVFormatContext *fmt_ctx;
static AVCodecContext *dec_ctx;
AVFilterContext *buffersink_ctx;
AVFilterContext *buffersrc_ctx;
AVFilterGraph *filter_graph;
static int audio_stream_index = -1;


#include <string.h>

int read_buffer(void *opaque, uint8_t *buf, int buf_size);
int read_buffer_video(void *opaque, uint8_t *buf, int buf_size);

void try_fuzz_audio(void);

unsigned int data_pointer = 0; // Where we are in the input data

FILE *fp_open;
FILE *fp_open_video;


int read_buffer(void *opaque, uint8_t *buf, int buf_size){
    if (!feof(fp_open)) {
        int true_size=fread(buf,1,buf_size,fp_open);
        return true_size;
    } else {
        return AVERROR_EOF; // return -1; // We actually need to return AVERROR_EOF instead of -1 here I think
    }
}


int read_buffer_video(void *opaque, uint8_t *buf, int buf_size){
    if (!feof(fp_open_video)) {
        int true_size=fread(buf,1,buf_size,fp_open_video);
        return true_size;
    } else {
        return AVERROR_EOF; // return -1; // We actually need to return AVERROR_EOF instead of -1 here I think
    }
}

#include <stdio.h>


unsigned char* inbuffer=NULL;
AVIOContext *avio_in=NULL;

static int open_input_file()
{
    data_pointer = 0; // Set  to zero before starting to read...
    const AVCodec *dec;
    int ret = 0;
    fp_open = fmemopen(STATIC_MP3_INPUT, sizeof(STATIC_MP3_INPUT), "r"); // fopen("small.mp3", "rb");
    if (fp_open == NULL) {
        return 1;
    }
    inbuffer = (unsigned char*)av_malloc(sizeof(STATIC_MP3_INPUT));
    avio_in =avio_alloc_context(inbuffer, sizeof(STATIC_MP3_INPUT),0,NULL,read_buffer,NULL,NULL);  
    if(avio_in==NULL){
        goto end;
    }
    fmt_ctx->pb=avio_in;
    fmt_ctx->flags=AVFMT_FLAG_CUSTOM_IO;
    if ((ret = avformat_open_input(&fmt_ctx, "small.mp3", NULL, NULL)) < 0) { // was originally:   if ((ret = avformat_open_input(&fmt_ctx, filename, NULL, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot open input file\n");
        goto end;
    }

    if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        goto end;
    }

    /* select the audio stream */
    ret = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, &dec, 0);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot find an audio stream in the input file\n");
        goto end;
    }
    audio_stream_index = ret;

    /* create decoding context */
    dec_ctx = avcodec_alloc_context3(dec);
    if (!dec_ctx)
        goto end;
        //return AVERROR(ENOMEM);
    avcodec_parameters_to_context(dec_ctx, fmt_ctx->streams[audio_stream_index]->codecpar);

    /* init the audio decoder */
    if ((ret = avcodec_open2(dec_ctx, dec, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot open audio decoder\n");
        goto end;
    }

end:
    return ret;
}

static int init_filters(const char *filters_descr)
{
    char args[512];
    int ret = 0;
    const AVFilter *abuffersrc  = avfilter_get_by_name("abuffer");
    const AVFilter *abuffersink = avfilter_get_by_name("abuffersink");
    AVFilterInOut *outputs = avfilter_inout_alloc();
    AVFilterInOut *inputs  = avfilter_inout_alloc();
    static const int out_sample_rate = 8000;
    const AVFilterLink *outlink;
    AVRational time_base = fmt_ctx->streams[audio_stream_index]->time_base;

    filter_graph = avfilter_graph_alloc();
    if (!outputs || !inputs || !filter_graph) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    /* buffer audio source: the decoded frames from the decoder will be inserted here. */
    if (dec_ctx->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC)
        av_channel_layout_default(&dec_ctx->ch_layout, dec_ctx->ch_layout.nb_channels);
    ret = snprintf(args, sizeof(args),
            "time_base=%d/%d:sample_rate=%d:sample_fmt=%s:channel_layout=",
             time_base.num, time_base.den, dec_ctx->sample_rate,
             av_get_sample_fmt_name(dec_ctx->sample_fmt));
    av_channel_layout_describe(&dec_ctx->ch_layout, args + ret, sizeof(args) - ret);
    ret = avfilter_graph_create_filter(&buffersrc_ctx, abuffersrc, "in",
                                       args, NULL, filter_graph);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot create audio buffer source\n");
        goto end;
    }

    /* buffer audio sink: to terminate the filter chain. */
    buffersink_ctx = avfilter_graph_alloc_filter(filter_graph, abuffersink, "out");
    if (!buffersink_ctx) {
        av_log(NULL, AV_LOG_ERROR, "Cannot create audio buffer sink\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }

    ret = av_opt_set(buffersink_ctx, "sample_formats", "s16",
                     AV_OPT_SEARCH_CHILDREN);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot set output sample format\n");
        goto end;
    }

    ret = av_opt_set(buffersink_ctx, "channel_layouts", "mono",
                     AV_OPT_SEARCH_CHILDREN);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot set output channel layout\n");
        goto end;
    }

    ret = av_opt_set_array(buffersink_ctx, "samplerates", AV_OPT_SEARCH_CHILDREN,
                           0, 1, AV_OPT_TYPE_INT, &out_sample_rate);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot set output sample rate\n");
        goto end;
    }

    ret = avfilter_init_dict(buffersink_ctx, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot initialize audio buffer sink\n");
        goto end;
    }

    /*
     * Set the endpoints for the filter graph. The filter_graph will
     * be linked to the graph described by filters_descr.
     */

    /*
     * The buffer source output must be connected to the input pad of
     * the first filter described by filters_descr; since the first
     * filter input label is not specified, it is set to "in" by
     * default.
     */
    outputs->name       = av_strdup("in");
    outputs->filter_ctx = buffersrc_ctx;
    outputs->pad_idx    = 0;
    outputs->next       = NULL;

    /*
     * The buffer sink input must be connected to the output pad of
     * the last filter described by filters_descr; since the last
     * filter output label is not specified, it is set to "out" by
     * default.
     */
    inputs->name       = av_strdup("out");
    inputs->filter_ctx = buffersink_ctx;
    inputs->pad_idx    = 0;
    inputs->next       = NULL;

    if ((ret = avfilter_graph_parse_ptr(filter_graph, filters_descr,
                                        &inputs, &outputs, NULL)) < 0)
        goto end;

    if ((ret = avfilter_graph_config(filter_graph, NULL)) < 0)
        goto end;

    /* Print summary of the sink buffer
     * Note: args buffer is reused to store channel layout string */
    outlink = buffersink_ctx->inputs[0];
    av_channel_layout_describe(&outlink->ch_layout, args, sizeof(args));
    av_log(NULL, AV_LOG_INFO, "Output: srate:%dHz fmt:%s chlayout:%s\n",
           (int)outlink->sample_rate,
           (char *)av_x_if_null(av_get_sample_fmt_name(outlink->format), "?"),
           args);

end:
    avfilter_inout_free(&inputs);
    avfilter_inout_free(&outputs);

    return ret;
}

static void print_frame(const AVFrame *frame)
{
    const int n = frame->nb_samples * frame->ch_layout.nb_channels;
    const uint16_t *p     = (uint16_t*)frame->data[0];
    const uint16_t *p_end = p + n;

    while (p < p_end) {
        fputc(*p    & 0xff, stdout);
        fputc(*p>>8 & 0xff, stdout);
        p++;
    }
    fflush(stdout);
}



void try_fuzz_audio() {
    int ret;
    AVPacket *packet = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
    AVFrame *filt_frame = av_frame_alloc();

    if (!packet || !frame || !filt_frame) {
        //fprintf(stderr, "Could not allocate frame or packet\n");
        //exit(1);
        return;
        //return 1;
    }

    fmt_ctx = avformat_alloc_context();
    if ((ret = open_input_file()) < 0)
       goto end;


    if ((ret = init_filters(fuzzbuf)) < 0)
        goto end;

    /* read all packets */
    while (1) {
        if ((ret = av_read_frame(fmt_ctx, packet)) < 0)
            break;

        if (packet->stream_index == audio_stream_index) {
            ret = avcodec_send_packet(dec_ctx, packet);
            if (ret < 0) {
                //fprintf(stderr, "Ok, so we afefefeffefefefefew going to the thing...\n");
                av_log(NULL, AV_LOG_ERROR, "Error while sending a packet to the decoder\n");
                break;
            }

            while (ret >= 0) {
                ret = avcodec_receive_frame(dec_ctx, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    break;
                } else if (ret < 0) {
                    av_log(NULL, AV_LOG_ERROR, "Error while receiving a frame from the decoder\n");
                    goto end;
                }

                if (ret >= 0) {
                    /* push the audio data from decoded frame into the filtergraph */
                    if (av_buffersrc_add_frame_flags(buffersrc_ctx, frame, AV_BUFFERSRC_FLAG_KEEP_REF) < 0) {
                        av_log(NULL, AV_LOG_ERROR, "Error while feeding the audio filtergraph\n");
                        break;
                    }

                    /* pull filtered audio from the filtergraph */
                    while (1) {
                        ret = av_buffersink_get_frame(buffersink_ctx, filt_frame);
                        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                            break;
                        }
                        if (ret < 0) {
                            goto end;
                        }
                        // print_frame(filt_frame);
                        av_frame_unref(filt_frame);
                    }
                    av_frame_unref(frame);
                }
            }
        }
        av_packet_unref(packet);
    }

    if (ret == AVERROR_EOF) {
        /* signal EOF to the filtergraph */
        if (av_buffersrc_add_frame_flags(buffersrc_ctx, NULL, 0) < 0) {
            av_log(NULL, AV_LOG_ERROR, "Error while closing the filtergraph\n");
            goto end;
        }
        //printf("Pulling the rest of the bullshit here...\n");
        /* pull remaining frames from the filtergraph */
        while (1) {
            ret = av_buffersink_get_frame(buffersink_ctx, filt_frame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                break;
            }
            if (ret < 0) {
                goto end;
            }
            // print_frame(filt_frame);
            av_frame_unref(filt_frame);
        }
    }

end:
    avfilter_graph_free(&filter_graph);
    avcodec_free_context(&dec_ctx);
    //avformat_close_input(&fmt_ctx);
    // avformat_free_context(fmt_ctx);
    // avformat_close_input

    av_packet_free(&packet);
    av_frame_free(&frame);
    av_frame_free(&filt_frame);

    if (fp_open) {
        //printf("Closing file...\n");
        fclose(fp_open);
    }
    // Freeing the bullshit:::

    //fprintf(stderr, "Freeing the bullshit...\n");
    //av_free(avio_in);
    //av_free(inbuffer);

    if (ret < 0 && ret != AVERROR_EOF) {
        return;
    }
    return;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	int ret;
	// Main fuzzing entrypoint.
	// Just copy the entire thing.
	if (size >= sizeof(fuzzbuf)-1) {
		return 0; // Return early on inputs too big.
	}
	// memcpy that thing into the fuzz buffer.
	// void *memcpy(void dest[restrict .n], const void src[restrict .n],
    //                size_t n);
	memset(fuzzbuf, 0x00, sizeof(fuzzbuf));
	memcpy(fuzzbuf, data, size);




    if (strstr(fuzzbuf, "abuffersink")) { // This is to avoid the crash in the thing
        // free(buf);
        return 0;
    }

    if (strstr(fuzzbuf, "mix=")) { // This is to avoid the timeout
        // free(buf);
        return 0;
    }
    // xbr=

    if (strstr(fuzzbuf, "xbr=")) { // This is to avoid the timeout
        // free(buf);
        return 0;
    }

    if (strstr(fuzzbuf, "scale=")) { // This is to avoid the timeout
        // free(buf);
        return 0;
    }

    if (strstr(fuzzbuf, "select=")) { // This is to avoid the timeout
        // free(buf);
        return 0;
    }



	/*

	AVFilterGraph *in_graph = NULL;
    if (!(in_graph = avfilter_graph_alloc())) { // If allocation fails, just bail out here early.
        // free(buf);
        return 0;
    }
    ret = avfilter_graph_parse_ptr(in_graph, buf, NULL, NULL, NULL);
    // Now free the graph object to avoid memory leaks...
    avfilter_graph_free(&in_graph); // This is a bit weird that this expects a pointer but idk....
	
	*/
	// Now call the function
	// try_fuzz_audio();
	//fprintf(stderr, "Now trying to fuzz the video processing part...\n");

	// First verify the syntax of the thing...

	AVFilterGraph *in_graph = NULL;
    if (!(in_graph = avfilter_graph_alloc())) { // If allocation fails, just bail out here early.
        // free(buf);
        return 0;
    }
    ret = avfilter_graph_parse_ptr(in_graph, fuzzbuf, NULL, NULL, NULL);



    //    if ((ret = avfilter_graph_parse_ptr(filter_graph, filters_descr,
    //                                    &inputs, &outputs, NULL)) < 0)



    // Now free the graph object to avoid memory leaks...
    avfilter_graph_free(&in_graph); // This is a bit weird that this expects a pointer but idk....
    if (ret < 0) { // Invalid syntax of the graph, therefore just return here.
    	//fprintf(stderr, "The graph was NOT valid!");
    	return 0;
    }

    //fprintf(stderr, "The graph seems to be valid...\n");

	try_fuzz_video(); // Call the video decoder thing...
	//fprintf(stderr, "Returned from the bullshit fuck.....\n");
	return 0; // Now just exit...
}

/*

int main(int argc, char **argv)
{
    memset(fuzzbuf, 0x00, sizeof(fuzzbuf)); // Zero out the buffer.
    // Now read from stdin into that buffer
    read(0, fuzzbuf, sizeof(fuzzbuf));
    try_fuzz_audio(); // First try with the audio
    printf("Reached the end...\n");
    return 0;
}

*/


























// Here is the source code of the video thing:

/*
 * Copyright (c) 2010 Nicolas George
 * Copyright (c) 2011 Stefano Sabatini
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * @file
 * API example for decoding and filtering
 * @example decode_filter_video.c
 */

//#define _XOPEN_SOURCE 600 /* for usleep */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


//const char *filter_descr = "scale=78:24,transpose=cclock";
/* other way:
   scale=78:24 [scl]; [scl] transpose=cclock // assumes "[in]" and "[out]" to be input output pads respectively
 */

static AVFormatContext *fmt_ctx;
static AVCodecContext *dec_ctx;
AVFilterContext *buffersink_ctx;
AVFilterContext *buffersrc_ctx;
AVFilterGraph *filter_graph;
static int video_stream_index = -1;
static int64_t last_pts = AV_NOPTS_VALUE;

static int open_input_file_video(void); // Here just declare the thing...

static int open_input_file_video()
{
    const AVCodec *dec;
    int ret;

    //fprintf(stderr, "Called open_input_file_video\n");

    data_pointer = 0; // Set  to zero before starting to read...
    //const AVCodec *dec;
    //int ret = 0;
    fp_open_video = fmemopen(STATIC_FLV_INPUT, sizeof(STATIC_FLV_INPUT), "r"); // fopen("small.mp3", "rb");
    if (fp_open_video == NULL) {
        //return 1;
    }
    inbuffer = (unsigned char*)av_malloc(sizeof(STATIC_FLV_INPUT));
    avio_in =avio_alloc_context(inbuffer, sizeof(STATIC_FLV_INPUT),0,NULL,read_buffer_video,NULL,NULL);  
    if(avio_in==NULL){
    	return 0;
        //goto end;
    }
    fmt_ctx->pb=avio_in;
    fmt_ctx->flags=AVFMT_FLAG_CUSTOM_IO;
    if ((ret = avformat_open_input(&fmt_ctx, "oofshit.mp4", NULL, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot open input file\n");
        return ret;
    }

    if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        return ret;
    }

    /* select the video stream */
    ret = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, &dec, 0);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot find a video stream in the input file\n");
        return ret;
    }
    video_stream_index = ret;

    /* create decoding context */
    dec_ctx = avcodec_alloc_context3(dec);
    if (!dec_ctx)
        return AVERROR(ENOMEM);
    avcodec_parameters_to_context(dec_ctx, fmt_ctx->streams[video_stream_index]->codecpar);

    /* init the video decoder */
    if ((ret = avcodec_open2(dec_ctx, dec, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot open video decoder\n");
        return ret;
    }

    return 0;
}

static int init_filters_video(const char *filters_descr)
{
    char args[512];
    int ret = 0;
    const AVFilter *buffersrc  = avfilter_get_by_name("buffer");
    const AVFilter *buffersink = avfilter_get_by_name("buffersink");
    AVFilterInOut *outputs = avfilter_inout_alloc();
    AVFilterInOut *inputs  = avfilter_inout_alloc();
    AVRational time_base = fmt_ctx->streams[video_stream_index]->time_base;

    //fprintf(stderr, "Called init_filters_video\n");

    filter_graph = avfilter_graph_alloc();
    //fprintf(stderr, "after avfilter_graph_alloc\n");
    if (!outputs || !inputs || !filter_graph) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    /* buffer video source: the decoded frames from the decoder will be inserted here. */
    snprintf(args, sizeof(args),
            "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
            dec_ctx->width, dec_ctx->height, dec_ctx->pix_fmt,
            time_base.num, time_base.den,
            dec_ctx->sample_aspect_ratio.num, dec_ctx->sample_aspect_ratio.den);

    ret = avfilter_graph_create_filter(&buffersrc_ctx, buffersrc, "in",
                                       args, NULL, filter_graph);
    //fprintf(stderr, "after avfilter_graph_create_filter\n");
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot create buffer source\n");
        goto end;
    }

    /* buffer video sink: to terminate the filter chain. */
    buffersink_ctx = avfilter_graph_alloc_filter(filter_graph, buffersink, "out");
    //fprintf(stderr, "after avfilter_graph_alloc_filter\n");
    if (!buffersink_ctx) {
        av_log(NULL, AV_LOG_ERROR, "Cannot create buffer sink\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }

    ret = av_opt_set(buffersink_ctx, "pixel_formats", "gray8",
                     AV_OPT_SEARCH_CHILDREN);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot set output pixel format\n");
        goto end;
    }

    ret = avfilter_init_dict(buffersink_ctx, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot initialize buffer sink\n");
        goto end;
    }

    /*
     * Set the endpoints for the filter graph. The filter_graph will
     * be linked to the graph described by filters_descr.
     */

    /*
     * The buffer source output must be connected to the input pad of
     * the first filter described by filters_descr; since the first
     * filter input label is not specified, it is set to "in" by
     * default.
     */
    outputs->name       = av_strdup("in");
    outputs->filter_ctx = buffersrc_ctx;
    outputs->pad_idx    = 0;
    outputs->next       = NULL;

    /*
     * The buffer sink input must be connected to the output pad of
     * the last filter described by filters_descr; since the last
     * filter output label is not specified, it is set to "out" by
     * default.
     */
    inputs->name       = av_strdup("out");
    inputs->filter_ctx = buffersink_ctx;
    inputs->pad_idx    = 0;
    inputs->next       = NULL;

    //fprintf(stderr, "before avfilter_graph_parse_ptr\n");

    if ((ret = avfilter_graph_parse_ptr(filter_graph, filters_descr,
                                    &inputs, &outputs, NULL)) < 0)
        goto end;

    //fprintf(stderr, "before avfilter_graph_config\n");
    if ((ret = avfilter_graph_config(filter_graph, NULL)) < 0)
        goto end;

    //fprintf(stderr, "after avfilter_graph_config\n");

end:
    avfilter_inout_free(&inputs);
    avfilter_inout_free(&outputs);

    return ret;
}



// Show function...


static void display_frame(const AVFrame *frame, AVRational time_base)
{
    int x, y;
    uint8_t *p0, *p;
    int64_t delay;

    if (frame->pts != AV_NOPTS_VALUE) {
        if (last_pts != AV_NOPTS_VALUE) {
            /* sleep roughly the right amount of time;
             * usleep is in microseconds, just like AV_TIME_BASE. */
            delay = av_rescale_q(frame->pts - last_pts,
                                 time_base, AV_TIME_BASE_Q);
            if (delay > 0 && delay < 1000000)
                usleep(delay);
        }
        last_pts = frame->pts;
    }

    /* Trivial ASCII grayscale display. */
    p0 = frame->data[0];
    puts("\033c");
    for (y = 0; y < frame->height; y++) {
        p = p0;
        for (x = 0; x < frame->width; x++)
            putchar(" .-+#"[*(p++) / 52]);
        putchar('\n');
        p0 += frame->linesize[0];
    }
    fflush(stdout);
}






int try_fuzz_video(void);


//int main(int argc, char **argv)
int try_fuzz_video() // This is based on the very original main function...
{
	//fprintf(stderr, "Now doing the bullshit fuck.....\n");
    int ret;
    AVPacket *packet;
    AVFrame *frame;
    AVFrame *filt_frame;
    /*
    if (argc != 2) {
        //fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }
    */
    if (fmt_ctx) {
    	// avformat_free_context(fmt_ctx);
    	avformat_free_context(fmt_ctx);
    }
    fmt_ctx = avformat_alloc_context();

    frame = av_frame_alloc();
    filt_frame = av_frame_alloc();
    packet = av_packet_alloc();
    if (!frame || !filt_frame || !packet) {
        //fprintf(stderr, "Could not allocate frame or packet\n");
        return 1;
        //exit(1);
    }

    if ((ret = open_input_file_video()) < 0)
        goto end;
    if ((ret = init_filters_video(fuzzbuf)) < 0)
        goto end;

    /* read all packets */
    while (1) {
        if ((ret = av_read_frame(fmt_ctx, packet)) < 0)
            break;

        if (packet->stream_index == video_stream_index) {
        	//fprintf(stderr, "Sending frame...\n");
            ret = avcodec_send_packet(dec_ctx, packet);
            if (ret < 0) {
                av_log(NULL, AV_LOG_ERROR, "Error while sending a packet to the decoder\n");
                break;
            }

            while (ret >= 0) {
            	//fprintf(stderr, "Receiving frame...\n");
                ret = avcodec_receive_frame(dec_ctx, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    break;
                } else if (ret < 0) {
                    av_log(NULL, AV_LOG_ERROR, "Error while receiving a frame from the decoder\n");
                    goto end;
                }

                frame->pts = frame->best_effort_timestamp;
                //fprintf(stderr, "Sending frame to filtergraph...\n");
                /* push the decoded frame into the filtergraph */
                if (av_buffersrc_add_frame_flags(buffersrc_ctx, frame, AV_BUFFERSRC_FLAG_KEEP_REF) < 0) {
                    av_log(NULL, AV_LOG_ERROR, "Error while feeding the filtergraph\n");
                    break;
                }

                /* pull filtered frames from the filtergraph */
                while (1) {
                    ret = av_buffersink_get_frame(buffersink_ctx, filt_frame);
                    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                        break;
                    if (ret < 0)
                        goto end;
                    // display_frame(filt_frame, buffersink_ctx->inputs[0]->time_base);
                    //fprintf(stderr, "Decoded frame...\n");
                    av_frame_unref(filt_frame);
                }
                av_frame_unref(frame);
            }
        }
        av_packet_unref(packet);
    }
    if (ret == AVERROR_EOF) {
        /* signal EOF to the filtergraph */
        if (av_buffersrc_add_frame_flags(buffersrc_ctx, NULL, 0) < 0) {
            av_log(NULL, AV_LOG_ERROR, "Error while closing the filtergraph\n");
            goto end;
        }

        /* pull remaining frames from the filtergraph */
        while (1) {
            ret = av_buffersink_get_frame(buffersink_ctx, filt_frame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                break;
            if (ret < 0)
                goto end;
            // display_frame(filt_frame, buffersink_ctx->inputs[0]->time_base);
            //fprintf(stderr, "Decoded frame end...\n");
            av_frame_unref(filt_frame);
        }
    }

end:
    avfilter_graph_free(&filter_graph);
    avcodec_free_context(&dec_ctx);
    avformat_close_input(&fmt_ctx);
    av_frame_free(&frame);
    av_frame_free(&filt_frame);
    av_packet_free(&packet);
    // We do not do this next part in the audio fuzzing, because we needed here in the video player.
    avformat_free_context(fmt_ctx);

    if (ret < 0 && ret != AVERROR_EOF) {
        //fprintf(stderr, "Error occurred: %s\n", av_err2str(ret));
        //exit(1);
        return 1;
    }

    return 0;

    // exit(0);
}












